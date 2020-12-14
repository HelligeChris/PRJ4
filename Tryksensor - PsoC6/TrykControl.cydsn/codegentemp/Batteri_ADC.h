/***************************************************************************//**
* \file     Batteri_ADC.h
* \version  3.10
*
* \brief
* Provides the source code to the API for the Batteri_ADC Component.
*
********************************************************************************
* \copyright
* (c) 2017-2018, Cypress Semiconductor Corporation. All rights reserved.
* This software, including source code, documentation and related
* materials ("Software"), is owned by Cypress Semiconductor
* Corporation ("Cypress") and is protected by and subject to worldwide
* patent protection (United States and foreign), United States copyright
* laws and international treaty provisions. Therefore, you may use this
* Software only as provided in the license agreement accompanying the
* software package from which you obtained this Software ("EULA").
* If no EULA applies, Cypress hereby grants you a personal, nonexclusive,
* non-transferable license to copy, modify, and compile the
* Software source code solely for use in connection with Cypress's
* integrated circuit products. Any reproduction, modification, translation,
* compilation, or representation of this Software except as specified
* above is prohibited without the express written permission of Cypress.
* Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO
* WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING,
* BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
* PARTICULAR PURPOSE. Cypress reserves the right to make
* changes to the Software without notice. Cypress does not assume any
* liability arising out of the application or use of the Software or any
* product or circuit described in the Software. Cypress does not
* authorize its products for use in any products where a malfunction or
* failure of the Cypress product may reasonably be expected to result in
* significant property damage, injury or death ("High Risk Product"). By
* including Cypress's product in a High Risk Product, the manufacturer
* of such system or application assumes all risk of such use and in doing
* so agrees to indemnify Cypress against all liability.
*******************************************************************************/
#if !defined(CY_Batteri_ADC_H)
#define CY_Batteri_ADC_H

#include <cy_device_headers.h>
#include <sar/cy_sar.h>

#define Batteri_ADC_VREF_ROUTED                  ((0) == 1u)
#if (Batteri_ADC_VREF_ROUTED)
#include "Batteri_ADC_vrefAMux.h"
#endif

#define Batteri_ADC_CLOCK_INTERNAL               ((1) == 1u)
#if (Batteri_ADC_CLOCK_INTERNAL)
#include "Batteri_ADC_intSarClock.h"
#endif /* Batteri_ADC_CLOCK_INTERNAL */

/**
* \addtogroup group_structures
*
*/
typedef struct
{
    uint32_t channelBase;                   /* Start of channels for the configuration */
    uint32_t numChannels;                   /* Number of channels in the configuration */
    const cy_stc_sar_config_t *hwConfigStc; /* PDL structure */
    uint32_t miscConfig;                    /* Miscellaneous configuration bits broken down as follows:
                                            [0] - Freerunning: Set if the sample mode is freerunning
                                            [2] - Mux Switch 0: Set when VSSA is used for the neg input to any single-ended channel
                                            */
#if (Batteri_ADC_CLOCK_INTERNAL)
    uint32_t clkDivider;                    /* Clock divider */
#endif /* Batteri_ADC_CLOCK_INTERNAL */

} Batteri_ADC_CONFIG_STRUCT;
/** @} structures */

/*******************************************************************************
* Function Prototypes
*******************************************************************************/
void Batteri_ADC_SelectConfig(uint32_t config, uint32_t restart);
void Batteri_ADC_InitConfig(const Batteri_ADC_CONFIG_STRUCT *config);
void Batteri_ADC_Init(void);
__STATIC_INLINE void Batteri_ADC_Enable(void);

/**
* \addtogroup group_general
* @{
*/
void Batteri_ADC_Start(void);
void Batteri_ADC_StartEx(cy_israddress userIsr);
__STATIC_INLINE void Batteri_ADC_Stop(void);
void Batteri_ADC_StartConvert(void);
__STATIC_INLINE void Batteri_ADC_StopConvert(void);
void Batteri_ADC_SetConvertMode(cy_en_sar_start_convert_sel_t mode);
void Batteri_ADC_SetEosMask(uint32_t mask);
uint32_t Batteri_ADC_IsEndConversion(cy_en_sar_return_mode_t retMode);
__STATIC_INLINE int16_t Batteri_ADC_GetResult16(uint32_t chan);
__STATIC_INLINE int32_t Batteri_ADC_GetResult32(uint32_t chan);
__STATIC_INLINE void Batteri_ADC_SetLowLimit(uint32_t lowLimit);
__STATIC_INLINE void Batteri_ADC_SetHighLimit(uint32_t highLimit);
__STATIC_INLINE void Batteri_ADC_SetLimitMask(uint32_t limitMask);
__STATIC_INLINE void Batteri_ADC_SetSatMask(uint32_t satMask);
__STATIC_INLINE cy_en_sar_status_t Batteri_ADC_SetOffset(uint32_t chan, int16_t offset);
__STATIC_INLINE cy_en_sar_status_t Batteri_ADC_SetGain(uint32_t chan, int32_t adcGain);
__STATIC_INLINE float32_t Batteri_ADC_CountsTo_Volts(uint32_t chan, int16_t adcCounts);
__STATIC_INLINE int16_t Batteri_ADC_CountsTo_mVolts(uint32_t chan, int16_t adcCounts);
__STATIC_INLINE int32_t Batteri_ADC_CountsTo_uVolts(uint32_t chan, int16_t adcCounts);

/** @} general */

void Batteri_ADC_SetChanMask(uint32_t enableMask);

/**
* \addtogroup group_power
* @{
*/
__STATIC_INLINE void Batteri_ADC_Sleep(void);
__STATIC_INLINE void Batteri_ADC_Wakeup(void);

/** @} power */

/**
* \addtogroup group_interrupt
* @{
*/
void Batteri_ADC_ISR(void);
void Batteri_ADC_IRQ_Enable(void);
void Batteri_ADC_IRQ_Disable(void);

/** @} interrupt */

/*******************************************************************************
                                  Parameters
The parameters that are set in the customizer are redefined as constants here.
*******************************************************************************/

/*  Sample Mode setting constants */
#define Batteri_ADC_TOTAL_CONFIGS                (1ul)

/* ************************************************************************** */
/* Begin configuration 0 customizer defines                                   */
/* ************************************************************************** */

#define Batteri_ADC_CFG0_SAMPLE_RATE             (100000)
#define Batteri_ADC_CFG0_CHANNEL_BASE            (0u)
#define Batteri_ADC_CFG0_CHANNEL_COUNT           (1u)
#define Batteri_ADC_CFG0_VREF_SEL_MASK           (0xc0u)
#define Batteri_ADC_CFG0_NOMINAL_CLOCK_FREQ      (16666666u)
#define Batteri_ADC_CFG0_CHANNEL_EN              (0x1u)

/* Sample Control Register */
#define Batteri_ADC_CFG0_SINGLE_ENDED_FORMAT     (0uL)
#define Batteri_ADC_CFG0_DIFFERENTIAL_FORMAT     (1uL)
#define Batteri_ADC_CFG0_SAMPLES_AVERAGED        (0uL)
#define Batteri_ADC_CFG0_RANGE_INTR_MASK         (0x0u)
#define Batteri_ADC_CFG0_SATURATE_INTR_MASK      (0x0u)
#define Batteri_ADC_CFG0_VNEG_INPUT_SEL          (7)
#define Batteri_ADC_CFG0_SINGLE_PRESENT          (0)
#define Batteri_ADC_CFG0_VREF_MV_VALUE           (1200)
#define Batteri_ADC_CFG0_APERTURE_TIME0          (153uL)
#define Batteri_ADC_CFG0_APERTURE_TIME1          (2uL)
#define Batteri_ADC_CFG0_APERTURE_TIME2          (2uL)
#define Batteri_ADC_CFG0_APERTURE_TIME3          (2uL)
#define Batteri_ADC_CFG0_FREERUNNING             (1u)
#define Batteri_ADC_CFG0_AVGERAGING_MODE         (1uL)
#define Batteri_ADC_CFG0_LOW_LIMIT               (512u)
#define Batteri_ADC_CFG0_HIGH_LIMIT              (3584u)
#define Batteri_ADC_CFG0_RANGE_COND              (0uL)
#define Batteri_ADC_CFG0_USE_SOC                 (0uL)
#define Batteri_ADC_CFG0_VREF_PWR                (3uL)
#define Batteri_ADC_CFG0_COMP_PWR                (3uL)
#define Batteri_ADC_CFG0_COMP_DLY                (3uL)

/* Clock parameters*/
#if (Batteri_ADC_CLOCK_INTERNAL)
    #define Batteri_ADC_CFG0_CLOCKDIVIDER        (((CYDEV_CLK_PERICLK__HZ) / (Batteri_ADC_CFG0_NOMINAL_CLOCK_FREQ)) - 1u)
#endif /* (Batteri_ADC_CLOCK_INTERNAL) */

/* ************************************************************************** */
/* End configuration 0 customizer defines                                     */
/* ************************************************************************** */

