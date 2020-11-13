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

int Datain[24] = {0};
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

CY_ISR(isr_timer)
{
    
    switch(states)
    {
        case State_Init:
        {
            Timer_1_Stop();

            inv_pin();
            if (counter == gain_)
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

            
            if (counter2 == 0)
            {
            inv_pin();
            if (!Pin_SCK_Read())
            {
                Datain[Dataindex] = Pin_DIN_Read();
                Dataindex++;
            }
            
            counter2 = 2;
            }
            counter2--;
            
            if (counter == gain_)
            {
                Timer_1_Stop();
                DataRX = Done;
                break;
            }
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
    }
    states = State_Init;
    while(Pin_DIN_Read());
    
    counter = 0;
    Pin_SCK_Write(0);
    Timer_1_ClearFIFO();
    Timer_1_Start();
    
    while(DataRX == Sending_DATA);
    
    
}

int ADC_read()
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
    
}


