
#include "trykControl.h"
#include "stdlib.h"

int32 vaegt = 0;
int fs = 80;

typedef enum{
    Running,
    Done
}state;
state sampleControl;

int32 *dataPtr;
float dataFilterPtr[100] = {0};
int samples;
int sampleCounter = 0;
int readDataFlag = 0;

CY_ISR(sampleEvent_handler)
{
    if(samples < sampleCounter)
    {
        SampleTimer_Stop();;
        sampleControl = Done;
        return;   
    }
    
    readDataFlag = 1;
}

float a[3] = {
    1,
    -1.29343135,
    0.49
};

float b[3] = {
    1,
    10,
    25
};

float* filter(int32* trykdata)
{    
    //realloc(dataFilterPtr, sizeof(float)*samples);
    float ymem[2] = {0};
    float xmem[2] = {0};
    
    for(int i = 0; i<samples; i++)
    {
        dataFilterPtr[i] = b[0]*trykdata[i] + b[1]*xmem[0] + b[2]*xmem[1]
                 - a[1]*ymem[0] - a[2]*ymem[1];
        xmem[1] = xmem[0];
        xmem[0] = trykdata[i];
        
        ymem[1] = ymem[0];
        ymem[0] = dataFilterPtr[i] * 0.00547;
        
        dataFilterPtr[i] = ymem[0];
    }
    
    return dataFilterPtr;
}

void initTrykSensor()
{
    ADC_init(128);
    sampleEvent_StartEx(sampleEvent_handler);
    SampleTimer_Init();
    
    //dataFilterPtr = malloc(sizeof(float));
    dataPtr = malloc(sizeof(int32));
}
void calibrateTrykSensor()
{
    
}

uint32 getVaegt(uint16 periode_ms)
{
    samples = (periode_ms * fs)/1000;
    realloc(dataPtr, sizeof(int32)*samples);
    
    
    
    SampleTimer_ClearFIFO();
    sampleCounter = 0;
    readDataFlag = 0;
    SampleTimer_Start();
    sampleControl = Running;
    
    while(sampleControl != Done)
    {
        if(readDataFlag)
        {
            dataPtr[sampleCounter] = ADC_read();
            sampleCounter++;
            readDataFlag = 0;
            
        }
    }
    //filter(dataPtr);

    vaegt = 0;
    for(int i = 0; i<samples; i++)
    {
        vaegt += dataPtr[i];
    }
    vaegt /= samples;
    
    for(int i = 0; i<samples; i++)
    {
        dataPtr[i] -= vaegt;
    }
    
    
    vaegt = 0;
    for(int i = 0; i<samples; i++)
    {
        vaegt += abs(dataPtr[i]);
    }
    vaegt /= samples;
    return vaegt;
}