/* ************************************************************************** */
/* Begin configuration 1 customizer defines                                   */
/* ************************************************************************** */

#if(Batteri_ADC_TOTAL_CONFIGS > 1)
    #define Batteri_ADC_CFG1_SAMPLE_RATE             ()
    #define Batteri_ADC_CFG1_CHANNEL_BASE            (u)
    #define Batteri_ADC_CFG1_CHANNEL_COUNT           (u)
    #define Batteri_ADC_CFG1_VREF_SEL_MASK           (u)
    #define Batteri_ADC_CFG1_NOMINAL_CLOCK_FREQ      (u)
    #define Batteri_ADC_CFG1_CHANNEL_EN              (u)

    /* Sample Control Register */
    #define Batteri_ADC_CFG1_SINGLE_ENDED_FORMAT     (uL)
    #define Batteri_ADC_CFG1_DIFFERENTIAL_FORMAT     (uL)
    #define Batteri_ADC_CFG1_SAMPLES_AVERAGED        (uL)
    #define Batteri_ADC_CFG1_RANGE_INTR_MASK         (u)
    #define Batteri_ADC_CFG1_SATURATE_INTR_MASK      (u)
    #define Batteri_ADC_CFG1_VNEG_INPUT_SEL          ()
    #define Batteri_ADC_CFG1_SINGLE_PRESENT          ()
    #define Batteri_ADC_CFG1_VREF_MV_VALUE           ()
    #define Batteri_ADC_CFG1_APERTURE_TIME0          (uL)
    #define Batteri_ADC_CFG1_APERTURE_TIME1          (uL)
    #define Batteri_ADC_CFG1_APERTURE_TIME2          (uL)
    #define Batteri_ADC_CFG1_APERTURE_TIME3          (uL)
    #define Batteri_ADC_CFG1_FREERUNNING             (u)
    #define Batteri_ADC_CFG1_AVGERAGING_MODE         (uL)
    #define Batteri_ADC_CFG1_LOW_LIMIT               (u)
    #define Batteri_ADC_CFG1_HIGH_LIMIT              (u)
    #define Batteri_ADC_CFG1_RANGE_COND              (uL)
    #define Batteri_ADC_CFG1_USE_SOC                 (0uL)
    #define Batteri_ADC_CFG1_VREF_PWR                (uL)
    #define Batteri_ADC_CFG1_COMP_PWR                (uL)
    #define Batteri_ADC_CFG1_COMP_DLY                (uL)

    /* Clock parameters*/
    #if (Batteri_ADC_CLOCK_INTERNAL)
        #define Batteri_ADC_CFG1_CLOCKDIVIDER        (((CYDEV_CLK_PERICLK__HZ) / (Batteri_ADC_CFG1_NOMINAL_CLOCK_FREQ)) - 1u)
    #endif /* (Batteri_ADC_CLOCK_INTERNAL) */
#endif /* #if(Batteri_ADC_TOTAL_CONFIGS > 1) */

/* ************************************************************************** */
/* End configuration 1 customizer defines                                     */
/* ************************************************************************** */

/* ************************************************************************** */
/* Begin configuration 2 customizer defines                                         */
/* ************************************************************************** */

#if(Batteri_ADC_TOTAL_CONFIGS > 2)
    #define Batteri_ADC_CFG2_SAMPLE_RATE             ()
    #define Batteri_ADC_CFG2_CHANNEL_BASE            (u)
    #define Batteri_ADC_CFG2_CHANNEL_COUNT           (u)
    #define Batteri_ADC_CFG2_VREF_SEL_MASK           (u)
    #define Batteri_ADC_CFG2_NOMINAL_CLOCK_FREQ      (u)
    #define Batteri_ADC_CFG2_CHANNEL_EN              (u)

    /* Sample Control Register */
    #define Batteri_ADC_CFG2_SINGLE_ENDED_FORMAT     (uL)
    #define Batteri_ADC_CFG2_DIFFERENTIAL_FORMAT     (uL)
    #define Batteri_ADC_CFG2_SAMPLES_AVERAGED        (uL)
    #define Batteri_ADC_CFG2_RANGE_INTR_MASK         (u)
    #define Batteri_ADC_CFG2_SATURATE_INTR_MASK      (u)
    #define Batteri_ADC_CFG2_VNEG_INPUT_SEL          ()
    #define Batteri_ADC_CFG2_SINGLE_PRESENT          ()
    #define Batteri_ADC_CFG2_VREF_MV_VALUE           ()
    #define Batteri_ADC_CFG2_APERTURE_TIME0          (uL)
    #define Batteri_ADC_CFG2_APERTURE_TIME1          (uL)
    #define Batteri_ADC_CFG2_APERTURE_TIME2          (uL)
    #define Batteri_ADC_CFG2_APERTURE_TIME3          (uL)
    #define Batteri_ADC_CFG2_FREERUNNING             (u)
    #define Batteri_ADC_CFG2_AVGERAGING_MODE         (uL)
    #define Batteri_ADC_CFG2_LOW_LIMIT               (u)
    #define Batteri_ADC_CFG2_HIGH_LIMIT              (u)
    #define Batteri_ADC_CFG2_RANGE_COND              (uL)
    #define Batteri_ADC_CFG2_USE_SOC                 (0uL)
    #define Batteri_ADC_CFG2_VREF_PWR                (uL)
    #define Batteri_ADC_CFG2_COMP_PWR                (uL)
    #define Batteri_ADC_CFG2_COMP_DLY                (uL)

    /* Clock parameters*/
    #if (Batteri_ADC_CLOCK_INTERNAL)
        #define Batteri_ADC_CFG2_CLOCKDIVIDER        (((CYDEV_CLK_PERICLK__HZ) / (Batteri_ADC_CFG2_NOMINAL_CLOCK_FREQ)) - 1u)
    #endif /* (Batteri_ADC_CLOCK_INTERNAL) */
#endif /* (Batteri_ADC_TOTAL_CONFIGS > 2) */


/* ************************************************************************** */
/* End configuration 2 customizer defines                                     */
/* ************************************************************************** */

/* ************************************************************************** */
/* Begin configuration 3 customizer defines                                   */
/* ************************************************************************** */
#if(Batteri_ADC_TOTAL_CONFIGS > 3)
    #define Batteri_ADC_CFG3_SAMPLE_RATE             ()
    #define Batteri_ADC_CFG3_CHANNEL_BASE            (u)
    #define Batteri_ADC_CFG3_CHANNEL_COUNT           (u)
    #define Batteri_ADC_CFG3_VREF_SEL_MASK           (u)
    #define Batteri_ADC_CFG3_NOMINAL_CLOCK_FREQ      (u)
    #define Batteri_ADC_CFG3_CHANNEL_EN              (u)

    /* Sample Control Register */
    #define Batteri_ADC_CFG3_SINGLE_ENDED_FORMAT     (uL)
    #define Batteri_ADC_CFG3_DIFFERENTIAL_FORMAT     (uL)
    #define Batteri_ADC_CFG3_SAMPLES_AVERAGED        (uL)
    #define Batteri_ADC_CFG3_RANGE_INTR_MASK         (u)
    #define Batteri_ADC_CFG3_SATURATE_INTR_MASK      (u)
    #define Batteri_ADC_CFG3_VNEG_INPUT_SEL          ()
    #define Batteri_ADC_CFG3_SINGLE_PRESENT          ()
    #define Batteri_ADC_CFG3_VREF_MV_VALUE           ()
    #define Batteri_ADC_CFG3_APERTURE_TIME0          (uL)
    #define Batteri_ADC_CFG3_APERTURE_TIME1          (uL)
    #define Batteri_ADC_CFG3_APERTURE_TIME2          (uL)
    #define Batteri_ADC_CFG3_APERTURE_TIME3          (uL)
    #define Batteri_ADC_CFG3_FREERUNNING             (u)
    #define Batteri_ADC_CFG3_AVGERAGING_MODE         (uL)
    #define Batteri_ADC_CFG3_LOW_LIMIT               (u)
    #define Batteri_ADC_CFG3_HIGH_LIMIT              (u)
    #define Batteri_ADC_CFG3_RANGE_COND              (uL)
    #define Batteri_ADC_CFG3_USE_SOC                 (0uL)
    #define Batteri_ADC_CFG3_VREF_PWR                (uL)
    #define Batteri_ADC_CFG3_COMP_PWR                (uL)
    #define Batteri_ADC_CFG3_COMP_DLY                (uL)

    /* Clock parameters*/
    #if (Batteri_ADC_CLOCK_INTERNAL)
        #define Batteri_ADC_CFG3_CLOCKDIVIDER        (((CYDEV_CLK_PERICLK__HZ) / (Batteri_ADC_CFG3_NOMINAL_CLOCK_FREQ)) - 1u)
    #endif /* (Batteri_ADC_CLOCK_INTERNAL) */
#endif /* (Batteri_ADC_TOTAL_CONFIGS > 3) */

/* ************************************************************************** */
/* End configuration 3 customizer defines                                     */
/* ************************************************************************** */

