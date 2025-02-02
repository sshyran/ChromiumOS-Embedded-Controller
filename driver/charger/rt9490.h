/* Copyright 2022 The Chromium OS Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 *
 * Richtek 5A 1-4 cell buck-boost switching battery charger driver.
 */
#include <stdbool.h>

#ifndef __CROS_EC_RT9490_H
#define __CROS_EC_RT9490_H

#define RT9490_ADDR_FLAGS	0x53

/* Registers */
#define RT9490_REG_SYS_MIN_REGU		0x00
#define RT9490_REG_VCHG_CTRL		0x01
#define RT9490_REG_ICHG_CTRL		0x03
#define RT9490_REG_MIVR_CTRL		0x05
#define RT9490_REG_AICR_CTRL		0x06
#define RT9490_REG_PRE_CHG		0x08
#define RT9490_REG_EOC_CTRL		0x09
#define RT9490_REG_RECHG		0x0A
#define RT9490_REG_VOTG_REGU		0x0B
#define RT9490_REG_IOTG_REGU		0x0D
#define RT9490_REG_SAFETY_TMR_CTRL	0x0E
#define RT9490_REG_CHG_CTRL0		0x0F
#define RT9490_REG_CHG_CTRL1		0x10
#define RT9490_REG_CHG_CTRL2		0x11
#define RT9490_REG_CHG_CTRL3		0x12
#define RT9490_REG_CHG_CTRL4		0x13
#define RT9490_REG_CHG_CTRL5		0x14
#define RT9490_REG_THREG_CTRL		0x16
#define RT9490_REG_JEITA_CTRL0		0x17
#define RT9490_REG_JEITA_CTRL1		0x18
#define RT9490_REG_AICC_CTRL		0x19
#define RT9490_REG_CHG_STATUS0		0x1B
#define RT9490_REG_CHG_STATUS1		0x1C
#define RT9490_REG_CHG_STATUS2		0x1D
#define RT9490_REG_CHG_STATUS3		0x1E
#define RT9490_REG_CHG_STATUS4		0x1F
#define RT9490_REG_FAULT_STATUS0	0x20
#define RT9490_REG_FAULT_STATUS1	0x21
#define RT9490_REG_CHG_IRQ_FLAG0	0x22
#define RT9490_REG_CHG_IRQ_FLAG1	0x23
#define RT9490_REG_CHG_IRQ_FLAG2	0x24
#define RT9490_REG_CHG_IRQ_FLAG3	0x25
#define RT9490_REG_CHG_IRQ_FLAG4	0x26
#define RT9490_REG_CHG_IRQ_FLAG5	0x27
#define RT9490_REG_CHG_IRQ_MASK0	0x28
#define RT9490_REG_CHG_IRQ_MASK1	0x29
#define RT9490_REG_CHG_IRQ_MASK2	0x2A
#define RT9490_REG_CHG_IRQ_MASK3	0x2B
#define RT9490_REG_CHG_IRQ_MASK4	0x2C
#define RT9490_REG_CHG_IRQ_MASK5	0x2D
#define RT9490_REG_ADC_CTRL		0x2E
#define RT9490_REG_ADC_CHANNEL0		0x2F
#define RT9490_REG_ADC_CHANNEL1		0x30
#define RT9490_REG_IBUS_ADC		0x31
#define RT9490_REG_IBAT_ADC		0x33
#define RT9490_REG_VBUS_ADC		0x35
#define RT9490_REG_VAC1_ADC		0x37
#define RT9490_REG_VAC2_ADC		0x39
#define RT9490_REG_VBAT_ADC		0x3B
#define RT9490_REG_VSYS_ADC		0x3D
#define RT9490_REG_TS_ADC		0x3F
#define RT9490_REG_TDIE_ADC		0x41
#define RT9490_REG_DP_ADC		0x43
#define RT9490_REG_DM_ADC		0x45
#define RT9490_REG_DPDM_MANU_CTRL	0x47
#define RT9490_REG_DEVICE_INFO		0x48
#define RT9490_REG_PUMP_EXP		0x49
#define RT9490_REG_ADD_CTRL0		0x4A
#define RT9490_REG_ADD_CTRL1		0x4B
#define RT9490_REG_ADD_CTRL2		0x4C
#define RT9490_REG_ADD_IRQ_FLAG		0x4D
#define RT9490_REG_ADD_IRQ_MASK6	0x4E

struct rt9490_init_setting {
	int eoc_current;
	int mivr;
	int boost_voltage;
	int boost_current;
};

/* CV */
#define RT9490_CV_MASK				0x7FF
#define RT9490_CV_MIN				3000
#define RT9490_CV_MAX				18800
#define RT9490_CV_STEP				10

/* ICGH */
#define RT9490_ICHG_MASK			0x1FF
#define RT9490_ICHG_SHIFT			0
#define RT9490_ICHG_MIN				50
#define RT9490_ICHG_MAX				5000
#define RT9490_ICHG_STEP			10
#define RT9490_ICHG_MIN_REG_VAL			0x0005

/* PRE CHG */
#define RT9490_IPRE_CHG_MASK			0x1F
#define RT9490_IPRE_CHG_MIN			40
#define RT9490_IPRE_CHG_MAX			2000
#define RT9490_IPRE_CHG_STEP			40
#define RT9490_IPREC_SHIFT			0

/* MIVR */
#define RT9490_MIVR_MIN				3600
#define RT9490_MIVR_MAX				22000
#define RT9490_MIVR_STEP			100
#define RT9490_MIVR_MIN_REG_VAL			0x24

