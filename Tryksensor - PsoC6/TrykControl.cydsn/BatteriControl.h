#pragma once
#include "project.h"

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
    return mV;
}