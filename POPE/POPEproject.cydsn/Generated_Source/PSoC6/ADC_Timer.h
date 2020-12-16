/*******************************************************************************
* File Name: ADC_Timer.h
* Version 1.0
*
* Description:
*  This file provides constants and parameter values for the ADC_Timer
*  component.
*
********************************************************************************
* Copyright 2016-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(ADC_Timer_CY_TCPWM_COUNTER_PDL_H)
#define ADC_Timer_CY_TCPWM_COUNTER_PDL_H

#include "cyfitter.h"
#include "tcpwm/cy_tcpwm_counter.h"

   
/*******************************************************************************
* Variables
*******************************************************************************/
/**
* \addtogroup group_globals
* @{
*/
extern uint8_t  ADC_Timer_initVar;
extern cy_stc_tcpwm_counter_config_t const ADC_Timer_config;
/** @} group_globals */


/***************************************
*  Conditional Compilation Parameters
***************************************/

#define ADC_Timer_INIT_COMPARE_OR_CAPTURE    (2UL)


/***************************************
*        Function Prototypes
****************************************/
/**
* \addtogroup group_general
* @{
*/
void ADC_Timer_Start(void);
__STATIC_INLINE cy_en_tcpwm_status_t ADC_Timer_Init(cy_stc_tcpwm_counter_config_t const *config);
__STATIC_INLINE void ADC_Timer_DeInit(void);
__STATIC_INLINE void ADC_Timer_Enable(void);
__STATIC_INLINE void ADC_Timer_Disable(void);
__STATIC_INLINE uint32_t ADC_Timer_GetStatus(void);

#if(CY_TCPWM_COUNTER_MODE_CAPTURE == ADC_Timer_INIT_COMPARE_OR_CAPTURE)
    __STATIC_INLINE uint32_t ADC_Timer_GetCapture(void);
    __STATIC_INLINE uint32_t ADC_Timer_GetCaptureBuf(void);
#else
    __STATIC_INLINE void ADC_Timer_SetCompare0(uint32_t compare0);
    __STATIC_INLINE uint32_t ADC_Timer_GetCompare0(void);
    __STATIC_INLINE void ADC_Timer_SetCompare1(uint32_t compare1);
    __STATIC_INLINE uint32_t ADC_Timer_GetCompare1(void);
    __STATIC_INLINE void ADC_Timer_EnableCompareSwap(bool enable);
#endif /* (CY_TCPWM_COUNTER_MODE_CAPTURE == ADC_Timer_INIT_COMPARE_OR_CAPTURE) */

__STATIC_INLINE void ADC_Timer_SetCounter(uint32_t count);
__STATIC_INLINE uint32_t ADC_Timer_GetCounter(void);
__STATIC_INLINE void ADC_Timer_SetPeriod(uint32_t period);
__STATIC_INLINE uint32_t ADC_Timer_GetPeriod(void);
__STATIC_INLINE void ADC_Timer_TriggerStart(void);
__STATIC_INLINE void ADC_Timer_TriggerReload(void);
__STATIC_INLINE void ADC_Timer_TriggerStop(void);
__STATIC_INLINE void ADC_Timer_TriggerCapture(void);
__STATIC_INLINE uint32_t ADC_Timer_GetInterruptStatus(void);
__STATIC_INLINE void ADC_Timer_ClearInterrupt(uint32_t source);
__STATIC_INLINE void ADC_Timer_SetInterrupt(uint32_t source);
__STATIC_INLINE void ADC_Timer_SetInterruptMask(uint32_t mask);
__STATIC_INLINE uint32_t ADC_Timer_GetInterruptMask(void);
__STATIC_INLINE uint32_t ADC_Timer_GetInterruptStatusMasked(void);
/** @} general */


/***************************************
*           API Constants
***************************************/

/**
* \addtogroup group_macros
* @{
*/
/** This is a ptr to the base address of the TCPWM instance */
#define ADC_Timer_HW                 (ADC_Timer_TCPWM__HW)

