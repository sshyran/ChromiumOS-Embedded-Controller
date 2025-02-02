/* Copyright 2019 The Chromium OS Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

/**
 * @file
 * @brief Register map for the STM32F4 family of chips
 *
 * This header file should not be included directly.
 * Please include registers.h instead.
 *
 * Known Chip Variants
 * - STM32F411
 * - STM32F412
 * - STM32F41X
 * - STM32F446
 */

#ifndef __CROS_EC_REGISTERS_H
#error "This header file should not be included directly."
#endif

/* --- IRQ numbers --- */
#define STM32_IRQ_WWDG             0
#define STM32_IRQ_PVD              1
#define STM32_IRQ_TAMPER_STAMP     2
#define STM32_IRQ_RTC_WAKEUP       3
#define STM32_IRQ_FLASH            4
#define STM32_IRQ_RCC              5
#define STM32_IRQ_EXTI0            6
#define STM32_IRQ_EXTI1            7
#define STM32_IRQ_EXTI2            8
#define STM32_IRQ_EXTI3            9
#define STM32_IRQ_EXTI4           10
#define STM32_IRQ_DMA_CHANNEL_1   11
#define STM32_IRQ_DMA_CHANNEL_2   12
#define STM32_IRQ_DMA_CHANNEL_3   13
#define STM32_IRQ_DMA_CHANNEL_4   14
#define STM32_IRQ_DMA_CHANNEL_5   15
#define STM32_IRQ_DMA_CHANNEL_6   16
#define STM32_IRQ_DMA_CHANNEL_7   17
#define STM32_IRQ_USB_HP          19
#define STM32_IRQ_USB_LP          20

#define STM32_IRQ_ADC1            18 /* STM32L4 only */
#define STM32_IRQ_CAN_TX          19 /* STM32F373 only */
#define STM32_IRQ_USB_LP_CAN_RX   20 /* STM32F373 only */
#define STM32_IRQ_DAC             21
#define STM32_IRQ_CAN_RX1         21 /* STM32F373 only */

#define STM32_IRQ_COMP            22

#define STM32_IRQ_CAN_SCE         22 /* STM32F373 only */
#define STM32_IRQ_EXTI9_5         23
#define STM32_IRQ_LCD             24 /* STM32L15X only */
#define STM32_IRQ_TIM15           24 /* STM32F373 only */
#if defined(CHIP_VARIANT_STM32F412)
#define STM32_IRQ_TIM9            24 /* STM32F412 only */
#else
#define STM32_IRQ_TIM9            25 /* STM32L15X only */
#endif
#define STM32_IRQ_TIM16           25 /* STM32F373 only */
#define STM32_IRQ_TIM10           26 /* STM32L15X only */
#define STM32_IRQ_TIM17           26 /* STM32F373 only */
#define STM32_IRQ_TIM11           27 /* STM32L15X only */
#define STM32_IRQ_TIM18_DAC2      27 /* STM32F373 only */
#define STM32_IRQ_TIM2            28
#define STM32_IRQ_TIM3            29
#define STM32_IRQ_TIM4            30
#define STM32_IRQ_I2C1_EV         31
#define STM32_IRQ_I2C1_ER         32
#define STM32_IRQ_I2C2_EV         33
#define STM32_IRQ_I2C2_ER         34
#define STM32_IRQ_SPI1            35
#define STM32_IRQ_SPI2            36
#define STM32_IRQ_USART1          37
#define STM32_IRQ_USART2          38
#define STM32_IRQ_USART3          39
#define STM32_IRQ_EXTI15_10       40
#define STM32_IRQ_RTC_ALARM       41
#define STM32_IRQ_USB_FS_WAKEUP   42 /* STM32L15X */
#define STM32_IRQ_CEC             42 /* STM32F373 only */
#define STM32_IRQ_TIM6_BASIC      43 /* STM32L15X only */
#define STM32_IRQ_TIM12           43 /* STM32F373 only */
#define STM32_IRQ_TIM7_BASIC      44 /* STM32L15X only */
#define STM32_IRQ_TIM13           44 /* STM32F373 only */
#define STM32_IRQ_TIM14           45 /* STM32F373 only */
#define STM32_IRQ_TIM5            50 /* STM32F373 */
#define STM32_IRQ_SPI3            51 /* STM32F373 */
#define STM32_IRQ_USART4          52 /* STM32F446 only */
#define STM32_IRQ_USART5          53 /* STM32F446 only */
#define STM32_IRQ_TIM6_DAC        54 /* STM32F373 */
#define STM32_IRQ_TIM7            55 /* STM32F373 */
#define STM32_IRQ_DMA2_CHANNEL1   56 /* STM32F373 */
#define STM32_IRQ_DMA2_CHANNEL2   57 /* STM32F373 */
#define STM32_IRQ_DMA2_CHANNEL3   58 /* STM32F373 */
#define STM32_IRQ_DMA2_CHANNEL4   59 /* STM32F373 only */
/* if MISC_REMAP bits are set */
#define STM32_IRQ_DMA2_CHANNEL5   60 /* STM32F373 */
#define STM32_IRQ_SDADC1          61 /* STM32F373 only */
#define STM32_IRQ_SDADC2          62 /* STM32F373 only */
#define STM32_IRQ_SDADC3          63 /* STM32F373 only */
#define STM32_IRQ_DMA2_CHANNEL6   68 /* STM32L4 only */
#define STM32_IRQ_DMA2_CHANNEL7   69 /* STM32L4 only */
#define STM32_IRQ_LPUART          70 /* STM32L4 only */
#define STM32_IRQ_USART9          70 /* STM32L4 only */
#define STM32_IRQ_USART6          71 /* STM32F446 only */
#define STM32_IRQ_I2C3_EV         72 /* STM32F446 only */
#define STM32_IRQ_I2C3_ER         73 /* STM32F446 only */
#define STM32_IRQ_USB_WAKEUP      76 /* STM32F373 only */
#define STM32_IRQ_TIM19           78 /* STM32F373 only */
#define STM32_IRQ_AES             79 /* STM32L4 only */
#define STM32_IRQ_RNG             80 /* STM32L4 only */
#define STM32_IRQ_FPU             81 /* STM32F373 only */


/* To simplify code generation, define DMA channel 9..10 */
#define STM32_IRQ_DMA_CHANNEL_9    STM32_IRQ_DMA2_CHANNEL1
#define STM32_IRQ_DMA_CHANNEL_10   STM32_IRQ_DMA2_CHANNEL2
#define STM32_IRQ_DMA_CHANNEL_13   STM32_IRQ_DMA2_CHANNEL6
#define STM32_IRQ_DMA_CHANNEL_14   STM32_IRQ_DMA2_CHANNEL7

/* aliases for easier code sharing */
#define STM32_IRQ_I2C1 STM32_IRQ_I2C1_EV
#define STM32_IRQ_I2C2 STM32_IRQ_I2C2_EV
#define STM32_IRQ_I2C3 STM32_IRQ_I2C3_EV

#if defined(CHIP_VARIANT_STM32F411) || defined(CHIP_VARIANT_STM32F412)
#define CHIP_VARIANT_STM32F41X
#endif

/*
 * STM32F4 introduces a concept of DMA stream to allow
 * fine allocation of a stream to a channel.
 */
#define STM32_IRQ_DMA1_STREAM0    11
#define STM32_IRQ_DMA1_STREAM1    12
#define STM32_IRQ_DMA1_STREAM2    13
#define STM32_IRQ_DMA1_STREAM3    14
#define STM32_IRQ_DMA1_STREAM4    15
#define STM32_IRQ_DMA1_STREAM5    16
#define STM32_IRQ_DMA1_STREAM6    17
#define STM32_IRQ_DMA1_STREAM7    47
#define STM32_IRQ_DMA2_STREAM0    56
#define STM32_IRQ_DMA2_STREAM1    57
#define STM32_IRQ_DMA2_STREAM2    58
#define STM32_IRQ_DMA2_STREAM3    59
#define STM32_IRQ_DMA2_STREAM4    60
#define STM32_IRQ_DMA2_STREAM5    68
#define STM32_IRQ_DMA2_STREAM6    69
#define STM32_IRQ_DMA2_STREAM7    70

#define STM32_IRQ_OTG_HS_WKUP     76
#define STM32_IRQ_OTG_HS_EP1_IN   75
#define STM32_IRQ_OTG_HS_EP1_OUT  74
#define STM32_IRQ_OTG_HS          77
#define STM32_IRQ_OTG_FS          67
#define STM32_IRQ_OTG_FS_WKUP     42

