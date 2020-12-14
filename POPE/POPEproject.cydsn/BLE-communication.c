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

#if  DEBUG_UART_ENABLED
char uart_string[50];   //UART debugging
int count = 0;
#endif

/* BLE Private Functions */
cy_en_ble_api_result_t BLE_SetPowerCharacteristicValue(POPE_char_index_t charIndex, uint16_t attrSize, uint8_t *attrValue);


/* Timer variables */
static cy_stc_ble_timer_info_t BLEtimerParam = { .timeout = 1u};
static volatile uint8_t BLEmainTimer = 1u;

/* Power Array */
uint8_t powerArray[2] = {0};


/* Callback function */
void BLE_EventHandler(uint32_t event, void *eventParam)
{
    UARTprint("6", "BLE:");
    switch(event)
    {
        case CY_BLE_EVT_STACK_ON:
            #if DEBUG_UART_ENABLED
            sprintf(uart_string, "Stack On \r \n ");
            UARTprint("7", uart_string);
            #endif
            Cy_BLE_GAPP_StartAdvertisement(CY_BLE_ADVERTISING_FAST, CY_BLE_PERIPHERAL_CONFIGURATION_0_INDEX);
            //Cy_BLE_GAP_GetBdAddress();
            break;
            
        case CY_BLE_EVT_GAP_DEVICE_DISCONNECTED: //Til debugging. Går ind i denne case når link er etableret.
            Cy_BLE_GAPP_StartAdvertisement(CY_BLE_ADVERTISING_FAST, CY_BLE_PERIPHERAL_CONFIGURATION_0_INDEX);
            #if DEBUG_UART_ENABLED
            sprintf(uart_string, "Device link connected \r \n ");
            UARTprint("7", uart_string);
            #endif
            break;
           
        case CY_BLE_EVT_TIMEOUT: 
            #if DEBUG_UART_ENABLED
            count++;
            sprintf(uart_string, "Timeout %i", count);
            UARTprint("7", uart_string);
            #endif
            if((((cy_stc_ble_timeout_param_t *)eventParam)->reasonCode == CY_BLE_GENERIC_APP_TO) && 
               (((cy_stc_ble_timeout_param_t *)eventParam)->timerHandle == BLEtimerParam.timerHandle)) //timeoutval == current timer val
            {
                BLEmainTimer++;
            }
            break;
            
        case CY_BLE_EVT_STACK_SHUTDOWN_COMPLETE:
            #if DEBUG_UART_ENABLED
            sprintf(uart_string, "Stack shutdown");
            UARTprint("7", uart_string);
            #endif
            Cy_SysPm_Hibernate();
            break;
            
        case CY_BLE_EVT_GAPP_ADVERTISEMENT_START_STOP:
            #if DEBUG_UART_ENABLED
            sprintf(uart_string, "Advertisement start/stop");
            UARTprint("7", uart_string);
            #endif
            if(Cy_BLE_GetAdvertisementState() == CY_BLE_ADV_STATE_STOPPED)
            {
                Cy_BLE_Stop();
                //evt deep sleep?
            }
            break;
        
        default:
            #if DEBUG_UART_ENABLED
            UARTprint("7", "Default");
            #endif
            break;
    }
}


bool BLE_checkTimer(){
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
    
    apiResult = BLE_SetPowerCharacteristicValue(POPE_POWER_MEASURE, sizeof(uint8)*2, (uint8_t*)&powerArray);
    
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
cy_en_ble_api_result_t BLE_SetPowerCharacteristicValue(POPE_char_index_t charIndex, uint16_t attrSize, uint8_t *attrValue)
{
    cy_en_ble_api_result_t apiResult = CY_BLE_SUCCESS;

    if(charIndex >= POPE_CHAR_COUNT)
    {
        apiResult = CY_BLE_ERROR_INVALID_PARAMETER;
    }
    else
    {
        /* GATT service characteristic handler, size, value */
        cy_stc_ble_gatts_db_attr_val_info_t dbAttrValInfo =
        {
            .handleValuePair.attrHandle = cy_ble_customConfigPtr->customs->customServInfo[charIndex].customServCharHandle,
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