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

#ifndef COMMON_H
#define COMMON_H

#include <project.h>
#include <stdio.h>
#include "BLE-communication.h"
#include "VT100Terminal.h"
#include "i2cFunctions.h"
#include "kadenceControl.h"
#include "POPE-app.h"

/********************************************************************************
    SIMULERING
*********************************************************************************/
#define SIMULATE 1
    
//Conditional Compilation Parameters
#define ENABLED 1u
#define DISABLED 0u
#define DEBUG_UART_ENABLED 1

//Functions
int HostMain(void);
void getData(int timeOut);

#endif
/* [] END OF FILE */