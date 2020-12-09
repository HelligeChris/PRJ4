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
#endif
    int timeOut = 0;

/* Connection handler */
static cy_stc_ble_conn_handle_t appConnHandle;


/* MAIN */
int HostMain(void)
{
    //init
    UART_DEB_Start();
    Cy_BLE_Start(BLE_EventHandler);
    CS_initKadenceSensor(3);
    startIdleCountdown();
    Cy_SysInt_Init(&WakeUp_cfg, wakeUpHandler);
    
    //set int til 0-40
    
    while(1)
    {
        Cy_BLE_ProcessEvents();
        BLE_sendBattery(battery);
        BLE_sendPower(power);
        
        //LowPowerImplementation(); LAV FUNKTION
        
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