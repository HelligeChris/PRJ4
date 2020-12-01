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
#include "ADCserial.h"
#include "stdio.h"

//Data længde fra HX711
#define SIZE 24

//Defination af states
typedef enum
{
    Sending_DATA,
    Done,
}state;
state DataRX;

//Default gain = 128
int gain_ = 50;
int counter = 0;

signed int Datain[SIZE] = {0};
int Dataindex = 0;

void inv_pin()
{
    //Invertere Sck Pin
    if (Pin_SCK_Read())
    {
        Pin_SCK_Write(0);
    }else{
        Pin_SCK_Write(1);
    }
}

CY_ISR(isr_timer_handler)
{
    Timer_1_Stop();
    
    //Stopper dataoverførelse og bestemmer hvilket gain næste dataoverførelse har
    if (counter == (gain_))
    {
        Timer_1_Stop();
        Pin_DIN_Write(1);
        DataRX = Done;
        Pin_SCK_Write(0);
        return;
    }
    
    
    inv_pin();
    
    //Læser de første 24 databit
    if ((!Pin_SCK_Read()) && (counter < (SIZE*2)))
    {
        Datain[Dataindex] = Pin_DIN_Read();
        Dataindex++;
    }
    
    counter++;
    Timer_1_Start();
}

int* send(int gain, uint period_ns)
{
    //Sætter puls længde
    Timer_1_WritePeriod((int)(period_ns/1000)*12*2);
    
    //Sikre gain ikke kan være en ugyldig værdig
    if (gain == 128)
    {
        gain_ = 25*2;
        
    }else if( gain == 64)
    {
        gain_ = 27*2;
    }else if( gain == 32)
    {
        gain_ = 26*2;
    }
    
    //Venter på HX711 er klar til at sende/modtage data
    while(Pin_DIN_Read());
    DataRX = Sending_DATA;

    //Initialisere dataoverførelse
    Dataindex = 0;
    counter = 0;
    Pin_SCK_Write(0);
    Timer_1_WriteCounter(0);
    //Starter dataoverførelse
    Timer_1_Start();
    //Venter på dataoverførelse er afsluttet
    while(DataRX == Sending_DATA);
    //Sikre Pin SCK er lav for at undgå at slukke HX711
    Pin_SCK_Write(0);
    
    return Datain;
}

void ADC_init()
{
    Timer_1_Init();
    isr_timer_StartEx(isr_timer_handler);
    Pin_SCK_Write(0);
    Pin_DIN_Write(0);
    
    //Sætter gain til 128
    send(128, 15000);
}

signed int ADC_read()
{
    //Modtager data fra HX711
    int* Data = send(128, 15000);
    int x = 0;
    
    //Konvertere fra unsigned int 24bit til signed int 32bit
    //Dette gøres da der ingen 24bit type er i c
    for(unsigned int i = 1; i <= SIZE; i++)
    {
        //Int array lægges over i enkelt variabel
        x += Data[SIZE - i]<< (i-1);
    }
    
    //Tjekker om tallet er negativt(1) eller positivt(0)
    if (Datain[0])
    {
        //Konvertere fra unsigned int 24bit til signed int 32bit
        x |= 0xFF<<24;
    }
    
    return x;
}