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
#pragma once

#include "common.h"
#include "trykControl.h"
#include "kadenceControl.h"
#include <math.h>

void lowPowerMode();
uint16_t getPower();
bool testKadence();
void startIdleCountdown();
void resetIdleCountdown();

//interrupts
void idleIntHandler();
void wakeUpHandler();

/* [] END OF FILE */
