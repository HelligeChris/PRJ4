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

//DEFINES
#define CY_BLE_ADVERTISING_FAST (0x00u)

//POPE characteristic index
typedef enum
{
    POPE_POWER_MEASURE,
    POPE_CHAR_COUNT
}POPE_char_index_t;

//BLE Public Functions
void BLE_EventHandler(uint32_t event, void* eventParam);
int BLE_checkTimer();
//void BLE_handlePowerMeasure();
cy_en_ble_api_result_t BLE_sendPower(uint16_t Power);
cy_en_ble_api_result_t BLE_sendBattery(uint8_t Battery);  //BatteryPercentage

//BLE Private Functions
cy_en_ble_api_result_t BLE_SetCharacteristicValue(POPE_char_index_t charIndex, uint16_t attrSize, uint8_t *attrValue);
    
/* [] END OF FILE */
