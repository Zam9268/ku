/*
 * Copyright (c) 2023, Texas Instruments Incorporated - http://www.ti.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ============ ti_msp_dl_config.h =============
 *  Configured MSPM0 DriverLib module declarations
 *
 *  DO NOT EDIT - This file is generated for the MSPM0G350X
 *  by the SysConfig tool.
 */
#ifndef ti_msp_dl_config_h
#define ti_msp_dl_config_h

#define CONFIG_MSPM0G350X

#if defined(__ti_version__) || defined(__TI_COMPILER_VERSION__)
#define SYSCONFIG_WEAK __attribute__((weak))
#elif defined(__IAR_SYSTEMS_ICC__)
#define SYSCONFIG_WEAK __weak
#elif defined(__GNUC__)
#define SYSCONFIG_WEAK __attribute__((weak))
#endif

#include <ti/devices/msp/msp.h>
#include <ti/driverlib/driverlib.h>
#include <ti/driverlib/m0p/dl_core.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  ======== SYSCFG_DL_init ========
 *  Perform all required MSP DL initialization
 *
 *  This function should be called once at a point before any use of
 *  MSP DL.
 */


/* clang-format off */

#define POWER_STARTUP_DELAY                                                (16)


#define GPIO_HFXT_PORT                                                     GPIOA
#define GPIO_HFXIN_PIN                                             DL_GPIO_PIN_5
#define GPIO_HFXIN_IOMUX                                         (IOMUX_PINCM10)
#define GPIO_HFXOUT_PIN                                            DL_GPIO_PIN_6
#define GPIO_HFXOUT_IOMUX                                        (IOMUX_PINCM11)
#define CPUCLK_FREQ                                                     80000000



/* Defines for PWM_0 */
#define PWM_0_INST                                                        TIMG12
#define PWM_0_INST_IRQHandler                                  TIMG12_IRQHandler
#define PWM_0_INST_INT_IRQN                                    (TIMG12_INT_IRQn)
#define PWM_0_INST_CLK_FREQ                                             80000000
/* GPIO defines for channel 0 */
#define GPIO_PWM_0_C0_PORT                                                 GPIOA
#define GPIO_PWM_0_C0_PIN                                         DL_GPIO_PIN_14
#define GPIO_PWM_0_C0_IOMUX                                      (IOMUX_PINCM36)
#define GPIO_PWM_0_C0_IOMUX_FUNC                    IOMUX_PINCM36_PF_TIMG12_CCP0
#define GPIO_PWM_0_C0_IDX                                    DL_TIMER_CC_0_INDEX
/* GPIO defines for channel 1 */
#define GPIO_PWM_0_C1_PORT                                                 GPIOB
#define GPIO_PWM_0_C1_PIN                                         DL_GPIO_PIN_14
#define GPIO_PWM_0_C1_IOMUX                                      (IOMUX_PINCM31)
#define GPIO_PWM_0_C1_IOMUX_FUNC                    IOMUX_PINCM31_PF_TIMG12_CCP1
#define GPIO_PWM_0_C1_IDX                                    DL_TIMER_CC_1_INDEX



/* Defines for TIMER_0 */
#define TIMER_0_INST                                                     (TIMG0)
#define TIMER_0_INST_IRQHandler                                 TIMG0_IRQHandler
#define TIMER_0_INST_INT_IRQN                                   (TIMG0_INT_IRQn)
#define TIMER_0_INST_LOAD_VALUE                                         (39062U)
/* Defines for TIMER_1 */
#define TIMER_1_INST                                                     (TIMG6)
#define TIMER_1_INST_IRQHandler                                 TIMG6_IRQHandler
#define TIMER_1_INST_INT_IRQN                                   (TIMG6_INT_IRQn)
#define TIMER_1_INST_LOAD_VALUE                                          (3999U)




