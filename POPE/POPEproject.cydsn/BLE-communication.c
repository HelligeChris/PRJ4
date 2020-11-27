///* ========================================
// *
// * Copyright YOUR COMPANY, THE YEAR
// * All Rights Reserved
// * UNPUBLISHED, LICENSED SOFTWARE.
// *
// * CONFIDENTIAL AND PROPRIETARY INFORMATION
// * WHICH IS THE PROPERTY OF your company.
// *
// * ========================================
//Includes
#include "BLE-communication.h"

/* BLE Private Functions */
cy_en_ble_api_result_t BLE_SetCharacteristicValue(POPE_char_index_t charIndex, uint16_t attrSize, uint8_t *attrValue);


/* Timer variables */
static cy_stc_ble_timer_info_t BLEtimerParam = { .timeout = 1u};
static volatile uint8_t BLEmainTimer = 1u;

/* Power Array */
uint8_t powerArray[2] = {0};


/* Callback function */
void BLE_EventHandler(uint32_t event, void *eventParam)
{
    switch(event)
    {
        case CY_BLE_EVT_STACK_ON:
            #if DEBUG_UART_ENABLED
            UART_DEB_PutString("Stack On \r \n ");
            #endif
            Cy_BLE_GAPP_StartAdvertisement(CY_BLE_ADVERTISING_FAST, CY_BLE_PERIPHERAL_CONFIGURATION_0_INDEX);
            //Cy_BLE_GAP_GetBdAddress();
            break;
            
        case CY_BLE_EVT_GAP_DEVICE_DISCONNECTED: //Til debugging. Går ind i denne case når link er etableret.
            Cy_BLE_GAPP_StartAdvertisement(CY_BLE_ADVERTISING_FAST, CY_BLE_PERIPHERAL_CONFIGURATION_0_INDEX);
            #if DEBUG_UART_ENABLED
            UART_DEB_PutString("Device link connected \r \n ");
            #endif
            break;
           
        case CY_BLE_EVT_TIMEOUT: 
            #if DEBUG_UART_ENABLED
            UART_DEB_PutString("Timeout \r \n ");
            #endif
            if((((cy_stc_ble_timeout_param_t *)eventParam)->reasonCode == CY_BLE_GENERIC_APP_TO) && 
               (((cy_stc_ble_timeout_param_t *)eventParam)->timerHandle == BLEtimerParam.timerHandle)) //timeoutval == current timer val
            {
                BLEmainTimer++;
            }
            break;
            
        case CY_BLE_EVT_STACK_SHUTDOWN_COMPLETE:
            #if DEBUG_UART_ENABLED
            UART_DEB_PutString("Case 3 \r \n ");
            #endif
            Cy_SysPm_Hibernate();
            break;
            
        case CY_BLE_EVT_GAPP_ADVERTISEMENT_START_STOP:
            #if DEBUG_UART_ENABLED
            UART_DEB_PutString("Case 7 \r \n ");
            #endif
            if(Cy_BLE_GetAdvertisementState() == CY_BLE_ADV_STATE_STOPPED)
            {
                Cy_BLE_Stop();
            }
            break;
            
        case CY_BLE_EVT_GATTS_READ_CHAR_VAL_ACCESS_REQ:
            #if DEBUG_UART_ENABLED
            UART_DEB_PutString("Read-req");
            #endif
            break;
        
        default:
            #if DEBUG_UART_ENABLED
            UART_DEB_PutString("Default \r \n ");
            #endif
            break;
    }
}


int BLE_checkTimer(){
    if (BLEmainTimer != 0){
        BLEmainTimer = 0;
        Cy_BLE_StartTimer(&BLEtimerParam);
        return 1;
    }
    return 0;
}


cy_en_ble_api_result_t BLE_sendPower(uint16_t Power)
{
    cy_en_ble_api_result_t apiResult = CY_BLE_SUCCESS;
    
    powerArray[1] = (uint8_t)Power;
    powerArray[0] = (Power >> 8);
    
    apiResult = BLE_SetCharacteristicValue(POPE_POWER_MEASURE, sizeof(uint8)*2, (uint8_t*)&powerArray);
    
    powerArray[1] = 0;
    powerArray[0] = 0;
    
    return apiResult;
}


cy_en_ble_api_result_t BLE_sendBattery(uint8_t Battery)
{
    cy_en_ble_api_result_t apiResult = CY_BLE_SUCCESS;
    apiResult =  Cy_BLE_BASS_SetCharacteristicValue(CY_BLE_BATTERY_SERVICE_INDEX, CY_BLE_BAS_BATTERY_LEVEL, 
                                                                        sizeof(uint8_t), &Battery);
    return apiResult;
}


/************************************************************************************************
    Hjælpe funktion til at sende POWER
*************************************************************************************************/
cy_en_ble_api_result_t BLE_SetCharacteristicValue(POPE_char_index_t charIndex, uint16_t attrSize, uint8_t *attrValue)
{
    cy_en_ble_api_result_t apiResult = CY_BLE_SUCCESS;

    if(charIndex >= POPE_CHAR_COUNT)
    {
        apiResult = CY_BLE_ERROR_INVALID_PARAMETER;
    }
    else
    {
        /* Store data in database */
        cy_stc_ble_gatts_db_attr_val_info_t dbAttrValInfo =
        {
            .handleValuePair.attrHandle = cy_ble_customConfigPtr->customs->customServInfo[charIndex].customServCharHandle, //cy_ble_cpsConfigPtr->cpss->charInfo[charIndex].charHandle,
            .handleValuePair.value.len  = attrSize,
            .handleValuePair.value.val  = attrValue,
            .offset                     = 0u,
            .flags                      = CY_BLE_GATT_DB_LOCALLY_INITIATED
        };

        if(Cy_BLE_GATTS_WriteAttributeValueCCCD(&dbAttrValInfo) != CY_BLE_GATT_ERR_NONE)
        {
            apiResult = CY_BLE_ERROR_INVALID_PARAMETER;
        }
    }
    return(apiResult);
}

/* [] END OF FILE */