/* Peripheral base addresses */
#define STM32_ADC1_BASE             0x40012000
#define STM32_ADC_BASE              0x40012300

#define STM32_CEC_BASE              0x40007800 /* STM32F373 */
#define STM32_CRC_BASE              0x40023000
#define STM32_CRS_BASE              0x40006c00 /* STM32F0XX */
#define STM32_DAC_BASE              0x40007400


#define STM32_DBGMCU_BASE           0xE0042000

#define STM32_DMA1_BASE             0x40026000
#define STM32_DMA2_BASE             0x40026400

#define STM32_EXTI_BASE             0x40013C00

#define STM32_FLASH_REGS_BASE       0x40023c00

#define STM32_GPIOA_BASE            0x40020000
#define STM32_GPIOB_BASE            0x40020400
#define STM32_GPIOC_BASE            0x40020800
#define STM32_GPIOD_BASE            0x40020C00
#define STM32_GPIOE_BASE            0x40021000
#define STM32_GPIOF_BASE            0x40021400 /* see RM0402/0390 table 1 */
#define STM32_GPIOG_BASE            0x40021800
#define STM32_GPIOH_BASE            0x40021C00

#define STM32_I2C1_BASE             0x40005400
#define STM32_I2C2_BASE             0x40005800
#define STM32_I2C3_BASE             0x40005C00
#define STM32_I2C4_BASE             0x40006000

#define STM32_IWDG_BASE             0x40003000
#define STM32_LCD_BASE              0x40002400

#define STM32_OPTB_BASE             0x1FFFC000
#define STM32_OTP_BASE              0x1FFF7800

#define STM32_PMSE_BASE             0x40013400
#define STM32_PWR_BASE              0x40007000

#define STM32_RCC_BASE              0x40023800

#define STM32_RI_BASE               0x40007C00 /* STM32L1xx only */
#define STM32_RNG_BASE              0x50060800 /* STM32L4 */
#define STM32_RTC_BASE              0x40002800

#define STM32_SPI1_BASE             0x40013000
#define STM32_SPI2_BASE             0x40003800
#define STM32_SPI3_BASE             0x40003c00 /* STM32F373, STM32L4, STM32F7 */

#define STM32_SYSCFG_BASE           0x40013800

#define STM32_TIM1_BASE             0x40012c00 /* STM32F373 */
#define STM32_TIM2_BASE             0x40000000
#define STM32_TIM3_BASE             0x40000400
#define STM32_TIM4_BASE             0x40000800
#define STM32_TIM5_BASE             0x40000c00 /* STM32F373 */
#define STM32_TIM6_BASE             0x40001000
#define STM32_TIM7_BASE             0x40001400
#define STM32_TIM9_BASE             0x40014000 /* STM32F41x only */
#define STM32_TIM10_BASE            0x40014400 /* STM32F41x only */
#define STM32_TIM11_BASE            0x40014800 /* STM32F41x only */
#define STM32_TIM12_BASE            0x40001800 /* STM32F373 */
#define STM32_TIM13_BASE            0x40001c00 /* STM32F373 */
#define STM32_TIM14_BASE            0x40002000 /* STM32F373 */
#define STM32_TIM15_BASE            0x40014000
#define STM32_TIM16_BASE            0x40014400
#define STM32_TIM17_BASE            0x40014800
#define STM32_TIM18_BASE            0x40009c00 /* STM32F373 only */
#define STM32_TIM19_BASE            0x40015c00 /* STM32F373 only */

#define STM32_UNIQUE_ID_BASE        0x1fff7a10

#define STM32_USART1_BASE           0x40011000
#define STM32_USART2_BASE           0x40004400
#define STM32_USART3_BASE           0x40004800
#define STM32_USART4_BASE           0x40004c00
#define STM32_USART5_BASE           0x40005000
#define STM32_USART6_BASE           0x40011400

#define STM32_USB_CAN_SRAM_BASE     0x40006000
#define STM32_USB_FS_BASE           0x40005C00

#define STM32_WWDG_BASE             0x40002C00


#ifndef __ASSEMBLER__

/* Register definitions */

/* --- USART --- */
#define STM32_USART_SR(base)       STM32_USART_REG(base, 0x00)
#define STM32_USART_SR_ORE		BIT(3)
#define STM32_USART_SR_RXNE		BIT(5)
#define STM32_USART_SR_TC		BIT(6)
#define STM32_USART_SR_TXE		BIT(7)
#define STM32_USART_DR(base)       STM32_USART_REG(base, 0x04)
#define STM32_USART_BRR(base)      STM32_USART_REG(base, 0x08)
#define STM32_USART_CR1(base)      STM32_USART_REG(base, 0x0C)
#define STM32_USART_CR1_RE		BIT(2)
#define STM32_USART_CR1_TE		BIT(3)
#define STM32_USART_CR1_RXNEIE		BIT(5)
#define STM32_USART_CR1_TCIE		BIT(6)
#define STM32_USART_CR1_TXEIE		BIT(7)
#define STM32_USART_CR1_PS		BIT(9)
#define STM32_USART_CR1_PCE		BIT(10)
#define STM32_USART_CR1_M		BIT(12)
#define STM32_USART_CR1_UE		BIT(13)
#define STM32_USART_CR1_OVER8		BIT(15) /* STM32L only */
#define STM32_USART_CR2(base)      STM32_USART_REG(base, 0x10)
#define STM32_USART_CR3(base)      STM32_USART_REG(base, 0x14)
#define STM32_USART_CR3_EIE		BIT(0)
#define STM32_USART_CR3_DMAR		BIT(6)
#define STM32_USART_CR3_DMAT		BIT(7)
#define STM32_USART_CR3_ONEBIT		BIT(11) /* STM32L only */
#define STM32_USART_GTPR(base)     STM32_USART_REG(base, 0x18)
/* register aliases */
#define STM32_USART_TDR(base)      STM32_USART_DR(base)
#define STM32_USART_RDR(base)      STM32_USART_DR(base)

/* --- GPIO --- */
#define STM32_GPIO_MODER(b)     REG32((b) + 0x00)
#define STM32_GPIO_OTYPER(b)    REG16((b) + 0x04)
#define STM32_GPIO_OSPEEDR(b)   REG32((b) + 0x08)
#define STM32_GPIO_PUPDR(b)     REG32((b) + 0x0C)
#define STM32_GPIO_IDR(b)       REG16((b) + 0x10)
#define STM32_GPIO_ODR(b)       REG16((b) + 0x14)
#define STM32_GPIO_BSRR(b)      REG32((b) + 0x18)
#define STM32_GPIO_LCKR(b)      REG32((b) + 0x1C)
#define STM32_GPIO_AFRL(b)      REG32((b) + 0x20)
#define STM32_GPIO_AFRH(b)      REG32((b) + 0x24)

#define GPIO_ALT_SYS                 0x0
#define GPIO_ALT_TIM2                0x1
#define GPIO_ALT_TIM3_4              0x2
#define GPIO_ALT_TIM9_11             0x3
#define GPIO_ALT_I2C                 0x4
#define GPIO_ALT_SPI                 0x5
#define GPIO_ALT_SPI3                0x6
#define GPIO_ALT_USART               0x7
#define GPIO_ALT_I2C_23              0x9
#define GPIO_ALT_USB                 0xA
#define GPIO_ALT_LCD                 0xB
#define GPIO_ALT_RI                  0xE
#define GPIO_ALT_EVENTOUT            0xF

/* --- I2C --- */
#define STM32_I2C_CR1(n)            REG16(stm32_i2c_reg(n, 0x00))
#define STM32_I2C_CR1_PE	BIT(0)
#define STM32_I2C_CR1_START	BIT(8)
#define STM32_I2C_CR1_STOP	BIT(9)
#define STM32_I2C_CR1_ACK	BIT(10)
#define STM32_I2C_CR1_POS	BIT(11)
#define STM32_I2C_CR1_SWRST	BIT(15)
#define STM32_I2C_CR2(n)            REG16(stm32_i2c_reg(n, 0x04))
#define STM32_I2C_CR2_ITERREN	BIT(8)
#define STM32_I2C_CR2_ITEVTEN	BIT(9)
#define STM32_I2C_CR2_ITBUFEN	BIT(10)
#define STM32_I2C_CR2_DMAEN	BIT(11)
#define STM32_I2C_CR2_LAST	BIT(12)
#define STM32_I2C_OAR1(n)           REG16(stm32_i2c_reg(n, 0x08))
#define STM32_I2C_OAR1_B14	BIT(14)
#define STM32_I2C_OAR2(n)           REG16(stm32_i2c_reg(n, 0x0C))
#define STM32_I2C_OAR2_ENDUAL	BIT(0)
#define STM32_I2C_DR(n)             REG16(stm32_i2c_reg(n, 0x10))
#define STM32_I2C_SR1(n)            REG16(stm32_i2c_reg(n, 0x14))
#define STM32_I2C_SR1_SB	BIT(0)
#define STM32_I2C_SR1_ADDR	BIT(1)
#define STM32_I2C_SR1_BTF	BIT(2)
#define STM32_I2C_SR1_STOPF	BIT(4)
#define STM32_I2C_SR1_RXNE	BIT(6)
#define STM32_I2C_SR1_TXE	BIT(7)
#define STM32_I2C_SR1_BERR	BIT(8)
#define STM32_I2C_SR1_ARLO	BIT(9)
#define STM32_I2C_SR1_AF	BIT(10)

