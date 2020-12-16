#include "project.h"
#include "VT100Terminal.h"
#include "trykControl.h"
#include "stdio.h"
#include "BatteriControl.h"


void ISR_UART_rx_handler()
{
    uint8_t bytesToRead = UART_1_GetNumInRxFifo();
    while (bytesToRead > 0)
    {
        uint8_t byteReceived = UART_1_Get();
        UART_1_Put(byteReceived); // echo back  
        bytesToRead--;
    }
}

int main(void)
{
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    __enable_irq();
    Cy_SysInt_Init(&UART_1_SCB_IRQ_cfg, ISR_UART_rx_handler);
    NVIC_EnableIRQ(UART_1_SCB_IRQ_cfg.intrSrc);
    UART_1_Start();
    UART_1_PutString("Startup\n\r");
    initTrykSensor();
    
    char buf[40] = {0};
    for(;;)
    {   
        CyDelay(200);
        //sprintf(buf, "%i\r\n", ADC_read());
        sprintf(buf, "%i\r\n", getVaegt(100));
        //sprintf(buf, "%d\r\n", getVoltageLevel_mV());
        UARTprint(buf);
        /* Place your application code here. */
    }
}