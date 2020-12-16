# THIS FILE IS AUTOMATICALLY GENERATED
# Project: C:\Users\cring\Documents\GitHub\PRJ4\POPE\POPEproject.cydsn\POPEproject.cyprj
# Date: Wed, 16 Dec 2020 16:56:58 GMT
#set_units -time ns
create_clock -name {CyWCO} -period 30517.578125 -waveform {0 15258.7890625} [list [get_pins {ClockBlock/wco}]]
create_clock -name {CyClk_LF} -period 30517.578125 -waveform {0 15258.7890625} [list [get_pins {ClockBlock/lfclk}]]
create_clock -name {CyILO} -period 31250 -waveform {0 15625} [list [get_pins {ClockBlock/ilo}]]
create_clock -name {CyFLL} -period 10 -waveform {0 5} [list [get_pins {ClockBlock/fll}]]
create_clock -name {CyClk_HF0} -period 10 -waveform {0 5} [list [get_pins {ClockBlock/hfclk_0}]]
create_clock -name {CyClk_Fast} -period 10 -waveform {0 5} [list [get_pins {ClockBlock/fastclk}]]
create_clock -name {CyClk_Peri} -period 20 -waveform {0 10} [list [get_pins {ClockBlock/periclk}]]
create_generated_clock -name {CyClk_Slow} -source [get_pins {ClockBlock/periclk}] -edges {1 2 3} [list [get_pins {ClockBlock/slowclk}]]
create_generated_clock -name {Clock_2} -source [get_pins {ClockBlock/periclk}] -edges {1 3 5} -nominal_period 50 [list [get_pins {ClockBlock/ff_div_11}]]
create_generated_clock -name {Clock_1} -source [get_pins {ClockBlock/periclk}] -edges {1 11 21} [list [get_pins {ClockBlock/ff_div_12}]]
create_generated_clock -name {Batteri_ADC_intSarClock} -source [get_pins {ClockBlock/periclk}] -edges {1 51 101} [list [get_pins {ClockBlock/ff_div_49}]]
create_generated_clock -name {Clock_3} -source [get_pins {ClockBlock/periclk}] -edges {1 501 1001} [list [get_pins {ClockBlock/ff_div_13}]]
create_generated_clock -name {UART_DEB_SCBCLK} -source [get_pins {ClockBlock/periclk}] -edges {1 33 67} [list [get_pins {ClockBlock/ff_div_5}]]
create_generated_clock -name {I2C_MPU6050_SCBCLK} -source [get_pins {ClockBlock/periclk}] -edges {1 33 65} [list [get_pins {ClockBlock/ff_div_6}]]
create_clock -name {CyPeriClk_App} -period 20 -waveform {0 10} [list [get_pins {ClockBlock/periclk_App}]]
create_clock -name {CyIMO} -period 125 -waveform {0 62.5} [list [get_pins {ClockBlock/imo}]]


# Component constraints for C:\Users\cring\Documents\GitHub\PRJ4\POPE\POPEproject.cydsn\TopDesign\TopDesign.cysch
# Project: C:\Users\cring\Documents\GitHub\PRJ4\POPE\POPEproject.cydsn\POPEproject.cyprj
# Date: Wed, 16 Dec 2020 16:56:30 GMT
