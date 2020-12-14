/*******************************************************************************
* File Name: SampleTimer.h
* Version 1.0
*
* Description:
*  This file provides constants and parameter values for the SampleTimer
*  component.
*
********************************************************************************
* Copyright 2016-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(SampleTimer_CY_TCPWM_COUNTER_PDL_H)
#define SampleTimer_CY_TCPWM_COUNTER_PDL_H

#include "cyfitter.h"
#include "tcpwm/cy_tcpwm_counter.h"

   
/*******************************************************************************
* Variables
*******************************************************************************/
/**
* \addtogroup group_globals
* @{
*/
extern uint8_t  SampleTimer_initVar;
extern cy_stc_tcpwm_counter_config_t const SampleTimer_config;
/** @} group_globals */


/***************************************
*  Conditional Compilation Parameters
***************************************/

#define SampleTimer_INIT_COMPARE_OR_CAPTURE    (2UL)


/***************************************
*        Function Prototypes
****************************************/
/**
* \addtogroup group_general
* @{
*/
void SampleTimer_Start(void);
__STATIC_INLINE cy_en_tcpwm_status_t SampleTimer_Init(cy_stc_tcpwm_counter_config_t const *config);
__STATIC_INLINE void SampleTimer_DeInit(void);
__STATIC_INLINE void SampleTimer_Enable(void);
__STATIC_INLINE void SampleTimer_Disable(void);
__STATIC_INLINE uint32_t SampleTimer_GetStatus(void);

#if(CY_TCPWM_COUNTER_MODE_CAPTURE == SampleTimer_INIT_COMPARE_OR_CAPTURE)
    __STATIC_INLINE uint32_t SampleTimer_GetCapture(void);
    __STATIC_INLINE uint32_t SampleTimer_GetCaptureBuf(void);
#else
    __STATIC_INLINE void SampleTimer_SetCompare0(uint32_t compare0);
    __STATIC_INLINE uint32_t SampleTimer_GetCompare0(void);
    __STATIC_INLINE void SampleTimer_SetCompare1(uint32_t compare1);
    __STATIC_INLINE uint32_t SampleTimer_GetCompare1(void);
    __STATIC_INLINE void SampleTimer_EnableCompareSwap(bool enable);
#endif /* (CY_TCPWM_COUNTER_MODE_CAPTURE == SampleTimer_INIT_COMPARE_OR_CAPTURE) */

__STATIC_INLINE void SampleTimer_SetCounter(uint32_t count);
__STATIC_INLINE uint32_t SampleTimer_GetCounter(void);
__STATIC_INLINE void SampleTimer_SetPeriod(uint32_t period);
__STATIC_INLINE uint32_t SampleTimer_GetPeriod(void);
__STATIC_INLINE void SampleTimer_TriggerStart(void);
__STATIC_INLINE void SampleTimer_TriggerReload(void);
__STATIC_INLINE void SampleTimer_TriggerStop(void);
__STATIC_INLINE void SampleTimer_TriggerCapture(void);
__STATIC_INLINE uint32_t SampleTimer_GetInterruptStatus(void);
__STATIC_INLINE void SampleTimer_ClearInterrupt(uint32_t source);
__STATIC_INLINE void SampleTimer_SetInterrupt(uint32_t source);
__STATIC_INLINE void SampleTimer_SetInterruptMask(uint32_t mask);
__STATIC_INLINE uint32_t SampleTimer_GetInterruptMask(void);
__STATIC_INLINE uint32_t SampleTimer_GetInterruptStatusMasked(void);
/** @} general */


/***************************************
*           API Constants
***************************************/

/**
* \addtogroup group_macros
* @{
*/
/** This is a ptr to the base address of the TCPWM instance */
#define SampleTimer_HW                 (SampleTimer_TCPWM__HW)

/** This is a ptr to the base address of the TCPWM CNT instance */
#define SampleTimer_CNT_HW             (SampleTimer_TCPWM__CNT_HW)

/** This is the counter instance number in the selected TCPWM */
#define SampleTimer_CNT_NUM            (SampleTimer_TCPWM__CNT_IDX)

/** This is the bit field representing the counter instance in the selected TCPWM */
#define SampleTimer_CNT_MASK           (1UL << SampleTimer_CNT_NUM)
/** @} group_macros */

#define SampleTimer_INPUT_MODE_MASK    (0x3U)
#define SampleTimer_INPUT_DISABLED     (7U)


