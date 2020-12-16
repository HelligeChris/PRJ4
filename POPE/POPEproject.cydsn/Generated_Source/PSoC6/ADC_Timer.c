/*******************************************************************************
* File Name: ADC_Timer.c
* Version 1.0
*
* Description:
*  This file provides the source code to the API for the ADC_Timer
*  component
*
********************************************************************************
* Copyright 2016-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "ADC_Timer.h"

/** Indicates whether or not the ADC_Timer has been initialized. 
*  The variable is initialized to 0 and set to 1 the first time 
*  ADC_Timer_Start() is called. This allows the Component to 
*  restart without reinitialization after the first call to 
*  the ADC_Timer_Start() routine.
*/
uint8_t ADC_Timer_initVar = 0U;

/** The instance-specific configuration structure. This should be used in the 
*  associated ADC_Timer_Init() function.
*/ 
cy_stc_tcpwm_counter_config_t const ADC_Timer_config =
{
        .period = 0UL,
        .clockPrescaler = 0UL,
        .runMode = 0UL,
        .countDirection = 0UL,
        .compareOrCapture = 2UL,
        .compare0 = 16384UL,
        .compare1 = 16384UL,
        .enableCompareSwap = false,
        .interruptSources = 1UL,
        .captureInputMode = 3UL,
        .captureInput = CY_TCPWM_INPUT_CREATOR,
        .reloadInputMode = 3UL,
        .reloadInput = CY_TCPWM_INPUT_CREATOR,
        .startInputMode = 3UL,
        .startInput = CY_TCPWM_INPUT_CREATOR,
        .stopInputMode = 3UL,
        .stopInput = CY_TCPWM_INPUT_CREATOR,
        .countInputMode = 3UL,
        .countInput = CY_TCPWM_INPUT_CREATOR,
};


/*******************************************************************************
* Function Name: ADC_Timer_Start
****************************************************************************//**
*
*  Calls the ADC_Timer_Init() when called the first time and enables 
*  the ADC_Timer. For subsequent calls the configuration is left 
*  unchanged and the component is just enabled.
*
* \globalvars
*  \ref ADC_Timer_initVar
*
*******************************************************************************/
void ADC_Timer_Start(void)
{
    if (0U == ADC_Timer_initVar)
    {
        (void)Cy_TCPWM_Counter_Init(ADC_Timer_HW, ADC_Timer_CNT_NUM, &ADC_Timer_config); 

        ADC_Timer_initVar = 1U;
    }

    Cy_TCPWM_Enable_Multiple(ADC_Timer_HW, ADC_Timer_CNT_MASK);
    
    #if (ADC_Timer_INPUT_DISABLED == 7UL)
        Cy_TCPWM_TriggerStart(ADC_Timer_HW, ADC_Timer_CNT_MASK);
    #endif /* (ADC_Timer_INPUT_DISABLED == 7UL) */    
}


/* [] END OF FILE */
