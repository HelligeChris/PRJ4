/*******************************************************************************
* File Name: idleTimer.h
* Version 1.0
*
* Description:
*  This file provides constants and parameter values for the idleTimer
*  component.
*
********************************************************************************
* Copyright 2016-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(idleTimer_CY_TCPWM_COUNTER_PDL_H)
#define idleTimer_CY_TCPWM_COUNTER_PDL_H

#include "cyfitter.h"
#include "tcpwm/cy_tcpwm_counter.h"

   
/*******************************************************************************
* Variables
*******************************************************************************/
/**
* \addtogroup group_globals
* @{
*/
extern uint8_t  idleTimer_initVar;
extern cy_stc_tcpwm_counter_config_t const idleTimer_config;
/** @} group_globals */


/***************************************
*  Conditional Compilation Parameters
***************************************/

#define idleTimer_INIT_COMPARE_OR_CAPTURE    (2UL)


/***************************************
*        Function Prototypes
****************************************/
/**
* \addtogroup group_general
* @{
*/
void idleTimer_Start(void);
__STATIC_INLINE cy_en_tcpwm_status_t idleTimer_Init(cy_stc_tcpwm_counter_config_t const *config);
__STATIC_INLINE void idleTimer_DeInit(void);
__STATIC_INLINE void idleTimer_Enable(void);
__STATIC_INLINE void idleTimer_Disable(void);
__STATIC_INLINE uint32_t idleTimer_GetStatus(void);

#if(CY_TCPWM_COUNTER_MODE_CAPTURE == idleTimer_INIT_COMPARE_OR_CAPTURE)
    __STATIC_INLINE uint32_t idleTimer_GetCapture(void);
    __STATIC_INLINE uint32_t idleTimer_GetCaptureBuf(void);
#else
    __STATIC_INLINE void idleTimer_SetCompare0(uint32_t compare0);
    __STATIC_INLINE uint32_t idleTimer_GetCompare0(void);
    __STATIC_INLINE void idleTimer_SetCompare1(uint32_t compare1);
    __STATIC_INLINE uint32_t idleTimer_GetCompare1(void);
    __STATIC_INLINE void idleTimer_EnableCompareSwap(bool enable);
#endif /* (CY_TCPWM_COUNTER_MODE_CAPTURE == idleTimer_INIT_COMPARE_OR_CAPTURE) */

__STATIC_INLINE void idleTimer_SetCounter(uint32_t count);
__STATIC_INLINE uint32_t idleTimer_GetCounter(void);
__STATIC_INLINE void idleTimer_SetPeriod(uint32_t period);
__STATIC_INLINE uint32_t idleTimer_GetPeriod(void);
__STATIC_INLINE void idleTimer_TriggerStart(void);
__STATIC_INLINE void idleTimer_TriggerReload(void);
__STATIC_INLINE void idleTimer_TriggerStop(void);
__STATIC_INLINE void idleTimer_TriggerCapture(void);
__STATIC_INLINE uint32_t idleTimer_GetInterruptStatus(void);
__STATIC_INLINE void idleTimer_ClearInterrupt(uint32_t source);
__STATIC_INLINE void idleTimer_SetInterrupt(uint32_t source);
__STATIC_INLINE void idleTimer_SetInterruptMask(uint32_t mask);
__STATIC_INLINE uint32_t idleTimer_GetInterruptMask(void);
__STATIC_INLINE uint32_t idleTimer_GetInterruptStatusMasked(void);
/** @} general */


/***************************************
*           API Constants
***************************************/

/**
* \addtogroup group_macros
* @{
*/
/** This is a ptr to the base address of the TCPWM instance */
#define idleTimer_HW                 (idleTimer_TCPWM__HW)

/** This is a ptr to the base address of the TCPWM CNT instance */
#define idleTimer_CNT_HW             (idleTimer_TCPWM__CNT_HW)

/** This is the counter instance number in the selected TCPWM */
#define idleTimer_CNT_NUM            (idleTimer_TCPWM__CNT_IDX)

/** This is the bit field representing the counter instance in the selected TCPWM */
#define idleTimer_CNT_MASK           (1UL << idleTimer_CNT_NUM)
/** @} group_macros */

#define idleTimer_INPUT_MODE_MASK    (0x3U)
#define idleTimer_INPUT_DISABLED     (7U)