#define Batteri_ADC_DEFAULT_SAMPLE_MODE_SEL      (0u)
#define Batteri_ADC_FREERUNNING                  (1u)
#define Batteri_ADC_HARDWARESOC                  (1u)
#define Batteri_ADC_NEG_SEL_VSSA_KELVIN          (0x0uL)
#define Batteri_ADC_NEG_SEL_VREF                 (0x7uL)
#define Batteri_ADC_PWR_CTRL_VREF_NORMAL_PWR     (0x0uL)

/** Batteri_ADC_TOTAL_CHANNELS_NUM
* This constant represents the number of input channels available for scanning.
*/
#define Batteri_ADC_TOTAL_CHANNELS_NUM           (1u)

/*******************************************************************************
*    Variables with External Linkage
*******************************************************************************/
/**
* \addtogroup group_globals
* Globals are noted in the descriptions of the functions that use globals.
* They are marked with (R), (W), or (RW) noting whether the variable is read,
* write, or read/write.
* @{
*/

/** Batteri_ADC_initVar
* The Batteri_ADC_initVar variable is used to indicate
* initial configuration of this component. The variable is initialized to zero and
* set to 1 the first time Batteri_ADC_Start() is called. This allows for
* component initialization without reinitialization in all subsequent calls to the
* Batteri_ADC_Start() routine.
*
* If reinitialization of the component is required, then the Batteri_ADC_Init() function
* can be called before the Batteri_ADC_Start() or Batteri_ADC_Enable()
* functions.
*/
extern uint8_t Batteri_ADC_initVar;
extern uint8_t Batteri_ADC_selected;
extern uint32_t Batteri_ADC_currentConfig;

#define Batteri_ADC_INIT_VAR_INIT_FLAG     (0x01u)

extern const Batteri_ADC_CONFIG_STRUCT Batteri_ADC_allConfigs[Batteri_ADC_TOTAL_CONFIGS];

/* SysPm callback structure for deep sleep entry and exit.
 * Call the Cy_SysPm_RegisterCallback function with this
 * structure before calling Cy_SysPm_DeepSleep.
*/
extern cy_stc_syspm_callback_t Batteri_ADC_DeepSleepCallbackStruct;

/** @} globals */

/* ************************************************************************** */
/* *******************Global MUX_SWITCH0 Definitions ************************ */
/* ************************************************************************** */
#if(Batteri_ADC_CFG0_VNEG_INPUT_SEL == Batteri_ADC_NEG_SEL_VSSA_KELVIN)
    /* Do not connect VSSA to VMINUS when one channel in differential mode used */
    #if((Batteri_ADC_TOTAL_CHANNELS_NUM == 1u) && (Batteri_ADC_CFG0_SINGLE_PRESENT == 0u))
        #define Batteri_ADC_MUX_SWITCH0_INIT      0u
    #else    /* multiple channels or one single ended channel */
        #define Batteri_ADC_MUX_SWITCH0_INIT      1u
    #endif /* ((Batteri_ADC_TOTAL_CHANNELS_NUM == 1u) && (Batteri_ADC_CFG0_SINGLE_PRESENT == 0u)) */
#else
    #define Batteri_ADC_MUX_SWITCH0_INIT          0u
#endif /* Batteri_ADC_CFG0_VNEG_INPUT_SEL == Batteri_ADC_NEG_SEL_VSSA_KELVIN */

/* ************************************************************************** */
/* Begin configuration 0 calculated defines                                   */
/* ************************************************************************** */
#define Batteri_ADC_CFG0_SAMPLE_TIME01_INIT \
        ((Batteri_ADC_CFG0_APERTURE_TIME0 \
        << SAR_SAMPLE_TIME01_SAMPLE_TIME0_Pos) \
        | (Batteri_ADC_CFG0_APERTURE_TIME1 \
        << SAR_SAMPLE_TIME01_SAMPLE_TIME1_Pos))

#define Batteri_ADC_CFG0_SAMPLE_TIME23_INIT \
        ((Batteri_ADC_CFG0_APERTURE_TIME2 \
        << SAR_SAMPLE_TIME23_SAMPLE_TIME2_Pos) \
        | (Batteri_ADC_CFG0_APERTURE_TIME3 \
        << SAR_SAMPLE_TIME23_SAMPLE_TIME3_Pos))

/* Enable soc pin if used */
#define Batteri_ADC_CFG0_DSI_TRIGGER_EN_INIT \
        (Batteri_ADC_CFG0_USE_SOC \
        << SAR_SAMPLE_CTRL_DSI_TRIGGER_EN_Pos)

/* Set soc operation to edge or level based on sample mode */
#if(Batteri_ADC_CFG0_FREERUNNING == Batteri_ADC_FREERUNNING)
    #define Batteri_ADC_CFG0_DSI_TRIGGER_LEVEL_INIT    (SAR_SAMPLE_CTRL_DSI_TRIGGER_LEVEL_Msk)
#else /* Edge trigger */
    #define Batteri_ADC_CFG0_DSI_TRIGGER_LEVEL_INIT    (0u)
#endif /* End Batteri_ADC_CFG0_FREERUNNING == Batteri_ADC_FREERUNNING */

/* Set SE_NEG_INPUT */
#if(Batteri_ADC_CFG0_VNEG_INPUT_SEL == Batteri_ADC_NEG_SEL_VSSA_KELVIN)
    #define Batteri_ADC_CFG0_SE_NEG_INPUT_INIT \
            ((uint32)(Batteri_ADC_NEG_SEL_VSSA_KELVIN \
            << SAR_CTRL_NEG_SEL_Pos ))
#elif(Batteri_ADC_CFG0_VNEG_INPUT_SEL == Batteri_ADC_NEG_SEL_VREF)

    /* Do not connect VNEG to VREF when one channel in differential mode used */
    /* Only needed for config 0 since 2+ configs == 2+ channels */
    #if((Batteri_ADC_CFG0_CHANNEL_COUNT == 1u) && (Batteri_ADC_CFG0_SINGLE_PRESENT == 0u))
        #define Batteri_ADC_CFG0_SE_NEG_INPUT_INIT     0u
    #else    /* multiple channels or one single channel */
        #define Batteri_ADC_CFG0_SE_NEG_INPUT_INIT     (Batteri_ADC_NEG_SEL_VREF \
                                                            << SAR_CTRL_NEG_SEL_Pos )
    #endif /* (Batteri_ADC_CFG0_CHANNEL_COUNT == 1u) && (Batteri_ADC_CFG0_CHANNELS_MODE != 0u) */
#elif (Batteri_ADC_CFG0_SINGLE_PRESENT != 0u)
    #define Batteri_ADC_CFG0_SE_NEG_INPUT_INIT         Batteri_ADC_CFG0_NEG_OTHER
#else
    #define Batteri_ADC_CFG0_SE_NEG_INPUT_INIT         0u
#endif /* Batteri_ADC_CFG0_VNEG_INPUT_SEL == Batteri_ADC_NEG_SEL_VSSA_KELVIN */

#if(Batteri_ADC_TOTAL_CHANNELS_NUM > 1u)
    #define Batteri_ADC_CFG0_NEG_OTHER                 (uint16)((uint16)Batteri_ADC_SARMUX__VNEG0 << SAR_CTRL_NEG_SEL_Pos)
    #define Batteri_ADC_CFG0_SWITCH_CONF_INIT          0u
#else /* Disable SAR sequencer from enabling routing switches in single channel mode */
    #define Batteri_ADC_CFG0_SWITCH_CONF_INIT          SAR_CTRL_SWITCH_DISABLE_Msk
    #define Batteri_ADC_CFG0_NEG_OTHER                 0u
#endif /* Batteri_ADC_CFG0_CHANNEL_COUNT > 1u */

/* If the SAR is configured for multiple channels, always set SAR_HW_CTRL_NEGVREF to 1 */
#if(Batteri_ADC_TOTAL_CHANNELS_NUM == 1u)
    #define Batteri_ADC_CFG0_HW_CTRL_NEGVREF_INIT      0u
#else
    #define Batteri_ADC_CFG0_HW_CTRL_NEGVREF_INIT      SAR_CTRL_SAR_HW_CTRL_NEGVREF_Msk
#endif /* Batteri_ADC_CFG0_CHANNEL_COUNT == 1u */

#define Batteri_ADC_CFG0_POWER_INIT  (Batteri_ADC_PWR_CTRL_VREF_NORMAL_PWR)

/* SAMPLE_CTRL initial values */
#define Batteri_ADC_CFG0_SE_RESULT_FORMAT_INIT \
        (Batteri_ADC_CFG0_SINGLE_ENDED_FORMAT \
        << SAR_SAMPLE_CTRL_SINGLE_ENDED_SIGNED_Pos)

#define Batteri_ADC_CFG0_DIFF_RESULT_FORMAT_INIT \
        (Batteri_ADC_CFG0_DIFFERENTIAL_FORMAT \
        << SAR_SAMPLE_CTRL_DIFFERENTIAL_SIGNED_Pos)

