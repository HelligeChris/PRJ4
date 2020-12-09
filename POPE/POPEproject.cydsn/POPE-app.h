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
#include "trykControl.h"
#include "kadenceControl.h"

void lowPowerMode();
uint16_t getPower();
bool testKadence();
void startIdleCountdown();
void resetIdleCountdown();

//interrupts
void idleIntHandler();
void wakeUpHandler();

/* [] END OF FILE */