/** This is a ptr to the base address of the TCPWM CNT instance */
#define ADC_Timer_CNT_HW             (ADC_Timer_TCPWM__CNT_HW)

/** This is the counter instance number in the selected TCPWM */
#define ADC_Timer_CNT_NUM            (ADC_Timer_TCPWM__CNT_IDX)

/** This is the bit field representing the counter instance in the selected TCPWM */
#define ADC_Timer_CNT_MASK           (1UL << ADC_Timer_CNT_NUM)
/** @} group_macros */

#define ADC_Timer_INPUT_MODE_MASK    (0x3U)
#define ADC_Timer_INPUT_DISABLED     (7U)


/*******************************************************************************
* Function Name: ADC_Timer_Init
****************************************************************************//**
*
* Invokes the Cy_TCPWM_Counter_Init() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE cy_en_tcpwm_status_t ADC_Timer_Init(cy_stc_tcpwm_counter_config_t const *config)
{
    return(Cy_TCPWM_Counter_Init(ADC_Timer_HW, ADC_Timer_CNT_NUM, config));
}


/*******************************************************************************
* Function Name: ADC_Timer_DeInit
****************************************************************************//**
*
* Invokes the Cy_TCPWM_Counter_DeInit() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void ADC_Timer_DeInit(void)                   
{
    Cy_TCPWM_Counter_DeInit(ADC_Timer_HW, ADC_Timer_CNT_NUM, &ADC_Timer_config);
}

/*******************************************************************************
* Function Name: ADC_Timer_Enable
****************************************************************************//**
*
* Invokes the Cy_TCPWM_Enable_Multiple() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void ADC_Timer_Enable(void)                   
{
    Cy_TCPWM_Enable_Multiple(ADC_Timer_HW, ADC_Timer_CNT_MASK);
}


/*******************************************************************************
* Function Name: ADC_Timer_Disable
****************************************************************************//**
*
* Invokes the Cy_TCPWM_Disable_Multiple() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void ADC_Timer_Disable(void)                  
{
    Cy_TCPWM_Disable_Multiple(ADC_Timer_HW, ADC_Timer_CNT_MASK);
}


/*******************************************************************************
* Function Name: ADC_Timer_GetStatus
****************************************************************************//**
*
* Invokes the Cy_TCPWM_Counter_GetStatus() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t ADC_Timer_GetStatus(void)                
{
    return(Cy_TCPWM_Counter_GetStatus(ADC_Timer_HW, ADC_Timer_CNT_NUM));
}


#if(CY_TCPWM_COUNTER_MODE_CAPTURE == ADC_Timer_INIT_COMPARE_OR_CAPTURE)
    /*******************************************************************************
    * Function Name: ADC_Timer_GetCapture
    ****************************************************************************//**
    *
    * Invokes the Cy_TCPWM_Counter_GetCapture() PDL driver function.
    *
    *******************************************************************************/
    __STATIC_INLINE uint32_t ADC_Timer_GetCapture(void)               
    {
        return(Cy_TCPWM_Counter_GetCapture(ADC_Timer_HW, ADC_Timer_CNT_NUM));
    }


    /*******************************************************************************
    * Function Name: ADC_Timer_GetCaptureBuf
    ****************************************************************************//**
    *
    * Invokes the Cy_TCPWM_Counter_GetCaptureBuf() PDL driver function.
    *
    *******************************************************************************/
    __STATIC_INLINE uint32_t ADC_Timer_GetCaptureBuf(void)            
    {
        return(Cy_TCPWM_Counter_GetCaptureBuf(ADC_Timer_HW, ADC_Timer_CNT_NUM));
    }