#define Batteri_ADC_CFG0_AVG_SAMPLES_NUM_INIT \
        (Batteri_ADC_CFG0_SAMPLES_AVERAGED \
        << SAR_SAMPLE_CTRL_AVG_CNT_Pos)

/* Combination of Average Mode and Average Shift */
#define Batteri_ADC_CFG0_AVG_MODE_INIT \
        (Batteri_ADC_CFG0_AVGERAGING_MODE \
        << SAR_SAMPLE_CTRL_AVG_SHIFT_Pos)

#define Batteri_ADC_CFG0_TRIGGER_OUT_INIT      (0u)
#define Batteri_ADC_CFG0_UAB_SCAN_MODE_INIT    (0u)

#define Batteri_ADC_CFG0_VREF_POWER_INIT  \
        (Batteri_ADC_CFG0_VREF_PWR \
        << SAR_CTRL_PWR_CTRL_VREF_Pos)

#define Batteri_ADC_CFG0_COMP_PWR_INIT  \
        (Batteri_ADC_CFG0_COMP_PWR \
        << SAR_CTRL_COMP_PWR_Pos)

#define Batteri_ADC_CFG0_COMP_DLY_INIT  \
        (Batteri_ADC_CFG0_COMP_DLY \
        << SAR_CTRL_COMP_DLY_Pos)

#define Batteri_ADC_CFG0_CTRL_INIT  \
        (Batteri_ADC_CFG0_VREF_POWER_INIT \
        | Batteri_ADC_CFG0_VREF_SEL_MASK \
        | Batteri_ADC_CFG0_SE_NEG_INPUT_INIT \
        | Batteri_ADC_CFG0_HW_CTRL_NEGVREF_INIT \
        | Batteri_ADC_CFG0_COMP_DLY_INIT \
        | SAR_CTRL_REFBUF_EN_Msk \
        | Batteri_ADC_CFG0_COMP_PWR_INIT \
        | SAR_CTRL_DSI_SYNC_CONFIG_Msk  \
        | Batteri_ADC_CFG0_SWITCH_CONF_INIT )

#define Batteri_ADC_CFG0_SAMPLE_CTRL_INIT \
        (Batteri_ADC_CFG0_SE_RESULT_FORMAT_INIT \
        | Batteri_ADC_CFG0_DIFF_RESULT_FORMAT_INIT \
        | Batteri_ADC_CFG0_AVG_SAMPLES_NUM_INIT \
        | Batteri_ADC_CFG0_AVG_MODE_INIT \
        | Batteri_ADC_CFG0_DSI_TRIGGER_LEVEL_INIT \
        | Batteri_ADC_CFG0_DSI_TRIGGER_EN_INIT \
        | Batteri_ADC_CFG0_UAB_SCAN_MODE_INIT \
        | SAR_SAMPLE_CTRL_VALID_IGNORE_Msk \
        | Batteri_ADC_CFG0_TRIGGER_OUT_INIT \
        | SAR_SAMPLE_CTRL_EOS_DSI_OUT_EN_Msk \
)

#define Batteri_ADC_CFG0_RANGE_THRES_INIT \
        (Batteri_ADC_CFG0_LOW_LIMIT \
        | (uint32)((uint32)Batteri_ADC_CFG0_HIGH_LIMIT \
        << SAR_RANGE_THRES_RANGE_HIGH_Pos))

#define Batteri_ADC_CFG0_RANGE_COND_INIT   (cy_en_sar_range_detect_condition_t)Batteri_ADC_CFG0_RANGE_COND

/* Misc Config
    [0] - Freerunning: Set if the sample mode is freerunning
*/
#define Batteri_ADC_CFG0_MISC_CONFIG_INIT \
        (Batteri_ADC_CFG0_FREERUNNING)

/* ************************************************************************** */
/* End configuration 0 calculated defines                                     */
/* ************************************************************************** */

/* ************************************************************************** */
/* Begin configuration 1 calculated defines                                   */
/* ************************************************************************** */
#if(Batteri_ADC_TOTAL_CONFIGS > 1)
    #define Batteri_ADC_CFG1_SAMPLE_TIME01_INIT \
            ((Batteri_ADC_CFG1_APERTURE_TIME0 \
            << SAR_SAMPLE_TIME01_SAMPLE_TIME0_Pos) \
            | (Batteri_ADC_CFG1_APERTURE_TIME1 \
            << SAR_SAMPLE_TIME01_SAMPLE_TIME1_Pos))

    #define Batteri_ADC_CFG1_SAMPLE_TIME23_INIT \
            ((Batteri_ADC_CFG1_APERTURE_TIME2 \
            << SAR_SAMPLE_TIME23_SAMPLE_TIME2_Pos) \
            | (Batteri_ADC_CFG1_APERTURE_TIME3 \
            << SAR_SAMPLE_TIME23_SAMPLE_TIME3_Pos))

    /* Enable soc pin if used */
    #define Batteri_ADC_CFG1_DSI_TRIGGER_EN_INIT \
            (Batteri_ADC_CFG1_USE_SOC \
            << SAR_SAMPLE_CTRL_DSI_TRIGGER_EN_Pos)

    /* Set soc operation to edge or level based on sample mode */
    #if(Batteri_ADC_CFG1_FREERUNNING == Batteri_ADC_FREERUNNING)
        #define Batteri_ADC_CFG1_DSI_TRIGGER_LEVEL_INIT    (SAR_SAMPLE_CTRL_DSI_TRIGGER_LEVEL_Msk)
    #else /* Edge trigger */
        #define Batteri_ADC_CFG1_DSI_TRIGGER_LEVEL_INIT    (0u)
    #endif /* End Batteri_ADC_CFG1_FREERUNNING == Batteri_ADC_FREERUNNING */

    /* Set SE_NEG_INPUT */
    #if(Batteri_ADC_CFG1_VNEG_INPUT_SEL == Batteri_ADC_NEG_SEL_VSSA_KELVIN)
        #define Batteri_ADC_CFG1_SE_NEG_INPUT_INIT \
            ((uint32)(Batteri_ADC_NEG_SEL_VSSA_KELVIN \
            << SAR_CTRL_NEG_SEL_Pos ))
    #elif(Batteri_ADC_CFG1_VNEG_INPUT_SEL == Batteri_ADC_NEG_SEL_VREF)
        #define Batteri_ADC_CFG1_SE_NEG_INPUT_INIT     (Batteri_ADC_NEG_SEL_VREF \
                                                            << SAR_CTRL_NEG_SEL_Pos )
    #elif (Batteri_ADC_CFG1_SINGLE_PRESENT != 0u)
        #define Batteri_ADC_CFG1_SE_NEG_INPUT_INIT         Batteri_ADC_CFG1_NEG_OTHER
    #else
        #define Batteri_ADC_CFG1_SE_NEG_INPUT_INIT         0u
    #endif /* Batteri_ADC_CFG1_VNEG_INPUT_SEL == Batteri_ADC_NEG_SEL_VSSA_KELVIN */

    #define Batteri_ADC_CFG1_NEG_OTHER                 (uint16)((uint16)Batteri_ADC_SARMUX__VNEG1 << SAR_CTRL_NEG_SEL_Pos)
    #define Batteri_ADC_CFG1_SWITCH_CONF_INIT          0u

    /* If the SAR is configured for multiple channels, always set SAR_HW_CTRL_NEGVREF to 1 */
    #define Batteri_ADC_CFG1_HW_CTRL_NEGVREF_INIT      SAR_CTRL_SAR_HW_CTRL_NEGVREF_Msk

    #define Batteri_ADC_CFG1_POWER_INIT  (Batteri_ADC_PWR_CTRL_VREF_NORMAL_PWR)

    /* SAMPLE_CTRL initial values */
    #define Batteri_ADC_CFG1_SE_RESULT_FORMAT_INIT \
            (Batteri_ADC_CFG1_SINGLE_ENDED_FORMAT \
            << SAR_SAMPLE_CTRL_SINGLE_ENDED_SIGNED_Pos)

    #define Batteri_ADC_CFG1_DIFF_RESULT_FORMAT_INIT \
            (Batteri_ADC_CFG1_DIFFERENTIAL_FORMAT \
            << SAR_SAMPLE_CTRL_DIFFERENTIAL_SIGNED_Pos)

    #define Batteri_ADC_CFG1_AVG_SAMPLES_NUM_INIT \
            (Batteri_ADC_CFG1_SAMPLES_AVERAGED \
            << SAR_SAMPLE_CTRL_AVG_CNT_Pos)

    /* Combination of Average Mode and Average Shift */
    #define Batteri_ADC_CFG1_AVG_MODE_INIT \
            (Batteri_ADC_CFG1_AVGERAGING_MODE \
            << SAR_SAMPLE_CTRL_AVG_SHIFT_Pos)

    #define Batteri_ADC_CFG1_TRIGGER_OUT_INIT      (0u)
    #define Batteri_ADC_CFG1_UAB_SCAN_MODE_INIT    (0u)

    #define Batteri_ADC_CFG1_VREF_POWER_INIT  \
            (Batteri_ADC_CFG1_VREF_PWR \
            << SAR_CTRL_PWR_CTRL_VREF_Pos)

    #define Batteri_ADC_CFG1_COMP_PWR_INIT  \
            (Batteri_ADC_CFG1_COMP_PWR \
            << SAR_CTRL_COMP_PWR_Pos)

    #define Batteri_ADC_CFG1_COMP_DLY_INIT  \
            (Batteri_ADC_CFG1_COMP_DLY \
            << SAR_CTRL_COMP_DLY_Pos)

    #define Batteri_ADC_CFG1_CTRL_INIT  \
            (Batteri_ADC_CFG1_VREF_POWER_INIT \
            | Batteri_ADC_CFG1_VREF_SEL_MASK \
            | Batteri_ADC_CFG1_SE_NEG_INPUT_INIT \
            | Batteri_ADC_CFG1_HW_CTRL_NEGVREF_INIT \
            | Batteri_ADC_CFG1_COMP_DLY_INIT \
            | SAR_CTRL_REFBUF_EN_Msk \
            | Batteri_ADC_CFG1_COMP_PWR_INIT \
            | SAR_CTRL_DSI_SYNC_CONFIG_Msk  \
            | Batteri_ADC_CFG1_SWITCH_CONF_INIT )

    #define Batteri_ADC_CFG1_SAMPLE_CTRL_INIT \
            (Batteri_ADC_CFG1_SE_RESULT_FORMAT_INIT \
            | Batteri_ADC_CFG1_DIFF_RESULT_FORMAT_INIT \
            | Batteri_ADC_CFG1_AVG_SAMPLES_NUM_INIT \
            | Batteri_ADC_CFG1_AVG_MODE_INIT \
            | Batteri_ADC_CFG1_DSI_TRIGGER_LEVEL_INIT \
            | Batteri_ADC_CFG1_DSI_TRIGGER_EN_INIT \
            | Batteri_ADC_CFG1_UAB_SCAN_MODE_INIT \
            | SAR_SAMPLE_CTRL_VALID_IGNORE_Msk \
            | Batteri_ADC_CFG1_TRIGGER_OUT_INIT \
            | SAR_SAMPLE_CTRL_EOS_DSI_OUT_EN_Msk \
    )

    #define Batteri_ADC_CFG1_RANGE_THRES_INIT \
            (Batteri_ADC_CFG1_LOW_LIMIT \
            | (uint32)((uint32)Batteri_ADC_CFG1_HIGH_LIMIT \
            << SAR_RANGE_THRES_RANGE_HIGH_Pos))

    #define Batteri_ADC_CFG1_RANGE_COND_INIT   (cy_en_sar_range_detect_condition_t)Batteri_ADC_CFG1_RANGE_COND

    /* Misc Config
        [0] - Freerunning: Set if the sample mode is freerunning
    */
    #define Batteri_ADC_CFG1_MISC_CONFIG_INIT \
            (Batteri_ADC_CFG1_FREERUNNING)
