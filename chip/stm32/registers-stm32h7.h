/* Copyright 2019 The Chromium OS Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

/**
 * @file
 * @brief Register map for the STM32H7 family of chips
 *
 * This header file should not be included directly.
 * Please include registers.h instead.
 *
 * Known Chip Variants
 * - STM32H7X3
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

#define STM32_IRQ_LPTIM1         93
#define STM32_IRQ_TIM15         116
#define STM32_IRQ_TIM16         117
#define STM32_IRQ_TIM17         118
#define STM32_IRQ_LPTIM2        138
#define STM32_IRQ_LPTIM3        139
#define STM32_IRQ_LPTIM4        140
#define STM32_IRQ_LPTIM5        141

/* To simplify code generation, define DMA channel 9..10 */
#define STM32_IRQ_DMA_CHANNEL_9    STM32_IRQ_DMA2_CHANNEL1
#define STM32_IRQ_DMA_CHANNEL_10   STM32_IRQ_DMA2_CHANNEL2
#define STM32_IRQ_DMA_CHANNEL_13   STM32_IRQ_DMA2_CHANNEL6
#define STM32_IRQ_DMA_CHANNEL_14   STM32_IRQ_DMA2_CHANNEL7

/* aliases for easier code sharing */
#define STM32_IRQ_I2C1 STM32_IRQ_I2C1_EV
#define STM32_IRQ_I2C2 STM32_IRQ_I2C2_EV
#define STM32_IRQ_I2C3 STM32_IRQ_I2C3_EV


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

#define STM32_GPV_BASE              0x51000000

#define STM32_DBGMCU_BASE           0x5C001000

#define STM32_BDMA_BASE             0x58025400
#define STM32_DMA1_BASE             0x40020000
#define STM32_DMA2_BASE             0x40020400
#define STM32_DMA2D_BASE            0x52001000
#define STM32_DMAMUX1_BASE          0x40020800
#define STM32_DMAMUX2_BASE          0x58025800
#define STM32_MDMA_BASE             0x52000000

#define STM32_EXTI_BASE             0x58000000

#define STM32_FLASH_REGS_BASE       0x52002000

#define STM32_GPIOA_BASE            0x58020000
#define STM32_GPIOB_BASE            0x58020400
#define STM32_GPIOC_BASE            0x58020800
#define STM32_GPIOD_BASE            0x58020C00
#define STM32_GPIOE_BASE            0x58021000
#define STM32_GPIOF_BASE            0x58021400
#define STM32_GPIOG_BASE            0x58021800
#define STM32_GPIOH_BASE            0x58021C00
#define STM32_GPIOI_BASE            0x58022000
#define STM32_GPIOJ_BASE            0x58022400
#define STM32_GPIOK_BASE            0x58022800

#define STM32_IWDG_BASE             0x58004800

#define STM32_LPTIM1_BASE           0x40002400
#define STM32_LPTIM2_BASE           0x58002400
#define STM32_LPTIM3_BASE           0x58002800
#define STM32_LPTIM4_BASE           0x58002C00
#define STM32_LPTIM5_BASE           0x58003000

#define STM32_PWR_BASE              0x58024800
#define STM32_RCC_BASE              0x58024400
#define STM32_RNG_BASE              0x48021800
#define STM32_RTC_BASE              0x58004000

#define STM32_SYSCFG_BASE           0x58000400

#define STM32_SPI1_BASE             0x40013000
#define STM32_SPI2_BASE             0x40003800
#define STM32_SPI3_BASE             0x40003c00
#define STM32_SPI4_BASE             0x40013400
#define STM32_SPI5_BASE             0x40015000

#define STM32_TIM1_BASE             0x40010000
#define STM32_TIM2_BASE             0x40000000
#define STM32_TIM3_BASE             0x40000400
#define STM32_TIM4_BASE             0x40000800
#define STM32_TIM5_BASE             0x40000c00
#define STM32_TIM6_BASE             0x40001000
#define STM32_TIM7_BASE             0x40001400
#define STM32_TIM8_BASE             0x40010400
#define STM32_TIM12_BASE            0x40001800
#define STM32_TIM13_BASE            0x40001c00
#define STM32_TIM14_BASE            0x40002000
#define STM32_TIM15_BASE            0x40014000
#define STM32_TIM16_BASE            0x40014400
#define STM32_TIM17_BASE            0x40014800

#define STM32_UNIQUE_ID_BASE        0x1ff1e800

#define STM32_USART1_BASE           0x40011000
#define STM32_USART2_BASE           0x40004400
#define STM32_USART3_BASE           0x40004800
#define STM32_USART4_BASE           0x40004c00
#define STM32_USART5_BASE           0x40005000
#define STM32_USART6_BASE           0x40011400
#define STM32_USART7_BASE           0x40007800
#define STM32_USART8_BASE           0x40007C00

#ifndef __ASSEMBLER__

/* Register definitions */

/* --- USART --- */
#define STM32_USART_CR1(base)         STM32_USART_REG(base, 0x00)
#define  STM32_USART_CR1_UE            BIT(0)
#define  STM32_USART_CR1_UESM          BIT(1)
#define  STM32_USART_CR1_RE            BIT(2)
#define  STM32_USART_CR1_TE            BIT(3)
#define  STM32_USART_CR1_RXNEIE        BIT(5)
#define  STM32_USART_CR1_TCIE          BIT(6)
#define  STM32_USART_CR1_TXEIE         BIT(7)
#define  STM32_USART_CR1_PS            BIT(9)
#define  STM32_USART_CR1_PCE           BIT(10)
#define  STM32_USART_CR1_M             BIT(12)
#define  STM32_USART_CR1_OVER8         BIT(15)
#define STM32_USART_CR2(base)         STM32_USART_REG(base, 0x04)
#define  STM32_USART_CR2_SWAP          BIT(15)
#define STM32_USART_CR3(base)         STM32_USART_REG(base, 0x08)
#define  STM32_USART_CR3_EIE           BIT(0)
#define  STM32_USART_CR3_DMAR          BIT(6)
#define  STM32_USART_CR3_DMAT          BIT(7)
#define  STM32_USART_CR3_ONEBIT        BIT(11)
#define  STM32_USART_CR3_OVRDIS        BIT(12)
#define  STM32_USART_CR3_WUS_START_BIT (2 << 20)
#define  STM32_USART_CR3_WUFIE         BIT(22)
#define STM32_USART_BRR(base)         STM32_USART_REG(base, 0x0C)
#define STM32_USART_GTPR(base)        STM32_USART_REG(base, 0x10)
#define STM32_USART_RTOR(base)        STM32_USART_REG(base, 0x14)
#define STM32_USART_RQR(base)         STM32_USART_REG(base, 0x18)
#define STM32_USART_ISR(base)         STM32_USART_REG(base, 0x1C)
#define STM32_USART_ICR(base)         STM32_USART_REG(base, 0x20)
#define  STM32_USART_ICR_ORECF         BIT(3)
#define  STM32_USART_ICR_TCCF          BIT(6)
#define STM32_USART_RDR(base)         STM32_USART_REG(base, 0x24)
#define STM32_USART_TDR(base)         STM32_USART_REG(base, 0x28)
#define STM32_USART_PRESC(base)       STM32_USART_REG(base, 0x2C)
/* register alias */
#define STM32_USART_SR(base)          STM32_USART_ISR(base)
#define  STM32_USART_SR_ORE            BIT(3)
#define  STM32_USART_SR_RXNE           BIT(5)
#define  STM32_USART_SR_TC             BIT(6)
#define  STM32_USART_SR_TXE            BIT(7)

/* --- GPIO --- */