/*******************************************************************************
* Function Name: SampleTimer_Init
****************************************************************************//**
*
* Invokes the Cy_TCPWM_Counter_Init() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE cy_en_tcpwm_status_t SampleTimer_Init(cy_stc_tcpwm_counter_config_t const *config)
{
    return(Cy_TCPWM_Counter_Init(SampleTimer_HW, SampleTimer_CNT_NUM, config));
}


/*******************************************************************************
* Function Name: SampleTimer_DeInit
****************************************************************************//**
*
* Invokes the Cy_TCPWM_Counter_DeInit() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void SampleTimer_DeInit(void)                   
{
    Cy_TCPWM_Counter_DeInit(SampleTimer_HW, SampleTimer_CNT_NUM, &SampleTimer_config);
}

/*******************************************************************************
* Function Name: SampleTimer_Enable
****************************************************************************//**
*
* Invokes the Cy_TCPWM_Enable_Multiple() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void SampleTimer_Enable(void)                   
{
    Cy_TCPWM_Enable_Multiple(SampleTimer_HW, SampleTimer_CNT_MASK);
}


/*******************************************************************************
* Function Name: SampleTimer_Disable
****************************************************************************//**
*
* Invokes the Cy_TCPWM_Disable_Multiple() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void SampleTimer_Disable(void)                  
{
    Cy_TCPWM_Disable_Multiple(SampleTimer_HW, SampleTimer_CNT_MASK);
}


/*******************************************************************************
* Function Name: SampleTimer_GetStatus
****************************************************************************//**
*
* Invokes the Cy_TCPWM_Counter_GetStatus() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t SampleTimer_GetStatus(void)                
{
    return(Cy_TCPWM_Counter_GetStatus(SampleTimer_HW, SampleTimer_CNT_NUM));
}


#if(CY_TCPWM_COUNTER_MODE_CAPTURE == SampleTimer_INIT_COMPARE_OR_CAPTURE)
    /*******************************************************************************
    * Function Name: SampleTimer_GetCapture
    ****************************************************************************//**
    *
    * Invokes the Cy_TCPWM_Counter_GetCapture() PDL driver function.
    *
    *******************************************************************************/
    __STATIC_INLINE uint32_t SampleTimer_GetCapture(void)               
    {
        return(Cy_TCPWM_Counter_GetCapture(SampleTimer_HW, SampleTimer_CNT_NUM));
    }


    /*******************************************************************************
    * Function Name: SampleTimer_GetCaptureBuf
    ****************************************************************************//**
    *
    * Invokes the Cy_TCPWM_Counter_GetCaptureBuf() PDL driver function.
    *
    *******************************************************************************/
    __STATIC_INLINE uint32_t SampleTimer_GetCaptureBuf(void)            
    {
        return(Cy_TCPWM_Counter_GetCaptureBuf(SampleTimer_HW, SampleTimer_CNT_NUM));
    }
#else
    /*******************************************************************************
    * Function Name: SampleTimer_SetCompare0
    ****************************************************************************//**
    *
    * Invokes the Cy_TCPWM_Counter_SetCompare0() PDL driver function.
    *
    *******************************************************************************/
    __STATIC_INLINE void SampleTimer_SetCompare0(uint32_t compare0)      
    {
        Cy_TCPWM_Counter_SetCompare0(SampleTimer_HW, SampleTimer_CNT_NUM, compare0);
    }


    /*******************************************************************************
    * Function Name: SampleTimer_GetCompare0
    ****************************************************************************//**
    *
    * Invokes the Cy_TCPWM_Counter_GetCompare0() PDL driver function.
    *
    *******************************************************************************/
    __STATIC_INLINE uint32_t SampleTimer_GetCompare0(void)              
    {
        return(Cy_TCPWM_Counter_GetCompare0(SampleTimer_HW, SampleTimer_CNT_NUM));
    }


    /*******************************************************************************
    * Function Name: SampleTimer_SetCompare1
    ****************************************************************************//**
    *
    * Invokes the Cy_TCPWM_Counter_SetCompare1() PDL driver function.
    *
    *******************************************************************************/
    __STATIC_INLINE void SampleTimer_SetCompare1(uint32_t compare1)      
    {
        Cy_TCPWM_Counter_SetCompare1(SampleTimer_HW, SampleTimer_CNT_NUM, compare1);
    }


    /*******************************************************************************
    * Function Name: SampleTimer_GetCompare1
    ****************************************************************************//**
    *
    * Invokes the Cy_TCPWM_Counter_GetCompare1() PDL driver function.
    *
    *******************************************************************************/
    __STATIC_INLINE uint32_t SampleTimer_GetCompare1(void)              
    {
        return(Cy_TCPWM_Counter_GetCompare1(SampleTimer_HW, SampleTimer_CNT_NUM));
    }


    /*******************************************************************************
    * Function Name: SampleTimer_EnableCompareSwap
    ****************************************************************************//**
    *
    * Invokes the Cy_TCPWM_Counter_EnableCompareSwap() PDL driver function.
    *
    *******************************************************************************/
    __STATIC_INLINE void SampleTimer_EnableCompareSwap(bool enable)  
    {
        Cy_TCPWM_Counter_EnableCompareSwap(SampleTimer_HW, SampleTimer_CNT_NUM, enable);
    }
#endif /* (CY_TCPWM_COUNTER_MODE_CAPTURE == SampleTimer_INIT_COMPARE_OR_CAPTURE) */


