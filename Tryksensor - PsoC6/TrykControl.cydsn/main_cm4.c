#include "project.h"
#include "VT100Terminal.h"
#include "trykControl.h"
#include "stdio.h"

CY_ISR_PROTO(ISR_UART_rx_handler);
void handleByteReceived(uint8_t byteReceived);

CY_ISR(ISR_UART_rx_handler)
{
    uint8_t bytesToRead = UART_1_GetRxBufferSize();
    while (bytesToRead > 0)
    {
        uint8_t byteReceived = UART_1_ReadRxData();
        UART_1_WriteTxData(byteReceived); // echo back    
        bytesToRead--;
    }
}

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    isr_uart_rx_StartEx(ISR_UART_rx_handler);
    UART_1_Start();
    UART_1_PutString("Startup\n\r");
    initTrykSensor();
    
    
    char buf[40] = {0};
    for(;;)
    {   
        CyDelay(200);
        //sprintf(buf, "%li\r\n", ADC_read());
        sprintf(buf, "%lu\r\n", getVaegt(100));
        UART_1_PutString(buf);
        /* Place your application code here. */
    }
}