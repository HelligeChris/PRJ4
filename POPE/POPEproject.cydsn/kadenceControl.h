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

typedef struct kadenceCtrl
{
    uint16 kadence;
    
}kadenceCtrl;

void initKadenceSensor();
void calibrateKadenceSensor();
uint16 getKadence();
/* [] END OF FILE */
