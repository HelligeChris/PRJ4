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

int main(void)
{
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    if (Cy_SysPm_IoIsFrozen())
    {
        Cy_SysPm_IoUnfreeze();
    }
   
     __enable_irq(); /* Enable global interrupts. */

    #if (CY_BLE_CONFIG_HOST_CORE == CY_BLE_CORE_CORTEX_M4)
    {
        HostMain();
    }
    
    #else
    for(;;)
    {
        Cy_SysPm_DeepSleep(CY_SYSPM_WAIT_FOR_INTERRUPT);
    }
    #endif
  
}

/* [] END OF FILE */
