/***************************************************************************//**
* \file     Batteri_ADC.c
* \version  3.10
*
* \brief
* Provides the source code to the API for the Batteri_ADC Component.
*
********************************************************************************
* \copyright
* (c) 2017-2018, Cypress Semiconductor Corporation. All rights reserved.
* This software, including source code, documentation and related
* materials ("Software"), is owned by Cypress Semiconductor
* Corporation ("Cypress") and is protected by and subject to worldwide
* patent protection (United States and foreign), United States copyright
* laws and international treaty provisions. Therefore, you may use this
* Software only as provided in the license agreement accompanying the
* software package from which you obtained this Software ("EULA").
* If no EULA applies, Cypress hereby grants you a personal, nonexclusive,
* non-transferable license to copy, modify, and compile the
* Software source code solely for use in connection with Cypress's
* integrated circuit products. Any reproduction, modification, translation,
* compilation, or representation of this Software except as specified
* above is prohibited without the express written permission of Cypress.
* Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO
* WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING,
* BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
* PARTICULAR PURPOSE. Cypress reserves the right to make
* changes to the Software without notice. Cypress does not assume any
* liability arising out of the application or use of the Software or any
* product or circuit described in the Software. Cypress does not
* authorize its products for use in any products where a malfunction or
* failure of the Cypress product may reasonably be expected to result in
* significant property damage, injury or death ("High Risk Product"). By
* including Cypress's product in a High Risk Product, the manufacturer
* of such system or application assumes all risk of such use and in doing
* so agrees to indemnify Cypress against all liability.
*******************************************************************************/
#include "Batteri_ADC.h"
#include <sysint/cy_sysint.h>
#include <cyfitter_sysint_cfg.h>

uint8_t Batteri_ADC_initVar = 0u;
uint8_t Batteri_ADC_selected = 0u; /* 0 if no configuration selected. 1 otherwise. */
uint32_t Batteri_ADC_currentConfig = 0u; /* Currently active configuration */

/*******************************************************************************
* Function Name: Batteri_ADC_Start
****************************************************************************//**
*
* \brief Performs all required initialization for this component and enables the
*  power. The power will be set to the appropriate power based on the clock
*  frequency.
*
* \param None
*
* \return None
*
* \sideeffect None
*
* \globalvars
*  \ref Batteri_ADC_initVar (RW)
*
*******************************************************************************/
void Batteri_ADC_Start(void)
{
    if (Batteri_ADC_INIT_VAR_INIT_FLAG != (Batteri_ADC_INIT_VAR_INIT_FLAG & Batteri_ADC_initVar))
    {
        Batteri_ADC_Init();
        Batteri_ADC_initVar |= Batteri_ADC_INIT_VAR_INIT_FLAG;
    }

    Batteri_ADC_Enable();

    return;
}

/*******************************************************************************
* Function Name: Batteri_ADC_StartEx
****************************************************************************//**
*
* \brief This function starts the Batteri_ADC and sets the Interrupt
* Service Routine to the provided address using the
* Cy_SysInt_Init() function. Refer to the Interrupt component
* datasheet for more information on the Cy_SysInt_Init() function.
*
* \param address This is the address of a user defined function for the ISR.
*
* \return None
*
* \sideeffect None
*
*******************************************************************************/
void Batteri_ADC_StartEx(cy_israddress userIsr)
{
    Batteri_ADC_Start();

    /* Interrupt core assignment will be up to the user. Initialize and enable the interrupt*/
    #ifdef Batteri_ADC_IRQ__INTC_CORTEXM4_ASSIGNED
    #if (CY_CPU_CORTEX_M4)
        (void)Cy_SysInt_Init(&Batteri_ADC_IRQ_cfg, userIsr);
        NVIC_EnableIRQ(Batteri_ADC_IRQ_cfg.intrSrc);
    #endif
    #endif

    #ifdef Batteri_ADC_IRQ__INTC_CORTEXM0P_ASSIGNED
    #if (CY_CPU_CORTEX_M0P)
        (void)Cy_SysInt_Init(&Batteri_ADC_IRQ_cfg, userIsr);
        NVIC_EnableIRQ(Batteri_ADC_IRQ_cfg.intrSrc);
    #endif
    #endif

}