/* Defines for I2C_0 */
#define I2C_0_INST                                                          I2C0
#define I2C_0_INST_IRQHandler                                    I2C0_IRQHandler
#define I2C_0_INST_INT_IRQN                                        I2C0_INT_IRQn
#define I2C_0_BUS_SPEED_HZ                                                400000
#define GPIO_I2C_0_SDA_PORT                                                GPIOA
#define GPIO_I2C_0_SDA_PIN                                        DL_GPIO_PIN_10
#define GPIO_I2C_0_IOMUX_SDA                                     (IOMUX_PINCM21)
#define GPIO_I2C_0_IOMUX_SDA_FUNC                      IOMUX_PINCM21_PF_I2C0_SDA
#define GPIO_I2C_0_SCL_PORT                                                GPIOA
#define GPIO_I2C_0_SCL_PIN                                         DL_GPIO_PIN_1
#define GPIO_I2C_0_IOMUX_SCL                                      (IOMUX_PINCM2)
#define GPIO_I2C_0_IOMUX_SCL_FUNC                       IOMUX_PINCM2_PF_I2C0_SCL


/* Defines for UART_1 */
#define UART_1_INST                                                        UART1
#define UART_1_INST_IRQHandler                                  UART1_IRQHandler
#define UART_1_INST_INT_IRQN                                      UART1_INT_IRQn
#define GPIO_UART_1_RX_PORT                                                GPIOA
#define GPIO_UART_1_TX_PORT                                                GPIOA
#define GPIO_UART_1_RX_PIN                                         DL_GPIO_PIN_9
#define GPIO_UART_1_TX_PIN                                         DL_GPIO_PIN_8
#define GPIO_UART_1_IOMUX_RX                                     (IOMUX_PINCM20)
#define GPIO_UART_1_IOMUX_TX                                     (IOMUX_PINCM19)
#define GPIO_UART_1_IOMUX_RX_FUNC                      IOMUX_PINCM20_PF_UART1_RX
#define GPIO_UART_1_IOMUX_TX_FUNC                      IOMUX_PINCM19_PF_UART1_TX
#define UART_1_BAUD_RATE                                                (115200)
#define UART_1_IBRD_40_MHZ_115200_BAUD                                      (21)
#define UART_1_FBRD_40_MHZ_115200_BAUD                                      (45)
/* Defines for UART_0 */
#define UART_0_INST                                                        UART3
#define UART_0_INST_IRQHandler                                  UART3_IRQHandler
#define UART_0_INST_INT_IRQN                                      UART3_INT_IRQn
#define GPIO_UART_0_RX_PORT                                                GPIOB
#define GPIO_UART_0_TX_PORT                                                GPIOB
#define GPIO_UART_0_RX_PIN                                         DL_GPIO_PIN_3
#define GPIO_UART_0_TX_PIN                                         DL_GPIO_PIN_2
#define GPIO_UART_0_IOMUX_RX                                     (IOMUX_PINCM16)
#define GPIO_UART_0_IOMUX_TX                                     (IOMUX_PINCM15)
#define GPIO_UART_0_IOMUX_RX_FUNC                      IOMUX_PINCM16_PF_UART3_RX
#define GPIO_UART_0_IOMUX_TX_FUNC                      IOMUX_PINCM15_PF_UART3_TX
#define UART_0_BAUD_RATE                                                (115200)
#define UART_0_IBRD_80_MHZ_115200_BAUD                                      (43)
#define UART_0_FBRD_80_MHZ_115200_BAUD                                      (26)
/* Defines for UART_2 */
#define UART_2_INST                                                        UART2
#define UART_2_INST_IRQHandler                                  UART2_IRQHandler
#define UART_2_INST_INT_IRQN                                      UART2_INT_IRQn
#define GPIO_UART_2_RX_PORT                                                GPIOA
#define GPIO_UART_2_TX_PORT                                                GPIOA
#define GPIO_UART_2_RX_PIN                                        DL_GPIO_PIN_22
#define GPIO_UART_2_TX_PIN                                        DL_GPIO_PIN_21
#define GPIO_UART_2_IOMUX_RX                                     (IOMUX_PINCM47)
#define GPIO_UART_2_IOMUX_TX                                     (IOMUX_PINCM46)
#define GPIO_UART_2_IOMUX_RX_FUNC                      IOMUX_PINCM47_PF_UART2_RX
#define GPIO_UART_2_IOMUX_TX_FUNC                      IOMUX_PINCM46_PF_UART2_TX
#define UART_2_BAUD_RATE                                                  (9600)
#define UART_2_IBRD_40_MHZ_9600_BAUD                                       (260)
#define UART_2_FBRD_40_MHZ_9600_BAUD                                        (27)