/*******************************************************************************
* Function Name: idleTimer_Init
****************************************************************************//**
*
* Invokes the Cy_TCPWM_Counter_Init() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE cy_en_tcpwm_status_t idleTimer_Init(cy_stc_tcpwm_counter_config_t const *config)
{
    return(Cy_TCPWM_Counter_Init(idleTimer_HW, idleTimer_CNT_NUM, config));
}


/*******************************************************************************
* Function Name: idleTimer_DeInit
****************************************************************************//**
*
* Invokes the Cy_TCPWM_Counter_DeInit() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void idleTimer_DeInit(void)                   
{
    Cy_TCPWM_Counter_DeInit(idleTimer_HW, idleTimer_CNT_NUM, &idleTimer_config);
}

/*******************************************************************************
* Function Name: idleTimer_Enable
****************************************************************************//**
*
* Invokes the Cy_TCPWM_Enable_Multiple() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void idleTimer_Enable(void)                   
{
    Cy_TCPWM_Enable_Multiple(idleTimer_HW, idleTimer_CNT_MASK);
}


/*******************************************************************************
* Function Name: idleTimer_Disable
****************************************************************************//**
*
* Invokes the Cy_TCPWM_Disable_Multiple() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void idleTimer_Disable(void)                  
{
    Cy_TCPWM_Disable_Multiple(idleTimer_HW, idleTimer_CNT_MASK);
}


/*******************************************************************************
* Function Name: idleTimer_GetStatus
****************************************************************************//**
*
* Invokes the Cy_TCPWM_Counter_GetStatus() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t idleTimer_GetStatus(void)                
{
    return(Cy_TCPWM_Counter_GetStatus(idleTimer_HW, idleTimer_CNT_NUM));
}


#if(CY_TCPWM_COUNTER_MODE_CAPTURE == idleTimer_INIT_COMPARE_OR_CAPTURE)
    /*******************************************************************************
    * Function Name: idleTimer_GetCapture
    ****************************************************************************//**
    *
    * Invokes the Cy_TCPWM_Counter_GetCapture() PDL driver function.
    *
    *******************************************************************************/
    __STATIC_INLINE uint32_t idleTimer_GetCapture(void)               
    {
        return(Cy_TCPWM_Counter_GetCapture(idleTimer_HW, idleTimer_CNT_NUM));
    }


    /*******************************************************************************
    * Function Name: idleTimer_GetCaptureBuf
    ****************************************************************************//**
    *
    * Invokes the Cy_TCPWM_Counter_GetCaptureBuf() PDL driver function.
    *
    *******************************************************************************/
    __STATIC_INLINE uint32_t idleTimer_GetCaptureBuf(void)            
    {
        return(Cy_TCPWM_Counter_GetCaptureBuf(idleTimer_HW, idleTimer_CNT_NUM));
    }
#else
    /*******************************************************************************
    * Function Name: idleTimer_SetCompare0
    ****************************************************************************//**
    *
    * Invokes the Cy_TCPWM_Counter_SetCompare0() PDL driver function.
    *
    *******************************************************************************/
    __STATIC_INLINE void idleTimer_SetCompare0(uint32_t compare0)      
    {
        Cy_TCPWM_Counter_SetCompare0(idleTimer_HW, idleTimer_CNT_NUM, compare0);
    }


    /*******************************************************************************
    * Function Name: idleTimer_GetCompare0
    ****************************************************************************//**
    *
    * Invokes the Cy_TCPWM_Counter_GetCompare0() PDL driver function.
    *
    *******************************************************************************/
    __STATIC_INLINE uint32_t idleTimer_GetCompare0(void)              
    {
        return(Cy_TCPWM_Counter_GetCompare0(idleTimer_HW, idleTimer_CNT_NUM));
    }


    /*******************************************************************************
    * Function Name: idleTimer_SetCompare1
    ****************************************************************************//**
    *
    * Invokes the Cy_TCPWM_Counter_SetCompare1() PDL driver function.
    *
    *******************************************************************************/
    __STATIC_INLINE void idleTimer_SetCompare1(uint32_t compare1)      
    {
        Cy_TCPWM_Counter_SetCompare1(idleTimer_HW, idleTimer_CNT_NUM, compare1);
    }


    /*******************************************************************************
    * Function Name: idleTimer_GetCompare1
    ****************************************************************************//**
    *
    * Invokes the Cy_TCPWM_Counter_GetCompare1() PDL driver function.
    *
    *******************************************************************************/
    __STATIC_INLINE uint32_t idleTimer_GetCompare1(void)              
    {
        return(Cy_TCPWM_Counter_GetCompare1(idleTimer_HW, idleTimer_CNT_NUM));
    }


    /*******************************************************************************
    * Function Name: idleTimer_EnableCompareSwap
    ****************************************************************************//**
    *
    * Invokes the Cy_TCPWM_Counter_EnableCompareSwap() PDL driver function.
    *
    *******************************************************************************/
    __STATIC_INLINE void idleTimer_EnableCompareSwap(bool enable)  
    {
        Cy_TCPWM_Counter_EnableCompareSwap(idleTimer_HW, idleTimer_CNT_NUM, enable);
    }
#endif /* (CY_TCPWM_COUNTER_MODE_CAPTURE == idleTimer_INIT_COMPARE_OR_CAPTURE) */


