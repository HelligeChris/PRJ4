#include "kadenceControl.h"
#include <stdint.h>

float scaleFactor = 0;  //Divider
int16_t CGX;            //Gyroscope x-axis values
char uart_string[50];   //UART debugging

void CS_initKadenceSensor(uint8 FSR)
{
    I2C_MPU6050_Start();//Start the SC I2C
    MPU6050_init();     //Initialize MPU6050
	MPU6050_initialize();
    MPU6050_setFullScaleGyroRange(FSR);
    //MPU6050_setDLPFMode(4); // Setting the LPF at 5Hz both Gyro and temoperature for 9250
}

//Returnerer RPM[0], frekvens[1] og periode[2].
//RPM = retur, frekvens = retur+1, periode = retur+2
float* CS_getKadence()
{
    static float kadenceArr[3];
    
    /* Get data from the MPU */
    CGX = MPU6050_getRotationX();
    
    int G_Range = MPU6050_getFullScaleGyroRange();
    
    if      (G_Range == 0) {scaleFactor = 131;}
    else if (G_Range == 1) {scaleFactor = 65.5;}
    else if (G_Range == 2) {scaleFactor = 32.8;}
    else if (G_Range == 3) {scaleFactor = 16.4;}
    
    float degS = CGX/scaleFactor;
    
    float RPM = fabs(degS/6);
    float f = fabs(RPM/60);
    float T = fabs(1/f);
    
    kadenceArr[0] = RPM;
    kadenceArr[1] = f;
    kadenceArr[2] = T;
    
    #if DEBUG_UART_ENABLED
    //UARTprint("1", "Kadence-control:");
    //Gyroscope values debug
    //sprintf(uart_string, "X value: %i",CGX);
    //UARTprint("2", uart_string);
    //Debugging - Print Gyroscope range
    //sprintf(uart_string, "Gyroscope range: %i", G_Range);
    //UARTprint("4", uart_string);
    //Debugging - Print Scale Factor
    //sprintf(uart_string, "Scale Factor:  X: %f", scaleFactor);
    //UARTprint("5", uart_string);
    //Debugging - Print Degrees/sec
    //sprintf(uart_string, "Degrees/sec X: %f", degS);
    //UARTprint("7", uart_string);
    //Debugging - Print RPM, frekvens og periode
//    sprintf(uart_string, "RPM: %f", RPM);
//    UARTprint("2", uart_string);
//    sprintf(uart_string, "Hz: %f", f);
//    UARTprint("3", uart_string);  
//    sprintf(uart_string, "T: %f", T);
//    UARTprint("4", uart_string);
    #endif
    
    return kadenceArr;
}


/** Default constructor, uses default I2C address.
 * @see MPU6050_DEFAULT_ADDRESS
 */
void MPU6050_init() {
    devAddr = MPU6050_DEFAULT_ADDRESS;
}
/** Specific address constructor.
 * @param address I2C address
 * @see MPU6050_DEFAULT_ADDRESS
 * @see MPU6050_ADDRESS_AD0_LOW
 * @see MPU6050_ADDRESS_AD0_HIGH
 */
/** Power on and prepare for general usage.
 * This will activate the device and take it out of sleep mode (which must be done
 * after start-up). This function also sets both the accelerometer and the gyroscope
 * to their most sensitive settings, namely +/- 2g and +/- 250 degrees/sec, and sets
 * the clock source to use the X Gyro for reference, which is slightly better than
 * the default internal clock source.
 */
void MPU6050_initialize() {
    MPU6050_setClockSource(MPU6050_CLOCK_PLL_XGYRO);
    MPU6050_setFullScaleGyroRange(MPU6050_GYRO_FS_250);
//    MPU6050_setFullScaleAccelRange(MPU6050_ACCEL_FS_2);
    MPU6050_setSleepEnabled(false); // thanks to Jack Elston for pointing this one out!
}
/** Set digital low-pass filter configuration.
 * @param mode New DLFP configuration setting
 * @see getDLPFBandwidth()
 * @see MPU6050_DLPF_BW_256
 * @see MPU6050_RA_CONFIG
 * @see MPU6050_CFG_DLPF_CFG_BIT
 * @see MPU6050_CFG_DLPF_CFG_LENGTH
 */