/* ****************************************************************************
* Function Name: Batteri_ADC_InitConfig
****************************************************************************//*
*
* \brief Configures all of the registers for a given configuration for scanning.
*
* \param scan Number of scan defined in the Batteri_ADC.
*
* \return None
*
* \sideeffect None
*
*******************************************************************************/
void Batteri_ADC_InitConfig(const Batteri_ADC_CONFIG_STRUCT *config)
{
    bool deInitRouting = false;

    /* If there is an internal SAR clock, set up its divider values. */
    #if (Batteri_ADC_CLOCK_INTERNAL)
        Batteri_ADC_intSarClock_Disable();
        Batteri_ADC_intSarClock_SetDivider(config->clkDivider);
        Batteri_ADC_intSarClock_Enable();
    #endif /* Batteri_ADC_CLOCK_INTERNAL */

    /* Init SAR and MUX registers */
    (void)Cy_SAR_DeInit(Batteri_ADC_SAR__HW, deInitRouting);
    (void)Cy_SAR_Init(Batteri_ADC_SAR__HW, config->hwConfigStc);

    /* Connect Vminus to VSSA when even one channel is single-ended or multiple channels configured */
    if(1uL == Batteri_ADC_MUX_SWITCH0_INIT)
    {
        Cy_SAR_SetVssaVminusSwitch(Batteri_ADC_SAR__HW, CY_SAR_SWITCH_CLOSE);

        /* Set MUX_HW_CTRL_VSSA in MUX_SWITCH_HW_CTRL when multiple channels enabled */
        if(1uL < config->numChannels)
        {
            Cy_SAR_SetVssaSarSeqCtrl(Batteri_ADC_SAR__HW, CY_SAR_SWITCH_SEQ_CTRL_ENABLE);
        }
    }

    return;
}

/* ****************************************************************************
* Function Name: Batteri_ADC_SelectConfig
****************************************************************************//*
*
* \brief Selects the predefined configuration for scanning.
*
* \param config Number of configuration in the Batteri_ADC.
*
* \param restart Set to 1u if the Batteri_ADC should be  restarted after
* selecting the configuration.
*
*******************************************************************************/
void Batteri_ADC_SelectConfig(uint32_t config, uint32_t restart)
{
    /* Check whether the configuration number is valid or not */
    if(Batteri_ADC_TOTAL_CONFIGS > config)
    {
        /* Stop the ADC before changing configurations */
        Batteri_ADC_Stop();
        Batteri_ADC_selected = 1u;

        if(0u == Batteri_ADC_initVar)
        {
            Batteri_ADC_Init();
            Batteri_ADC_initVar |= Batteri_ADC_INIT_VAR_INIT_FLAG;
        }
        #if (Batteri_ADC_VREF_ROUTED)
            Batteri_ADC_vrefAMux_DisconnectAll();
        #endif

        Batteri_ADC_InitConfig(&Batteri_ADC_allConfigs[config]);

        #if (Batteri_ADC_VREF_ROUTED)
            Batteri_ADC_vrefAMux_Select((uint8)config);
        #endif

        Batteri_ADC_currentConfig = config;

        if(1u == restart)
        {
            /* Restart the ADC */
            Batteri_ADC_Start();

            /* Restart the scan */
            Batteri_ADC_StartConvert();
        }
    }
    return;
}