/*******************************************************************************
* Function Name: idleTimer_SetCounter
****************************************************************************//**
*
* Invokes the Cy_TCPWM_Counter_SetCounter() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void idleTimer_SetCounter(uint32_t count)          
{
    Cy_TCPWM_Counter_SetCounter(idleTimer_HW, idleTimer_CNT_NUM, count);
}


/*******************************************************************************
* Function Name: idleTimer_GetCounter
****************************************************************************//**
*
* Invokes the Cy_TCPWM_Counter_GetCounter() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t idleTimer_GetCounter(void)               
{
    return(Cy_TCPWM_Counter_GetCounter(idleTimer_HW, idleTimer_CNT_NUM));
}


/*******************************************************************************
* Function Name: idleTimer_SetPeriod
****************************************************************************//**
*
* Invokes the Cy_TCPWM_Counter_SetPeriod() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void idleTimer_SetPeriod(uint32_t period)          
{
    Cy_TCPWM_Counter_SetPeriod(idleTimer_HW, idleTimer_CNT_NUM, period);
}


/*******************************************************************************
* Function Name: idleTimer_GetPeriod
****************************************************************************//**
*
* Invokes the Cy_TCPWM_Counter_GetPeriod() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t idleTimer_GetPeriod(void)                
{
    return(Cy_TCPWM_Counter_GetPeriod(idleTimer_HW, idleTimer_CNT_NUM));
}


/*******************************************************************************
* Function Name: idleTimer_TriggerStart
****************************************************************************//**
*
* Invokes the Cy_TCPWM_TriggerStart() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void idleTimer_TriggerStart(void)             
{
    Cy_TCPWM_TriggerStart(idleTimer_HW, idleTimer_CNT_MASK);
}


/*******************************************************************************
* Function Name: idleTimer_TriggerReload
****************************************************************************//**
*
* Invokes the Cy_TCPWM_TriggerReloadOrIndex() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void idleTimer_TriggerReload(void)     
{
    Cy_TCPWM_TriggerReloadOrIndex(idleTimer_HW, idleTimer_CNT_MASK);
}


/*******************************************************************************
* Function Name: idleTimer_TriggerStop
****************************************************************************//**
*
* Invokes the Cy_TCPWM_TriggerStopOrKill() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void idleTimer_TriggerStop(void)
{
    Cy_TCPWM_TriggerStopOrKill(idleTimer_HW, idleTimer_CNT_MASK);
}


/*******************************************************************************
* Function Name: idleTimer_TriggerCapture
****************************************************************************//**
*
* Invokes the Cy_TCPWM_TriggerCaptureOrSwap() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void idleTimer_TriggerCapture(void)     
{
    Cy_TCPWM_TriggerCaptureOrSwap(idleTimer_HW, idleTimer_CNT_MASK);
}


/*******************************************************************************
* Function Name: idleTimer_GetInterruptStatus
****************************************************************************//**
*
* Invokes the Cy_TCPWM_GetInterruptStatus() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t idleTimer_GetInterruptStatus(void)       
{
    return(Cy_TCPWM_GetInterruptStatus(idleTimer_HW, idleTimer_CNT_NUM));
}


/*******************************************************************************
* Function Name: idleTimer_ClearInterrupt
****************************************************************************//**
*
* Invokes the Cy_TCPWM_ClearInterrupt() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void idleTimer_ClearInterrupt(uint32_t source)     
{
    Cy_TCPWM_ClearInterrupt(idleTimer_HW, idleTimer_CNT_NUM, source);
}


/*******************************************************************************
* Function Name: idleTimer_SetInterrupt
****************************************************************************//**
*
* Invokes the Cy_TCPWM_SetInterrupt() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void idleTimer_SetInterrupt(uint32_t source)
{
    Cy_TCPWM_SetInterrupt(idleTimer_HW, idleTimer_CNT_NUM, source);
}


/*******************************************************************************
* Function Name: idleTimer_SetInterruptMask
****************************************************************************//**
*
* Invokes the Cy_TCPWM_SetInterruptMask() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void idleTimer_SetInterruptMask(uint32_t mask)     
{
    Cy_TCPWM_SetInterruptMask(idleTimer_HW, idleTimer_CNT_NUM, mask);
}


/*******************************************************************************
* Function Name: idleTimer_GetInterruptMask
****************************************************************************//**
*
* Invokes the Cy_TCPWM_GetInterruptMask() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t idleTimer_GetInterruptMask(void)         
{
    return(Cy_TCPWM_GetInterruptMask(idleTimer_HW, idleTimer_CNT_NUM));
}


/*******************************************************************************
* Function Name: idleTimer_GetInterruptStatusMasked
****************************************************************************//**
*
* Invokes the Cy_TCPWM_GetInterruptStatusMasked() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t idleTimer_GetInterruptStatusMasked(void)
{
    return(Cy_TCPWM_GetInterruptStatusMasked(idleTimer_HW, idleTimer_CNT_NUM));
}

#endif /* idleTimer_CY_TCPWM_COUNTER_PDL_H */


/* [] END OF FILE */
