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

typedef struct trykCtrl
{
    uint32 vaegt;
}trykCtrl;

void initTrykSensor();
void calibrateTrykSensor();
uint32 getVaegt(uint16_t periode);
/* [] END OF FILE */
