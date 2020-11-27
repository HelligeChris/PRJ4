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
#include "project.h"
#include "common.h"

int main(void)
{
    __enable_irq(); /* Enable global interrupts. */

    #if(CY_BLE_CONFIG_HOST_CORE == CY_BLE_CORE_CORTEX_M0P)
    {
        Cy_SysEnableCM4(CY_CORTEX_M4_APPL_ADDR); 
        HostMain();
    }
    #else
    {
        #if(CY_BLE_STACK_MODE_IPC)
        {
            Cy_BLE_Start(NULL);
        }
        #endif
        Cy_SysEnableCM4(CY_CORTEX_M4_APPL_ADDR);
        
        for(;;)
        {
            #if(CY_BLE_STACK_MODE_IPC)
            {
               Cy_BLE_ProcessEvents();
               Cy_SysPm_DeepSleep(CY_SYSPM_WAIT_FOR_INTERRUPT);
            } 
            #endif
        }
        #endif
    
    }
    
    
    
    

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;)
    {
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
