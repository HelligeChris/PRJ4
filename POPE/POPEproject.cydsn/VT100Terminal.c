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

/* [] END OF FILE */
#include "VT100Terminal.h"

void delline(int numberoflines)
{
        for(int i = 0; i < numberoflines; i++) 
    {
        UART_DEB_PutString("\x1b[2K");
    }
}

void movecursor(char* y, char* x)
{
    UART_DEB_PutString("\x1b[");
    UART_DEB_PutString(y);
    UART_DEB_PutString(";");
    UART_DEB_PutString(x);
    UART_DEB_PutString("f");
}

void UARTprint(char* line, char* string)
{
    movecursor(line, "0");
    delline(1);
    movecursor(line, "0");
    UART_DEB_PutString(string);
}

void clearTerm(int lines)
{
    char buf[10];
        for(int i = 0;i < lines; i++)
    {
        
        snprintf(buf, 5, "%d", i);
        
        movecursor(buf, "0");
        delline(1);
    }
}