/*******************************************************************************
* Function Name: SampleTimer_SetCounter
****************************************************************************//**
*
* Invokes the Cy_TCPWM_Counter_SetCounter() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void SampleTimer_SetCounter(uint32_t count)          
{
    Cy_TCPWM_Counter_SetCounter(SampleTimer_HW, SampleTimer_CNT_NUM, count);
}


/*******************************************************************************
* Function Name: SampleTimer_GetCounter
****************************************************************************//**
*
* Invokes the Cy_TCPWM_Counter_GetCounter() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t SampleTimer_GetCounter(void)               
{
    return(Cy_TCPWM_Counter_GetCounter(SampleTimer_HW, SampleTimer_CNT_NUM));
}


/*******************************************************************************
* Function Name: SampleTimer_SetPeriod
****************************************************************************//**
*
* Invokes the Cy_TCPWM_Counter_SetPeriod() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void SampleTimer_SetPeriod(uint32_t period)          
{
    Cy_TCPWM_Counter_SetPeriod(SampleTimer_HW, SampleTimer_CNT_NUM, period);
}


/*******************************************************************************
* Function Name: SampleTimer_GetPeriod
****************************************************************************//**
*
* Invokes the Cy_TCPWM_Counter_GetPeriod() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t SampleTimer_GetPeriod(void)                
{
    return(Cy_TCPWM_Counter_GetPeriod(SampleTimer_HW, SampleTimer_CNT_NUM));
}


/*******************************************************************************
* Function Name: SampleTimer_TriggerStart
****************************************************************************//**
*
* Invokes the Cy_TCPWM_TriggerStart() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void SampleTimer_TriggerStart(void)             
{
    Cy_TCPWM_TriggerStart(SampleTimer_HW, SampleTimer_CNT_MASK);
}


/*******************************************************************************
* Function Name: SampleTimer_TriggerReload
****************************************************************************//**
*
* Invokes the Cy_TCPWM_TriggerReloadOrIndex() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void SampleTimer_TriggerReload(void)     
{
    Cy_TCPWM_TriggerReloadOrIndex(SampleTimer_HW, SampleTimer_CNT_MASK);
}


/*******************************************************************************
* Function Name: SampleTimer_TriggerStop
****************************************************************************//**
*
* Invokes the Cy_TCPWM_TriggerStopOrKill() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void SampleTimer_TriggerStop(void)
{
    Cy_TCPWM_TriggerStopOrKill(SampleTimer_HW, SampleTimer_CNT_MASK);
}


/*******************************************************************************
* Function Name: SampleTimer_TriggerCapture
****************************************************************************//**
*
* Invokes the Cy_TCPWM_TriggerCaptureOrSwap() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void SampleTimer_TriggerCapture(void)     
{
    Cy_TCPWM_TriggerCaptureOrSwap(SampleTimer_HW, SampleTimer_CNT_MASK);
}


/*******************************************************************************
* Function Name: SampleTimer_GetInterruptStatus
****************************************************************************//**
*
* Invokes the Cy_TCPWM_GetInterruptStatus() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t SampleTimer_GetInterruptStatus(void)       
{
    return(Cy_TCPWM_GetInterruptStatus(SampleTimer_HW, SampleTimer_CNT_NUM));
}


/*******************************************************************************
* Function Name: SampleTimer_ClearInterrupt
****************************************************************************//**
*
* Invokes the Cy_TCPWM_ClearInterrupt() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void SampleTimer_ClearInterrupt(uint32_t source)     
{
    Cy_TCPWM_ClearInterrupt(SampleTimer_HW, SampleTimer_CNT_NUM, source);
}


/*******************************************************************************
* Function Name: SampleTimer_SetInterrupt
****************************************************************************//**
*
* Invokes the Cy_TCPWM_SetInterrupt() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void SampleTimer_SetInterrupt(uint32_t source)
{
    Cy_TCPWM_SetInterrupt(SampleTimer_HW, SampleTimer_CNT_NUM, source);
}


/*******************************************************************************
* Function Name: SampleTimer_SetInterruptMask
****************************************************************************//**
*
* Invokes the Cy_TCPWM_SetInterruptMask() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void SampleTimer_SetInterruptMask(uint32_t mask)     
{
    Cy_TCPWM_SetInterruptMask(SampleTimer_HW, SampleTimer_CNT_NUM, mask);
}


/*******************************************************************************
* Function Name: SampleTimer_GetInterruptMask
****************************************************************************//**
*
* Invokes the Cy_TCPWM_GetInterruptMask() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t SampleTimer_GetInterruptMask(void)         
{
    return(Cy_TCPWM_GetInterruptMask(SampleTimer_HW, SampleTimer_CNT_NUM));
}


/*******************************************************************************
* Function Name: SampleTimer_GetInterruptStatusMasked
****************************************************************************//**
*
* Invokes the Cy_TCPWM_GetInterruptStatusMasked() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t SampleTimer_GetInterruptStatusMasked(void)
{
    return(Cy_TCPWM_GetInterruptStatusMasked(SampleTimer_HW, SampleTimer_CNT_NUM));
}

#endif /* SampleTimer_CY_TCPWM_COUNTER_PDL_H */


/* [] END OF FILE */
