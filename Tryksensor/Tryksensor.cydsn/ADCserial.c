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

#define SIZE 24

typedef enum
{
    Sending_DATA,
    Done,
}state;

state DataRX;

int gain_ = 25;
int counter = 0;

signed int Datain[SIZE] = {0};
int Dataindex = 0;

void inv_pin()
{
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
    
    if (counter == (gain_))
    {
        Timer_1_Stop();
        Pin_DIN_Write(1);
        DataRX = Done;
        Pin_SCK_Write(0);
        return;
    }

    
    inv_pin();
    if ((!Pin_SCK_Read()) && (counter < (SIZE)))
    {
        Datain[Dataindex] = Pin_DIN_Read();
        Dataindex++;
    }
    
    
    counter++;
    Timer_1_Start();
}

int* send(int gain, uint period_ns)
{
    Timer_1_WritePeriod((int)(period_ns/1000)*12);
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
    
    while(Pin_DIN_Read());
    DataRX = Sending_DATA;
    
    Dataindex = 0;
    counter = 0;
    Pin_SCK_Write(0);
    Timer_1_ClearFIFO();
    Timer_1_Start();
    while(DataRX == Sending_DATA);
    Pin_SCK_Write(0);
    
    
    return Datain;
}

void ADC_init()
{
    Timer_1_Init();
    isr_timer_StartEx(isr_timer_handler);
    Pin_SCK_Write(0);
    
    send(128, 1000);
}

signed int ADC_read()
{
    int* Data = send(128, 1000);
    int x = 0;
    for(unsigned int i = 1; i <= SIZE; i++)
    {
        x += Data[SIZE - i]<< (i-1);
    }
    
    if (Datain[0])
    {
        x |= 0xFF<<24;
    }
    
    return x;
}



/*
#include "ADCserial.h"
#include "stdio.h"

#define SIZE 24

typedef enum
{
    State_Init,
    State_Data,
}state;

typedef enum
{
    Reading_DATA,
    Sending_DATA,
    Done,
}state2;

state2 DataRX;
state states;

int gain_ = 25;
int counter = 0;
int counter2 = 0;

signed int Datain[SIZE] = {0};
int Dataindex = 0;

void inv_pin()
{
    if (Pin_SCK_Read())
    {
        Pin_SCK_Write(0);
    }else{
        Pin_SCK_Write(1);
    }
}

CY_ISR(isr_timer_handler)
{
    
    switch(states)
    {
        case State_Init:
        {
            Timer_1_Stop();

            inv_pin();
            if (counter == (gain_*2-2))
            {
                Timer_1_Stop();
                DataRX = Done;
                break;
            }
            counter++;
            Timer_1_Start();
        }
        break;
        
        case State_Data:
        {
            Timer_1_Stop();
            
            if (counter == (gain_*2*2))
            {
                Timer_1_Stop();
                Pin_DIN_Write(1);
                DataRX = Done;
                Pin_SCK_Write(0);
                break;
            }

            
            if (counter2 == 0)
            {
                inv_pin();
                if ((!Pin_SCK_Read()) && (counter < (SIZE*2*2)))
                {
                    Datain[Dataindex] = Pin_DIN_Read();
                    Dataindex++;
                }
            
                counter2 = 2;
            }
            counter2--;

            counter++;
            Timer_1_Start();
        }
        break;
    }
}

void ADC_init(int gain)
{
    if (gain == 128)
    {
        gain_ = 25;
        
    }else if( gain == 64)
    {
        gain_ = 27;
    }else if( gain == 32)
    {
        gain_ = 26;
    }
    
    Timer_1_Init();
    isr_timer_StartEx(isr_timer_handler);
    Pin_SCK_Write(0);
    
    states = State_Init;
    while(Pin_DIN_Read());
    
    DataRX = Sending_DATA;
    counter = 0;
    Pin_SCK_Write(0);
    Timer_1_ClearFIFO();
    Timer_1_Start();
    
    while(DataRX == Sending_DATA);
    
    
}

signed int ADC_read()
{
    states = State_Data;
    
    while(Pin_DIN_Read());
    DataRX = Reading_DATA;
    
    Dataindex = 0;
    counter = 0;
    Pin_SCK_Write(0);
    Timer_1_ClearFIFO();
    Timer_1_Start();
    
    while(DataRX == Reading_DATA);
    
    int x = 0;
    for(unsigned int i = 1; i <= SIZE; i++)
    {
        x += Datain[SIZE - i]<< (i-1);
    }
    
    if (Datain[0])
    {
        x |= 0xFF<<24;
    }
    
    return x;
}



*/

