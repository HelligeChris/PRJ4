/*******************************************************************************
* File Name: SampleTimer.c
* Version 1.0
*
* Description:
*  This file provides the source code to the API for the SampleTimer
*  component
*
********************************************************************************
* Copyright 2016-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "SampleTimer.h"

/** Indicates whether or not the SampleTimer has been initialized. 
*  The variable is initialized to 0 and set to 1 the first time 
*  SampleTimer_Start() is called. This allows the Component to 
*  restart without reinitialization after the first call to 
*  the SampleTimer_Start() routine.
*/
uint8_t SampleTimer_initVar = 0U;

/** The instance-specific configuration structure. This should be used in the 
*  associated SampleTimer_Init() function.
*/ 
cy_stc_tcpwm_counter_config_t const SampleTimer_config =
{
        .period = 32768UL,
        .clockPrescaler = 0UL,
        .runMode = 0UL,
        .countDirection = 0UL,
        .compareOrCapture = 2UL,
        .compare0 = 16384UL,
        .compare1 = 16384UL,
        .enableCompareSwap = false,
        .interruptSources = 0UL,
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
* Function Name: SampleTimer_Start
****************************************************************************//**
*
*  Calls the SampleTimer_Init() when called the first time and enables 
*  the SampleTimer. For subsequent calls the configuration is left 
*  unchanged and the component is just enabled.
*
* \globalvars
*  \ref SampleTimer_initVar
*
*******************************************************************************/
void SampleTimer_Start(void)
{
    if (0U == SampleTimer_initVar)
    {
        (void)Cy_TCPWM_Counter_Init(SampleTimer_HW, SampleTimer_CNT_NUM, &SampleTimer_config); 

        SampleTimer_initVar = 1U;
    }

    Cy_TCPWM_Enable_Multiple(SampleTimer_HW, SampleTimer_CNT_MASK);
    
    #if (SampleTimer_INPUT_DISABLED == 7UL)
        Cy_TCPWM_TriggerStart(SampleTimer_HW, SampleTimer_CNT_MASK);
    #endif /* (SampleTimer_INPUT_DISABLED == 7UL) */    
}


/* [] END OF FILE */
