/*******************************************************************************
* File Name: idleTimer.c
* Version 1.0
*
* Description:
*  This file provides the source code to the API for the idleTimer
*  component
*
********************************************************************************
* Copyright 2016-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "idleTimer.h"

/** Indicates whether or not the idleTimer has been initialized. 
*  The variable is initialized to 0 and set to 1 the first time 
*  idleTimer_Start() is called. This allows the Component to 
*  restart without reinitialization after the first call to 
*  the idleTimer_Start() routine.
*/
uint8_t idleTimer_initVar = 0U;

/** The instance-specific configuration structure. This should be used in the 
*  associated idleTimer_Init() function.
*/ 
cy_stc_tcpwm_counter_config_t const idleTimer_config =
{
        .period = 39062UL,
        .clockPrescaler = 7UL,
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
* Function Name: idleTimer_Start
****************************************************************************//**
*
*  Calls the idleTimer_Init() when called the first time and enables 
*  the idleTimer. For subsequent calls the configuration is left 
*  unchanged and the component is just enabled.
*
* \globalvars
*  \ref idleTimer_initVar
*
*******************************************************************************/
void idleTimer_Start(void)
{
    if (0U == idleTimer_initVar)
    {
        (void)Cy_TCPWM_Counter_Init(idleTimer_HW, idleTimer_CNT_NUM, &idleTimer_config); 

        idleTimer_initVar = 1U;
    }

    Cy_TCPWM_Enable_Multiple(idleTimer_HW, idleTimer_CNT_MASK);
    
    #if (idleTimer_INPUT_DISABLED == 7UL)
        Cy_TCPWM_TriggerStart(idleTimer_HW, idleTimer_CNT_MASK);
    #endif /* (idleTimer_INPUT_DISABLED == 7UL) */    
}


/* [] END OF FILE */
