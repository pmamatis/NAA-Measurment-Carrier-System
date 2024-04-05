/**
* @file TODO
* @author Paul Mamatis
* @version 1.0
* @date  Jun 14, 2023
*
* @section DESCRIPTION TODO
*/


#ifndef MQTT_WRAPPER_H_
#define MQTT_WRAPPER_H_

#if defined(MQTT)
#include <stdint.h>
#include <Measurement/pms_measurement.h>
#include "mqtt.h"
#include "Config/pms_control_commands.h"

#define MQTT_DATA_PACKAGE_AMT STREAM_BUFF_TRIG_LVL_BYTE

#define MQTT_CONFIG_TOPIC CONFIG_TOPIC

#define MQTT_QoS 1 /**< quality of Service, measurement data publish  */


/** struct which defines how the measurement dat are pushed into the mqtt broker */
#pragma pack(push,4)
typedef struct measurement_payload{
	uint32_t version;
	int64_t timestamp;
//	uint32_t timestamp_s;
//	uint32_t timestamp_us;
	float bus_voltage;
	float current;
	float power;
}measurement_payload;
#pragma pack(pop)


void start_mqtt(void);
//void publish_mqtt_msg(char* payload);
void publish_mqtt_msg_float(char* topic, float payload);
void publish_mqtt_msg_string(char* topic,char* payload, size_t size );
void mqtt_subscribe_topic(char* topic);

#if defined (DATA_CHUNKING)
void publish_mqtt_msg_measurement(char* topic,  measurement_data_t *payload);
#else
void publish_mqtt_msg_measurement(char* topic,  measurement_payload *payload);
#endif


void mqtt_init();
void mqtt_subscribe_topics(mqtt_client_t *client);

/**
 * @brief struct to store msg information
 */
typedef struct{
	char* topic;
	measurement_data_t payload_f;
	void* payload_ptr;
	uint16_t length;
}mqtt_msg_t;

typedef struct{
	char* topic;
	char* payload;
}mqtt_msg_str_t;

typedef enum{
	FLOAT =0,
	STRING
}type_enum_t;
#endif

 /* MQTT_WRAPPER_H_ */
#endif