#endif /* Batteri_ADC_TOTAL_CONFIGS > 1 */

/* ************************************************************************** */
/* End configuration 1 calculated defines                                     */
/* ************************************************************************** */

/* ************************************************************************** */
/* Begin configuration 2 calculated defines                                   */
/* ************************************************************************** */
#if(Batteri_ADC_TOTAL_CONFIGS > 2)
    #define Batteri_ADC_CFG2_SAMPLE_TIME01_INIT \
            ((Batteri_ADC_CFG2_APERTURE_TIME0 \
            << SAR_SAMPLE_TIME01_SAMPLE_TIME0_Pos) \
            | (Batteri_ADC_CFG2_APERTURE_TIME1 \
            << SAR_SAMPLE_TIME01_SAMPLE_TIME1_Pos))

    #define Batteri_ADC_CFG2_SAMPLE_TIME23_INIT \
            ((Batteri_ADC_CFG2_APERTURE_TIME2 \
            << SAR_SAMPLE_TIME23_SAMPLE_TIME2_Pos) \
            | (Batteri_ADC_CFG2_APERTURE_TIME3 \
            << SAR_SAMPLE_TIME23_SAMPLE_TIME3_Pos))

    /* Enable soc pin if used */
    #define Batteri_ADC_CFG2_DSI_TRIGGER_EN_INIT \
            (Batteri_ADC_CFG2_USE_SOC \
            << SAR_SAMPLE_CTRL_DSI_TRIGGER_EN_Pos)

    /* Set soc operation to edge or level based on sample mode */
    #if(Batteri_ADC_CFG2_FREERUNNING == Batteri_ADC_FREERUNNING)
        #define Batteri_ADC_CFG2_DSI_TRIGGER_LEVEL_INIT    (SAR_SAMPLE_CTRL_DSI_TRIGGER_LEVEL_Msk)
    #else /* Edge trigger */
        #define Batteri_ADC_CFG2_DSI_TRIGGER_LEVEL_INIT    (0u)
    #endif /* End Batteri_ADC_CFG2_FREERUNNING == Batteri_ADC_FREERUNNING */

    /* Set SE_NEG_INPUT */
    #if(Batteri_ADC_CFG2_VNEG_INPUT_SEL == Batteri_ADC_NEG_SEL_VSSA_KELVIN)
        #define Batteri_ADC_CFG2_SE_NEG_INPUT_INIT \
            ((uint32)(Batteri_ADC_NEG_SEL_VSSA_KELVIN \
            << SAR_CTRL_NEG_SEL_Pos ))
    #elif(Batteri_ADC_CFG2_VNEG_INPUT_SEL == Batteri_ADC_NEG_SEL_VREF)
        #define Batteri_ADC_CFG2_SE_NEG_INPUT_INIT     (Batteri_ADC_NEG_SEL_VREF \
                                                                << SAR_CTRL_NEG_SEL_Pos )
    #elif (Batteri_ADC_CFG2_SINGLE_PRESENT != 0u)
        #define Batteri_ADC_CFG2_SE_NEG_INPUT_INIT         Batteri_ADC_CFG2_NEG_OTHER
    #else
        #define Batteri_ADC_CFG2_SE_NEG_INPUT_INIT         0u
    #endif /* Batteri_ADC_CFG2_VNEG_INPUT_SEL == Batteri_ADC_NEG_SEL_VSSA_KELVIN */

   #define Batteri_ADC_CFG2_NEG_OTHER                 (uint16)((uint16)Batteri_ADC_SARMUX__VNEG2 << SAR_CTRL_NEG_SEL_Pos)

    #define Batteri_ADC_CFG2_SWITCH_CONF_INIT          0u

    /* If the SAR is configured for multiple channels, always set SAR_HW_CTRL_NEGVREF to 1 */
    #define Batteri_ADC_CFG2_HW_CTRL_NEGVREF_INIT      SAR_CTRL_SAR_HW_CTRL_NEGVREF_Msk

    #define Batteri_ADC_CFG2_POWER_INIT  (Batteri_ADC_PWR_CTRL_VREF_NORMAL_PWR)

    /* SAMPLE_CTRL initial values */
    #define Batteri_ADC_CFG2_SE_RESULT_FORMAT_INIT \
            (Batteri_ADC_CFG2_SINGLE_ENDED_FORMAT \
            << SAR_SAMPLE_CTRL_SINGLE_ENDED_SIGNED_Pos)

    #define Batteri_ADC_CFG2_DIFF_RESULT_FORMAT_INIT \
            (Batteri_ADC_CFG2_DIFFERENTIAL_FORMAT \
            << SAR_SAMPLE_CTRL_DIFFERENTIAL_SIGNED_Pos)

    #define Batteri_ADC_CFG2_AVG_SAMPLES_NUM_INIT \
            (Batteri_ADC_CFG2_SAMPLES_AVERAGED \
            << SAR_SAMPLE_CTRL_AVG_CNT_Pos)

    /* Combination of Average Mode and Average Shift */
    #define Batteri_ADC_CFG2_AVG_MODE_INIT \
            (Batteri_ADC_CFG2_AVGERAGING_MODE \
            << SAR_SAMPLE_CTRL_AVG_SHIFT_Pos)

    #define Batteri_ADC_CFG2_TRIGGER_OUT_INIT      (0u)
    #define Batteri_ADC_CFG2_UAB_SCAN_MODE_INIT    (0u)


    #define Batteri_ADC_CFG2_VREF_POWER_INIT  \
            (Batteri_ADC_CFG2_VREF_PWR \
            << SAR_CTRL_PWR_CTRL_VREF_Pos)

    #define Batteri_ADC_CFG2_COMP_PWR_INIT  \
            (Batteri_ADC_CFG2_COMP_PWR \
            << SAR_CTRL_COMP_PWR_Pos)

    #define Batteri_ADC_CFG2_COMP_DLY_INIT  \
            (Batteri_ADC_CFG2_COMP_DLY \
            << SAR_CTRL_COMP_DLY_Pos)

    #define Batteri_ADC_CFG2_CTRL_INIT  \
            (Batteri_ADC_CFG2_VREF_POWER_INIT \
            | Batteri_ADC_CFG2_VREF_SEL_MASK \
            | Batteri_ADC_CFG2_SE_NEG_INPUT_INIT \
            | Batteri_ADC_CFG2_HW_CTRL_NEGVREF_INIT \
            | Batteri_ADC_CFG2_COMP_DLY_INIT \
            | SAR_CTRL_REFBUF_EN_Msk \
            | Batteri_ADC_CFG2_COMP_PWR_INIT \
            | SAR_CTRL_DSI_SYNC_CONFIG_Msk  \
            | Batteri_ADC_CFG2_SWITCH_CONF_INIT )


    #define Batteri_ADC_CFG2_SAMPLE_CTRL_INIT \
            (Batteri_ADC_CFG2_SE_RESULT_FORMAT_INIT \
            | Batteri_ADC_CFG2_DIFF_RESULT_FORMAT_INIT \
            | Batteri_ADC_CFG2_AVG_SAMPLES_NUM_INIT \
            | Batteri_ADC_CFG2_AVG_MODE_INIT \
            | Batteri_ADC_CFG2_DSI_TRIGGER_LEVEL_INIT \
            | Batteri_ADC_CFG2_DSI_TRIGGER_EN_INIT \
            | Batteri_ADC_CFG2_UAB_SCAN_MODE_INIT \
            | SAR_SAMPLE_CTRL_VALID_IGNORE_Msk \
            | Batteri_ADC_CFG2_TRIGGER_OUT_INIT \
            | SAR_SAMPLE_CTRL_EOS_DSI_OUT_EN_Msk \
    )

    #define Batteri_ADC_CFG2_RANGE_THRES_INIT \
            (Batteri_ADC_CFG2_LOW_LIMIT \
            | (uint32)((uint32)Batteri_ADC_CFG2_HIGH_LIMIT \
            << SAR_RANGE_THRES_RANGE_HIGH_Pos))

    #define Batteri_ADC_CFG2_RANGE_COND_INIT   (cy_en_sar_range_detect_condition_t)Batteri_ADC_CFG2_RANGE_COND

    /* Misc Config
        [0] - Freerunning: Set if the sample mode is freerunning
    */
    #define Batteri_ADC_CFG2_MISC_CONFIG_INIT \
            (Batteri_ADC_CFG2_FREERUNNING)