#define STM32_I2C_SR2(n)            REG16(stm32_i2c_reg(n, 0x18))
#define STM32_I2C_SR2_BUSY	BIT(1)
#define STM32_I2C_SR2_TRA	BIT(2)
#define STM32_I2C_SR2_DUALF	BIT(7)

#define STM32_I2C_CCR(n)            REG16(stm32_i2c_reg(n, 0x1C))
#define STM32_I2C_CCR_DUTY	BIT(14)
#define STM32_I2C_CCR_FM	BIT(15)
#define STM32_I2C_TRISE(n)          REG16(stm32_i2c_reg(n, 0x20))

#define STM32_FMPI2C_CR1(n)        REG32(stm32_i2c_reg(n, 0x00))
#define  FMPI2C_CR1_PE             BIT(0)
#define  FMPI2C_CR1_TXDMAEN        BIT(14)
#define  FMPI2C_CR1_RXDMAEN        BIT(15)
#define STM32_FMPI2C_CR2(n)        REG32(stm32_i2c_reg(n, 0x04))
#define  FMPI2C_CR2_RD_WRN         BIT(10)
#define  FMPI2C_READ               1
#define  FMPI2C_WRITE              0
#define  FMPI2C_CR2_START          BIT(13)
#define  FMPI2C_CR2_STOP           BIT(14)
#define  FMPI2C_CR2_NACK           BIT(15)
#define  FMPI2C_CR2_RELOAD         BIT(24)
#define  FMPI2C_CR2_AUTOEND        BIT(25)
#define  FMPI2C_CR2_SADD(addr)     ((addr) & 0x3ff)
#define  FMPI2C_CR2_SADD_MASK      FMPI2C_CR2_SADD(0x3ff)
#define  FMPI2C_CR2_SIZE(size)     (((size) & 0xff) << 16)
#define  FMPI2C_CR2_SIZE_MASK      FMPI2C_CR2_SIZE(0xf)
#define STM32_FMPI2C_OAR1(n)       REG32(stm32_i2c_reg(n, 0x08))
#define STM32_FMPI2C_OAR2(n)       REG32(stm32_i2c_reg(n, 0x0C))
#define STM32_FMPI2C_TIMINGR(n)    REG32(stm32_i2c_reg(n, 0x10))
#define  TIMINGR_THE_RIGHT_VALUE   0xC0000E12
#define  FMPI2C_TIMINGR_PRESC(val) (((val) & 0xf) << 28)
#define  FMPI2C_TIMINGR_SCLDEL(val) (((val) & 0xf) << 20)
#define  FMPI2C_TIMINGR_SDADEL(val) (((val) & 0xf) << 16)
#define  FMPI2C_TIMINGR_SCLH(val)  (((val) & 0xff) << 8)
#define  FMPI2C_TIMINGR_SCLL(val)  (((val) & 0xff) << 0)
#define STM32_FMPI2C_TIMEOUTR(n)   REG32(stm32_i2c_reg(n, 0x14))

#define STM32_FMPI2C_ISR(n)        REG32(stm32_i2c_reg(n, 0x18))
#define  FMPI2C_ISR_TXE            BIT(0)
#define  FMPI2C_ISR_TXIS           BIT(1)
#define  FMPI2C_ISR_RXNE           BIT(2)
#define  FMPI2C_ISR_ADDR           BIT(3)
#define  FMPI2C_ISR_NACKF          BIT(4)
#define  FMPI2C_ISR_STOPF          BIT(5)
#define  FMPI2C_ISR_BERR           BIT(8)
#define  FMPI2C_ISR_ARLO           BIT(9)
#define  FMPI2C_ISR_BUSY           BIT(15)
#define STM32_FMPI2C_ICR(n)        REG32(stm32_i2c_reg(n, 0x1C))

#define STM32_FMPI2C_PECR(n)       REG32(stm32_i2c_reg(n, 0x20))
#define STM32_FMPI2C_RXDR(n)       REG32(stm32_i2c_reg(n, 0x24))
#define STM32_FMPI2C_TXDR(n)       REG32(stm32_i2c_reg(n, 0x28))

/* --- Power / Reset / Clocks --- */
#define STM32_PWR_CSR               REG32(STM32_PWR_BASE + 0x04)


#define STM32_RCC_CR                    REG32(STM32_RCC_BASE + 0x00)
#define STM32_RCC_CR_HSION		BIT(0)
#define STM32_RCC_CR_HSIRDY		BIT(1)
#define STM32_RCC_CR_HSEON		BIT(16)
#define STM32_RCC_CR_HSERDY		BIT(17)
#define STM32_RCC_CR_PLLON		BIT(24)
#define STM32_RCC_CR_PLLRDY		BIT(25)

#if defined(CHIP_VARIANT_STM32F446)
/* Required or recommended clocks for stm32f446 */
#define STM32F4_PLL_REQ 2000000
#define STM32F4_RTC_REQ 1000000
#define STM32F4_IO_CLOCK  42000000
#define STM32F4_USB_REQ 48000000
#define STM32F4_VCO_CLOCK 336000000
#define STM32F4_HSI_CLOCK 16000000
#define STM32F4_LSI_CLOCK 32000
#define STM32F4_TIMER_CLOCK STM32F4_IO_CLOCK
#define STM32F4_PLLP_DIV 4
#define STM32F4_AHB_PRE 0x8
#define STM32F4_APB1_PRE 0x0
#define STM32F4_APB2_PRE 0x0
#define STM32_FLASH_ACR_LATENCY     BIT(0)
/* optimized flash latency for < 30Mhz clock (0-WS) e.g. HSI/HSE */
#define STM32_FLASH_ACR_LATENCY_SLOW      0

#elif defined(CHIP_VARIANT_STM32F412)
/* Required or recommended clocks for stm32f412 */
#define STM32F4_PLL_REQ 2000000
#define STM32F4_RTC_REQ 1000000
#define STM32F4_IO_CLOCK  48000000
#define STM32F4_USB_REQ 48000000
#define STM32F4_VCO_CLOCK 384000000
#define STM32F4_HSI_CLOCK 16000000
#define STM32F4_LSI_CLOCK 32000
#define STM32F4_TIMER_CLOCK (STM32F4_IO_CLOCK * 2)
#define STM32F4_PLLP_DIV 4
#define STM32F4_AHB_PRE 0x0
#define STM32F4_APB1_PRE 0x4
#define STM32F4_APB2_PRE 0x4
#define STM32_FLASH_ACR_LATENCY     (3 << 0)
/* optimized flash latency for < 30Mhz clock (0-WS) e.g. HSI/HSE */
#define STM32_FLASH_ACR_LATENCY_SLOW      0

#elif defined(CHIP_VARIANT_STM32F411)
/* Required or recommended clocks for stm32f411 */
#define STM32F4_PLL_REQ 2000000
#define STM32F4_RTC_REQ 1000000
#define STM32F4_IO_CLOCK  48000000
#define STM32F4_USB_REQ 48000000
#define STM32F4_VCO_CLOCK 384000000
#define STM32F4_HSI_CLOCK 16000000
#define STM32F4_LSI_CLOCK 32000
#define STM32F4_TIMER_CLOCK STM32F4_IO_CLOCK
#define STM32F4_PLLP_DIV 4
#define STM32F4_AHB_PRE 0x8
#define STM32F4_APB1_PRE 0x0
#define STM32F4_APB2_PRE 0x0
#define STM32_FLASH_ACR_LATENCY     BIT(0)
/* optimized flash latency for < 30Mhz clock (0-WS) e.g. HSI/HSE */
#define STM32_FLASH_ACR_LATENCY_SLOW    0

