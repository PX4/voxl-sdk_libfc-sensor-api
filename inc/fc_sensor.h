#ifndef FC_SENSOR_H
#define FC_SENSOR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

// Flight controller specific interface (legacy)
typedef void (*fc_receive_cb)(const char *topic,
			      const uint8_t *data,
			      uint32_t length_in_bytes);
typedef void (*fc_advertise_cb)(const char *topic);
typedef void (*fc_add_subscription_cb)(const char *topic);
typedef void (*fc_remove_subscription_cb)(const char *topic);

typedef struct {
	fc_receive_cb               rx_callback;
	fc_advertise_cb             ad_callback;
	fc_add_subscription_cb      sub_callback;
	fc_remove_subscription_cb   remove_sub_callback;
} fc_callbacks;

int fc_sensor_get_time_offset(void);
int fc_sensor_set_library_name(const char *name);
int fc_sensor_initialize(bool enable_debug_messages, fc_callbacks *callbacks);
int fc_sensor_advertise(const char *topic);
int fc_sensor_subscribe(const char *topic);
int fc_sensor_unsubscribe(const char *topic);
int fc_sensor_send_data(const char *topic,
			const uint8_t *data,
			uint32_t length_in_bytes);
void fc_sensor_kill_slpi(void);

// SLPI link generic interface (recommended for new designs)

typedef void (*slpi_link_cb)(const uint8_t *data, uint32_t length_in_bytes);

int slpi_link_init(bool enable_debug_messages, slpi_link_cb callback, const char *library_name);
int slpi_link_get_time_offset(void);
int slpi_link_send(const uint8_t *data, uint32_t length_in_bytes);
void slpi_link_reset(void);

#ifdef __cplusplus
}
#endif

#endif // FC_SENSOR_H
