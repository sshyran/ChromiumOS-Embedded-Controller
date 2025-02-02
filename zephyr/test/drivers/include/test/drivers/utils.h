/* Copyright 2022 The Chromium OS Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef ZEPHYR_TEST_DRIVERS_INCLUDE_UTILS_H_
#define ZEPHYR_TEST_DRIVERS_INCLUDE_UTILS_H_

#include <zephyr/drivers/emul.h>
#include <zephyr/drivers/gpio/gpio_emul.h>
#include <string.h>

#include "charger.h"
#include "emul/tcpc/emul_tcpci_partner_src.h"
#include "extpower.h"
#include "host_command.h"

/** @brief Set chipset to S0 state. Call all necessary hooks. */
void test_set_chipset_to_s0(void);

/** @brief Set chipset to G3 state. Call all necessary hooks. */
void test_set_chipset_to_g3(void);

/*
 * TODO(b/217755888): Implement ztest assume API upstream
 */

/**
 * @brief Assume that this function call won't be reached
 * @param msg Optional message to print if the assumption fails
 */
#define zassume_unreachable(msg, ...) zassert_unreachable(msg, ##__VA_ARGS__)

/**
 * @brief Assume that @a cond is true
 * @param cond Condition to check
 * @param msg Optional message to print if the assumption fails
 */
#define zassume_true(cond, msg, ...) zassert_true(cond, msg, ##__VA_ARGS__)

/**
 * @brief Assume that @a cond is false
 * @param cond Condition to check
 * @param msg Optional message to print if the assumption fails
 */
#define zassume_false(cond, msg, ...) zassert_false(cond, msg, ##__VA_ARGS__)

/**
 * @brief Assume that @a cond is 0 (success)
 * @param cond Condition to check
 * @param msg Optional message to print if the assumption fails
 */
#define zassume_ok(cond, msg, ...) zassert_ok(cond, msg, ##__VA_ARGS__)

/**
 * @brief Assume that @a ptr is NULL
 * @param ptr Pointer to compare
 * @param msg Optional message to print if the assumption fails
 */
#define zassume_is_null(ptr, msg, ...) zassert_is_null(ptr, msg, ##__VA_ARGS__)

/**
 * @brief Assume that @a ptr is not NULL
 * @param ptr Pointer to compare
 * @param msg Optional message to print if the assumption fails
 */