#define STM32_GPIO_MODER(b)           REG32((b) + 0x00)
#define STM32_GPIO_OTYPER(b)          REG16((b) + 0x04)
#define STM32_GPIO_OSPEEDR(b)         REG32((b) + 0x08)
#define STM32_GPIO_PUPDR(b)           REG32((b) + 0x0C)
#define STM32_GPIO_IDR(b)             REG16((b) + 0x10)
#define STM32_GPIO_ODR(b)             REG16((b) + 0x14)
#define STM32_GPIO_BSRR(b)            REG32((b) + 0x18)
#define STM32_GPIO_LCKR(b)            REG32((b) + 0x1C)
#define STM32_GPIO_AFRL(b)            REG32((b) + 0x20)
#define STM32_GPIO_AFRH(b)            REG32((b) + 0x24)

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
#define STM32_I2C_CR1(n)              REG16(stm32_i2c_reg(n, 0x00))
#define  STM32_I2C_CR1_PE              BIT(0)
#define  STM32_I2C_CR1_START           BIT(8)
#define  STM32_I2C_CR1_STOP            BIT(9)
#define  STM32_I2C_CR1_ACK             BIT(10)
#define  STM32_I2C_CR1_POS             BIT(11)
#define  STM32_I2C_CR1_SWRST           BIT(15)
#define STM32_I2C_CR2(n)              REG16(stm32_i2c_reg(n, 0x04))
#define  STM32_I2C_CR2_ITERREN         BIT(8)
#define  STM32_I2C_CR2_ITEVTEN         BIT(9)
#define  STM32_I2C_CR2_ITBUFEN         BIT(10)
#define  STM32_I2C_CR2_DMAEN           BIT(11)
#define  STM32_I2C_CR2_LAST            BIT(12)
#define STM32_I2C_OAR1(n)             REG16(stm32_i2c_reg(n, 0x08))
#define  STM32_I2C_OAR1_B14            BIT(14)
#define STM32_I2C_OAR2(n)             REG16(stm32_i2c_reg(n, 0x0C))
#define  STM32_I2C_OAR2_ENDUAL         BIT(0)
#define STM32_I2C_DR(n)               REG16(stm32_i2c_reg(n, 0x10))
#define STM32_I2C_SR1(n)              REG16(stm32_i2c_reg(n, 0x14))
#define  STM32_I2C_SR1_SB              BIT(0)
#define  STM32_I2C_SR1_ADDR            BIT(1)
#define  STM32_I2C_SR1_BTF             BIT(2)
#define  STM32_I2C_SR1_STOPF           BIT(4)
#define  STM32_I2C_SR1_RXNE            BIT(6)
#define  STM32_I2C_SR1_TXE             BIT(7)
#define  STM32_I2C_SR1_BERR            BIT(8)
#define  STM32_I2C_SR1_ARLO            BIT(9)
#define  STM32_I2C_SR1_AF              BIT(10)

#define STM32_I2C_SR2(n)              REG16(stm32_i2c_reg(n, 0x18))
#define  STM32_I2C_SR2_BUSY            BIT(1)
#define  STM32_I2C_SR2_TRA             BIT(2)
#define  STM32_I2C_SR2_DUALF           BIT(7)

#define STM32_I2C_CCR(n)              REG16(stm32_i2c_reg(n, 0x1C))
#define  STM32_I2C_CCR_DUTY            BIT(14)
#define  STM32_I2C_CCR_FM              BIT(15)
#define STM32_I2C_TRISE(n)            REG16(stm32_i2c_reg(n, 0x20))


/* --- Power / Reset / Clocks --- */
#define STM32_PWR_CSR               REG32(STM32_PWR_BASE + 0x04)
#define STM32_PWR_CR2               REG32(STM32_PWR_BASE + 0x08)
#define STM32_PWR_CR3               REG32(STM32_PWR_BASE + 0x0C)
#define  STM32_PWR_CR3_BYPASS        BIT(0)
#define  STM32_PWR_CR3_LDOEN         BIT(1)
#define  STM32_PWR_CR3_SCUEN         BIT(2)
#define  STM32_PWR_CR3_VBE           BIT(8)
#define  STM32_PWR_CR3_VBRS          BIT(9)
#define  STM32_PWR_CR3_USB33DEN      BIT(24)
#define  STM32_PWR_CR3_USBREGEN      BIT(25)
#define  STM32_PWR_CR3_USB33RDY      BIT(26)
#define STM32_PWR_CPUCR             REG32(STM32_PWR_BASE + 0x10)
#define  STM32_PWR_CPUCR_PDDS_D1     BIT(0)
#define  STM32_PWR_CPUCR_PDDS_D2     BIT(1)
#define  STM32_PWR_CPUCR_PDDS_D3     BIT(2)
#define  STM32_PWR_CPUCR_STOPF       BIT(5)
#define  STM32_PWR_CPUCR_SBF         BIT(6)
#define  STM32_PWR_CPUCR_SBF_D1      BIT(7)
#define  STM32_PWR_CPUCR_SBF_D2      BIT(8)
#define  STM32_PWR_CPUCR_CSSF        BIT(9)
#define  STM32_PWR_CPUCR_RUN_D3      BIT(11)
#define STM32_PWR_D3CR              REG32(STM32_PWR_BASE + 0x18)
#define  STM32_PWR_D3CR_VOS1         (3 << 14)
#define  STM32_PWR_D3CR_VOS2         (2 << 14)
#define  STM32_PWR_D3CR_VOS3         (1 << 14)
#define  STM32_PWR_D3CR_VOSMASK      (3 << 14)
#define  STM32_PWR_D3CR_VOSRDY       (1 << 13)
#define STM32_PWR_WKUPCR            REG32(STM32_PWR_BASE + 0x20)
#define STM32_PWR_WKUPFR            REG32(STM32_PWR_BASE + 0x24)
#define STM32_PWR_WKUPEPR           REG32(STM32_PWR_BASE + 0x28)


#define STM32_RCC_CR                REG32(STM32_RCC_BASE + 0x000)
#define STM32_RCC_ICSCR             REG32(STM32_RCC_BASE + 0x004)
#define STM32_RCC_CRRCR             REG32(STM32_RCC_BASE + 0x008)
#define STM32_RCC_CFGR              REG32(STM32_RCC_BASE + 0x010)
#define STM32_RCC_D1CFGR            REG32(STM32_RCC_BASE + 0x018)
#define STM32_RCC_D2CFGR            REG32(STM32_RCC_BASE + 0x01C)
#define STM32_RCC_D3CFGR            REG32(STM32_RCC_BASE + 0x020)
#define STM32_RCC_PLLCKSELR         REG32(STM32_RCC_BASE + 0x028)
#define STM32_RCC_PLLCFGR           REG32(STM32_RCC_BASE + 0x02C)
#define STM32_RCC_PLL1DIVR          REG32(STM32_RCC_BASE + 0x030)
#define STM32_RCC_PLL1FRACR         REG32(STM32_RCC_BASE + 0x034)
#define STM32_RCC_PLL2DIVR          REG32(STM32_RCC_BASE + 0x038)
#define STM32_RCC_PLL2FRACR         REG32(STM32_RCC_BASE + 0x03C)
#define STM32_RCC_PLL3DIVR          REG32(STM32_RCC_BASE + 0x040)
#define STM32_RCC_PLL3FRACR         REG32(STM32_RCC_BASE + 0x044)
#define STM32_RCC_D1CCIPR           REG32(STM32_RCC_BASE + 0x04C)
#define STM32_RCC_D2CCIP1R          REG32(STM32_RCC_BASE + 0x050)
#define STM32_RCC_D2CCIP2R          REG32(STM32_RCC_BASE + 0x054)
#define STM32_RCC_D3CCIPR           REG32(STM32_RCC_BASE + 0x058)
#define STM32_RCC_CIER              REG32(STM32_RCC_BASE + 0x060)
#define STM32_RCC_CIFR              REG32(STM32_RCC_BASE + 0x064)
#define STM32_RCC_CICR              REG32(STM32_RCC_BASE + 0x068)
#define STM32_RCC_BDCR              REG32(STM32_RCC_BASE + 0x070)
#define STM32_RCC_CSR               REG32(STM32_RCC_BASE + 0x074)