#else
    /*******************************************************************************
    * Function Name: ADC_Timer_SetCompare0
    ****************************************************************************//**
    *
    * Invokes the Cy_TCPWM_Counter_SetCompare0() PDL driver function.
    *
    *******************************************************************************/
    __STATIC_INLINE void ADC_Timer_SetCompare0(uint32_t compare0)      
    {
        Cy_TCPWM_Counter_SetCompare0(ADC_Timer_HW, ADC_Timer_CNT_NUM, compare0);
    }


    /*******************************************************************************
    * Function Name: ADC_Timer_GetCompare0
    ****************************************************************************//**
    *
    * Invokes the Cy_TCPWM_Counter_GetCompare0() PDL driver function.
    *
    *******************************************************************************/
    __STATIC_INLINE uint32_t ADC_Timer_GetCompare0(void)              
    {
        return(Cy_TCPWM_Counter_GetCompare0(ADC_Timer_HW, ADC_Timer_CNT_NUM));
    }


    /*******************************************************************************
    * Function Name: ADC_Timer_SetCompare1
    ****************************************************************************//**
    *
    * Invokes the Cy_TCPWM_Counter_SetCompare1() PDL driver function.
    *
    *******************************************************************************/
    __STATIC_INLINE void ADC_Timer_SetCompare1(uint32_t compare1)      
    {
        Cy_TCPWM_Counter_SetCompare1(ADC_Timer_HW, ADC_Timer_CNT_NUM, compare1);
    }


    /*******************************************************************************
    * Function Name: ADC_Timer_GetCompare1
    ****************************************************************************//**
    *
    * Invokes the Cy_TCPWM_Counter_GetCompare1() PDL driver function.
    *
    *******************************************************************************/
    __STATIC_INLINE uint32_t ADC_Timer_GetCompare1(void)              
    {
        return(Cy_TCPWM_Counter_GetCompare1(ADC_Timer_HW, ADC_Timer_CNT_NUM));
    }


    /*******************************************************************************
    * Function Name: ADC_Timer_EnableCompareSwap
    ****************************************************************************//**
    *
    * Invokes the Cy_TCPWM_Counter_EnableCompareSwap() PDL driver function.
    *
    *******************************************************************************/
    __STATIC_INLINE void ADC_Timer_EnableCompareSwap(bool enable)  
    {
        Cy_TCPWM_Counter_EnableCompareSwap(ADC_Timer_HW, ADC_Timer_CNT_NUM, enable);
    }
#endif /* (CY_TCPWM_COUNTER_MODE_CAPTURE == ADC_Timer_INIT_COMPARE_OR_CAPTURE) */