/*******************************************************************************
* Function Name: Batteri_ADC_StartConvert
****************************************************************************//**
*
* \brief In continuous mode, this API starts the conversion process and it runs
* continuously.

* In Single Shot mode, the function triggers a single scan and
* every scan requires a call of this function. The mode is set with the
* Sample Mode parameter in the customizer. The customizer setting can be
* overridden at run time with the Batteri_ADC_SetConvertMode() function.
*
* \param None
*
* \return None
*
* \sideeffect None
*
*******************************************************************************/
void Batteri_ADC_StartConvert(void)
{
    if (SAR_SAMPLE_CTRL_DSI_TRIGGER_LEVEL_Msk == (Batteri_ADC_SAR__HW->SAMPLE_CTRL & SAR_SAMPLE_CTRL_DSI_TRIGGER_LEVEL_Msk))
    {
        Cy_SAR_StartConvert(Batteri_ADC_SAR__HW, CY_SAR_START_CONVERT_CONTINUOUS);
    }
    else
    {
        Cy_SAR_StartConvert(Batteri_ADC_SAR__HW, CY_SAR_START_CONVERT_SINGLE_SHOT);
    }
}

/*******************************************************************************
* Function Name: Batteri_ADC_SetConvertMode
****************************************************************************//**
*
* \brief Sets the conversion mode to either Single-Shot or continuous. This
* function overrides the settings applied in the customizer. Changing
* configurations will restore the values set in the customizer.
*
* \param mode Sets the conversion mode.
*
* \return None
*
* \sideeffect None
*
*******************************************************************************/
void Batteri_ADC_SetConvertMode(cy_en_sar_start_convert_sel_t mode)
{
    switch(mode)
    {
    case CY_SAR_START_CONVERT_CONTINUOUS:
        Batteri_ADC_SAR__HW->SAMPLE_CTRL |= SAR_SAMPLE_CTRL_DSI_TRIGGER_LEVEL_Msk;
        break;
    case CY_SAR_START_CONVERT_SINGLE_SHOT:
    default:
        Batteri_ADC_SAR__HW->SAMPLE_CTRL &= ~SAR_SAMPLE_CTRL_DSI_TRIGGER_LEVEL_Msk;
        break;
    }
}

/* ****************************************************************************
* Function Name: Batteri_ADC_IRQ_Enable
****************************************************************************//*
*
* \brief Enables interrupts to occur at the end of a conversion. Global
* interrupts must also be enabled for the Batteri_ADC interrupts to occur.
*
* \param None
*
* \return None
*
* \sideeffect None
*
*******************************************************************************/
void Batteri_ADC_IRQ_Enable(void){
    /* Interrupt core assignment will be up to the user. */
    #ifdef Batteri_ADC_IRQ__INTC_CORTEXM4_ASSIGNED
    #if (CY_CPU_CORTEX_M4)
        NVIC_EnableIRQ(Batteri_ADC_IRQ_cfg.intrSrc);
    #endif
    #endif

    #ifdef Batteri_ADC_IRQ__INTC_CORTEXM0P_ASSIGNED
    #if (CY_CPU_CORTEX_M0P)
        NVIC_EnableIRQ(Batteri_ADC_IRQ_cfg.intrSrc);
    #endif
    #endif
}

/* ****************************************************************************
* Function Name: Batteri_ADC_IRQ_Disable
****************************************************************************//*
*
* \brief Disables end of conversion interrupts.
*
* \param None
*
* \return None
*
* \sideeffect None
*
*******************************************************************************/
void Batteri_ADC_IRQ_Disable(void){
    /* Interrupt core assignment will be up to the user. */
    #ifdef Batteri_ADC_IRQ__INTC_CORTEXM4_ASSIGNED
    #if (CY_CPU_CORTEX_M4)
        NVIC_DisableIRQ(Batteri_ADC_IRQ_cfg.intrSrc);
    #endif
    #endif

    #ifdef Batteri_ADC_IRQ__INTC_CORTEXM0P_ASSIGNED
    #if (CY_CPU_CORTEX_M0P)
        NVIC_DisableIRQ(Batteri_ADC_IRQ_cfg.intrSrc);
    #endif
    #endif
}