#elif defined(CHIP_VARIANT_STM32F76X)
/* Required or recommended clocks for stm32f767/769 */
#define STM32F4_PLL_REQ 2000000
#define STM32F4_RTC_REQ 1000000
#define STM32F4_IO_CLOCK 45000000
#define STM32F4_USB_REQ 45000000 /* not compatible with USB, will use PLLSAI */
#define STM32F4_VCO_CLOCK 360000000
#define STM32F4_HSI_CLOCK 16000000
#define STM32F4_LSI_CLOCK 32000
#define STM32F4_TIMER_CLOCK (STM32F4_IO_CLOCK * 2)
#define STM32F4_PLLP_DIV 2   /* sys = VCO/2  = 180 Mhz */
#define STM32F4_AHB_PRE 0x0  /* AHB = sysclk = 180 Mhz */
#define STM32F4_APB1_PRE 0x5 /* APB1 = AHB /4 = 45 Mhz */
#define STM32F4_APB2_PRE 0x5 /* APB2 = AHB /4 = 45 Mhz */
#define STM32_FLASH_ACR_LATENCY     (5 << 0)
/* optimized flash latency for < 30Mhz clock (0-WS) e.g. HSI/HSE */
#define STM32_FLASH_ACR_LATENCY_SLOW      0

#else
#error "No valid clocks defined"
#endif

#define STM32_RCC_PLLCFGR               REG32(STM32_RCC_BASE + 0x04)
/* PLL Division factor */
#define  PLLCFGR_PLLM_OFF		0
#define  PLLCFGR_PLLM(val)		(((val) & 0x1f) << PLLCFGR_PLLM_OFF)
/* PLL Multiplication factor */
#define  PLLCFGR_PLLN_OFF		6
#define  PLLCFGR_PLLN(val)		(((val) & 0x1ff) << PLLCFGR_PLLN_OFF)
/* Main CPU Clock */
#define  PLLCFGR_PLLP_OFF		16
#define  PLLCFGR_PLLP(val)		(((val) & 0x3) << PLLCFGR_PLLP_OFF)

#define  PLLCFGR_PLLSRC_HSI		(0 << 22)
#define  PLLCFGR_PLLSRC_HSE		BIT(22)
/* USB OTG FS: Must equal 48MHz */
#define  PLLCFGR_PLLQ_OFF		24
#define  PLLCFGR_PLLQ(val)		(((val) & 0xf) << PLLCFGR_PLLQ_OFF)
/* SYSTEM */
#define  PLLCFGR_PLLR_OFF		28
#define  PLLCFGR_PLLR(val)		(((val) & 0x7) << PLLCFGR_PLLR_OFF)

#define STM32_RCC_CFGR                  REG32(STM32_RCC_BASE + 0x08)
#define STM32_RCC_CFGR_SW_HSI		(0 << 0)
#define STM32_RCC_CFGR_SW_HSE		(1 << 0)
#define STM32_RCC_CFGR_SW_PLL		(2 << 0)
#define STM32_RCC_CFGR_SW_PLL_R		(3 << 0)
#define STM32_RCC_CFGR_SW_MASK		(3 << 0)
#define STM32_RCC_CFGR_SWS_HSI		(0 << 2)
#define STM32_RCC_CFGR_SWS_HSE		(1 << 2)
#define STM32_RCC_CFGR_SWS_PLL		(2 << 2)
#define STM32_RCC_CFGR_SWS_PLL_R	(3 << 2)
#define STM32_RCC_CFGR_SWS_MASK		(3 << 2)
/* AHB Prescalar: nonlinear values, look up in RM0390 */
#define  CFGR_HPRE_OFF			4
#define  CFGR_HPRE(val)			(((val) & 0xf) << CFGR_HPRE_OFF)
/* APB1 Low Speed Prescalar < 45MHz */
#define  CFGR_PPRE1_OFF			10
#define  CFGR_PPRE1(val)		(((val) & 0x7) << CFGR_PPRE1_OFF)
/* APB2 High Speed Prescalar < 90MHz */
#define  CFGR_PPRE2_OFF			13
#define  CFGR_PPRE2(val)		(((val) & 0x7) << CFGR_PPRE2_OFF)
/* RTC CLock: Must equal 1MHz */
#define  CFGR_RTCPRE_OFF		16
#define  CFGR_RTCPRE(val)		(((val) & 0x1f) << CFGR_RTCPRE_OFF)

#define STM32_RCC_CIR                   REG32(STM32_RCC_BASE + 0x0C)
#define STM32_RCC_AHB1RSTR              REG32(STM32_RCC_BASE + 0x10)
#define  RCC_AHB1RSTR_OTGHSRST		BIT(29)

#define STM32_RCC_AHB2RSTR              REG32(STM32_RCC_BASE + 0x14)
#define STM32_RCC_AHB3RSTR              REG32(STM32_RCC_BASE + 0x18)

#define STM32_RCC_APB1RSTR              REG32(STM32_RCC_BASE + 0x20)
#define STM32_RCC_APB2RSTR              REG32(STM32_RCC_BASE + 0x24)

#define STM32_RCC_AHB1ENR               REG32(STM32_RCC_BASE + 0x30)
#define STM32_RCC_AHB1ENR_GPIO_PORTA	BIT(0)
#define STM32_RCC_AHB1ENR_GPIO_PORTB	BIT(1)
#define STM32_RCC_AHB1ENR_GPIO_PORTC	BIT(2)
#define STM32_RCC_AHB1ENR_GPIO_PORTD	BIT(3)
#define STM32_RCC_AHB1ENR_GPIO_PORTE	BIT(4)
#define STM32_RCC_AHB1ENR_GPIO_PORTF	BIT(5)
#define STM32_RCC_AHB1ENR_GPIO_PORTG	BIT(6)
#define STM32_RCC_AHB1ENR_GPIO_PORTH	BIT(7)
#define STM32_RCC_AHB1ENR_GPIOMASK	(0xff << 0)
#define STM32_RCC_AHB1ENR_BKPSRAMEN	BIT(18)
#define STM32_RCC_AHB1ENR_DMA1EN	BIT(21)
#define STM32_RCC_AHB1ENR_DMA2EN	BIT(22)

/* TODO(nsanders): normalize naming.*/
#define STM32_RCC_HB1_DMA1		BIT(21)
#define STM32_RCC_HB1_DMA2		BIT(22)
#define STM32_RCC_AHB1ENR_OTGHSEN	BIT(29)
#define STM32_RCC_AHB1ENR_OTGHSULPIEN	BIT(30)

#define STM32_RCC_AHB2ENR               REG32(STM32_RCC_BASE + 0x34)
#define STM32_RCC_AHB2ENR_RNGEN		BIT(6)
#define STM32_RCC_AHB2ENR_OTGFSEN	BIT(7)
#define STM32_RCC_AHB3ENR               REG32(STM32_RCC_BASE + 0x38)

#define STM32_RCC_APB1ENR               REG32(STM32_RCC_BASE + 0x40)
#define STM32_RCC_PWREN                 BIT(28)
#define STM32_RCC_I2C1EN                BIT(21)
#define STM32_RCC_I2C2EN                BIT(22)
#define STM32_RCC_I2C3EN                BIT(23)
#define STM32_RCC_FMPI2C4EN             BIT(24)

#define STM32_RCC_APB2ENR               REG32(STM32_RCC_BASE + 0x44)
#define STM32_RCC_APB2ENR_ADC1EN        BIT(8) /* STM32F4 */

#define STM32_RCC_PB2_USART6            BIT(5)
#define STM32_RCC_SYSCFGEN		BIT(14)

#define STM32_RCC_AHB1LPENR             REG32(STM32_RCC_BASE + 0x50)
#define STM32_RCC_AHB2LPENR             REG32(STM32_RCC_BASE + 0x54)
#define STM32_RCC_AHB3LPENR             REG32(STM32_RCC_BASE + 0x58)
#define STM32_RCC_APB1LPENR             REG32(STM32_RCC_BASE + 0x60)
#define STM32_RCC_APB2LPENR             REG32(STM32_RCC_BASE + 0x64)

#define STM32_RCC_BDCR                  REG32(STM32_RCC_BASE + 0x70)
#define STM32_RCC_CSR                   REG32(STM32_RCC_BASE + 0x74)
#define STM32_RCC_CSR_LSION		BIT(0)
#define STM32_RCC_CSR_LSIRDY		BIT(1)