#define zassume_not_null(ptr, msg, ...) \
	zassert_not_null(ptr, msg, ##__VA_ARGS__)

/**
 * @brief Assume that @a a equals @a b
 *
 * @a a and @a b won't be converted and will be compared directly.
 *
 * @param a Value to compare
 * @param b Value to compare
 * @param msg Optional message to print if the assumption fails
 */
#define zassume_equal(a, b, msg, ...) zassert_equal(a, b, msg, ##__VA_ARGS__)

/**
 * @brief Assume that @a a does not equal @a b
 *
 * @a a and @a b won't be converted and will be compared directly.
 *
 * @param a Value to compare
 * @param b Value to compare
 * @param msg Optional message to print if the assumption fails
 */
#define zassume_not_equal(a, b, msg, ...) \
	zassert_not_equal(a, b, msg, ##__VA_ARGS__)

/**
 * @brief Assume that @a a equals @a b
 *
 * @a a and @a b will be converted to `void *` before comparing.
 *
 * @param a Value to compare
 * @param b Value to compare
 * @param msg Optional message to print if the assumption fails
 */
#define zassume_equal_ptr(a, b, msg, ...) \
	zassert_equal_ptr(a, b, msg, ##__VA_ARGS__)

/**
 * @brief Assume that @a a is within @a b with delta @a d
 *
 * @param a Value to compare
 * @param b Value to compare
 * @param d Delta
 * @param msg Optional message to print if the assumption fails
 */
#define zassume_within(a, b, d, msg, ...) \
	zassert_within(a, b, d, msg, ##__VA_ARGS__)

/**
 * @brief Assume that 2 memory buffers have the same contents
 *
 * This macro calls the final memory comparison assumption macro.
 * Using double expansion allows providing some arguments by macros that
 * would expand to more than one values (ANSI-C99 defines that all the macro
 * arguments have to be expanded before macro call).
 *
 * @param ... Arguments, see @ref zassume_mem_equal__
 *            for real arguments accepted.
 */
#define zassume_mem_equal(...) zassert_mem_equal(##__VA_ARGS__)

/**
 * Run the host command to get the charge state for a given charger number.
 *
 * This function assumes a successful host command processing and will make a
 * call to the zassume_* API. A failure here will abort the calling test.
 *
 * @param chgnum The charger number to query.
 * @return The result of the query.
 */
static inline struct ec_response_charge_state host_cmd_charge_state(int chgnum)
{
	struct ec_params_charge_state params = {
		.chgnum = chgnum,
		.cmd = CHARGE_STATE_CMD_GET_STATE,
	};
	struct ec_response_charge_state response;
	struct host_cmd_handler_args args =
		BUILD_HOST_COMMAND(EC_CMD_CHARGE_STATE, 0, response, params);

	zassume_ok(host_command_process(&args),
		   "Failed to get charge state for chgnum %d", chgnum);
	return response;
}

/**
 * Run the host command to get the USB PD power info for a given port.
 *
 * This function assumes a successful host command processing and will make a
 * call to the zassume_* API. A failure here will abort the calling test.
 *
 * @param port The USB port to get info from.
 * @return The result of the query.
 */
static inline struct ec_response_usb_pd_power_info host_cmd_power_info(int port)
{
	struct ec_params_usb_pd_power_info params = { .port = port };
	struct ec_response_usb_pd_power_info response;
	struct host_cmd_handler_args args = BUILD_HOST_COMMAND(
		EC_CMD_USB_PD_POWER_INFO, 0, response, params);

	zassume_ok(host_command_process(&args),
		   "Failed to get power info for port %d", port);
	return response;
}

/**
 * Run the host command to get the Type-C status information for a given port.
 *
 * This function assumes a successful host command processing and will make a
 * call to the zassume_* API. A failure here will abort the calling test.
 *
 * @param port The USB port to get info from.
 * @return The result of the query.
 */
static inline struct ec_response_typec_status host_cmd_typec_status(int port)
{
	struct ec_params_typec_status params = { .port = port };
	struct ec_response_typec_status response;
	struct host_cmd_handler_args args =
		BUILD_HOST_COMMAND(EC_CMD_TYPEC_STATUS, 0, response, params);

	zassume_ok(host_command_process(&args),
		   "Failed to get Type-C state for port %d", port);
	return response;
}

static inline struct ec_response_usb_pd_control
host_cmd_usb_pd_control(int port, enum usb_pd_control_swap swap)
{
	struct ec_params_usb_pd_control params = { .port = port, .swap = swap };
	struct ec_response_usb_pd_control response;
	struct host_cmd_handler_args args =
		BUILD_HOST_COMMAND(EC_CMD_USB_PD_CONTROL, 0, response, params);

	zassume_ok(host_command_process(&args),
		   "Failed to process usb_pd_control_swap for port %d, swap %d",
		   port, swap);
	return response;
}

/**
 * Run the host command to get the charge state.
 *
 * @return The result of the query.
 */
static inline struct ec_response_charge_control
host_cmd_get_charge_control(void)
{
	struct ec_params_charge_control params = {
		.cmd = EC_CHARGE_CONTROL_CMD_GET
	};
	struct ec_response_charge_control response;
	struct host_cmd_handler_args args =
		BUILD_HOST_COMMAND(EC_CMD_CHARGE_CONTROL, 2, response, params);

	zassume_ok(host_command_process(&args),
		   "Failed to get charge control values");

	return response;
}

/**
 * @brief Call the host command MOTION_SENSE with the dump sub-command
 *
 * Note: this function uses the zassume_ API. It will skip the test if the host
 * command fails.
 *
 * @param max_sensor_count The maximum number of sensor data objects to populate
 *        in the response object.
 * @param response Pointer to the response object to fill.
 */
void host_cmd_motion_sense_dump(int max_sensor_count,
				struct ec_response_motion_sense *response);

/**
 * @brief Call the host command MOTION_SENSE with the data sub-command
 *
 * @param sensor_num The sensor index in the motion_sensors array to query
 * @param response Pointer to the response data structure to fill on success
 * @return The result code from the host command
 */
int host_cmd_motion_sense_data(uint8_t sensor_num,
			       struct ec_response_motion_sense *response);

/**
 * @brief Call the host command MOTION_SENSE with the info sub-command
 *
 * @param cmd_version The command version
 * @param sensor_num The sensor index in the motion_sensors array to query
 * @param response Pointer to the response data structure to fill on success
 * @return The result code from the host command
 */
int host_cmd_motion_sense_info(uint8_t cmd_version, uint8_t sensor_num,
			       struct ec_response_motion_sense *response);

/**
 * @brief Call the host command MOTION_SENSE with the ec_rate sub-command
 *
 * This function performs a read of the current rate by passing
 * EC_MOTION_SENSE_NO_VALUE as the data rate. Otherwise, the data rate should be
 * updated.
 *
 * @param sensor_num The sensor index in the motion_sensors array to query
 * @param data_rate_ms The new data rate or EC_MOTION_SENSE_NO_VALUE to read
 * @param response Pointer to the response data structure to fill on success
 * @return The result code from the host command
 */
int host_cmd_motion_sense_ec_rate(uint8_t sensor_num, int data_rate_ms,
				  struct ec_response_motion_sense *response);

/**
 * @brief Call the host command MOTION_SENSE with the odr sub-command
 *
 * This function performs a read of the current odr by passing
 * EC_MOTION_SENSE_NO_VALUE as the data rate. Otherwise, the data rate should be
 * updated.
 *
 * @param sensor_num The sensor index in the motion_sensors array to query
 * @param odr The new ODR to set
 * @param round_up Whether or not to round up the ODR
 * @param response Pointer to the response data structure to fill on success
 * @return The result code form the host command
 */
int host_cmd_motion_sense_odr(uint8_t sensor_num, int32_t odr, bool round_up,
			      struct ec_response_motion_sense *response);

/**
 * @brief Call the host command MOTION_SENSE with the sensor range sub-command
 *
 * This function attempts to set the sensor range and returns the range value.
 * If the range value is EC_MOTION_SENSE_NO_VALUE, then the host command will
 * not attempt to update the range.
 *
 * @param sensor_num The sensor index in the motion_sensors array to query
 * @param range The new range to set
 * @param round_up Whether or not to round up the range.
 * @param response Pointer to the response data structure to fill on success
 * @return The result code from the host command
 */
int host_cmd_motion_sense_range(uint8_t sensor_num, int32_t range,
				bool round_up,
				struct ec_response_motion_sense *response);

/**
 * @brief Call the host command MOTION_SENSE with the sensor offset sub-command
 *
 * This function attempts to set the offset if the flags field includes
 * MOTION_SENSE_SET_OFFSET. Otherwise, the temperature and offsets are ignored.
 * The response field will include the current (after modification) offsets and
 * temperature.
 *
 * @param sensor_num The sensor index in the motion_sensors array to query
 * @param flags The flags to pass to the host command
 * @param temperature The temperature at which the offsets were attained (set)
 * @param offset_x The X offset to set
 * @param offset_y The Y offset to set
 * @param offset_z The Z offset to set
 * @param response Pointer to the response data structure to fill on success
 * @return The result code from the host command
 */
int host_cmd_motion_sense_offset(uint8_t sensor_num, uint16_t flags,
				 int16_t temperature, int16_t offset_x,
				 int16_t offset_y, int16_t offset_z,
				 struct ec_response_motion_sense *response);

/**
 * @brief Call the host command MOTION_SENSE with the sensor scale sub-command
 *
 * This function attempts to set the scale if the flags field includes
 * MOTION_SENSE_SET_OFFSET. Otherwise, the temperature and scales are ignored.
 * The response field will include the current (after modification) scales and
 * temperature.
 *
 * @param sensor_num The sensor index in the motion_sensors array to query
 * @param flags The flags to pass to the host command
 * @param temperature The temperature at which the scales were attained (set)
 * @param scale_x The X scale to set
 * @param scale_y The Y scale to set
 * @param scale_z The Z scale to set
 * @param response Pointer to the response data structure to fill on success
 * @return The result code from the host command
 */
int host_cmd_motion_sense_scale(uint8_t sensor_num, uint16_t flags,
				int16_t temperature, int16_t scale_x,
				int16_t scale_y, int16_t scale_z,
				struct ec_response_motion_sense *response);

/**
 * @brief Enable/disable sensor calibration via host command
 *
 * @param sensor_num The sensor index in the motion_sensors array to query
 * @param enable Whether to enable or disable the calibration
 * @param response Pointer to the response data structure to fill on success
 * @return The result code from the host command
 */
int host_cmd_motion_sense_calib(uint8_t sensor_num, bool enable,
				struct ec_response_motion_sense *response);

/**
 * @brief Set the sensor's fifo flush bit
 *
 * @param sensor_num The sensor index in the motion_sensors array to query
 * @param response Pointer to the response data structure to fill on success
 * @return The result code from the host command
 */
int host_cmd_motion_sense_fifo_flush(uint8_t sensor_num,
				     struct ec_response_motion_sense *response);

/**
 * @brief Get the current fifo info
 *
 * @param response Pointer to the response data structure to fill on success
 * @return The result code from the host command
 */
int host_cmd_motion_sense_fifo_info(struct ec_response_motion_sense *response);

/**
 * @brief Get the current fifo data
 *
 * @param buffer_length The number of entries available on the response pointer
 * @param response Pointer to the response data structure to fill on success
 * @return The result code from the host command
 */
int host_cmd_motion_sense_fifo_read(uint8_t buffer_length,
				    struct ec_response_motion_sense *response);

/**
 * @brief Call the int_enable motionsense host command
 *
 * @param enable 0 for disable, 1 for enable. All others are invalid
 * @param response Pointer to the response data structure to fill on success
 * @return The result code from the host command
 */
int host_cmd_motion_sense_int_enable(int8_t enable,
				     struct ec_response_motion_sense *response);

/**
 * @brief Call the spoof motion_sense subcommand
 *
 * @param sensor_num The sensor index in motion_sensors
 * @param enable The enable field, for normal operations this will be one of
 * enum motionsense_spoof_mode
 * @param values0 The X value to set if using custom mode
 * @param values1 The Y value to set if using custom mode
 * @param values2 The Z value to set if using custom mode
 * @param response Pointer to the response data structure to fill on success
 * @return The result code from the host command
 */
int host_cmd_motion_sense_spoof(uint8_t sensor_num, uint8_t enable,
				int16_t values0, int16_t values1,
				int16_t values2,
				struct ec_response_motion_sense *response);

/**
 * Run the host command to get the PD discovery responses.
 *
 * @param port          The USB-C port number
 * @param partner_type  SOP, SOP', or SOP''
 * @param response      Destination buffer for command response;
 *                      should hold struct ec_response_typec_discovery and
 *                      enough struct svid_mode_info for expected response.
 * @param response_size Number of bytes in response
 */
void host_cmd_typec_discovery(int port, enum typec_partner_type partner_type,
			      void *response, size_t response_size);

#define GPIO_ACOK_OD_NODE DT_NODELABEL(gpio_acok_od)
#define GPIO_ACOK_OD_PIN  DT_GPIO_PIN(GPIO_ACOK_OD_NODE, gpios)

/**
 * Set whether or not AC is enabled.
 *
 * If enabled, the device _should_ begin charging.
 *
 * This function assumes a successful gpio emulator call and will make a call
 * to the zassume_* API. A failure here will abort the calling test.
 *
 * This function sleeps to wait for the GPIO interrupt to take place.
 *
 * @param enabled Whether or not to enable AC.
 */
static inline void set_ac_enabled(bool enabled)
{
	const struct device *acok_dev =
		DEVICE_DT_GET(DT_GPIO_CTLR(GPIO_ACOK_OD_NODE, gpios));

	zassume_ok(gpio_emul_input_set(acok_dev, GPIO_ACOK_OD_PIN, enabled),
		   NULL);
	k_sleep(K_MSEC(CONFIG_EXTPOWER_DEBOUNCE_MS + 1));
	zassume_equal(enabled, extpower_is_present(), NULL);
}

/**
 * @brief Connect a power source to a given port.
 *
 * Note: this is function currently only supports an ISL923X charger chip.
 *
 * @param partner Pointer to the emulated TCPCI partner device
 * @param src Pointer to the emulated source extension
 * @param pdo_index The index of the PDO object within the src to use
 * @param tcpci_emul The TCPCI emulator that the source will connect to
 * @param charger_emul The charger chip emulator
 */
void connect_source_to_port(struct tcpci_partner_data *partner,
			    struct tcpci_src_emul_data *src, int pdo_index,
			    const struct emul *tcpci_emul,
			    const struct emul *charger_emul);

/**
 * @brief Disconnect a power source from a given port.
 *
 * Note: this is function currently only supports an ISL923X charger chip.
 *
 * @param tcpci_emul The TCPCI emulator that will be disconnected
 * @param charger_emul The charger chip emulator
 */
void disconnect_source_from_port(const struct emul *tcpci_emul,
				 const struct emul *charger_emul);

/**
 * @brief Allocate memory for a test pourpose
 *
 * @param bytes Number of bytes to allocate
 *
 * @return Pointer to valid memory or NULL
 */
void *test_malloc(size_t bytes);

/**
 * @brief Free memory allocated by @ref test_malloc
 *
 * @param mem Pointer to the memory
 */
void test_free(void *mem);

#endif /* ZEPHYR_TEST_DRIVERS_INCLUDE_UTILS_H_ */