/* AICR */
#define RT9490_AICR_MASK			0x1FF
#define RT9490_AICR_SHIFT			0
#define RT9490_AICR_MIN				100
#define RT9490_AICR_MAX				3300
#define RT9490_AICR_STEP			10
#define RT9490_AICR_MIN_REG_VAL			0x000A

/* EOC */
#define RT9490_IEOC_MIN				40
#define RT9490_IEOC_MAX				1000
#define RT9490_IEOC_STEP			40
#define RT9490_IEOC_MIN_REG_VAL			0x01
#define RT9490_IEOC_SHIFT			0
#define RT9490_IEOC_MASK			0x1F

/* DEVICE INFO */
#define RT9490_DEVICE_ID			0x60
#define RT9490_DEVICE_INFO_MASK			0x78

/* EOC_CTRL */
#define RT9490_RST_ALL_MASK			BIT(7)

/* CHG_CTRL0 */
#define RT9490_EN_CHG				BIT(5)
#define RT9490_EN_AICC				BIT(4)
#define RT9490_FORCE_AICC			BIT(3)
#define RT9490_EN_HZ				BIT(2)

/* CHG_CTRL1 */
#define RT9490_VAC_OVP_SHIFT			4
#define RT9490_VAC_OVP_MASK			(3 << RT9490_VAC_OVP_SHIFT)
#define RT9490_VAC_OVP_26V			0
#define RT9490_VAC_OVP_22V			1
#define RT9490_VAC_OVP_12V			2
#define RT9490_VAC_OVP_7V			3

#define RT9490_WATCHDOG_MASK			0x07
#define RT9490_WATCHDOG_DISABLE			0
#define RT9490_WATCHDOG_0_5_SEC			1 /* 0.5 sec */
#define RT9490_WATCHDOG_1_SEC			2
#define RT9490_WATCHDOG_2_SEC			3
#define RT9490_WATCHDOG_20_SEC			4
#define RT9490_WATCHDOG_40_SEC			5
#define RT9490_WATCHDOG_80_SEC			6
#define RT9490_WATCHDOG_160_SEC			7

/* CHG_CTRL2 */
#define RT9490_BC12_EN				BIT(6)

/* CHG_CTRL3 */
#define RT9490_EN_OTG				BIT(6)

/* CHG_CTRL5 */
#define RT9490_ILIM_HZ_EN			BIT(1)

/* CHG_STATUS4 */
#define RT9490_JEITA_COLD_MASK			BIT(3)
#define RT9490_JEITA_COOL_MASK			BIT(2)
#define RT9490_JEITA_WARM_MASK			BIT(1)
#define RT9490_JEITA_HOT_MASK			BIT(0)

/* CHG_IRQ_FLAG1 */
#define RT9490_BC12_DONE_FLAG			BIT(0)

/* CHG_IRQ_MASK0 */
#define RT9490_CHG_IRQ_MASK0_ALL		0xFF

/* CHG_IRQ_MASK1 */
#define RT9490_BC12_DONE_MASK			BIT(0)
#define RT9490_CHG_IRQ_MASK1_ALL		0xD7

/* CHG_IRQ_MASK2 */
#define RT9490_CHG_IRQ_MASK2_ALL		0x7F

/* CHG_IRQ_MASK3 */
#define RT9490_CHG_IRQ_MASK3_ALL		0x1F

/* CHG_IRQ_MASK4 */
#define RT9490_CHG_IRQ_MASK4_ALL		0xFF

/* CHG_IRQ_MASK5 */
#define RT9490_CHG_IRQ_MASK5_ALL		0xF4

/* SAFETY TMR CTRL */
#define RT9490_EN_TRICHG_TMR			BIT(5)
#define RT9490_EN_PRECHG_TMR			BIT(4)
#define RT9490_EN_FASTCHG_TMR			BIT(3)

/* VOTG REGU */
#define RT9490_VOTG_MASK			0x7FF
#define RT9490_VOTG_MIN				2800
#define RT9490_VOTG_MAX				22000
#define RT9490_VOTG_STEP			10

/* IOTG REGU */
#define RT9490_IOTG_MASK			0x7F
#define RT9490_IOTG_MIN				120
#define RT9490_IOTG_MAX				3320
#define RT9490_IOTG_STEP			40

/* JEITA_CTRL1 */
#define RT9490_JEITA_DIS			BIT(0)

/* CHG_STATUS1 */
#define RT9490_CHG_STAT_MASK			0xE0
#define RT9490_CHG_STAT_SHIFT			5
#define RT9490_VBUS_STAT_MASK			0x1E
#define RT9490_VBUS_STAT_SHIFT			1
#define RT9490_BC12_DONE_STAT			BIT(0)

#define RT9490_SDP				0x1
#define RT9490_CDP				0x2
#define RT9490_DCP				0x3

/* FAULT STATUS0 */
#define RT9490_VBAT_OVP_STAT			BIT(5)

/* ADC CTRL */
#define RT9490_ADC_EN				BIT(7)

/* ADC CHANNEL0 */
#define RT9490_VSYS_ADC_DIS			BIT(3)

/* ADD CTRL0 */
#define RT9490_AUTO_AICR			BIT(5)
#define RT9490_TD_EOC				BIT(4)
#define RT9490_AUTO_MIVR			BIT(2)
#define RT9490_JEITA_COLD_HOT			BIT(0)

/* ADD CTRL1 */
#define RT9490_PWM_1MHZ_EN			BIT(4)

extern const struct charger_drv rt9490_drv;
extern const struct bc12_drv rt9490_bc12_drv;

void rt9490_interrupt(int port);

int rt9490_enable_adc(int chgnum, bool en);
/* enable pwm frequency 1MHz mode */
int rt9490_enable_pwm_1mhz(int chgnum, bool en);

#endif /* __CROS_EC_RT9490_H */