/* Defines for SPI_LCD */
#define SPI_LCD_INST                                                       SPI1
#define SPI_LCD_INST_IRQHandler                                 SPI1_IRQHandler
#define SPI_LCD_INST_INT_IRQN                                     SPI1_INT_IRQn
#define GPIO_SPI_LCD_PICO_PORT                                            GPIOB
#define GPIO_SPI_LCD_PICO_PIN                                    DL_GPIO_PIN_15
#define GPIO_SPI_LCD_IOMUX_PICO                                 (IOMUX_PINCM32)
#define GPIO_SPI_LCD_IOMUX_PICO_FUNC                 IOMUX_PINCM32_PF_SPI1_PICO
#define GPIO_SPI_LCD_POCI_PORT                                            GPIOA
#define GPIO_SPI_LCD_POCI_PIN                                    DL_GPIO_PIN_16
#define GPIO_SPI_LCD_IOMUX_POCI                                 (IOMUX_PINCM38)
#define GPIO_SPI_LCD_IOMUX_POCI_FUNC                 IOMUX_PINCM38_PF_SPI1_POCI
/* GPIO configuration for SPI_LCD */
#define GPIO_SPI_LCD_SCLK_PORT                                            GPIOA
#define GPIO_SPI_LCD_SCLK_PIN                                    DL_GPIO_PIN_17
#define GPIO_SPI_LCD_IOMUX_SCLK                                 (IOMUX_PINCM39)
#define GPIO_SPI_LCD_IOMUX_SCLK_FUNC                 IOMUX_PINCM39_PF_SPI1_SCLK



/* Port definition for Pin Group GPIO_LEDS */
#define GPIO_LEDS_PORT                                                   (GPIOA)

/* Defines for LED_0: GPIOA.0 with pinCMx 1 on package pin 33 */
#define GPIO_LEDS_LED_0_PIN                                      (DL_GPIO_PIN_0)
#define GPIO_LEDS_LED_0_IOMUX                                     (IOMUX_PINCM1)
/* Port definition for Pin Group KEYA */
#define KEYA_PORT                                                        (GPIOA)

/* Defines for S2: GPIOA.18 with pinCMx 40 on package pin 11 */
#define KEYA_S2_PIN                                             (DL_GPIO_PIN_18)
#define KEYA_S2_IOMUX                                            (IOMUX_PINCM40)
/* Port definition for Pin Group KEYB */
#define KEYB_PORT                                                        (GPIOB)

/* Defines for S3: GPIOB.21 with pinCMx 49 on package pin 20 */
#define KEYB_S3_PIN                                             (DL_GPIO_PIN_21)
#define KEYB_S3_IOMUX                                            (IOMUX_PINCM49)
/* Port definition for Pin Group GPIO_RGBS */
#define GPIO_RGBS_PORT                                                   (GPIOB)

