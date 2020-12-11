
#pragma once
#include "common.h"

typedef struct kadenceCtrl
{
    uint16 kadence;
    int loop;            // Averaging variable
    int FullScaleRange;    // Between 0-3 with 3 being maximum.
    float scaleFactor;      // Divider
    int16_t CGX;               //Gyroscope X-value
    char uart_String[50];       //UART string for debugging

}kadenceCtrl;

void CS_initKadenceSensor(uint8_t FSR);
float* CS_getKadence();

uint8_t devAddr;
uint8_t buffer[22];
int16_t MPU6050_getRotationX();

void MPU6050_initialize(uint8_t FSR);
void MPU6050_setSleepEnabled(bool enabled);
void MPU6050_getRotation(int16_t* x, int16_t* y, int16_t* z);
uint8_t MPU6050_getFullScaleGyroRange();
void MPU6050_setFullScaleGyroRange(uint8_t range);
void MPU6050_setDLPFMode(uint8_t bandwidth);
void MPU6050_setClockSource(uint8_t source);

#define MPU6050_DEFAULT_ADDRESS         0x68
#define MPU6050_RA_GYRO_CONFIG          0x1B
#define MPU6050_RA_PWR_MGMT_1           0x6B
#define MPU6050_RA_GYRO_XOUT_H          0x43
#define MPU6050_GCONFIG_FS_SEL_LENGTH   2
#define MPU6050_GCONFIG_FS_SEL_BIT      4
#define MPU6050_PWR1_SLEEP_BIT          6
#define MPU6050_PWR1_CLKSEL_BIT         2
#define MPU6050_PWR1_CLKSEL_LENGTH      3
#define MPU6050_CLOCK_PLL_XGYRO         0x01
#define MPU6050_GYRO_FS_250             0x00
#define MPU6050_RA_CONFIG               0x1A
#define MPU6050_CFG_DLPF_CFG_BIT        2
#define MPU6050_CFG_DLPF_CFG_LENGTH     3