#define STM32_RCC_PB2_TIM1		BIT(0)
#define STM32_RCC_PB2_TIM8		BIT(1)
#define STM32_RCC_PB2_TIM9		BIT(16)
#define STM32_RCC_PB2_TIM10		BIT(17)
#define STM32_RCC_PB2_TIM11		BIT(18)

#define STM32_RCC_DCKCFGR2              REG32(STM32_RCC_BASE + 0x94)
#define  DCKCFGR2_FMPI2C1SEL(val)       (((val) & 0x3) << 22)
#define  DCKCFGR2_FMPI2C1SEL_MASK       (0x3 << 22)
#define  FMPI2C1SEL_APB                 0x0

#define STM32_SYSCFG_MEMRMP             REG32(STM32_SYSCFG_BASE + 0x00)
#define STM32_SYSCFG_PMC                REG32(STM32_SYSCFG_BASE + 0x04)
#define STM32_SYSCFG_EXTICR(n)          REG32(STM32_SYSCFG_BASE + 8 + 4 * (n))
#define STM32_SYSCFG_CMPCR              REG32(STM32_SYSCFG_BASE + 0x20)
#define STM32_SYSCFG_CFGR               REG32(STM32_SYSCFG_BASE + 0x2C)


/* Peripheral bits for RCC_APB/AHB regs */
#define STM32_RCC_PB2_USART1		BIT(4)

/* Reset causes definitions */
/* Reset causes in RCC CSR register */
#define STM32_RCC_RESET_CAUSE STM32_RCC_CSR
#define  RESET_CAUSE_WDG                (BIT(30)|BIT(29))
#define  RESET_CAUSE_SFT                BIT(28)
#define  RESET_CAUSE_POR                BIT(27)
#define  RESET_CAUSE_PIN                BIT(26)
#define  RESET_CAUSE_OTHER              (BIT(31)|BIT(30)|BIT(29)|BIT(28)| \
					 BIT(27)|BIT(26)|BIT(25))
#define  RESET_CAUSE_RMVF                BIT(24)
/* Power cause in PWR CSR register */
#define STM32_PWR_RESET_CAUSE STM32_PWR_CSR
#define  RESET_CAUSE_SBF                BIT(1)
#define STM32_PWR_RESET_CAUSE_CLR STM32_PWR_CR
#define  RESET_CAUSE_SBF_CLR            BIT(3)

/* --- Watchdogs --- */

/* --- Real-Time Clock --- */
#define STM32_RTC_TR                REG32(STM32_RTC_BASE + 0x00)
#define STM32_RTC_DR                REG32(STM32_RTC_BASE + 0x04)
#define STM32_RTC_CR                REG32(STM32_RTC_BASE + 0x08)
#define STM32_RTC_CR_BYPSHAD        BIT(5)
#define STM32_RTC_CR_ALRAE          BIT(8)
#define STM32_RTC_CR_ALRAIE         BIT(12)
#define STM32_RTC_ISR               REG32(STM32_RTC_BASE + 0x0C)
#define STM32_RTC_ISR_ALRAWF        BIT(0)
#define STM32_RTC_ISR_RSF           BIT(5)
#define STM32_RTC_ISR_INITF         BIT(6)
#define STM32_RTC_ISR_INIT          BIT(7)
#define STM32_RTC_ISR_ALRAF         BIT(8)
#define STM32_RTC_PRER              REG32(STM32_RTC_BASE + 0x10)
#define STM32_RTC_PRER_A_MASK       (0x7f << 16)
#define STM32_RTC_PRER_S_MASK       (0x7fff << 0)
#define STM32_RTC_WUTR              REG32(STM32_RTC_BASE + 0x14)
#define STM32_RTC_CALIBR            REG32(STM32_RTC_BASE + 0x18)
#define STM32_RTC_ALRMAR            REG32(STM32_RTC_BASE + 0x1C)
#define STM32_RTC_ALRMBR            REG32(STM32_RTC_BASE + 0x20)
#define STM32_RTC_WPR               REG32(STM32_RTC_BASE + 0x24)
#define STM32_RTC_SSR               REG32(STM32_RTC_BASE + 0x28)
#define STM32_RTC_TSTR              REG32(STM32_RTC_BASE + 0x30)
#define STM32_RTC_TSDR              REG32(STM32_RTC_BASE + 0x34)
#define STM32_RTC_TAFCR             REG32(STM32_RTC_BASE + 0x40)
#define STM32_RTC_ALRMASSR          REG32(STM32_RTC_BASE + 0x44)
#define STM32_RTC_BACKUP(n)         REG32(STM32_RTC_BASE + 0x50 + 4 * (n))

#define STM32_BKP_DATA(n)           STM32_RTC_BACKUP(n)
#define STM32_BKP_BYTES             80

/* --- SPI --- */

/* The SPI controller registers */
struct stm32_spi_regs {
	uint16_t cr1;
	uint16_t _pad0;
	uint16_t cr2;
	uint16_t _pad1;
	unsigned sr;
	uint8_t dr;
	uint8_t _pad2;
	uint16_t _pad3;
	unsigned crcpr;
	unsigned rxcrcr;
	unsigned txcrcr;
	unsigned i2scfgr;	/* STM32L only */
	unsigned i2spr;		/* STM32L only */
};
/* Must be volatile, or compiler optimizes out repeated accesses */
typedef volatile struct stm32_spi_regs stm32_spi_regs_t;

#define STM32_SPI1_REGS ((stm32_spi_regs_t *)STM32_SPI1_BASE)
#define STM32_SPI2_REGS ((stm32_spi_regs_t *)STM32_SPI2_BASE)
#define STM32_SPI3_REGS ((stm32_spi_regs_t *)STM32_SPI3_BASE)
#define STM32_SPI4_REGS ((stm32_spi_regs_t *)STM32_SPI4_BASE)

#define STM32_SPI_CR1_BIDIMODE		BIT(15)
#define STM32_SPI_CR1_BIDIOE		BIT(14)
#define STM32_SPI_CR1_CRCEN		BIT(13)
#define STM32_SPI_CR1_SSM		BIT(9)
#define STM32_SPI_CR1_SSI		BIT(8)
#define STM32_SPI_CR1_LSBFIRST		BIT(7)
#define STM32_SPI_CR1_SPE		BIT(6)
#define STM32_SPI_CR1_BR_DIV64R		(5 << 3)
#define STM32_SPI_CR1_BR_DIV4R		BIT(3)
#define STM32_SPI_CR1_MSTR		BIT(2)
#define STM32_SPI_CR1_CPOL		BIT(1)
#define STM32_SPI_CR1_CPHA		BIT(0)
#define STM32_SPI_CR2_FRXTH		BIT(12)
#define STM32_SPI_CR2_DATASIZE(n)	(((n) - 1) << 8)
#define STM32_SPI_CR2_TXEIE		BIT(7)
#define STM32_SPI_CR2_RXNEIE		BIT(6)
#define STM32_SPI_CR2_NSSP		BIT(3)
#define STM32_SPI_CR2_SSOE		BIT(2)
#define STM32_SPI_CR2_TXDMAEN		BIT(1)
#define STM32_SPI_CR2_RXDMAEN		BIT(0)

#define STM32_SPI_SR_RXNE		BIT(0)
#define STM32_SPI_SR_TXE		BIT(1)
#define STM32_SPI_SR_CRCERR		BIT(4)
#define STM32_SPI_SR_BSY		BIT(7)
#define STM32_SPI_SR_FRLVL		(3 << 9)
#define STM32_SPI_SR_FTLVL		(3 << 11)

/* --- Debug --- */