/* Defines for RGB_B: GPIOB.22 with pinCMx 50 on package pin 21 */
#define GPIO_RGBS_RGB_B_PIN                                     (DL_GPIO_PIN_22)
#define GPIO_RGBS_RGB_B_IOMUX                                    (IOMUX_PINCM50)
/* Defines for RGB_R: GPIOB.26 with pinCMx 57 on package pin 28 */
#define GPIO_RGBS_RGB_R_PIN                                     (DL_GPIO_PIN_26)
#define GPIO_RGBS_RGB_R_IOMUX                                    (IOMUX_PINCM57)
/* Defines for RGB_G: GPIOB.27 with pinCMx 58 on package pin 29 */
#define GPIO_RGBS_RGB_G_PIN                                     (DL_GPIO_PIN_27)
#define GPIO_RGBS_RGB_G_IOMUX                                    (IOMUX_PINCM58)
/* Port definition for Pin Group GPIO_KEY */
#define GPIO_KEY_PORT                                                    (GPIOB)

/* Defines for KEY_2: GPIOB.23 with pinCMx 51 on package pin 22 */
#define GPIO_KEY_KEY_2_PIN                                      (DL_GPIO_PIN_23)
#define GPIO_KEY_KEY_2_IOMUX                                     (IOMUX_PINCM51)
/* Defines for KEY_3: GPIOB.24 with pinCMx 52 on package pin 23 */
#define GPIO_KEY_KEY_3_PIN                                      (DL_GPIO_PIN_24)
#define GPIO_KEY_KEY_3_IOMUX                                     (IOMUX_PINCM52)
/* Port definition for Pin Group PORTA */
#define PORTA_PORT                                                       (GPIOA)

/* Defines for BEEP: GPIOA.27 with pinCMx 60 on package pin 31 */
#define PORTA_BEEP_PIN                                          (DL_GPIO_PIN_27)
#define PORTA_BEEP_IOMUX                                         (IOMUX_PINCM60)
/* Defines for AIN1: GPIOA.4 with pinCMx 9 on package pin 44 */
#define PORTA_AIN1_PIN                                           (DL_GPIO_PIN_4)
#define PORTA_AIN1_IOMUX                                          (IOMUX_PINCM9)
/* Defines for BIN1: GPIOA.7 with pinCMx 14 on package pin 49 */
#define PORTA_BIN1_PIN                                           (DL_GPIO_PIN_7)
#define PORTA_BIN1_IOMUX                                         (IOMUX_PINCM14)
/* Defines for BIN2: GPIOA.3 with pinCMx 8 on package pin 43 */
#define PORTA_BIN2_PIN                                           (DL_GPIO_PIN_3)
#define PORTA_BIN2_IOMUX                                          (IOMUX_PINCM8)
/* Port definition for Pin Group PORTB */
#define PORTB_PORT                                                       (GPIOB)

