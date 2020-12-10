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
    
}


uint16_t getPower()
{
    uint16_t power = 0;
    uint8_t crankLength = 175;  //mm
    //evt. flere variabler...
    
    //getVaegt();
    CS_getKadence();
    
    //udregn power
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

/* [] END OF FILE */