#endif /* Batteri_ADC_TOTAL_CONFIGS > 2 */

/* ************************************************************************** */
/* End configuration 2 calculated defines                                     */
/* ************************************************************************** */

/* ************************************************************************** */
/* Begin configuration 3 calculated defines                                   */
/* ************************************************************************** */
#if(Batteri_ADC_TOTAL_CONFIGS > 3)
    #define Batteri_ADC_CFG3_SAMPLE_TIME01_INIT \
            ((Batteri_ADC_CFG3_APERTURE_TIME0 \
            << SAR_SAMPLE_TIME01_SAMPLE_TIME0_Pos) \
            | (Batteri_ADC_CFG3_APERTURE_TIME1 \
            << SAR_SAMPLE_TIME01_SAMPLE_TIME1_Pos))

    #define Batteri_ADC_CFG3_SAMPLE_TIME23_INIT \
            ((Batteri_ADC_CFG3_APERTURE_TIME2 \
            << SAR_SAMPLE_TIME23_SAMPLE_TIME2_Pos) \
            | (Batteri_ADC_CFG3_APERTURE_TIME3 \
            << SAR_SAMPLE_TIME23_SAMPLE_TIME3_Pos))

    /* Enable soc pin if used */
    #define Batteri_ADC_CFG3_DSI_TRIGGER_EN_INIT \
            (Batteri_ADC_CFG3_USE_SOC \
             << SAR_SAMPLE_CTRL_DSI_TRIGGER_EN_Pos)

    /* Set soc operation to edge or level based on sample mode */
    #if(Batteri_ADC_CFG3_FREERUNNING == Batteri_ADC_FREERUNNING)
        #define Batteri_ADC_CFG3_DSI_TRIGGER_LEVEL_INIT    (SAR_SAMPLE_CTRL_DSI_TRIGGER_LEVEL_Msk)
    #else /* Edge trigger */
        #define Batteri_ADC_CFG3_DSI_TRIGGER_LEVEL_INIT    (0u)
    #endif /* End Batteri_ADC_CFG3_FREERUNNING == Batteri_ADC_FREERUNNING */

    /* Set SE_NEG_INPUT  */
    #if(Batteri_ADC_CFG3_VNEG_INPUT_SEL == Batteri_ADC_NEG_SEL_VSSA_KELVIN)
        #define Batteri_ADC_CFG3_SE_NEG_INPUT_INIT \
            ((uint32)(Batteri_ADC_NEG_SEL_VSSA_KELVIN \
            << SAR_CTRL_NEG_SEL_Pos ))
    #elif(Batteri_ADC_CFG3_VNEG_INPUT_SEL == Batteri_ADC_NEG_SEL_VREF)
        #define Batteri_ADC_CFG3_SE_NEG_INPUT_INIT     (Batteri_ADC_NEG_SEL_VREF \
                                                                << SAR_CTRL_NEG_SEL_Pos )
    #elif (Batteri_ADC_CFG3_SINGLE_PRESENT != 0u)
        #define Batteri_ADC_CFG3_SE_NEG_INPUT_INIT         Batteri_ADC_CFG3_NEG_OTHER
    #else
        #define Batteri_ADC_CFG3_SE_NEG_INPUT_INIT         0u
    #endif /* Batteri_ADC_CFG3_VNEG_INPUT_SEL == Batteri_ADC_NEG_SEL_VSSA_KELVIN */

    #define Batteri_ADC_CFG3_NEG_OTHER                 (uint16)((uint16)Batteri_ADC_SARMUX__VNEG3 << SAR_CTRL_NEG_SEL_Pos)

    #define Batteri_ADC_CFG3_SWITCH_CONF_INIT          0u

    /* If the SAR is configured for multiple channels, always set SAR_HW_CTRL_NEGVREF to 1 */
    #define Batteri_ADC_CFG3_HW_CTRL_NEGVREF_INIT      SAR_CTRL_SAR_HW_CTRL_NEGVREF_Msk

    #define Batteri_ADC_CFG3_POWER_INIT  (Batteri_ADC_PWR_CTRL_VREF_NORMAL_PWR)

    /* SAMPLE_CTRL initial values */
    #define Batteri_ADC_CFG3_SE_RESULT_FORMAT_INIT \
            (Batteri_ADC_CFG3_SINGLE_ENDED_FORMAT \
            << SAR_SAMPLE_CTRL_SINGLE_ENDED_SIGNED_Pos)

    #define Batteri_ADC_CFG3_DIFF_RESULT_FORMAT_INIT \
            (Batteri_ADC_CFG3_DIFFERENTIAL_FORMAT \
            << SAR_SAMPLE_CTRL_DIFFERENTIAL_SIGNED_Pos)

    #define Batteri_ADC_CFG3_AVG_SAMPLES_NUM_INIT \
            (Batteri_ADC_CFG3_SAMPLES_AVERAGED \
            << SAR_SAMPLE_CTRL_AVG_CNT_Pos)

    /* Combination of Average Mode and Average Shift */
    #define Batteri_ADC_CFG3_AVG_MODE_INIT \
            (Batteri_ADC_CFG3_AVGERAGING_MODE \
            << SAR_SAMPLE_CTRL_AVG_SHIFT_Pos)

    #define Batteri_ADC_CFG3_TRIGGER_OUT_INIT      (0u)
    #define Batteri_ADC_CFG3_UAB_SCAN_MODE_INIT    (0u)

    #define Batteri_ADC_CFG3_VREF_POWER_INIT  \
            (Batteri_ADC_CFG3_VREF_PWR \
            << SAR_CTRL_PWR_CTRL_VREF_Pos)

    #define Batteri_ADC_CFG3_COMP_PWR_INIT  \
            (Batteri_ADC_CFG3_COMP_PWR \
            << SAR_CTRL_COMP_PWR_Pos)

    #define Batteri_ADC_CFG3_COMP_DLY_INIT  \
            (Batteri_ADC_CFG3_COMP_DLY \
            << SAR_CTRL_COMP_DLY_Pos)

    #define Batteri_ADC_CFG3_CTRL_INIT  \
            (Batteri_ADC_CFG3_VREF_POWER_INIT \
            | Batteri_ADC_CFG3_VREF_SEL_MASK \
            | Batteri_ADC_CFG3_SE_NEG_INPUT_INIT \
            | Batteri_ADC_CFG3_HW_CTRL_NEGVREF_INIT \
            | Batteri_ADC_CFG3_COMP_DLY_INIT \
            | SAR_CTRL_REFBUF_EN_Msk \
            | Batteri_ADC_CFG3_COMP_PWR_INIT \
            | SAR_CTRL_DSI_SYNC_CONFIG_Msk  \
            | Batteri_ADC_CFG3_SWITCH_CONF_INIT )


    #define Batteri_ADC_CFG3_SAMPLE_CTRL_INIT \
            (Batteri_ADC_CFG3_SE_RESULT_FORMAT_INIT \
            | Batteri_ADC_CFG3_DIFF_RESULT_FORMAT_INIT \
            | Batteri_ADC_CFG3_AVG_SAMPLES_NUM_INIT \
            | Batteri_ADC_CFG3_AVG_MODE_INIT \
            | Batteri_ADC_CFG3_DSI_TRIGGER_LEVEL_INIT \
            | Batteri_ADC_CFG3_DSI_TRIGGER_EN_INIT \
            | Batteri_ADC_CFG3_UAB_SCAN_MODE_INIT \
            | SAR_SAMPLE_CTRL_VALID_IGNORE_Msk \
            | Batteri_ADC_CFG3_TRIGGER_OUT_INIT \
            | SAR_SAMPLE_CTRL_EOS_DSI_OUT_EN_Msk \
    )

    #define Batteri_ADC_CFG3_RANGE_THRES_INIT \
            (Batteri_ADC_CFG3_LOW_LIMIT \
            | (uint32)((uint32)Batteri_ADC_CFG3_HIGH_LIMIT \
            << SAR_RANGE_THRES_RANGE_HIGH_Pos))

    #define Batteri_ADC_CFG3_RANGE_COND_INIT   (cy_en_sar_range_detect_condition_t)Batteri_ADC_CFG3_RANGE_COND

    /* Misc Config
        [0] - Freerunning: Set if the sample mode is freerunning
    */
    #define Batteri_ADC_CFG3_MISC_CONFIG_INIT \
            (Batteri_ADC_CFG3_FREERUNNING )