#define STM32_RCC_APB2RSTR          REG32(STM32_RCC_BASE + 0x098)

#define STM32_RCC_RSR               REG32(STM32_RCC_BASE + 0x0D0)
#define STM32_RCC_AHB3ENR           REG32(STM32_RCC_BASE + 0x0D4)
#define STM32_RCC_AHB1ENR           REG32(STM32_RCC_BASE + 0x0D8)
#define STM32_RCC_AHB2ENR           REG32(STM32_RCC_BASE + 0x0DC)
#define STM32_RCC_AHB2ENR_RNGEN     BIT(6)
#define STM32_RCC_AHB2ENR_HASHEN    BIT(5)
#define STM32_RCC_AHB2ENR_CRYPTEN   BIT(4)
#define STM32_RCC_AHB4ENR           REG32(STM32_RCC_BASE + 0x0E0)
#define STM32_RCC_AHB4ENR_GPIOMASK  0x3ff
#define STM32_RCC_APB3ENR           REG32(STM32_RCC_BASE + 0x0E4)
#define STM32_RCC_APB1LENR          REG32(STM32_RCC_BASE + 0x0E8)
#define STM32_RCC_APB1HENR          REG32(STM32_RCC_BASE + 0x0EC)
#define STM32_RCC_APB2ENR           REG32(STM32_RCC_BASE + 0x0F0)
#define STM32_RCC_APB4ENR           REG32(STM32_RCC_BASE + 0x0F4)
#define STM32_RCC_SYSCFGEN          BIT(1)
#define STM32_RCC_AHB3LPENR         REG32(STM32_RCC_BASE + 0x0FC)
#define STM32_RCC_AHB1LPENR         REG32(STM32_RCC_BASE + 0x100)
#define STM32_RCC_AHB2LPENR         REG32(STM32_RCC_BASE + 0x104)
#define STM32_RCC_AHB4LPENR         REG32(STM32_RCC_BASE + 0x108)
#define STM32_RCC_APB3LPENR         REG32(STM32_RCC_BASE + 0x10C)
#define STM32_RCC_APB1LLPENR        REG32(STM32_RCC_BASE + 0x110)
#define STM32_RCC_APB1HLPENR        REG32(STM32_RCC_BASE + 0x114)
#define STM32_RCC_APB2LPENR         REG32(STM32_RCC_BASE + 0x118)
#define STM32_RCC_APB4LPENR         REG32(STM32_RCC_BASE + 0x11C)
/* Aliases */
#define STM32_RCC_APB1ENR           STM32_RCC_APB1LENR

#define STM32_RCC_CR_HSION                     BIT(0)
#define STM32_RCC_CR_HSIRDY                    BIT(2)
#define STM32_RCC_CR_CSION                     BIT(7)
#define STM32_RCC_CR_CSIRDY                    BIT(8)
#define STM32_RCC_CR_HSI48ON                   BIT(12)
#define STM32_RCC_CR_HSI48RDY                  BIT(13)
#define STM32_RCC_CR_PLL1ON                    BIT(24)
#define STM32_RCC_CR_PLL1RDY                   BIT(25)
#define STM32_RCC_CR_PLL2ON                    BIT(26)
#define STM32_RCC_CR_PLL2RDY                   BIT(27)
#define STM32_RCC_CR_PLL3ON                    BIT(28)
#define STM32_RCC_CR_PLL3RDY                   BIT(29)
#define STM32_RCC_CFGR_SW_HSI                  (0 << 0)
#define STM32_RCC_CFGR_SW_CSI                  (1 << 0)
#define STM32_RCC_CFGR_SW_HSE                  (2 << 0)
#define STM32_RCC_CFGR_SW_PLL1                 (3 << 0)
#define STM32_RCC_CFGR_SW_MASK                 (3 << 0)
#define STM32_RCC_CFGR_SWS_HSI                 (0 << 3)
#define STM32_RCC_CFGR_SWS_CSI                 (1 << 3)
#define STM32_RCC_CFGR_SWS_HSE                 (2 << 3)
#define STM32_RCC_CFGR_SWS_PLL1                (3 << 3)
#define STM32_RCC_CFGR_SWS_MASK                (3 << 3)
#define STM32_RCC_D1CFGR_HPRE_DIV1             (0 << 0)
#define STM32_RCC_D1CFGR_HPRE_DIV2             (8 << 0)
#define STM32_RCC_D1CFGR_HPRE_DIV4             (9 << 0)
#define STM32_RCC_D1CFGR_HPRE_DIV8            (10 << 0)
#define STM32_RCC_D1CFGR_HPRE_DIV16           (11 << 0)
#define STM32_RCC_D1CFGR_D1PPRE_DIV1           (0 << 4)
#define STM32_RCC_D1CFGR_D1PPRE_DIV2           (4 << 4)
#define STM32_RCC_D1CFGR_D1PPRE_DIV4           (5 << 4)
#define STM32_RCC_D1CFGR_D1PPRE_DIV8           (6 << 4)
#define STM32_RCC_D1CFGR_D1PPRE_DIV16          (7 << 4)
#define STM32_RCC_D1CFGR_D1CPRE_DIV1           (0 << 8)
#define STM32_RCC_D1CFGR_D1CPRE_DIV2           (8 << 8)
#define STM32_RCC_D1CFGR_D1CPRE_DIV4           (9 << 8)
#define STM32_RCC_D1CFGR_D1CPRE_DIV8          (10 << 8)
#define STM32_RCC_D1CFGR_D1CPRE_DIV16         (1BIT(8))
#define STM32_RCC_PLLCKSEL_PLLSRC_HSI          (0 << 0)
#define STM32_RCC_PLLCKSEL_PLLSRC_CSI          (1 << 0)
#define STM32_RCC_PLLCKSEL_PLLSRC_HSE          (2 << 0)
#define STM32_RCC_PLLCKSEL_PLLSRC_NONE         (3 << 0)
#define STM32_RCC_PLLCKSEL_PLLSRC_MASK         (3 << 0)
#define STM32_RCC_PLLCKSEL_DIVM1(m)            ((m) << 4)
#define STM32_RCC_PLLCKSEL_DIVM2(m)            ((m) << 12)
#define STM32_RCC_PLLCKSEL_DIVM3(m)            ((m) << 20)
#define STM32_RCC_PLLCFG_PLL1VCOSEL_FRACEN     BIT(0)
#define STM32_RCC_PLLCFG_PLL1VCOSEL_WIDE       (0 << 1)
#define STM32_RCC_PLLCFG_PLL1VCOSEL_MEDIUM     BIT(1)
#define STM32_RCC_PLLCFG_PLL1RGE_1M_2M         (0 << 2)
#define STM32_RCC_PLLCFG_PLL1RGE_2M_4M         (1 << 2)
#define STM32_RCC_PLLCFG_PLL1RGE_4M_8M         (2 << 2)
#define STM32_RCC_PLLCFG_PLL1RGE_8M_16M        (3 << 2)
#define STM32_RCC_PLLCFG_DIVP1EN               BIT(16)
#define STM32_RCC_PLLCFG_DIVQ1EN               BIT(17)
#define STM32_RCC_PLLCFG_DIVR1EN               BIT(18)
#define STM32_RCC_PLLDIV_DIVN(n)               (((n) - 1) << 0)
#define STM32_RCC_PLLDIV_DIVP(p)               (((p) - 1) << 9)
#define STM32_RCC_PLLDIV_DIVQ(q)               (((q) - 1) << 16)
#define STM32_RCC_PLLDIV_DIVR(r)               (((r) - 1) << 24)
#define STM32_RCC_PLLFRAC(n)                   ((n) << 3)
#define STM32_RCC_D2CCIP1R_SPI123SEL_PLL1Q     (0 << 12)
#define STM32_RCC_D2CCIP1R_SPI123SEL_PLL2P     (1 << 12)
#define STM32_RCC_D2CCIP1R_SPI123SEL_PLL3P     (2 << 12)
#define STM32_RCC_D2CCIP1R_SPI123SEL_I2SCKIN   (3 << 12)
#define STM32_RCC_D2CCIP1R_SPI123SEL_PERCK     (4 << 12)
#define STM32_RCC_D2CCIP1R_SPI123SEL_MASK      (7 << 12)
#define STM32_RCC_D2CCIP1R_SPI45SEL_APB        (0 << 16)
#define STM32_RCC_D2CCIP1R_SPI45SEL_PLL2Q      (1 << 16)
#define STM32_RCC_D2CCIP1R_SPI45SEL_PLL3Q      (2 << 16)
#define STM32_RCC_D2CCIP1R_SPI45SEL_HSI        (3 << 16)
#define STM32_RCC_D2CCIP1R_SPI45SEL_CSI        (4 << 16)
#define STM32_RCC_D2CCIP1R_SPI45SEL_HSE        (5 << 16)
#define STM32_RCC_D2CCIP1R_SPI45SEL_MASK       (7 << 16)
#define STM32_RCC_D2CCIP2_USART234578SEL_PCLK  (0 << 0)
#define STM32_RCC_D2CCIP2_USART234578SEL_PLL2Q (1 << 0)
#define STM32_RCC_D2CCIP2_USART234578SEL_PLL3Q (2 << 0)
#define STM32_RCC_D2CCIP2_USART234578SEL_HSI   (3 << 0)
#define STM32_RCC_D2CCIP2_USART234578SEL_CSI   (4 << 0)
#define STM32_RCC_D2CCIP2_USART234578SEL_LSE   (5 << 0)
#define STM32_RCC_D2CCIP2_USART234578SEL_MASK  (7 << 0)
#define STM32_RCC_D2CCIP2_USART16SEL_PCLK      (0 << 3)
#define STM32_RCC_D2CCIP2_USART16SEL_PLL2Q     (1 << 3)
#define STM32_RCC_D2CCIP2_USART16SEL_PLL3Q     (2 << 3)
#define STM32_RCC_D2CCIP2_USART16SEL_HSI       (3 << 3)
#define STM32_RCC_D2CCIP2_USART16SEL_CSI       (4 << 3)
#define STM32_RCC_D2CCIP2_USART16SEL_LSE       (5 << 3)
#define STM32_RCC_D2CCIP2_USART16SEL_MASK      (7 << 3)
#define STM32_RCC_D2CCIP2_RNGSEL_HSI48         (0 << 8)
#define STM32_RCC_D2CCIP2_RNGSEL_PLL1Q         (1 << 8)
#define STM32_RCC_D2CCIP2_RNGSEL_LSE           (2 << 8)
#define STM32_RCC_D2CCIP2_RNGSEL_LSI           (3 << 8)
#define STM32_RCC_D2CCIP2_RNGSEL_MASK          (3 << 8)
#define STM32_RCC_D2CCIP2_LPTIM1SEL_PCLK       (0 << 28)
#define STM32_RCC_D2CCIP2_LPTIM1SEL_PLL2       (1 << 28)
#define STM32_RCC_D2CCIP2_LPTIM1SEL_PLL3       (2 << 28)
#define STM32_RCC_D2CCIP2_LPTIM1SEL_LSE        (3 << 28)
#define STM32_RCC_D2CCIP2_LPTIM1SEL_LSI        (4 << 28)
#define STM32_RCC_D2CCIP2_LPTIM1SEL_PER        (5 << 28)
#define STM32_RCC_D2CCIP2_LPTIM1SEL_MASK       (7 << 28)
#define STM32_RCC_CSR_LSION                    BIT(0)
#define STM32_RCC_CSR_LSIRDY                   BIT(1)

