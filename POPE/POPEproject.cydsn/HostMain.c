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
#include "common.h"

//SIMULATE
#if (SIMULATE)
    uint16_t power = 1;
    uint8_t battery = 50;
    char uart_string[50];   //UART debugging
#endif
    int timeOut = 0;

/* Connection handler */
static cy_stc_ble_conn_handle_t appConnHandle;

/* Deep Sleep Params */
cy_stc_syspm_callback_params_t callBackParams = {
    /*.base = &*/ NULL,
    /*.context = &*/ NULL
};

/* Deep Sleep Handlers */
cy_stc_syspm_callback_t DeepSleepHandler = {
    .callback = DeepSleepCallback,
    .type = CY_SYSPM_DEEPSLEEP,
    .skipMode = CY_SYSPM_SKIP_CHECK_READY | CY_SYSPM_SKIP_CHECK_FAIL,
    .callbackParams = &callBackParams,
    .prevItm = NULL,
    .nextItm = NULL
};

/* MAIN */
int HostMain(void)
{
    Cy_SysPm_SystemEnterLp();   //Low Power mode
    
    //init
    UART_DEB_Start();
    Cy_BLE_Start(BLE_EventHandler);
    CS_initKadenceSensor(3);
    startIdleCountdown();
    
    Cy_SysPm_RegisterCallback(&DeepSleepHandler);
    
    //Wake up interrupt (scb_8_interrupt_IRQn = serial com intterupt)
    cy_stc_sysint_t wakeUpIsr = {
        .intrSrc = scb_8_interrupt_IRQn,
        .intrPriority = 0,
    };
    
    //init interrupts
    Cy_SysInt_Init(&wakeUpIsr, wakeUpHandler);
    NVIC_EnableIRQ(idleInt_cfg.intrSrc);
    NVIC_EnableIRQ(wakeUpIsr.intrSrc);
    
    while(1)
    {
        Cy_BLE_ProcessEvents();
        BLE_sendBattery(battery);
        BLE_sendPower(power);
        
        if(testKadence() == true)
        {
            resetIdleCountdown();
        }
        if(Cy_BLE_GetAdvertisementState() == CY_BLE_ADV_STATE_STOPPED) // Hvis der ikke bliver bonded inden for 180sek
        {
            Cy_SysPm_DeepSleep(CY_SYSPM_WAIT_FOR_INTERRUPT);
        }
        
        timeOut = BLE_checkTimer();
        getData(timeOut);
    }
}

/* Deep Sleep Callback */
cy_en_syspm_status_t DeepSleepCallback(cy_stc_syspm_callback_params_t *callbackParams, cy_en_syspm_callback_mode_t mode)
{
    cy_en_syspm_status_t retVal = CY_SYSPM_FAIL;
    
    switch(mode)
    {
        case CY_SYSPM_BEFORE_TRANSITION:    //Ting der skal gøres inden Deep Sleep
            idleTimer_Disable();
            UART_DEB_Disable();
            Cy_BLE_Disable();
            
            retVal = CY_SYSPM_SUCCESS;
            break;
            
        case CY_SYSPM_AFTER_TRANSITION:     //Ting der skal gøres efter Deep Sleep
            idleTimer_Enable();
            resetIdleCountdown();
            Cy_BLE_Enable();
            
            retVal = CY_SYSPM_SUCCESS;
            break;
            
        default:
            break;
    }
    return retVal;
}


void getData(int timeOut){
    #if (SIMULATE)
        if(timeOut){
            power += 100;
            battery++;
            float* CS = CS_getKadence();
            UARTprint("1", "Kadence-control:");
            sprintf(uart_string, "RPM: %f", CS[0]);
            UARTprint("2", uart_string);
            sprintf(uart_string, "Frq: %f", CS[1]);
            UARTprint("3", uart_string);  
            sprintf(uart_string, "Prd: %f", CS[2]);
            UARTprint("4", uart_string);
        }
    #endif
    #if (SIMULATE != 1)
        if(timeOut){
            //getPower();
            //getBattery();
        }
    #endif
}

/* [] END OF FILE */