#endif /* Batteri_ADC_TOTAL_CONFIGS > 3 */

/* ************************************************************************** */
/* End configuration 3 calculated defines                                     */
/* ************************************************************************** */

/******************************************************************************
* Function Name: Batteri_ADC_Enable
****************************************************************************//*
*
* \brief Enables the component.
*
* \param None
*
* \return None
*
* \sideeffect
*  None
*
*******************************************************************************/
__STATIC_INLINE void Batteri_ADC_Enable(void)
{
    Cy_SAR_Enable(Batteri_ADC_SAR__HW);
}

/*******************************************************************************
* Function Name: Batteri_ADC_Stop
****************************************************************************//**
*
* \brief This function stops ADC conversions and puts the ADC into its lowest
* power mode.
*
* \param None
*
* \return None
*
* \sideeffect
* Do not use the Batteri_ADC_Stop() API to halt conversions. Instead use the
* Batteri_ADC_StopConvert() API. If you use the Batteri_ADC_Stop() API
* to halt conversions then later use the Batteri_ADC_Start() and
* Batteri_ADC_StartConvert() APIs to resume conversions, the first channel
* of the scan may be corrupt. The Batteri_ADC_StopConvert() API will enable
* the Batteri_ADC to complete the current scan of channels. After the
* channel scan is complete, the Batteri_ADC will stop all conversions, which
* can be detected by the use of an ISR or the Batteri_ADC_IsEndConversion()
* function.
*
*******************************************************************************/
__STATIC_INLINE void Batteri_ADC_Stop(void)
{
    Cy_SAR_Disable(Batteri_ADC_SAR__HW);
}

/*******************************************************************************
* Function Name: Batteri_ADC_StopConvert
****************************************************************************//**
*
* \brief Forces the Batteri_ADC to stop conversions. If a conversion is
* currently executing, that conversion will complete, but no further conversions
* will occur.
*
* \param None
*
* \return None
*
* \sideeffect None
*
*******************************************************************************/
__STATIC_INLINE void Batteri_ADC_StopConvert(void)
{
    Cy_SAR_StopConvert(Batteri_ADC_SAR__HW);
}

/*******************************************************************************
* Function Name: Batteri_ADC_GetResult16
****************************************************************************//**
*
* \brief Gets the data available in the channel result data register
*
* \param chan The Batteri_ADC channel to read the result from. The first
* channel is 0.
*
* \return Returns converted data as a signed 16-bit integer.
*
* \sideeffect None
*
*******************************************************************************/
__STATIC_INLINE int16_t Batteri_ADC_GetResult16(uint32_t chan)
{
    /* Halt CPU in debug mode if channel is out of valid range */
    CY_ASSERT(chan < Batteri_ADC_allConfigs[Batteri_ADC_currentConfig].numChannels);

    return Cy_SAR_GetResult16(Batteri_ADC_SAR__HW, chan);
}

/*******************************************************************************
* Function Name: Batteri_ADC_GetResult32
****************************************************************************//**
*
* \brief Gets the data available in the channel result data register.
*
* \param chan The Batteri_ADC channel to read the result from. The first
* channel is 0.
*
* \return Returns converted data as a signed 32-bit integer.
*
* \sideeffect None
*
*******************************************************************************/
__STATIC_INLINE int32_t Batteri_ADC_GetResult32(uint32_t chan)
{
    int32_t finalResult;

    /* Halt CPU in debug mode if channel is out of valid range */
    CY_ASSERT(chan < Batteri_ADC_allConfigs[Batteri_ADC_currentConfig].numChannels);

    finalResult = Cy_SAR_GetResult32(Batteri_ADC_SAR__HW, chan);

    return finalResult;
}

/*******************************************************************************
* Function Name: Batteri_ADC_SetLowLimit
****************************************************************************//**
*
* \brief Sets the low limit parameter for a limit condition.
*
* \param lowLimit The low limit for a limit condition.
*
* \return None
*
* \sideeffect None
*
*******************************************************************************/
__STATIC_INLINE void Batteri_ADC_SetLowLimit(uint32_t lowLimit)
{
    Cy_SAR_SetLowLimit(Batteri_ADC_SAR__HW, lowLimit);
}

/*******************************************************************************
* Function Name: Batteri_ADC_SetHighLimit
****************************************************************************//**
*
* \brief Sets the high limit parameter for a limit condition.
*
* \param highLimit The high limit for a limit condition.
*
* \return None
*
* \sideeffect None
*
*******************************************************************************/
__STATIC_INLINE void Batteri_ADC_SetHighLimit(uint32_t highLimit)
{
    Cy_SAR_SetHighLimit(Batteri_ADC_SAR__HW, highLimit);
}

/*******************************************************************************
* Function Name: Batteri_ADC_SetLimitMask
****************************************************************************//**
*
* \brief Sets the channel limit condition mask.
*
*
* \param limitMask
* Sets which channels can cause a limit condition interrupt.
* Bit N of the mask enables the limit condition interrupt for channel N.
* The limitMask cannot be larger than the number of channels.
* If a channel is not enabled, it cannot cause any interrupts.
*
* \return None
*
* \sideeffect None
*
*******************************************************************************/
__STATIC_INLINE void Batteri_ADC_SetLimitMask(uint32_t limitMask)
{
    Cy_SAR_SetRangeInterruptMask(Batteri_ADC_SAR__HW, limitMask);
}

/*******************************************************************************
* Function Name: Batteri_ADC_SetSatMask
****************************************************************************//**
*
* \brief Sets the channel saturation event mask.
*
* \param satMask
* Sets which channels can cause a saturation event interrupt.
* Bit N of the mask enables the saturation event interrupt for channel N.
* The satMask cannot be larger than the number of channels.
* If a channel is not enabled, it cannot cause any interrupts.
*
* \return None
*
* \sideeffect None
*
*******************************************************************************/
__STATIC_INLINE void Batteri_ADC_SetSatMask(uint32_t satMask)
{
    Cy_SAR_SetSatInterruptMask(Batteri_ADC_SAR__HW, satMask);
}

/*******************************************************************************
* Function Name: Batteri_ADC_SetOffset
****************************************************************************//**
*
* \brief Sets the ADC offset that is used by the functions Batteri_ADC_CountsTo_uVolts,
* Batteri_ADC_CountsTo_mVolts, and Batteri_ADC_CountsTo_Volts.
*
* Offset is applied to counts before unit scaling and gain.  All CountsTo_[mV, uV, V]olts()
* functions use the following equation:
*     V = (Counts/AvgDivider - Offset)*TEN_VOLT/Gain
* See CountsTo_Volts() for more about this formula.
*
* To set channel 0's offset based on known V_offset_mV, use:
*     Batteri_ADC_SetOffset(0uL, -1 * V_offset_mV * (1uL << (Resolution - 1)) / V_ref_mV);
*
* \param chan Batteri_ADC channel number.
*
* \param offset This value is a measured value when the inputs are shorted or
* connected to the same input voltage.
*
* \return cy_en_sar_status_t
* - CY_SAR_BAD_PARAM: channel number is equal to or greater than CY_SAR_MAX_NUM_CHANNELS
* - CY_SAR_SUCCESS: offset was set successfully
*
* \sideeffect None
*
*******************************************************************************/
__STATIC_INLINE cy_en_sar_status_t Batteri_ADC_SetOffset(uint32_t chan, int16_t offset)
{
    /* Halt CPU in debug mode if channel is out of valid range */
    CY_ASSERT(chan < Batteri_ADC_allConfigs[Batteri_ADC_currentConfig].numChannels);

    return Cy_SAR_SetOffset(chan, offset);
}

