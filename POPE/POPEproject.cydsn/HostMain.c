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

//SIMULATE Power & Battery
#if (SIMULATE)
    uint16_t power = 1;
    uint8_t battery = 50;
    char uart_string[50];   //UART debugging
#endif
    int timeOut = 0;


/* MAIN */
int HostMain(void)
{
    Cy_SysPm_SystemEnterLp();   //Low Power mode
    
    /* initiering */
    UART_DEB_Start();
    Cy_BLE_Start(BLE_EventHandler);
    CS_initKadenceSensor(3);
    startIdleCountdown();
    //init interrupt
    NVIC_EnableIRQ(idleInt_cfg.intrSrc);
    
    while(1)
    {
        Cy_BLE_ProcessEvents();     //skal kaldes hvert loop
        
        timeOut = BLE_checkTimer(); //Hent data 1 gang i sekundet
        #if (SIMULATE != 1)
            if(timeOut){
                //getPower();
                //getBattery();
            }
        #endif
        #if SIMULATE
            getData(timeOut);       //simulering
        #endif
        
        BLE_sendBattery(battery);
        BLE_sendPower(power);
        
        if(testKadence() == true)
        {
            resetIdleCountdown();
        }
    }
}

//Simulering af data
void getData(int timeOut){
    #if (SIMULATE)
        if(timeOut){
            power += 100;
            battery++;
            float* CS = CS_getKadence();
            #if DEBUG_UART_ENABLED
                UARTprint("1", "Kadence-control:");
                sprintf(uart_string, "RPM: %f", CS[0]);
                UARTprint("2", uart_string);
                sprintf(uart_string, "Frq: %f", CS[1]);
                UARTprint("3", uart_string);  
                sprintf(uart_string, "Prd: %f", CS[2]);
                UARTprint("4", uart_string);
            #endif
        }
    #endif
}

/* [] END OF FILE */