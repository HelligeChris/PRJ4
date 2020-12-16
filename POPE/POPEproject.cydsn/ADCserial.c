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
int period_ns_;

signed int Datain[SIZE] = {0};
int Dataindex = 0;

void inv_pin()
{
    //Invertere Sck Pin
    if (Cy_GPIO_Read(Pin_SCK_0_PORT, Pin_SCK_NUM))
    {
        Cy_GPIO_Write(Pin_SCK_0_PORT, Pin_SCK_0_NUM, 0);
    }else{
        Cy_GPIO_Write(Pin_SCK_0_PORT, Pin_SCK_0_NUM, 1);
    }
}

void isr_timer_handler()
{
    
    //Stopper dataoverførelse og bestemmer hvilket gain næste dataoverførelse har
    if (counter == (gain_))
    {
        ADC_Timer_Disable();
        ADC_Timer_ClearInterrupt(isr_timer_cfg.intrSrc);
        Cy_GPIO_Write(Pin_DIN_0_PORT, Pin_DIN_0_NUM, 1);
        DataRX = Done;
        Cy_GPIO_Write(Pin_SCK_0_PORT, Pin_SCK_0_NUM, 0);
        return;
    }
    ADC_Timer_SetPeriod((int)(period_ns_/100)-1);

    inv_pin();
    
    //Læser de første 24 databit
    if ((!Cy_GPIO_Read(Pin_SCK_0_PORT, Pin_SCK_NUM)) && (counter < (SIZE*2)))
    {
        Datain[Dataindex] = Cy_GPIO_Read(Pin_DIN_0_PORT, Pin_DIN_0_NUM);
        Dataindex++;
    }
    
    counter++;
}

int* send(int gain, uint period_ns)
{
    //Sætter puls længde
    period_ns_ = period_ns;
    ADC_Timer_SetPeriod((int)(period_ns_/100)-1);

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
    while(Cy_GPIO_Read(Pin_DIN_0_PORT, Pin_DIN_0_NUM));
    DataRX = Sending_DATA;

    //Initialisere dataoverførelse
    Dataindex = 0;
    counter = 0;
    Cy_GPIO_Write(Pin_SCK_0_PORT, Pin_SCK_0_NUM, 0);
    ADC_Timer_SetCounter(0);
    //Starter dataoverførelse
    ADC_Timer_Start();
    //Venter på dataoverførelse er afsluttet
    while(DataRX == Sending_DATA);
    //Sikre Pin SCK er lav for at undgå at slukke HX711
    Cy_GPIO_Write(Pin_SCK_0_PORT, Pin_SCK_0_NUM, 0);
    
    return Datain;
}

void ADC_init()
{
    Cy_SysInt_Init(&isr_timer_cfg, isr_timer_handler);
    NVIC_EnableIRQ(isr_timer_cfg.intrSrc);
    
    Cy_GPIO_Write(Pin_SCK_0_PORT, Pin_SCK_0_NUM, 0);
    Cy_GPIO_Write(Pin_DIN_0_PORT, Pin_DIN_0_NUM, 0);
    
    //Sætter gain til 128
    send(128, 15000);
}

int32 ADC_read()
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