/*******************************************************************************
* Function Name: Batteri_ADC_SetGain
****************************************************************************//**
*
* \brief Sets the Batteri_ADC gain in counts per 10 volt for the voltage
* conversion functions. This value is set by default by the reference and
* input range settings. Gain is applied after offset and unit scaling.  All
* CountsTo_[mV, uV, V]olts() functions use the following equation:
*     V = (Counts/AvgDivider - Offset)*TEN_VOLT/Gain
* See CountsTo_Volts() for more about this formula.
*
* To set channel 0's gain based on known V_ref_mV, use:
*     Batteri_ADC_SetGain(0uL, 10000 * (1uL << (Resolution - 1)) / V_ref_mV);
*
* \param chan Batteri_ADC channel number.
*
* \param adcGain Batteri_ADC gain in counts per 10 volt.
*
* \return cy_en_sar_status_t
* - CY_SAR_BAD_PARAM: channel number is equal to or greater than CY_SAR_MAX_NUM_CHANNELS
* - CY_SAR_SUCCESS: gain was set successfully
*
* \sideeffect None
*
*******************************************************************************/
__STATIC_INLINE cy_en_sar_status_t Batteri_ADC_SetGain(uint32_t chan, int32_t adcGain)
{
    /* Halt CPU in debug mode if channel is out of valid range */
    CY_ASSERT(chan < Batteri_ADC_allConfigs[Batteri_ADC_currentConfig].numChannels);

    return Cy_SAR_SetGain(chan, adcGain);
}

/*******************************************************************************
* Function Name: Batteri_ADC_CountsTo_Volts
****************************************************************************//**
*
* \brief Converts the ADC output to Volts as a float32. For example, if the ADC
* measured 0.534 volts, the return value would be 0.534.
* The calculation of voltage depends on the contents of Cy_SAR_offset[],
* Cy_SAR_countsPer10Volt[], and other parameters.  The equation used is:
*
*     V = (Counts/AvgDivider - Offset)*TEN_VOLT/Gain
* -Counts = Raw Counts from SAR register
* -AvgDivider = divider based on averaging mode
*     -Sequential, Sum: AvgDivider = number averaged
*         Note: The divider should be a maximum of 16. If using more averages,
*         pre-scale Counts by (number averaged / 16)
*     -Interleaved, Sum: AvgDivider = number averaged
*     -Sequential, Fixed: AvgDivider = 1
* -Offset = Cy_SAR_offset[]
* -TEN_VOLT = 10V constant and unit scalar.
* -Gain = Cy_SAR_countsPer10Volt[]
*
* When the Vref is based on Vdda, the value used for Vdda is set for the project
* in the System tab of the DWR.
*
* \param chan Batteri_ADC channel number.
*
* \param adcCounts Result from the Batteri_ADC conversion.
*
* \return Result in Volts.
*
* \sideeffect None
*
*******************************************************************************/
__STATIC_INLINE float32_t Batteri_ADC_CountsTo_Volts(uint32_t chan, int16_t adcCounts)
{
    /* Halt CPU in debug mode if channel is out of valid range */
    CY_ASSERT(chan < Batteri_ADC_allConfigs[Batteri_ADC_currentConfig].numChannels);

    return Cy_SAR_CountsTo_Volts(Batteri_ADC_SAR__HW, chan, adcCounts);
}

/*******************************************************************************
* Function Name: Batteri_ADC_CountsTo_mVolts
****************************************************************************//**
*
* \brief Converts the ADC output to millivolts as an int16. For example, if the ADC
* measured 0.534 volts, the return value would be 534.
* The calculation of voltage depends on the contents of Cy_SAR_offset[],
* Cy_SAR_countsPer10Volt[], and other parameters.  The equation used is:
*
*     V = (Counts/AvgDivider - Offset)*TEN_VOLT/Gain
* -Counts = Raw Counts from SAR register
* -AvgDivider = divider based on averaging mode
*     -Sequential, Sum: AvgDivider = number averaged
*         Note: The divider should be a maximum of 16. If using more averages,
*         pre-scale Counts by (number averaged / 16)
*     -Interleaved, Sum: AvgDivider = number averaged
*     -Sequential, Fixed: AvgDivider = 1
* -Offset = Cy_SAR_offset[]
* -TEN_VOLT = 10V constant and unit scalar.
* -Gain = Cy_SAR_countsPer10Volt[]
*
* When the Vref is based on Vdda, the value used for Vdda is set for the project
* in the System tab of the DWR.
*
* \param chan Batteri_ADC channel number.
*
* \param adcCounts Result from the Batteri_ADC conversion.
*
* \return Result in mV.
*
* \sideeffect None.
*
*******************************************************************************/
__STATIC_INLINE int16_t Batteri_ADC_CountsTo_mVolts(uint32_t chan, int16_t adcCounts)
{
    /* Halt CPU in debug mode if channel is out of valid range */
    CY_ASSERT(chan < Batteri_ADC_allConfigs[Batteri_ADC_currentConfig].numChannels);

    return Cy_SAR_CountsTo_mVolts(Batteri_ADC_SAR__HW, chan, adcCounts);
}

/*******************************************************************************
* Function Name: Batteri_ADC_CountsTo_uVolts
****************************************************************************//**
*
* \brief Converts the ADC output to microvolts as an int32. For example, if the ADC
* measured 0.534 volts, the return value would be 534000.
* The calculation of voltage depends on the contents of Cy_SAR_offset[],
* Cy_SAR_countsPer10Volt[], and other parameters.  The equation used is:
*
*     V = (Counts/AvgDivider - Offset)*TEN_VOLT/Gain
* -Counts = Raw Counts from SAR register
* -AvgDivider = divider based on averaging mode
*     -Sequential, Sum: AvgDivider = number averaged
*         Note: The divider should be a maximum of 16. If using more averages,
*         pre-scale Counts by (number averaged / 16)
*     -Interleaved, Sum: AvgDivider = number averaged
*     -Sequential, Fixed: AvgDivider = 1
* -Offset = Cy_SAR_offset[]
* -TEN_VOLT = 10V constant and unit scalar.
* -Gain = Cy_SAR_countsPer10Volt[]
*
* When the Vref is based on Vdda, the value used for Vdda is set for the project
* in the System tab of the DWR.
*
* \param chan Batteri_ADC channel number.
*
* \param adcCounts Result from the Batteri_ADC conversion.
*
* \return Result in microvolts.
*
* \sideeffect None
*
*******************************************************************************/
__STATIC_INLINE int32_t Batteri_ADC_CountsTo_uVolts(uint32_t chan, int16_t adcCounts)
{
    /* Halt CPU in debug mode if channel is out of valid range */
    CY_ASSERT(chan < Batteri_ADC_allConfigs[Batteri_ADC_currentConfig].numChannels);

    return Cy_SAR_CountsTo_uVolts(Batteri_ADC_SAR__HW, chan, adcCounts);
}

/*******************************************************************************
* Function Name: Batteri_ADC_Sleep
****************************************************************************//**
*
* \brief This is the preferred routine to prepare the component for sleep. The
* Batteri_ADC_Sleep() routine saves the current component state. Then it
* calls the Batteri_ADC_Stop() function.
*
* Calling this routine directly is not needed.
* The Batteri_ADC_DeepSleepCallbackStruct will ensure this routine
* is called before the device enters Deep Sleep mode.
*
* \param None
*
* \return None
*
* \sideeffect If this function is called twice in the enable state of the
* component, the disabled state of the component will be stored. So
* Batteri_ADC_Enable() and Batteri_ADC_StartConvert() must be called
* after Batteri_ADC_Wakeup() in this case.
*
* \globalvars
*  \ref Batteri_ADC_backup (W)
*
* \globalvars
*  \ref Batteri_ADC_backup
*
*******************************************************************************/
__STATIC_INLINE void Batteri_ADC_Sleep(void)
{
    Cy_SAR_Sleep(Batteri_ADC_SAR__HW);
}


/*******************************************************************************
* Function Name: Batteri_ADC_Wakeup
****************************************************************************//**
*
* \brief This is the preferred routine to restore the component to the state when
* Batteri_ADC_Sleep() was called.
* If the component was enabled before the Batteri_ADC_Sleep()
* function was called, the Batteri_ADC_Wakeup() function also re-enables the
* component.
*
* Calling this routine directly is not needed.
* The Batteri_ADC_DeepSleepCallbackStruct will ensure this routine
* is called after the device wakes up from Deep Sleep mode.
*
* \param None
*
* \return None
*
* \sideeffect
* Calling this function without previously calling Batteri_ADC_Sleep() may lead to
* unpredictable results.
*
* \globalvars
*  \ref Batteri_ADC_backup (R)
*
* \globalvars
*  \ref Batteri_ADC_backup
*
*******************************************************************************/
__STATIC_INLINE void Batteri_ADC_Wakeup(void)
{
    Cy_SAR_Wakeup(Batteri_ADC_SAR__HW);
}

#endif /* !defined(CY_Batteri_ADC_H) */

/* [] END OF FILE */