#define STM32_SYSCFG_PMCR           REG32(STM32_SYSCFG_BASE + 0x04)
#define STM32_SYSCFG_EXTICR(n)      REG32(STM32_SYSCFG_BASE + 8 + 4 * (n))

/* Peripheral bits for APB1ENR regs */
#define STM32_RCC_PB1_LPTIM1            BIT(9)

/* Peripheral bits for APB2ENR regs */
#define STM32_RCC_PB2_TIM1              BIT(0)
#define STM32_RCC_PB2_TIM2              BIT(1)
#define STM32_RCC_PB2_USART1            BIT(4)
#define STM32_RCC_PB2_SPI1              BIT(12)
#define STM32_RCC_PB2_SPI4              BIT(13)
#define STM32_RCC_PB2_TIM15             BIT(16)
#define STM32_RCC_PB2_TIM16             BIT(17)
#define STM32_RCC_PB2_TIM17             BIT(18)

/* Peripheral bits for AHB1/2/3/4ENR regs */
#define STM32_RCC_HB1_DMA1              BIT(0)
#define STM32_RCC_HB1_DMA2              BIT(1)
#define STM32_RCC_HB3_MDMA              BIT(0)
#define STM32_RCC_HB4_BDMA              BIT(21)


/* Peripheral bits for RCC_APB/AHB and DBGMCU regs */
#define STM32_RCC_PB2_USART1           BIT(4)

/* Reset causes definitions */
#define STM32_RCC_RESET_CAUSE STM32_RCC_RSR
#define  RESET_CAUSE_WDG                (BIT(28)|BIT(26))
#define  RESET_CAUSE_SFT                BIT(24)
#define  RESET_CAUSE_POR                BIT(23)
#define  RESET_CAUSE_PIN                BIT(22)
#define  RESET_CAUSE_OTHER              (BIT(31)|BIT(30)|BIT(29)|BIT(28)| \
					 BIT(27)|BIT(26)|BIT(25)|BIT(24)| \
					 BIT(23)|BIT(22)|BIT(21)|BIT(20)| \
					 BIT(19)|BIT(18)|BIT(17))
#define  RESET_CAUSE_RMVF               BIT(16)

/* Power cause in PWR CPUCR register (Standby&Stop modes) */
#define STM32_PWR_RESET_CAUSE STM32_PWR_CPUCR
#define STM32_PWR_RESET_CAUSE_CLR STM32_PWR_CPUCR
#define  RESET_CAUSE_SBF                BIT(6)
#define  RESET_CAUSE_SBF_CLR            BIT(9)

/* --- Watchdogs --- */