#define  STM32_DBGMCU_CR_SLEEP                      BIT(0)
#define  STM32_DBGMCU_CR_STOP                       BIT(1)
#define  STM32_DBGMCU_CR_STBY                       BIT(2)
#define  STM32_DBGMCU_CR_TRACE_MASK                 (BIT(5)|BIT(6)|BIT(7))
#define   STM32_DBGMCU_CR_TRACE_EN                   BIT(5)
#define   STM32_DBGMCU_CR_TRACE_MODE_ASYNC           0
#define   STM32_DBGMCU_CR_TRACE_MODE_SYNC1           BIT(6)
#define   STM32_DBGMCU_CR_TRACE_MODE_SYNC2           BIT(7)
#define   STM32_DBGMCU_CR_TRACE_MODE_SYNC4           (BIT(6)|BIT(7))
#define STM32_DBGMCU_APB1FZ         REG32(STM32_DBGMCU_BASE + 0x08)
#define  STM32_DBGMCU_APB1FZ_TIM2                   BIT(0)
#define  STM32_DBGMCU_APB1FZ_TIM3                   BIT(1)
#define  STM32_DBGMCU_APB1FZ_TIM4                   BIT(2)
#define  STM32_DBGMCU_APB1FZ_TIM5                   BIT(3)
#define  STM32_DBGMCU_APB1FZ_TIM6                   BIT(4)
#define  STM32_DBGMCU_APB1FZ_TIM7                   BIT(5)
#define  STM32_DBGMCU_APB1FZ_TIM12                  BIT(6)
#define  STM32_DBGMCU_APB1FZ_TIM13                  BIT(7)
#define  STM32_DBGMCU_APB1FZ_TIM14                  BIT(8)
#define  STM32_DBGMCU_APB1FZ_RTC                    BIT(10)
#define  STM32_DBGMCU_APB1FZ_WWDG                   BIT(11)
#define  STM32_DBGMCU_APB1FZ_IWDG                   BIT(12)
#define  STM32_DBGMCU_APB1FZ_I2C1_SMBUS_TIMEOUT     BIT(21)
#define  STM32_DBGMCU_APB1FZ_I2C2_SMBUS_TIMEOUT     BIT(22)
#define  STM32_DBGMCU_APB1FZ_I2C3_SMBUS_TIMEOUT     BIT(23)
#define  STM32_DBGMCU_APB1FZ_I2CFMP_SMBUS_TIMEOUT   BIT(24)
#define  STM32_DBGMCU_APB1FZ_CAN1                   BIT(25)
#define  STM32_DBGMCU_APB1FZ_CAN2                   BIT(26)
#define STM32_DBGMCU_APB2FZ         REG32(STM32_DBGMCU_BASE + 0x0C)
#define  STM32_DBGMCU_APB2FZ_TIM1                   BIT(0)
#define  STM32_DBGMCU_APB2FZ_TIM8                   BIT(1)
#define  STM32_DBGMCU_APB2FZ_TIM9                   BIT(16)
#define  STM32_DBGMCU_APB2FZ_TIM10                  BIT(17)
#define  STM32_DBGMCU_APB2FZ_TIM11                  BIT(18)

/* --- Flash --- */
#define STM32_FLASH_ACR             REG32(STM32_FLASH_REGS_BASE + 0x00)
#define STM32_FLASH_ACR_SHIFT           0
#define STM32_FLASH_ACR_LAT_MASK        0xf
#define STM32_FLASH_ACR_PRFTEN          BIT(8)
#define STM32_FLASH_ACR_ICEN            BIT(9)
#define STM32_FLASH_ACR_DCEN            BIT(10)
#define STM32_FLASH_ACR_ICRST           BIT(11)
#define STM32_FLASH_ACR_DCRST           BIT(12)
#define STM32_FLASH_KEYR            REG32(STM32_FLASH_REGS_BASE + 0x04)
#define  FLASH_KEYR_KEY1                0x45670123
#define  FLASH_KEYR_KEY2                0xCDEF89AB
#define STM32_FLASH_OPTKEYR         REG32(STM32_FLASH_REGS_BASE + 0x08)
#define  FLASH_OPTKEYR_KEY1             0x08192A3B
#define  FLASH_OPTKEYR_KEY2             0x4C5D6E7F
#define STM32_FLASH_SR              REG32(STM32_FLASH_REGS_BASE + 0x0c)
#define  FLASH_SR_EOP                   BIT(0)
#define  FLASH_SR_OPERR                 BIT(1)
#define  FLASH_SR_WRPERR                BIT(4)
#define  FLASH_SR_PGAERR                BIT(5)
#define  FLASH_SR_PGPERR                BIT(6)
#define  FLASH_SR_PGSERR                BIT(7)
#define  FLASH_SR_RDERR                 BIT(8)
#define  FLASH_SR_ALL_ERR \
	(FLASH_SR_OPERR | FLASH_SR_WRPERR | FLASH_SR_PGAERR | \
	 FLASH_SR_PGPERR | FLASH_SR_PGSERR | FLASH_SR_RDERR)
#define  FLASH_SR_BUSY                   BIT(16)
#define STM32_FLASH_CR              REG32(STM32_FLASH_REGS_BASE + 0x10)
#define  FLASH_CR_PG                    BIT(0)
#define  FLASH_CR_PER                   BIT(1)
#define  FLASH_CR_MER                   BIT(2)
#define STM32_FLASH_CR_SNB_OFFSET       (3)
#define STM32_FLASH_CR_SNB(sec) \
	(((sec) & 0xf) << STM32_FLASH_CR_SNB_OFFSET)
#define STM32_FLASH_CR_SNB_MASK         (STM32_FLASH_CR_SNB(0xf))
#define STM32_FLASH_CR_PSIZE_OFFSET     (8)
#define STM32_FLASH_CR_PSIZE(size) \
	(((size) & 0x3) << STM32_FLASH_CR_PSIZE_OFFSET)
#define STM32_FLASH_CR_PSIZE_MASK       (STM32_FLASH_CR_PSIZE(0x3))
#define  FLASH_CR_STRT                  BIT(16)
#define  FLASH_CR_LOCK                  BIT(31)
#define STM32_FLASH_OPTCR           REG32(STM32_FLASH_REGS_BASE + 0x14)
#define  FLASH_OPTLOCK                  BIT(0)
#define  FLASH_OPTSTRT                  BIT(1)
#define STM32_FLASH_BOR_LEV_OFFSET      (2)
#define  FLASH_OPTCR_RDP_SHIFT		(8)
#define  FLASH_OPTCR_RDP_MASK		(0xFF << FLASH_OPTCR_RDP_SHIFT)
#define  FLASH_OPTCR_RDP_LEVEL_0		(0xAA << FLASH_OPTCR_RDP_SHIFT)
/* RDP Level 1: Anything but 0xAA/0xCC */
#define  FLASH_OPTCR_RDP_LEVEL_1		(0x00 << FLASH_OPTCR_RDP_SHIFT)
#define  FLASH_OPTCR_RDP_LEVEL_2		(0xCC << FLASH_OPTCR_RDP_SHIFT)
#define STM32_FLASH_nWRP_OFFSET         (16)
#define STM32_FLASH_nWRP(_bank)         BIT(_bank + STM32_FLASH_nWRP_OFFSET)
#define STM32_FLASH_nWRP_ALL            (0xFF << STM32_FLASH_nWRP_OFFSET)
#define STM32_FLASH_OPT_LOCKED      (STM32_FLASH_OPTCR & FLASH_OPTLOCK)

#define STM32_OPTB_RDP_USER         REG32(STM32_OPTB_BASE + 0x00)
#define STM32_OPTB_RDP_OFF              0x00
#define STM32_OPTB_USER_OFF             0x02
#define STM32_OPTB_WRP_OFF(n)       (0x08 + (n&3) * 2)
#define STM32_OPTB_WP               REG32(STM32_OPTB_BASE + 0x08)
#define STM32_OPTB_nWRP(_bank)          BIT(_bank)
#define STM32_OPTB_nWRP_ALL             (0xFF)

#define STM32_OPTB_COMPL_SHIFT      8

#define STM32_OTP_BLOCK_NB              16
#define STM32_OTP_BLOCK_SIZE            32
#define STM32_OTP_BLOCK_DATA(_block, _offset) \
	(STM32_OTP_BASE + STM32_OTP_BLOCK_SIZE * (_block) + (_offset) * 4)
#define STM32_OTP_UNLOCK_BYTE           0x00
#define STM32_OTP_LOCK_BYTE             0xFF
#define STM32_OTP_LOCK_BASE         \
	(STM32_OTP_BASE + STM32_OTP_BLOCK_NB * STM32_OTP_BLOCK_SIZE)
#define STM32_OTP_LOCK(_block) \
	(STM32_OTP_LOCK_BASE + ((_block) / 4) * 4)
#define STM32_OPT_LOCK_MASK(_block)    ((0xFF << ((_block) % 4) * 8))

/* --- External Interrupts --- */
#define STM32_EXTI_IMR              REG32(STM32_EXTI_BASE + 0x00)
#define STM32_EXTI_EMR              REG32(STM32_EXTI_BASE + 0x04)
#define STM32_EXTI_RTSR             REG32(STM32_EXTI_BASE + 0x08)
#define STM32_EXTI_FTSR             REG32(STM32_EXTI_BASE + 0x0c)
#define STM32_EXTI_SWIER            REG32(STM32_EXTI_BASE + 0x10)
#define STM32_EXTI_PR               REG32(STM32_EXTI_BASE + 0x14)

