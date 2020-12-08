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

char uart_string[50];   //UART debugging

void lowPowerImplementation()
{
    
}

uint16_t getPower()
{
    uint16_t power = 0;
    uint8_t crankLength = 175;  //mm
    //evt. flere variabler...
    
    //getVaegt();
    float* RPM = CS_getKadence();
    sprintf(uart_string, "RPM value: %i",(int)RPM);
    UARTprint("1", uart_string);
    
    //udregn power
    return power;
}

bool testKadence()
{
    bool highCadence = true;
    //test kadencen
        //return false hvis under 200mHz
    return highCadence;
}

void startIdleCountdown()
{
    
}

void resetIdleCountdown()
{
    
}

bool calibratePOPE()
{
    bool calibrationDone = false;
    //udfør kalibrering
        //return false hvis fejl?
    return calibrationDone;
}

/* [] END OF FILE */
