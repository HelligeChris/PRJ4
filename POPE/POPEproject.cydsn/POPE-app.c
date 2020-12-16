/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "POPE-app.h"

float* RPM;
uint16 idleCounter = 0;

#if DEBUG_UART_ENABLED
    char uart_string[50];   //UART debugging
#endif


void lowPowerMode()
{
    //
}

uint16_t getPower()
{
    float power = 0;
    float crankLength = 0.175;  //m
    float* kadence = CS_getKadence();
    uint16 periode = (uint16)(kadence[2]*1000);
    periode = 1000;
    periode = periode > 5000 ? 5000 : periode;
    
    uint16_t mass = getVaegt(periode);

    sprintf(uart_string, "Mass: %i", mass);
    UARTprint("20",uart_string);
    mass /= 1000;
    /* Udregninger */
    float torque = mass * pow(crankLength*2*M_PI, 2) / pow(periode/1000, 2);
    float angVeloc = 2*M_PI / (periode/1000);
    
    //udregn power
    power = torque * angVeloc;
    
    sprintf(uart_string, "Udregnet watt: %f", power);
    UARTprint("21",uart_string);
    return power;
}


bool testKadence()
{
    bool highCadence = false;
    RPM = CS_getKadence();
    if(RPM[0] > 12)   //200mHz
    {
        highCadence = true;
    }
    return highCadence;
}

void startIdleCountdown()
{
    Cy_SysInt_Init(&idleInt_cfg, idleIntHandler);
    idleTimer_Start();
    idleCounter = 0;
    idleTimer_SetCounter(0);
}


void resetIdleCountdown()
{
    idleCounter = 0;
    idleTimer_SetCounter(0);
}

//interrupt
void idleIntHandler()
{
    idleCounter++;
    if(idleCounter == 300)
    {
        #if DEBUG_UART_ENABLED
            sprintf(uart_string, "CPU Deep Sleep: %i", idleCounter);
            UARTprint("9", uart_string);
        #endif
        //Cy_SysPm_DeepSleep(CY_SYSPM_WAIT_FOR_INTERRUPT);
    }
    #if DEBUG_UART_ENABLED
        sprintf(uart_string, "idleCounter overflow: %i", idleCounter);
        UARTprint("10", uart_string);
    #endif
}

void wakeUpHandler()
{
    
}

///* Deep Sleep Params */
//cy_stc_syspm_callback_params_t callBackParams = {
//    /*.base = &*/ NULL,
//    /*.context = &*/ NULL
//};
//
///* Deep Sleep Handlers */
//cy_stc_syspm_callback_t DeepSleepHandler = {
//    .callback = DeepSleepCallback,
//    .type = CY_SYSPM_DEEPSLEEP,
//    .skipMode = CY_SYSPM_SKIP_CHECK_READY | CY_SYSPM_SKIP_CHECK_FAIL,
//    .callbackParams = &callBackParams,
//    .prevItm = NULL,
//    .nextItm = NULL
//};

//    //Wake up interrupt (scb_8_interrupt_IRQn = serial com intterupt)
//    cy_stc_sysint_t wakeUpIsr = {
//        .intrSrc = scb_8_interrupt_IRQn,
//        .intrPriority = 0,
//    };

/* Deep Sleep Callback */
//cy_en_syspm_status_t DeepSleepCallback(cy_stc_syspm_callback_params_t *callbackParams, cy_en_syspm_callback_mode_t mode)
//{
//    cy_en_syspm_status_t retVal = CY_SYSPM_FAIL;
//    
//    switch(mode)
//    {
//        case CY_SYSPM_BEFORE_TRANSITION:    //Ting der skal gøres inden Deep Sleep
//            idleTimer_Disable();
//            UART_DEB_Disable();
//            Cy_BLE_Disable();
//            
//            retVal = CY_SYSPM_SUCCESS;
//            break;
//            
//        case CY_SYSPM_AFTER_TRANSITION:     //Ting der skal gøres efter Deep Sleep
//            idleTimer_Enable();
//            resetIdleCountdown();
//            Cy_BLE_Enable();
//            
//            retVal = CY_SYSPM_SUCCESS;
//            break;
//            
//        default:
//            break;
//    }
//    return retVal;
//}

/* [] END OF FILE */