/* Defines for B1: GPIOB.8 with pinCMx 25 on package pin 60 */
#define PORTB_B1_PIN                                             (DL_GPIO_PIN_8)
#define PORTB_B1_IOMUX                                           (IOMUX_PINCM25)
/* Defines for B2: GPIOB.9 with pinCMx 26 on package pin 61 */
#define PORTB_B2_PIN                                             (DL_GPIO_PIN_9)
#define PORTB_B2_IOMUX                                           (IOMUX_PINCM26)
/* Defines for B3: GPIOB.10 with pinCMx 27 on package pin 62 */
#define PORTB_B3_PIN                                            (DL_GPIO_PIN_10)
#define PORTB_B3_IOMUX                                           (IOMUX_PINCM27)
/* Defines for B4: GPIOB.11 with pinCMx 28 on package pin 63 */
#define PORTB_B4_PIN                                            (DL_GPIO_PIN_11)
#define PORTB_B4_IOMUX                                           (IOMUX_PINCM28)
/* Defines for B5: GPIOB.12 with pinCMx 29 on package pin 64 */
#define PORTB_B5_PIN                                            (DL_GPIO_PIN_12)
#define PORTB_B5_IOMUX                                           (IOMUX_PINCM29)
/* Defines for AC1: GPIOB.5 with pinCMx 18 on package pin 53 */
// pins affected by this interrupt request:["AC1","BC1","AC2","BC2"]
#define PORTB_INT_IRQN                                          (GPIOB_INT_IRQn)
#define PORTB_INT_IIDX                          (DL_INTERRUPT_GROUP1_IIDX_GPIOB)
#define PORTB_AC1_IIDX                                       (DL_GPIO_IIDX_DIO5)
#define PORTB_AC1_PIN                                            (DL_GPIO_PIN_5)
#define PORTB_AC1_IOMUX                                          (IOMUX_PINCM18)
/* Defines for BC1: GPIOB.4 with pinCMx 17 on package pin 52 */
#define PORTB_BC1_IIDX                                       (DL_GPIO_IIDX_DIO4)
#define PORTB_BC1_PIN                                            (DL_GPIO_PIN_4)
#define PORTB_BC1_IOMUX                                          (IOMUX_PINCM17)
/* Defines for AC2: GPIOB.7 with pinCMx 24 on package pin 59 */
#define PORTB_AC2_IIDX                                       (DL_GPIO_IIDX_DIO7)
#define PORTB_AC2_PIN                                            (DL_GPIO_PIN_7)
#define PORTB_AC2_IOMUX                                          (IOMUX_PINCM24)
/* Defines for BC2: GPIOB.6 with pinCMx 23 on package pin 58 */
#define PORTB_BC2_IIDX                                       (DL_GPIO_IIDX_DIO6)
#define PORTB_BC2_PIN                                            (DL_GPIO_PIN_6)
#define PORTB_BC2_IOMUX                                          (IOMUX_PINCM23)
/* Defines for AIN2: GPIOB.0 with pinCMx 12 on package pin 47 */
#define PORTB_AIN2_PIN                                           (DL_GPIO_PIN_0)
#define PORTB_AIN2_IOMUX                                         (IOMUX_PINCM12)
/* Port definition for Pin Group GPIO_LCD */
#define GPIO_LCD_PORT                                                    (GPIOB)

/* Defines for LCD_RSD: GPIOB.16 with pinCMx 33 on package pin 4 */
#define GPIO_LCD_LCD_RSD_PIN                                    (DL_GPIO_PIN_16)
#define GPIO_LCD_LCD_RSD_IOMUX                                   (IOMUX_PINCM33)
/* Defines for LCD_DC: GPIOB.17 with pinCMx 43 on package pin 14 */
#define GPIO_LCD_LCD_DC_PIN                                     (DL_GPIO_PIN_17)
#define GPIO_LCD_LCD_DC_IOMUX                                    (IOMUX_PINCM43)
/* Defines for LCD_CS: GPIOB.20 with pinCMx 48 on package pin 19 */
#define GPIO_LCD_LCD_CS_PIN                                     (DL_GPIO_PIN_20)
#define GPIO_LCD_LCD_CS_IOMUX                                    (IOMUX_PINCM48)



/* clang-format on */

void SYSCFG_DL_init(void);
void SYSCFG_DL_initPower(void);
void SYSCFG_DL_GPIO_init(void);
void SYSCFG_DL_SYSCTL_init(void);
void SYSCFG_DL_SYSCTL_CLK_init(void);
void SYSCFG_DL_PWM_0_init(void);
void SYSCFG_DL_TIMER_0_init(void);
void SYSCFG_DL_TIMER_1_init(void);
void SYSCFG_DL_I2C_0_init(void);
void SYSCFG_DL_UART_1_init(void);
void SYSCFG_DL_UART_0_init(void);
void SYSCFG_DL_UART_2_init(void);
void SYSCFG_DL_SPI_LCD_init(void);

void SYSCFG_DL_SYSTICK_init(void);

bool SYSCFG_DL_saveConfiguration(void);
bool SYSCFG_DL_restoreConfiguration(void);

#ifdef __cplusplus
}
#endif

#endif /* ti_msp_dl_config_h */