#define EXTI_RTC_ALR_EVENT BIT(17)

/* --- ADC --- */
#define STM32_ADC_SR               REG32(STM32_ADC1_BASE + 0x00)
#define STM32_ADC_CR1              REG32(STM32_ADC1_BASE + 0x04)
#define STM32_ADC_CR2              REG32(STM32_ADC1_BASE + 0x08)
#define STM32_ADC_CR2_ADON         BIT(0)
#define STM32_ADC_CR2_CONT         BIT(1)
#define STM32_ADC_CR2_CAL          BIT(2)
#define STM32_ADC_CR2_RSTCAL       BIT(3)
#define STM32_ADC_CR2_ALIGN        BIT(11)
#define STM32_ADC_CR2_SWSTART      BIT(30)
#define STM32_ADC_SMPR1            REG32(STM32_ADC1_BASE + 0x0C)
#define STM32_ADC_SMPR2            REG32(STM32_ADC1_BASE + 0x10)
#define STM32_ADC_JOFR(n)          REG32(STM32_ADC1_BASE + 0x14 + ((n)&3) * 4)
#define STM32_ADC_HTR              REG32(STM32_ADC1_BASE + 0x24)
#define STM32_ADC_LTR              REG32(STM32_ADC1_BASE + 0x28)
#define STM32_ADC_SQR(n)           REG32(STM32_ADC1_BASE + 0x28 + ((n)&3) * 4)
#define STM32_ADC_SQR1             REG32(STM32_ADC1_BASE + 0x2C)
#define STM32_ADC_SQR2             REG32(STM32_ADC1_BASE + 0x30)
#define STM32_ADC_SQR3             REG32(STM32_ADC1_BASE + 0x34)
#define STM32_ADC_JSQR             REG32(STM32_ADC1_BASE + 0x38)
#define STM32_ADC_JDR(n)           REG32(STM32_ADC1_BASE + 0x3C + ((n)&3) * 4)
#define STM32_ADC_DR               REG32(STM32_ADC1_BASE + 0x4C)

/* --- Comparators --- */


/* --- DMA --- */
/*
 * Available DMA streams, numbered from 0.
 *
 * Named channel to respect older interface, but a stream can serve
 * any channels, as long as they are in the same DMA controller.
 *
 * Stream 0 - 7 are managed by controller DMA1, 8 - 15 DMA2.
 */
enum dma_channel {
	/* Channel numbers */
	STM32_DMA1_STREAM0 = 0,
	STM32_DMA1_STREAM1 = 1,
	STM32_DMA1_STREAM2 = 2,
	STM32_DMA1_STREAM3 = 3,
	STM32_DMA1_STREAM4 = 4,
	STM32_DMA1_STREAM5 = 5,
	STM32_DMA1_STREAM6 = 6,
	STM32_DMA1_STREAM7 = 7,
	STM32_DMAS_COUNT = 8,
	STM32_DMA2_STREAM0 = 8,
	STM32_DMA2_STREAM1 = 9,
	STM32_DMA2_STREAM2 = 10,
	STM32_DMA2_STREAM3 = 11,
	STM32_DMA2_STREAM4 = 12,
	STM32_DMA2_STREAM5 = 13,
	STM32_DMA2_STREAM6 = 14,
	STM32_DMA2_STREAM7 = 15,

	STM32_DMAS_USART1_TX = STM32_DMA2_STREAM7,
	STM32_DMAS_USART1_RX = STM32_DMA2_STREAM5,

	/* Legacy naming for uart.c */
	STM32_DMAC_USART1_TX = STM32_DMAS_USART1_TX,
	STM32_DMAC_USART1_RX = STM32_DMAS_USART1_RX,
#ifdef CHIP_VARIANT_STM32F41X
	STM32_DMAS_USART2_TX = STM32_DMA1_STREAM6,
	STM32_DMAS_USART2_RX = STM32_DMA1_STREAM5,

	/* Legacy naming for uart.c */
	STM32_DMAC_USART2_TX = STM32_DMAS_USART2_TX,
	STM32_DMAC_USART2_RX = STM32_DMAS_USART2_RX,
#endif

#ifdef CHIP_VARIANT_STM32F41X
	STM32_DMAC_I2C1_TX = STM32_DMA1_STREAM1,
	STM32_DMAC_I2C1_RX = STM32_DMA1_STREAM0,

	STM32_DMAC_I2C2_TX = STM32_DMA1_STREAM7,
	STM32_DMAC_I2C2_RX = STM32_DMA1_STREAM3,

	STM32_DMAC_I2C3_TX = STM32_DMA1_STREAM4,
	STM32_DMAC_I2C3_RX = STM32_DMA1_STREAM2,
#else
	STM32_DMAC_I2C1_TX = STM32_DMA1_STREAM6,
	STM32_DMAC_I2C1_RX = STM32_DMA1_STREAM0,

	STM32_DMAC_I2C2_TX = STM32_DMA1_STREAM7,
	STM32_DMAC_I2C2_RX = STM32_DMA1_STREAM3,

	STM32_DMAC_I2C3_TX = STM32_DMA1_STREAM4,
	STM32_DMAC_I2C3_RX = STM32_DMA1_STREAM1,
#endif

	STM32_DMAC_FMPI2C4_TX = STM32_DMA1_STREAM5,
	STM32_DMAC_FMPI2C4_RX = STM32_DMA1_STREAM2,

	/* Legacy naming for spi_controller.c */
	STM32_DMAC_SPI1_TX = STM32_DMA2_STREAM3, /* REQ 3 */
	STM32_DMAC_SPI1_RX = STM32_DMA2_STREAM0, /* REQ 3 */
	STM32_DMAC_SPI2_TX = STM32_DMA1_STREAM4, /* REQ 0 */
	STM32_DMAC_SPI2_RX = STM32_DMA1_STREAM3, /* REQ 0 */
	STM32_DMAC_SPI3_TX = STM32_DMA1_STREAM7, /* REQ 0 */
	STM32_DMAC_SPI3_RX = STM32_DMA1_STREAM0, /* REQ 0 */
	STM32_DMAC_SPI4_TX = STM32_DMA2_STREAM1, /* STM32H7 */
	STM32_DMAC_SPI4_RX = STM32_DMA2_STREAM4, /* STM32H7 */
};

#define STM32_REQ_USART1_TX 4
#define STM32_REQ_USART1_RX 4

#define STM32_REQ_USART2_TX 4
#define STM32_REQ_USART2_RX 4

#define STM32_I2C1_TX_REQ_CH 1
#define STM32_I2C1_RX_REQ_CH 1

#define STM32_I2C2_TX_REQ_CH 7
#define STM32_I2C2_RX_REQ_CH 7

#define STM32_I2C3_TX_REQ_CH 3
#define STM32_I2C3_RX_REQ_CH 1

#define STM32_FMPI2C4_TX_REQ_CH 2
#define STM32_FMPI2C4_RX_REQ_CH 2

#define STM32_SPI1_TX_REQ_CH 3
#define STM32_SPI1_RX_REQ_CH 3
#define STM32_SPI2_TX_REQ_CH 0
#define STM32_SPI2_RX_REQ_CH 0
#define STM32_SPI3_TX_REQ_CH 0
#define STM32_SPI3_RX_REQ_CH 0

#define STM32_DMAS_TOTAL_COUNT 16

/* Registers for a single stream of a DMA controller */
struct stm32_dma_stream {
	uint32_t	scr;		/* Control */
	uint32_t	sndtr;		/* Number of data to transfer */
	uint32_t	spar;		/* Peripheral address */
	uint32_t	sm0ar;		/* Memory address 0 */
	uint32_t	sm1ar;		/*  address 1 for double buffer */
	uint32_t	sfcr;		/* FIFO control */
};

/* Always use stm32_dma_stream_t so volatile keyword is included! */
typedef volatile struct stm32_dma_stream stm32_dma_stream_t;

/* Common code and header file must use this */
typedef stm32_dma_stream_t dma_chan_t;
struct stm32_dma_regs {
	uint32_t	isr[2];
	uint32_t	ifcr[2];
	stm32_dma_stream_t stream[STM32_DMAS_COUNT];
};


/* Always use stm32_dma_regs_t so volatile keyword is included! */
typedef volatile struct stm32_dma_regs stm32_dma_regs_t;

#define STM32_DMA1_REGS ((stm32_dma_regs_t *)STM32_DMA1_BASE)

#define STM32_DMA2_REGS ((stm32_dma_regs_t *)STM32_DMA2_BASE)