/*******************************************************************************
* Function Name: ADC_Timer_SetCounter
****************************************************************************//**
*
* Invokes the Cy_TCPWM_Counter_SetCounter() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void ADC_Timer_SetCounter(uint32_t count)          
{
    Cy_TCPWM_Counter_SetCounter(ADC_Timer_HW, ADC_Timer_CNT_NUM, count);
}


/*******************************************************************************
* Function Name: ADC_Timer_GetCounter
****************************************************************************//**
*
* Invokes the Cy_TCPWM_Counter_GetCounter() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t ADC_Timer_GetCounter(void)               
{
    return(Cy_TCPWM_Counter_GetCounter(ADC_Timer_HW, ADC_Timer_CNT_NUM));
}


/*******************************************************************************
* Function Name: ADC_Timer_SetPeriod
****************************************************************************//**
*
* Invokes the Cy_TCPWM_Counter_SetPeriod() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void ADC_Timer_SetPeriod(uint32_t period)          
{
    Cy_TCPWM_Counter_SetPeriod(ADC_Timer_HW, ADC_Timer_CNT_NUM, period);
}


/*******************************************************************************
* Function Name: ADC_Timer_GetPeriod
****************************************************************************//**
*
* Invokes the Cy_TCPWM_Counter_GetPeriod() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t ADC_Timer_GetPeriod(void)                
{
    return(Cy_TCPWM_Counter_GetPeriod(ADC_Timer_HW, ADC_Timer_CNT_NUM));
}


/*******************************************************************************
* Function Name: ADC_Timer_TriggerStart
****************************************************************************//**
*
* Invokes the Cy_TCPWM_TriggerStart() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void ADC_Timer_TriggerStart(void)             
{
    Cy_TCPWM_TriggerStart(ADC_Timer_HW, ADC_Timer_CNT_MASK);
}


/*******************************************************************************
* Function Name: ADC_Timer_TriggerReload
****************************************************************************//**
*
* Invokes the Cy_TCPWM_TriggerReloadOrIndex() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void ADC_Timer_TriggerReload(void)     
{
    Cy_TCPWM_TriggerReloadOrIndex(ADC_Timer_HW, ADC_Timer_CNT_MASK);
}


/*******************************************************************************
* Function Name: ADC_Timer_TriggerStop
****************************************************************************//**
*
* Invokes the Cy_TCPWM_TriggerStopOrKill() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void ADC_Timer_TriggerStop(void)
{
    Cy_TCPWM_TriggerStopOrKill(ADC_Timer_HW, ADC_Timer_CNT_MASK);
}


/*******************************************************************************
* Function Name: ADC_Timer_TriggerCapture
****************************************************************************//**
*
* Invokes the Cy_TCPWM_TriggerCaptureOrSwap() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void ADC_Timer_TriggerCapture(void)     
{
    Cy_TCPWM_TriggerCaptureOrSwap(ADC_Timer_HW, ADC_Timer_CNT_MASK);
}


/*******************************************************************************
* Function Name: ADC_Timer_GetInterruptStatus
****************************************************************************//**
*
* Invokes the Cy_TCPWM_GetInterruptStatus() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t ADC_Timer_GetInterruptStatus(void)       
{
    return(Cy_TCPWM_GetInterruptStatus(ADC_Timer_HW, ADC_Timer_CNT_NUM));
}


/*******************************************************************************
* Function Name: ADC_Timer_ClearInterrupt
****************************************************************************//**
*
* Invokes the Cy_TCPWM_ClearInterrupt() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void ADC_Timer_ClearInterrupt(uint32_t source)     
{
    Cy_TCPWM_ClearInterrupt(ADC_Timer_HW, ADC_Timer_CNT_NUM, source);
}


/*******************************************************************************
* Function Name: ADC_Timer_SetInterrupt
****************************************************************************//**
*
* Invokes the Cy_TCPWM_SetInterrupt() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void ADC_Timer_SetInterrupt(uint32_t source)
{
    Cy_TCPWM_SetInterrupt(ADC_Timer_HW, ADC_Timer_CNT_NUM, source);
}


/*******************************************************************************
* Function Name: ADC_Timer_SetInterruptMask
****************************************************************************//**
*
* Invokes the Cy_TCPWM_SetInterruptMask() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void ADC_Timer_SetInterruptMask(uint32_t mask)     
{
    Cy_TCPWM_SetInterruptMask(ADC_Timer_HW, ADC_Timer_CNT_NUM, mask);
}


/*******************************************************************************
* Function Name: ADC_Timer_GetInterruptMask
****************************************************************************//**
*
* Invokes the Cy_TCPWM_GetInterruptMask() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t ADC_Timer_GetInterruptMask(void)         
{
    return(Cy_TCPWM_GetInterruptMask(ADC_Timer_HW, ADC_Timer_CNT_NUM));
}


/*******************************************************************************
* Function Name: ADC_Timer_GetInterruptStatusMasked
****************************************************************************//**
*
* Invokes the Cy_TCPWM_GetInterruptStatusMasked() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t ADC_Timer_GetInterruptStatusMasked(void)
{
    return(Cy_TCPWM_GetInterruptStatusMasked(ADC_Timer_HW, ADC_Timer_CNT_NUM));
}

#endif /* ADC_Timer_CY_TCPWM_COUNTER_PDL_H */


/* [] END OF FILE */