/* --- Real-Time Clock --- */
#define STM32_RTC_TR                REG32(STM32_RTC_BASE + 0x00)
#define STM32_RTC_DR                REG32(STM32_RTC_BASE + 0x04)
#define STM32_RTC_CR                REG32(STM32_RTC_BASE + 0x08)
#define  STM32_RTC_CR_BYPSHAD        BIT(5)
#define  STM32_RTC_CR_ALRAE          BIT(8)
#define  STM32_RTC_CR_ALRAIE         BIT(12)
#define STM32_RTC_ISR               REG32(STM32_RTC_BASE + 0x0C)
#define  STM32_RTC_ISR_ALRAWF        BIT(0)
#define  STM32_RTC_ISR_RSF           BIT(5)
#define  STM32_RTC_ISR_INITF         BIT(6)
#define  STM32_RTC_ISR_INIT          BIT(7)
#define  STM32_RTC_ISR_ALRAF         BIT(8)
#define STM32_RTC_PRER              REG32(STM32_RTC_BASE + 0x10)
#define  STM32_RTC_PRER_A_MASK       (0x7f << 16)
#define  STM32_RTC_PRER_S_MASK       (0x7fff << 0)
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
#define STM32_BKP_BYTES             128

/* --- SPI --- */

/* The SPI controller registers */
struct stm32_spi_regs {
	uint32_t cr1;
	uint32_t cr2;
	uint32_t cfg1;
	uint32_t cfg2;
	uint32_t ier;
	uint32_t sr;
	uint32_t ifcr;
	uint32_t _pad0;
	uint32_t txdr;
	uint32_t _pad1[3];
	uint32_t rxdr;
	uint32_t _pad2[3];
	uint32_t crcpoly;
	uint32_t rxcrcr;
	uint32_t txcrcr;
	uint32_t udrdr;
};
/* Must be volatile, or compiler optimizes out repeated accesses */
typedef volatile struct stm32_spi_regs stm32_spi_regs_t;

#define STM32_SPI1_REGS ((stm32_spi_regs_t *)STM32_SPI1_BASE)
#define STM32_SPI2_REGS ((stm32_spi_regs_t *)STM32_SPI2_BASE)
#define STM32_SPI3_REGS ((stm32_spi_regs_t *)STM32_SPI3_BASE)
#define STM32_SPI4_REGS ((stm32_spi_regs_t *)STM32_SPI4_BASE)

#define STM32_SPI_CR1_SPE                      BIT(0)
#define STM32_SPI_CR1_CSTART                   BIT(9)
#define STM32_SPI_CR1_SSI                      BIT(12)
#define STM32_SPI_CR1_DIV(div)                 ((div) << 28)
#define STM32_SPI_CFG1_DATASIZE(n)             (((n) - 1) << 0)
#define STM32_SPI_CFG1_FTHLV(n)                (((n) - 1) << 5)
#define STM32_SPI_CFG1_UDRCFG_CONST            (0 << 9)
#define STM32_SPI_CFG1_UDRCFG_LAST_RX          (1 << 9)
#define STM32_SPI_CFG1_UDRCFG_LAST_TX          (2 << 9)
#define STM32_SPI_CFG1_UDRDET_BEGIN_FRM        (0 << 11)
#define STM32_SPI_CFG1_UDRDET_END_FRM          (1 << 11)
#define STM32_SPI_CFG1_UDRDET_BEGIN_SS         (2 << 11)
#define STM32_SPI_CFG1_RXDMAEN                 BIT(14)
#define STM32_SPI_CFG1_TXDMAEN                 BIT(15)
#define STM32_SPI_CFG1_CRCSIZE(n)              (((n) - 1) << 16)
#define  STM32_SPI_CFG2_MSTR                   BIT(22)
#define  STM32_SPI_CFG2_SSM                    BIT(26)
#define  STM32_SPI_CFG2_AFCNTR                 BIT(31)

#define STM32_SPI_SR_RXNE                      BIT(0)
#define STM32_SPI_SR_UDR                       BIT(5)
#define STM32_SPI_SR_FRLVL                     (3 << 13)
#define STM32_SPI_SR_TXC                       BIT(12)

/* --- Debug --- */
#define STM32_DBGMCU_APB3FZ         REG32(STM32_DBGMCU_BASE + 0x34)
#define STM32_DBGMCU_APB1LFZ        REG32(STM32_DBGMCU_BASE + 0x3C)
#define STM32_DBGMCU_APB1HFZ        REG32(STM32_DBGMCU_BASE + 0x44)
#define STM32_DBGMCU_APB2FZ         REG32(STM32_DBGMCU_BASE + 0x4C)
#define STM32_DBGMCU_APB4FZ         REG32(STM32_DBGMCU_BASE + 0x54)
/* Alias */
#define STM32_DBGMCU_APB1FZ         STM32_DBGMCU_APB1LFZ

/* --- Flash --- */
#define STM32_FLASH_REG(bank, offset)     REG32(((bank) ? 0x100 : 0) + \
					  STM32_FLASH_REGS_BASE + (offset))

#define STM32_FLASH_ACR(bank)             STM32_FLASH_REG(bank, 0x00)
#define STM32_FLASH_ACR_LATENCY_SHIFT (0)
#define STM32_FLASH_ACR_LATENCY_MASK  (7 << STM32_FLASH_ACR_LATENCY_SHIFT)
#define STM32_FLASH_ACR_WRHIGHFREQ_85MHZ  (0 << 4)
#define STM32_FLASH_ACR_WRHIGHFREQ_185MHZ (1 << 4)
#define STM32_FLASH_ACR_WRHIGHFREQ_285MHZ (2 << 4)
#define STM32_FLASH_ACR_WRHIGHFREQ_385MHZ (3 << 4)

#define STM32_FLASH_KEYR(bank)            STM32_FLASH_REG(bank, 0x04)
#define  FLASH_KEYR_KEY1                   0x45670123
#define  FLASH_KEYR_KEY2                   0xCDEF89AB
#define STM32_FLASH_OPTKEYR(bank)         STM32_FLASH_REG(bank, 0x08)
#define  FLASH_OPTKEYR_KEY1                0x08192A3B
#define  FLASH_OPTKEYR_KEY2                0x4C5D6E7F
#define STM32_FLASH_CR(bank)              STM32_FLASH_REG(bank, 0x0C)
#define  FLASH_CR_LOCK                     BIT(0)
#define  FLASH_CR_PG                       BIT(1)
#define  FLASH_CR_SER                      BIT(2)
#define  FLASH_CR_BER                      BIT(3)
#define  FLASH_CR_PSIZE_BYTE               (0 << 4)
#define  FLASH_CR_PSIZE_HWORD              (1 << 4)
#define  FLASH_CR_PSIZE_WORD               (2 << 4)
#define  FLASH_CR_PSIZE_DWORD              (3 << 4)
#define  FLASH_CR_PSIZE_MASK               (3 << 4)
#define  FLASH_CR_FW                       BIT(6)
#define  FLASH_CR_STRT                     BIT(7)
#define  FLASH_CR_SNB(sec)                 (((sec) & 0x7) << 8)
#define  FLASH_CR_SNB_MASK                FLASH_CR_SNB(0x7)
#define STM32_FLASH_SR(bank)              STM32_FLASH_REG(bank, 0x10)
#define  FLASH_SR_BUSY                     BIT(0)
#define  FLASH_SR_WBNE                     BIT(1)
#define  FLASH_SR_QW                       BIT(2)
#define  FLASH_SR_CRC_BUSY                 BIT(3)
#define  FLASH_SR_EOP                      BIT(16)
#define  FLASH_SR_WRPERR                   BIT(17)
#define  FLASH_SR_PGSERR                   BIT(18)
#define  FLASH_SR_STRBERR                  BIT(19)
#define  FLASH_SR_INCERR                   BIT(21)
#define  FLASH_SR_OPERR                    BIT(22)
#define  FLASH_SR_RDPERR                   BIT(23)
#define  FLASH_SR_RDSERR                   BIT(24)
#define  FLASH_SR_SNECCERR                 BIT(25)
#define  FLASH_SR_DBECCERR                 BIT(26)
#define  FLASH_SR_CRCEND                   BIT(27)
#define STM32_FLASH_CCR(bank)             STM32_FLASH_REG(bank, 0x14)
#define  FLASH_CCR_ERR_MASK              (FLASH_SR_WRPERR | FLASH_SR_PGSERR \
					| FLASH_SR_STRBERR | FLASH_SR_INCERR \
					| FLASH_SR_OPERR | FLASH_SR_RDPERR \
					| FLASH_SR_RDSERR | FLASH_SR_SNECCERR \
					| FLASH_SR_DBECCERR)
