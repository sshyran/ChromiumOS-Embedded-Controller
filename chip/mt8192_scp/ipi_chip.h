/* Copyright 2020 The Chromium OS Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef __CROS_EC_IPI_CHIP_H
#define __CROS_EC_IPI_CHIP_H

/*
 * Length of EC version string is at most 32 byte (NULL included), which
 * also aligns SCP fw_version length.
 */
#define SCP_FW_VERSION_LEN 32

/*
 * Video decoder supported capability:
 * BIT(4): 0 enable 4K
 *         1 disable 4K
 */
#define VCODEC_CAPABILITY_4K_DISABLED BIT(4)

#ifndef SCP_IPI_INIT
#error If CONFIG_IPI is enabled, SCP_IPI_INIT must be defined.
#endif

/*
 * Share buffer layout for SCP_IPI_INIT response. This structure should sync
 * across kernel and EC.
 */
struct scp_run_t {
	uint32_t signaled;
	int8_t fw_ver[SCP_FW_VERSION_LEN];
	uint32_t dec_capability;
	uint32_t enc_capability;
};

/*
 * The layout of the IPC0 AP/SCP shared buffer.
 * This should sync across kernel and EC.
 */
struct ipc_shared_obj {
	/* IPI ID */
	int32_t id;
	/* Length of the contents in buffer. */
	uint32_t len;
	/* Shared buffer contents. */
	uint8_t buffer[CONFIG_IPC_SHARED_OBJ_BUF_SIZE];
};

/* Send a IPI contents to AP.  This shouldn't be used in ISR context. */
int ipi_send(int32_t id, const void *buf, uint32_t len, int wait);

/*
 * An IPC IRQ could be shared across many IPI handlers.
 * Those handlers would usually operate on disabling or enabling the IPC IRQ.
 * This may disorder the actual timing to on/off the IRQ when there are many
 * tasks try to operate on it.  As a result, any access to the SCP_IRQ_*
 * should go through ipi_{en,dis}able_irq(), which support a counter to
 * enable/disable the IRQ at correct timing.
 */
/* Disable IPI IRQ. */
void ipi_disable_irq(void);
/* Enable IPI IRQ. */
void ipi_enable_irq(void);

#endif /* __CROS_EC_IPI_CHIP_H */