/*******************************************************************************
* Function Name: Batteri_ADC_SetEosMask
****************************************************************************//**
*
* \brief Sets or clears the End of Scan (EOS) interrupt mask.
*
* \param mask 1 to set the mask, 0 to clear the mask.
*
* \return None
*
* \sideeffect All other bits in the INTR register are cleared by this function.
*
*******************************************************************************/
void Batteri_ADC_SetEosMask(uint32_t mask)
{
    uint32_t intrMaskReg;

    intrMaskReg = (0uL == mask) ? CY_SAR_DEINIT : SAR_INTR_MASK_EOS_MASK_Msk;

    Cy_SAR_SetInterruptMask(Batteri_ADC_SAR__HW, intrMaskReg);
}

/******************************************************************************
* Function Name: Batteri_ADC_SetChanMask
****************************************************************************//*
*
* \brief Sets enable/disable mask for all channels in current configuration.
*
*
* \param enableMask
*  Channel enable/disable mask.
*
* \sideeffect
*  None.
*
*******************************************************************************/
void Batteri_ADC_SetChanMask(uint32_t enableMask)
{
    uint32 chanCount = Batteri_ADC_allConfigs[Batteri_ADC_currentConfig].numChannels;
    enableMask &= (uint32)((uint32)(1ul << chanCount) - 1ul);

    Cy_SAR_SetChanMask(Batteri_ADC_SAR__HW, enableMask);
}

/*******************************************************************************
* Function Name: Batteri_ADC_IsEndConversion
****************************************************************************//**
*
* \brief Immediately returns the status of the conversion or does not return
* (blocking) until the conversion completes, depending on the retMode parameter.
* In blocking mode, there is a time out of about 10 seconds for a CPU speed of
* 100 Mhz.
*
* \param retMode Check conversion return mode.
*
* \return uint32_t: If a nonzero value is returned, the last conversion is complete.
* If the returned value is zero, the Batteri_ADC is still calculating the last result.
*
* \sideeffect This function reads the end of conversion status, and clears it afterward.
*
*******************************************************************************/
uint32_t Batteri_ADC_IsEndConversion(cy_en_sar_return_mode_t retMode)
{
    uint32 endOfConversion = 0u;
    cy_en_sar_status_t result;

    result = Cy_SAR_IsEndConversion(Batteri_ADC_SAR__HW, retMode);

    if (result == CY_SAR_SUCCESS)
    {
        endOfConversion = 1u;
    }

    return endOfConversion;
}

/* ****************************************************************************
* Function Name: Batteri_ADC_Init
****************************************************************************//*
*
* \brief Initialize the component according to parameters defined in the
* customizer.
*
* \param None
*
* \return None
*
* \sideeffect None
*
*******************************************************************************/
void Batteri_ADC_Init(void)
{
    uint32_t configNum = 0u;

    if(0u == Batteri_ADC_initVar)
    {
        /* Interrupt core assignment will be up to the user. Initialize but do not enable the interrupt*/
        #ifdef Batteri_ADC_IRQ__INTC_CORTEXM4_ASSIGNED
        #if (CY_CPU_CORTEX_M4)
            (void)Cy_SysInt_Init(&Batteri_ADC_IRQ_cfg, &Batteri_ADC_ISR);
        #endif
        #endif

        #ifdef Batteri_ADC_IRQ__INTC_CORTEXM0P_ASSIGNED
        #if (CY_CPU_CORTEX_M0P)
            (void)Cy_SysInt_Init(&Batteri_ADC_IRQ_cfg, &Batteri_ADC_ISR);
        #endif
        #endif

        /* Initialize configuration zero if SelectConfig has not been called */
        if(0u == Batteri_ADC_selected)
        {
            Batteri_ADC_selected = 1u;
            configNum = 0uL;

            /* Change Vref selection if is was routed by Creator. Break. */
            #if (Batteri_ADC_VREF_ROUTED)
                Batteri_ADC_vrefAMux_DisconnectAll();
            #endif

            Batteri_ADC_InitConfig(&Batteri_ADC_allConfigs[configNum]);

            /* Change Vref selection if is was routed by Creator. Make. */
            #if (Batteri_ADC_VREF_ROUTED)
                Batteri_ADC_vrefAMux_Select((uint8)configNum);
            #endif
        }
    }
}
/* [] END OF FILE */