#define STM32_FLASH_OPTCR(bank)           STM32_FLASH_REG(bank, 0x18)
#define  FLASH_OPTCR_OPTLOCK              BIT(0)
#define  FLASH_OPTCR_OPTSTART             BIT(1)
#define STM32_FLASH_OPTSR_CUR(bank)       STM32_FLASH_REG(bank, 0x1C)
#define STM32_FLASH_OPTSR_PRG(bank)       STM32_FLASH_REG(bank, 0x20)
#define  FLASH_OPTSR_BUSY                 BIT(0)   /* only in OPTSR_CUR */
#define  FLASH_OPTSR_RDP_MASK             (0xFF << 8)
#define  FLASH_OPTSR_RDP_LEVEL_0          (0xAA << 8)
/* RDP Level 1: Anything but 0xAA/0xCC */
#define  FLASH_OPTSR_RDP_LEVEL_1          (0x00 << 8)
#define  FLASH_OPTSR_RDP_LEVEL_2          (0xCC << 8)
#define  FLASH_OPTSR_RSS1                 BIT(26)
#define  FLASH_OPTSR_RSS2                 BIT(27)
#define STM32_FLASH_OPTCCR(bank)          STM32_FLASH_REG(bank, 0x24)
#define STM32_FLASH_PRAR_CUR(bank)        STM32_FLASH_REG(bank, 0x28)
#define STM32_FLASH_PRAR_PRG(bank)        STM32_FLASH_REG(bank, 0x2C)
#define STM32_FLASH_SCAR_CUR(bank)        STM32_FLASH_REG(bank, 0x30)
#define STM32_FLASH_SCAR_PRG(bank)        STM32_FLASH_REG(bank, 0x34)
#define STM32_FLASH_WPSN_CUR(bank)        STM32_FLASH_REG(bank, 0x38)
#define STM32_FLASH_WPSN_PRG(bank)        STM32_FLASH_REG(bank, 0x3C)
#define STM32_FLASH_BOOT_CUR(bank)        STM32_FLASH_REG(bank, 0x40)
#define STM32_FLASH_BOOT_PRG(bank)        STM32_FLASH_REG(bank, 0x44)
#define STM32_FLASH_CRC_CR(bank)          STM32_FLASH_REG(bank, 0x50)
#define STM32_FLASH_CRC_SADDR(bank)       STM32_FLASH_REG(bank, 0x54)
#define STM32_FLASH_CRC_EADDR(bank)       STM32_FLASH_REG(bank, 0x58)
#define STM32_FLASH_CRC_DATA(bank)        STM32_FLASH_REG(bank, 0x5C)
#define STM32_FLASH_ECC_FA(bank)          STM32_FLASH_REG(bank, 0x60)

/* --- External Interrupts --- */
#define STM32_EXTI_RTSR1            REG32(STM32_EXTI_BASE + 0x00)
#define STM32_EXTI_FTSR1            REG32(STM32_EXTI_BASE + 0x04)
#define STM32_EXTI_SWIER1           REG32(STM32_EXTI_BASE + 0x08)
#define STM32_EXTI_D3PMR1           REG32(STM32_EXTI_BASE + 0x0C)
#define STM32_EXTI_D3PCR1L          REG32(STM32_EXTI_BASE + 0x10)
#define STM32_EXTI_D3PCR1H          REG32(STM32_EXTI_BASE + 0x14)
#define STM32_EXTI_RTSR2            REG32(STM32_EXTI_BASE + 0x20)
#define STM32_EXTI_FTSR2            REG32(STM32_EXTI_BASE + 0x24)
#define STM32_EXTI_SWIER2           REG32(STM32_EXTI_BASE + 0x28)
#define STM32_EXTI_D3PMR2           REG32(STM32_EXTI_BASE + 0x2C)
#define STM32_EXTI_D3PCR2L          REG32(STM32_EXTI_BASE + 0x30)
#define STM32_EXTI_D3PCR2H          REG32(STM32_EXTI_BASE + 0x34)
#define STM32_EXTI_RTSR3            REG32(STM32_EXTI_BASE + 0x40)
#define STM32_EXTI_FTSR3            REG32(STM32_EXTI_BASE + 0x44)
#define STM32_EXTI_SWIER3           REG32(STM32_EXTI_BASE + 0x48)
#define STM32_EXTI_D3PMR3           REG32(STM32_EXTI_BASE + 0x4C)
#define STM32_EXTI_D3PCR3L          REG32(STM32_EXTI_BASE + 0x50)
#define STM32_EXTI_D3PCR3H          REG32(STM32_EXTI_BASE + 0x54)
#define STM32_EXTI_CPUIMR1          REG32(STM32_EXTI_BASE + 0x80)
#define STM32_EXTI_CPUIER1          REG32(STM32_EXTI_BASE + 0x84)
#define STM32_EXTI_CPUPR1           REG32(STM32_EXTI_BASE + 0x88)
#define STM32_EXTI_CPUIMR2          REG32(STM32_EXTI_BASE + 0x90)
#define STM32_EXTI_CPUIER2          REG32(STM32_EXTI_BASE + 0x94)
#define STM32_EXTI_CPUPR2           REG32(STM32_EXTI_BASE + 0x98)
#define STM32_EXTI_CPUIMR3          REG32(STM32_EXTI_BASE + 0xA0)
#define STM32_EXTI_CPUIER3          REG32(STM32_EXTI_BASE + 0xA4)
#define STM32_EXTI_CPUPR3           REG32(STM32_EXTI_BASE + 0xA8)
/* Aliases */
#define STM32_EXTI_IMR              STM32_EXTI_CPUIMR1
#define STM32_EXTI_EMR              STM32_EXTI_CPUIMR1
#define STM32_EXTI_RTSR             STM32_EXTI_RTSR1
#define STM32_EXTI_FTSR             STM32_EXTI_FTSR1
#define STM32_EXTI_SWIER            STM32_EXTI_SWIER1
#define STM32_EXTI_PR               STM32_EXTI_CPUPR1


/* --- ADC --- */

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

	STM32_DMAC_I2C1_TX = STM32_DMA1_STREAM6,
	STM32_DMAC_I2C1_RX = STM32_DMA1_STREAM0,

	STM32_DMAC_I2C2_TX = STM32_DMA1_STREAM7,
	STM32_DMAC_I2C2_RX = STM32_DMA1_STREAM3,

	STM32_DMAC_I2C3_TX = STM32_DMA1_STREAM4,
	STM32_DMAC_I2C3_RX = STM32_DMA1_STREAM1,

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
#define STM32_DMA_CCR_DIR_P2M           (0 << 6)
#define STM32_DMA_CCR_DIR_M2P           (1 << 6)
#define STM32_DMA_CCR_DIR_M2M           (2 << 6)
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
#define STM32_DMA_CCR_PBURST(b_len)     ((((b_len) - 4) / 4) << 21)
#define STM32_DMA_CCR_MBURST(b_len)     ((((b_len) - 4) / 4) << 21)
#define STM32_DMA_CCR_CHANNEL_MASK      (0 << 25)
#define STM32_DMA_CCR_CHANNEL(channel)  (0)
#define STM32_DMA_CCR_RSVD_MASK         (0xF0100000)
#define STM32_DMA_SFCR_DMDIS            BIT(2)
#define STM32_DMA_SFCR_FTH(level)       (((level) - 1) << 0)


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


