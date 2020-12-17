#pragma once
#include "project.h"
#include "VT100Terminal.h"

uint16 mV;

uint16 getVoltageLevel_mV();

uint16 getVoltageLevel_mV()
{
    //Starter Batteri ADC konvertering
    Batteri_ADC_Start();
    Batteri_ADC_StartConvert();
    //Venter på Batteri ADC konvertering er færdig
    Batteri_ADC_IsEndConversion(1);
    //Stopper ADC konvertering
    Batteri_ADC_StopConvert();
    //Konvertere resultatet fra Batteri ADC til mV
    mV = Batteri_ADC_CountsTo_mVolts(0, Batteri_ADC_GetResult16(0));
    //Stopper Batteri ADC
    Batteri_ADC_Stop();
    
    char buf[40];
    sprintf(buf, "%d mV\r\n", mV);
    UARTprint("2", buf);
    
    mV = ((mV-3000.0) / (4200.0-3000.0)) * 100;  
    return mV;
}