#define STM32_DMA_REGS(channel) \
	((channel) < STM32_DMAS_COUNT ? STM32_DMA1_REGS : STM32_DMA2_REGS)

#define STM32_DMA_CCR_EN                BIT(0)
#define STM32_DMA_CCR_DMEIE             BIT(1)
#define STM32_DMA_CCR_TEIE              BIT(2)
#define STM32_DMA_CCR_HTIE              BIT(3)
#define STM32_DMA_CCR_TCIE              BIT(4)
#define STM32_DMA_CCR_PFCTRL            BIT(5)
#define STM32_DMA_CCR_DIR_P2M		(0 << 6)
#define STM32_DMA_CCR_DIR_M2P		(1 << 6)
#define STM32_DMA_CCR_DIR_M2M		(2 << 6)
#define STM32_DMA_CCR_CIRC              BIT(8)
#define STM32_DMA_CCR_PINC              BIT(9)
#define STM32_DMA_CCR_MINC              BIT(10)
#define STM32_DMA_CCR_PSIZE_8_BIT       (0 << 11)
#define STM32_DMA_CCR_PSIZE_16_BIT      (1 << 11)
#define STM32_DMA_CCR_PSIZE_32_BIT      (2 << 11)
#define STM32_DMA_CCR_MSIZE_8_BIT       (0 << 13)
#define STM32_DMA_CCR_MSIZE_16_BIT      (1 << 13)
#define STM32_DMA_CCR_MSIZE_32_BIT      (2 << 13)
#define STM32_DMA_CCR_PINCOS            BIT(15)
#define STM32_DMA_CCR_PL_LOW            (0 << 16)
#define STM32_DMA_CCR_PL_MEDIUM         (1 << 16)
#define STM32_DMA_CCR_PL_HIGH           (2 << 16)
#define STM32_DMA_CCR_PL_VERY_HIGH      (3 << 16)
#define STM32_DMA_CCR_DBM               BIT(18)
#define STM32_DMA_CCR_CT                BIT(19)
#define STM32_DMA_CCR_PBURST(b_len)		 ((((b_len) - 4) / 4) << 21)
#define STM32_DMA_CCR_MBURST(b_len)		 ((((b_len) - 4) / 4) << 21)
#define STM32_DMA_CCR_CHANNEL_MASK		 (0x7 << 25)
#define STM32_DMA_CCR_CHANNEL(channel)		 ((channel) << 25)
#define STM32_DMA_CCR_RSVD_MASK		(0xF0100000)


#define STM32_DMA_SFCR_DMDIS		BIT(2)
#define STM32_DMA_SFCR_FTH(level)	(((level) - 1) << 0)


#define STM32_DMA_CH_LOCAL(channel)     ((channel) % STM32_DMAS_COUNT)
#define STM32_DMA_CH_LH(channel)        \
	((STM32_DMA_CH_LOCAL(channel) < 4) ? 0 : 1)
#define STM32_DMA_CH_OFFSET(channel)    \
	(((STM32_DMA_CH_LOCAL(channel) % 4) * 6) + \
	(((STM32_DMA_CH_LOCAL(channel) % 4) >= 2) ? 4 : 0))
#define STM32_DMA_CH_GETBITS(channel, val) \
	(((val) >> STM32_DMA_CH_OFFSET(channel)) & 0x3f)
#define STM32_DMA_GET_IFCR(channel)      \
	(STM32_DMA_CH_GETBITS(channel,   \
	STM32_DMA_REGS(channel)->ifcr[STM32_DMA_CH_LH(channel)]))
#define STM32_DMA_GET_ISR(channel)       \
	(STM32_DMA_CH_GETBITS(channel,   \
	STM32_DMA_REGS(channel)->isr[STM32_DMA_CH_LH(channel)]))

#define STM32_DMA_SET_IFCR(channel, val) \
	(STM32_DMA_REGS(channel)->ifcr[STM32_DMA_CH_LH(channel)] = \
	(STM32_DMA_REGS(channel)->ifcr[STM32_DMA_CH_LH(channel)] & \
	~(0x3f << STM32_DMA_CH_OFFSET(channel))) | \
	(((val) & 0x3f) << STM32_DMA_CH_OFFSET(channel)))
#define STM32_DMA_SET_ISR(channel, val) \
	(STM32_DMA_REGS(channel)->isr[STM32_DMA_CH_LH(channel)] = \
	(STM32_DMA_REGS(channel)->isr[STM32_DMA_CH_LH(channel)] & \
	~(0x3f << STM32_DMA_CH_OFFSET(channel))) | \
	(((val) & 0x3f) << STM32_DMA_CH_OFFSET(channel)))

#define STM32_DMA_FEIF                  BIT(0)
#define STM32_DMA_DMEIF                 BIT(2)
#define STM32_DMA_TEIF                  BIT(3)
#define STM32_DMA_HTIF                  BIT(4)
#define STM32_DMA_TCIF                  BIT(5)
#define STM32_DMA_ALL                   0x3d



/* --- CRC --- */
#define STM32_CRC_DR                REG32(STM32_CRC_BASE + 0x0)
#define STM32_CRC_DR32              REG32(STM32_CRC_BASE + 0x0)
#define STM32_CRC_DR16              REG16(STM32_CRC_BASE + 0x0)
#define STM32_CRC_DR8               REG8(STM32_CRC_BASE + 0x0)

#define STM32_CRC_IDR               REG32(STM32_CRC_BASE + 0x4)
#define STM32_CRC_CR                REG32(STM32_CRC_BASE + 0x8)
#define STM32_CRC_INIT              REG32(STM32_CRC_BASE + 0x10)
#define STM32_CRC_POL               REG32(STM32_CRC_BASE + 0x14)

#define STM32_CRC_CR_RESET          BIT(0)
#define STM32_CRC_CR_POLYSIZE_32    (0 << 3)
#define STM32_CRC_CR_POLYSIZE_16    (1 << 3)
#define STM32_CRC_CR_POLYSIZE_8     (2 << 3)
#define STM32_CRC_CR_POLYSIZE_7     (3 << 3)
#define STM32_CRC_CR_REV_IN_BYTE    (1 << 5)
#define STM32_CRC_CR_REV_IN_HWORD   (2 << 5)
#define STM32_CRC_CR_REV_IN_WORD    (3 << 5)
#define STM32_CRC_CR_REV_OUT        BIT(7)

#define EP_MASK     0x0F0F
#define EP_TX_DTOG  0x0040
#define EP_TX_MASK  0x0030
#define EP_TX_VALID 0x0030
#define EP_TX_NAK   0x0020
#define EP_TX_STALL 0x0010
#define EP_TX_DISAB 0x0000
#define EP_RX_DTOG  0x4000
#define EP_RX_MASK  0x3000
#define EP_RX_VALID 0x3000
#define EP_RX_NAK   0x2000
#define EP_RX_STALL 0x1000
#define EP_RX_DISAB 0x0000

#define EP_STATUS_OUT 0x0100

#define EP_TX_RX_MASK (EP_TX_MASK | EP_RX_MASK)
#define EP_TX_RX_VALID (EP_TX_VALID | EP_RX_VALID)

#define STM32_TOGGLE_EP(n, mask, val, flags) \
	STM32_USB_EP(n) = (((STM32_USB_EP(n) & (EP_MASK | (mask))) \
			^ (val)) | (flags))

/* --- TRNG --- */
#define STM32_RNG_CR                REG32(STM32_RNG_BASE + 0x0)
#define STM32_RNG_CR_RNGEN          BIT(2)
#define STM32_RNG_CR_IE             BIT(3)
#define STM32_RNG_CR_CED            BIT(5)
#define STM32_RNG_SR                REG32(STM32_RNG_BASE + 0x4)
#define STM32_RNG_SR_DRDY           BIT(0)
#define STM32_RNG_DR                REG32(STM32_RNG_BASE + 0x8)

/* --- AXI interconnect --- */

/* STM32H7: AXI_TARGx_FN_MOD exists for masters x = 1, 2 and 7 */
#define STM32_AXI_TARG_FN_MOD(x)    REG32(STM32_GPV_BASE + 0x1108 + \
					  0x1000 * (x))
#define  WRITE_ISS_OVERRIDE         BIT(1)
#define  READ_ISS_OVERRIDE          BIT(0)

/* --- MISC --- */
#define STM32_UNIQUE_ID_ADDRESS     REG32_ADDR(STM32_UNIQUE_ID_BASE)
#define STM32_UNIQUE_ID_LENGTH      (3 * 4)

#endif /* !__ASSEMBLER__ */
