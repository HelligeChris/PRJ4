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


/* MAIN */
int HostMain(void)
{
    //init
    Cy_SysPm_SystemEnterLp();   //Low Power, alt virker stadig
    
    UART_DEB_Start();
    Cy_BLE_Start(BLE_EventHandler);
    CS_initKadenceSensor(3);
    startIdleCountdown();
    Cy_SysInt_Init(&WakeUp_cfg, wakeUpHandler);
    NVIC_EnableIRQ(idleInt_cfg.intrSrc);
    NVIC_EnableIRQ(WakeUp_cfg.intrSrc);
    
    //set int til 0-40
    
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