/* The requests for the DMA1/DMA2 controllers are routed through DMAMUX1. */
/* DMAMUX1/2 registers */
#define DMAMUX1 0
#define DMAMUX2 1
#define STM32_DMAMUX_BASE(n)        ((n) ? STM32_DMAMUX2_BASE \
					 : STM32_DMAMUX1_BASE)
#define STM32_DMAMUX_REG32(n, off)  REG32(STM32_DMAMUX_BASE(n) + (off))
#define STM2_DMAMUX_CxCR(n, x)      STM32_DMAMUX_REG32(n, 4 * (x))
#define STM2_DMAMUX_CSR(n)          STM32_DMAMUX_REG32(n, 0x80)
#define STM2_DMAMUX_CFR(n)          STM32_DMAMUX_REG32(n, 0x84)
#define STM2_DMAMUX_RGxCR(n, x)     STM32_DMAMUX_REG32(n, 0x100 + 4 * (x))
#define STM2_DMAMUX_RGSR(n)         STM32_DMAMUX_REG32(n, 0x140)
#define STM2_DMAMUX_RGCFR(n)        STM32_DMAMUX_REG32(n, 0x144)

enum dmamux1_request {
	DMAMUX1_REQ_ADC1 = 9,
	DMAMUX1_REQ_ADC2 = 10,
	DMAMUX1_REQ_TIM1_CH1 = 11,
	DMAMUX1_REQ_TIM1_CH2 = 12,
	DMAMUX1_REQ_TIM1_CH3 = 13,
	DMAMUX1_REQ_TIM1_CH4 = 14,
	DMAMUX1_REQ_TIM1_UP = 15,
	DMAMUX1_REQ_TIM1_TRIG = 16,
	DMAMUX1_REQ_TIM1_COM = 17,
	DMAMUX1_REQ_TIM2_CH1 = 18,
	DMAMUX1_REQ_TIM2_CH2 = 19,
	DMAMUX1_REQ_TIM2_CH3 = 20,
	DMAMUX1_REQ_TIM2_CH4 = 21,
	DMAMUX1_REQ_TIM2_UP = 22,
	DMAMUX1_REQ_TIM3_CH1 = 23,
	DMAMUX1_REQ_TIM3_CH2 = 24,
	DMAMUX1_REQ_TIM3_CH3 = 25,
	DMAMUX1_REQ_TIM3_CH4 = 26,
	DMAMUX1_REQ_TIM3_UP = 27,
	DMAMUX1_REQ_TIM3_TRIG = 28,
	DMAMUX1_REQ_TIM4_CH1 = 29,
	DMAMUX1_REQ_TIM4_CH2 = 30,
	DMAMUX1_REQ_TIM4_CH3 = 31,
	DMAMUX1_REQ_TIM4_UP = 32,
	DMAMUX1_REQ_I2C1_RX = 33,
	DMAMUX1_REQ_I2C1_TX = 34,
	DMAMUX1_REQ_I2C2_RX = 35,
	DMAMUX1_REQ_I2C2_TX = 36,
	DMAMUX1_REQ_SPI1_RX = 37,
	DMAMUX1_REQ_SPI1_TX = 38,
	DMAMUX1_REQ_SPI2_RX = 39,
	DMAMUX1_REQ_SPI2_TX = 40,
	DMAMUX1_REQ_USART1_RX = 41,
	DMAMUX1_REQ_USART1_TX = 42,
	DMAMUX1_REQ_USART2_RX = 43,
	DMAMUX1_REQ_USART2_TX = 44,
	DMAMUX1_REQ_USART3_RX = 45,
	DMAMUX1_REQ_USART3_TX = 46,
	DMAMUX1_REQ_TIM8_CH1 = 47,
	DMAMUX1_REQ_TIM8_CH2 = 48,
	DMAMUX1_REQ_TIM8_CH3 = 49,
	DMAMUX1_REQ_TIM8_CH4 = 50,
	DMAMUX1_REQ_TIM8_UP = 51,
	DMAMUX1_REQ_TIM8_TRIG = 52,
	DMAMUX1_REQ_TIM8_COM = 53,
	DMAMUX1_REQ_TIM5_CH1 = 55,
	DMAMUX1_REQ_TIM5_CH2 = 56,
	DMAMUX1_REQ_TIM5_CH3 = 57,
	DMAMUX1_REQ_TIM5_CH4 = 58,
	DMAMUX1_REQ_TIM5_UP = 59,
	DMAMUX1_REQ_TIM5_TRIG = 60,
	DMAMUX1_REQ_SPI3_RX = 61,
	DMAMUX1_REQ_SPI3_TX = 62,
	DMAMUX1_REQ_UART4_RX = 63,
	DMAMUX1_REQ_UART4_TX = 64,
	DMAMUX1_REQ_USART5_RX = 65,
	DMAMUX1_REQ_UART5_TX = 66,
	DMAMUX1_REQ_DAC1 = 67,
	DMAMUX1_REQ_DAC2 = 68,
	DMAMUX1_REQ_TIM6_UP = 69,
	DMAMUX1_REQ_TIM7_UP = 70,
	DMAMUX1_REQ_USART6_RX = 71,
	DMAMUX1_REQ_USART6_TX = 72,
	DMAMUX1_REQ_I2C3_RX = 73,
	DMAMUX1_REQ_I2C3_TX = 74,
	DMAMUX1_REQ_DCMI = 75,
	DMAMUX1_REQ_CRYP_IN = 76,
	DMAMUX1_REQ_CRYP_OUT = 77,
	DMAMUX1_REQ_HASH_IN = 78,
	DMAMUX1_REQ_UART7_RX = 79,
	DMAMUX1_REQ_UART7_TX = 80,
	DMAMUX1_REQ_UART8_RX = 81,
	DMAMUX1_REQ_UART8_TX = 82,
	DMAMUX1_REQ_SPI4_RX = 83,
	DMAMUX1_REQ_SPI4_TX = 84,
	DMAMUX1_REQ_SPI5_RX = 85,
	DMAMUX1_REQ_SPI5_TX = 86,
	DMAMUX1_REQ_SAI1_A = 87,
	DMAMUX1_REQ_SAI1_B = 88,
	DMAMUX1_REQ_SAI2_A = 89,
	DMAMUX1_REQ_SAI2_B = 90,
	DMAMUX1_REQ_SWPMI_RX = 91,
	DMAMUX1_REQ_SWPMI_TX = 92,
	DMAMUX1_REQ_SPDIFRX_DT = 93,
	DMAMUX1_REQ_SPDIFRX_CS = 94,
	DMAMUX1_REQ_TIM15_CH1 = 105,
	DMAMUX1_REQ_TIM15_UP = 106,
	DMAMUX1_REQ_TIM15_TRIG = 107,
	DMAMUX1_REQ_TIM15_COM = 108,
	DMAMUX1_REQ_TIM16_CH1 = 109,
	DMAMUX1_REQ_TIM16_UP = 110,
	DMAMUX1_REQ_TIM17_CH1 = 111,
	DMAMUX1_REQ_TIM17_UP = 112,
	DMAMUX1_REQ_SAI3_A = 113,
	DMAMUX1_REQ_SAI3_B = 114,
	DMAMUX1_REQ_ADC3 = 115,
};