void MPU6050_setDLPFMode(uint8_t mode) {
    I2CWriteBits(devAddr, MPU6050_RA_CONFIG, MPU6050_CFG_DLPF_CFG_BIT, MPU6050_CFG_DLPF_CFG_LENGTH, mode);
}
// GYRO_CONFIG register
/** Get full-scale gyroscope range.
 * The FS_SEL parameter allows setting the full-scale range of the gyro sensors,
 * as described in the table below.
 *
 * <pre>
 * 0 = +/- 250 degrees/sec
 * 1 = +/- 500 degrees/sec
 * 2 = +/- 1000 degrees/sec
 * 3 = +/- 2000 degrees/sec
 * </pre>
 *
 * @return Current full-scale gyroscope range setting
 * @see MPU6050_GYRO_FS_250
 * @see MPU6050_RA_GYRO_CONFIG
 * @see MPU6050_GCONFIG_FS_SEL_BIT
 * @see MPU6050_GCONFIG_FS_SEL_LENGTH
 */
uint8_t MPU6050_getFullScaleGyroRange() {
    I2CReadBits(devAddr, MPU6050_RA_GYRO_CONFIG, MPU6050_GCONFIG_FS_SEL_BIT, MPU6050_GCONFIG_FS_SEL_LENGTH, buffer);
    return buffer[0];
}
/** Set full-scale gyroscope range.
 * @param range New full-scale gyroscope range value
 * @see getFullScaleRange()
 * @see MPU6050_GYRO_FS_250
 * @see MPU6050_RA_GYRO_CONFIG
 * @see MPU6050_GCONFIG_FS_SEL_BIT
 * @see MPU6050_GCONFIG_FS_SEL_LENGTH
 */
void MPU6050_setFullScaleGyroRange(uint8_t range) {
    I2CWriteBits(devAddr, MPU6050_RA_GYRO_CONFIG, MPU6050_GCONFIG_FS_SEL_BIT, MPU6050_GCONFIG_FS_SEL_LENGTH, range);
}
/** Get X-axis gyroscope reading.
 * @return X-axis rotation measurement in 16-bit 2's complement format
 * @see getMotion6()
 * @see MPU6050_RA_GYRO_XOUT_H
 */
int16_t MPU6050_getRotationX() {
    I2CReadBytes(devAddr, MPU6050_RA_GYRO_XOUT_H, 2, buffer);
    
    return (((int16_t)buffer[0]) << 8) | buffer[1];
}
/** Set sleep mode status.
 * @param enabled New sleep mode enabled status
 * @see getSleepEnabled()
 * @see MPU6050_RA_PWR_MGMT_1
 * @see MPU6050_PWR1_SLEEP_BIT
 */
void MPU6050_setSleepEnabled(bool enabled) {
    I2CWriteBit(devAddr, MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_SLEEP_BIT, enabled);
}
/** Set clock source setting.
 * An internal 8MHz oscillator, gyroscope based clock, or external sources can
 * be selected as the MPU-60X0 clock source. When the internal 8 MHz oscillator
 * or an external source is chosen as the clock source, the MPU-60X0 can operate
 * in low power modes with the gyroscopes disabled.
 *
 * Upon power up, the MPU-60X0 clock source defaults to the internal oscillator.
 * However, it is highly recommended that the device be configured to use one of
 * the gyroscopes (or an external clock source) as the clock reference for
 * improved stability. The clock source can be selected according to the following table:
 *
 * <pre>
 * CLK_SEL | Clock Source
 * --------+--------------------------------------
 * 0       | Internal oscillator
 * 1       | PLL with X Gyro reference
 * 2       | PLL with Y Gyro reference
 * 3       | PLL with Z Gyro reference
 * 4       | PLL with external 32.768kHz reference
 * 5       | PLL with external 19.2MHz reference
 * 6       | Reserved
 * 7       | Stops the clock and keeps the timing generator in reset
 * </pre>
 *
 * @param source New clock source setting
 * @see getClockSource()
 * @see MPU6050_RA_PWR_MGMT_1
 * @see MPU6050_PWR1_CLKSEL_BIT
 * @see MPU6050_PWR1_CLKSEL_LENGTH
 */
void MPU6050_setClockSource(uint8_t source) {
    I2CWriteBits(devAddr, MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_CLKSEL_BIT, MPU6050_PWR1_CLKSEL_LENGTH, source);
}
