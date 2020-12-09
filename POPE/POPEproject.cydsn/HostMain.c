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

char uart_string[50];   //UART debugging

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
    UART_DEB_Start();
    UART_DEB_PutString("Main \r \n ");
    
    //INIT UI -> lav function? LED'er (debugging)
    
    Cy_BLE_Start(BLE_EventHandler);
    //CS_initKadenceSensor(3);
    
    //float* RPM;
    
    while(1)
    {
        //power = getPower();     //lav getPower() funktion
        //battery = getVoltageLevel_mV(); //lav getVoltageLevel_mV() funktion
        
        Cy_BLE_ProcessEvents();
        //errcheck?
        BLE_sendBattery(battery);
        //errcheck?
        BLE_sendPower(power);
        //errcheck?
        
        //LowPowerImplementation(); LAV FUNKTION
        
        if(Cy_BLE_GetConnectionState(appConnHandle) == CY_BLE_CONN_STATE_CONNECTED)
        {
            //Opsaml data
            //Cy_BLE_ProcessEvents(); /*maybe*/
        }
        
        else if(Cy_BLE_GetConnectionState(appConnHandle) == CY_BLE_CONN_STATE_DISCONNECTED) /*check bond list flag)*/
        {
            //App_RemoveDevicesFromBondList(); //Lav function/kopier funktion
        }
        
        timeOut = BLE_checkTimer();
        #if (SIMULATE)
        if(timeOut){
            power += 100;
            battery++;
        }
        #endif
    }
}

/* [] END OF FILE */