/* --- CRC --- */
#define STM32_CRC_DR                REG32(STM32_CRC_BASE + 0x0)
#define STM32_CRC_DR32              REG32(STM32_CRC_BASE + 0x0)
#define STM32_CRC_DR16              REG16(STM32_CRC_BASE + 0x0)
#define STM32_CRC_DR8               REG8(STM32_CRC_BASE + 0x0)
#define STM32_CRC_IDR               REG32(STM32_CRC_BASE + 0x4)
#define STM32_CRC_CR                REG32(STM32_CRC_BASE + 0x8)
#define  STM32_CRC_CR_RESET          BIT(0)
#define  STM32_CRC_CR_POLYSIZE_32    (0 << 3)
#define  STM32_CRC_CR_POLYSIZE_16    (1 << 3)
#define  STM32_CRC_CR_POLYSIZE_8     (2 << 3)
#define  STM32_CRC_CR_POLYSIZE_7     (3 << 3)
#define  STM32_CRC_CR_REV_IN_BYTE    (1 << 5)
#define  STM32_CRC_CR_REV_IN_HWORD   (2 << 5)
#define  STM32_CRC_CR_REV_IN_WORD    (3 << 5)
#define  STM32_CRC_CR_REV_OUT        BIT(7)
#define STM32_CRC_INIT              REG32(STM32_CRC_BASE + 0x10)
#define STM32_CRC_POL               REG32(STM32_CRC_BASE + 0x14)

/* --- PMSE --- */
#define STM32_PMSE_ARCR             REG32(STM32_PMSE_BASE + 0x0)
#define STM32_PMSE_ACCR             REG32(STM32_PMSE_BASE + 0x4)
#define STM32_PMSE_CR               REG32(STM32_PMSE_BASE + 0x8)
#define STM32_PMSE_CRTDR            REG32(STM32_PMSE_BASE + 0x14)
#define STM32_PMSE_IER              REG32(STM32_PMSE_BASE + 0x18)
#define STM32_PMSE_SR               REG32(STM32_PMSE_BASE + 0x1c)
#define STM32_PMSE_IFCR             REG32(STM32_PMSE_BASE + 0x20)
#define STM32_PMSE_PxPMR(x)         REG32(STM32_PMSE_BASE + 0x2c + (x) * 4)
#define STM32_PMSE_PAPMR            REG32(STM32_PMSE_BASE + 0x2c)
#define STM32_PMSE_PBPMR            REG32(STM32_PMSE_BASE + 0x30)
#define STM32_PMSE_PCPMR            REG32(STM32_PMSE_BASE + 0x34)
#define STM32_PMSE_PDPMR            REG32(STM32_PMSE_BASE + 0x38)
#define STM32_PMSE_PEPMR            REG32(STM32_PMSE_BASE + 0x3c)
#define STM32_PMSE_PFPMR            REG32(STM32_PMSE_BASE + 0x40)
#define STM32_PMSE_PGPMR            REG32(STM32_PMSE_BASE + 0x44)
#define STM32_PMSE_PHPMR            REG32(STM32_PMSE_BASE + 0x48)
#define STM32_PMSE_PIPMR            REG32(STM32_PMSE_BASE + 0x4c)
#define STM32_PMSE_MRCR             REG32(STM32_PMSE_BASE + 0x100)
#define STM32_PMSE_MCCR             REG32(STM32_PMSE_BASE + 0x104)

/* --- USB --- */
#define STM32_USB_EP(n)            REG16(STM32_USB_FS_BASE + (n) * 4)

#define STM32_USB_CNTR             REG16(STM32_USB_FS_BASE + 0x40)
#define  STM32_USB_CNTR_FRES        BIT(0)
#define  STM32_USB_CNTR_PDWN        BIT(1)
#define  STM32_USB_CNTR_LP_MODE     BIT(2)
#define  STM32_USB_CNTR_FSUSP       BIT(3)
#define  STM32_USB_CNTR_RESUME      BIT(4)
#define  STM32_USB_CNTR_L1RESUME    BIT(5)
#define  STM32_USB_CNTR_L1REQM      BIT(7)
#define  STM32_USB_CNTR_ESOFM       BIT(8)
#define  STM32_USB_CNTR_SOFM        BIT(9)
#define  STM32_USB_CNTR_RESETM      BIT(10)
#define  STM32_USB_CNTR_SUSPM       BIT(11)
#define  STM32_USB_CNTR_WKUPM       BIT(12)
#define  STM32_USB_CNTR_ERRM        BIT(13)
#define  STM32_USB_CNTR_PMAOVRM     BIT(14)
#define  STM32_USB_CNTR_CTRM        BIT(15)

#define STM32_USB_ISTR             REG16(STM32_USB_FS_BASE + 0x44)
#define  STM32_USB_ISTR_EP_ID_MASK  (0x000f)
#define  STM32_USB_ISTR_DIR         BIT(4)
#define  STM32_USB_ISTR_L1REQ       BIT(7)
#define  STM32_USB_ISTR_ESOF        BIT(8)
#define  STM32_USB_ISTR_SOF         BIT(9)
#define  STM32_USB_ISTR_RESET       BIT(10)
#define  STM32_USB_ISTR_SUSP        BIT(11)
#define  STM32_USB_ISTR_WKUP        BIT(12)
#define  STM32_USB_ISTR_ERR         BIT(13)
#define  STM32_USB_ISTR_PMAOVR      BIT(14)
#define  STM32_USB_ISTR_CTR         BIT(15)

#define STM32_USB_FNR              REG16(STM32_USB_FS_BASE + 0x48)

#define STM32_USB_FNR_RXDP_RXDM_SHIFT (14)
#define STM32_USB_FNR_RXDP_RXDM_MASK  (3 << STM32_USB_FNR_RXDP_RXDM_SHIFT)

#define STM32_USB_DADDR            REG16(STM32_USB_FS_BASE + 0x4C)
#define STM32_USB_BTABLE           REG16(STM32_USB_FS_BASE + 0x50)
#define STM32_USB_LPMCSR           REG16(STM32_USB_FS_BASE + 0x54)
#define STM32_USB_BCDR             REG16(STM32_USB_FS_BASE + 0x58)
#define  STM32_USB_BCDR_BCDEN       BIT(0)
#define  STM32_USB_BCDR_DCDEN       BIT(1)
#define  STM32_USB_BCDR_PDEN        BIT(2)
#define  STM32_USB_BCDR_SDEN        BIT(3)
#define  STM32_USB_BCDR_DCDET       BIT(4)
#define  STM32_USB_BCDR_PDET        BIT(5)
#define  STM32_USB_BCDR_SDET        BIT(6)
#define  STM32_USB_BCDR_PS2DET      BIT(7)

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
#define  STM32_RNG_CR_RNGEN          BIT(2)
#define  STM32_RNG_CR_IE             BIT(3)
#define  STM32_RNG_CR_CED            BIT(5)
#define STM32_RNG_SR                REG32(STM32_RNG_BASE + 0x4)
#define  STM32_RNG_SR_DRDY           BIT(0)
#define STM32_RNG_DR                REG32(STM32_RNG_BASE + 0x8)

/* --- AXI interconnect --- */

/* STM32H7: AXI_TARGx_FN_MOD exists for masters x = 1, 2 and 7 */
#define STM32_AXI_TARG_FN_MOD(x)    REG32(STM32_GPV_BASE + 0x1108 + \
					  0x1000 * (x))
#define  WRITE_ISS_OVERRIDE          BIT(1)
#define  READ_ISS_OVERRIDE           BIT(0)

/* --- MISC --- */
#define STM32_UNIQUE_ID_ADDRESS     REG32_ADDR(STM32_UNIQUE_ID_BASE)
#define STM32_UNIQUE_ID_LENGTH      (3 * 4)

#endif /* !__ASSEMBLER__ */
