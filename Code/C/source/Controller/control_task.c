/*
 * control_task.c
 *
 *  Created on: Aug 22, 2023
 *      Author: paul
 *
 * 	@brief TODO description
 */



/*******************************************************************************
* Includes
*******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>



#include "Controller/control_task.h"

/** Command strings */
#include "Config/pms_control_commands.h"

#include "Measurement/pms_HardwareCheck.h"

//MQTT
#include "mqtt.h"
#include "Ethernet/pms_mqtt_wrapper.h"
#include "message_buffer.h"
#include "Ethernet/pushData_task.h"

//Timestamp
#include "Measurement/pms_timestamp.h"
#include "fsl_rit.h"
#include "Measurement/pms_Timer.h"
#include "Measurement/pms_measurement.h"

//µC
#include "LPC54S018.h"
#include "board.h"
#include "core_cm4.h"

//Measurement
#include "Measurement/INA226_driver/ina226_measurement_frequency_adjusting.h"
#include "Measurement/I2C/pms_i2c_init.h"


/*******************************************************************************
* Defines
*******************************************************************************/
#define TOPIC_MSG_BUFF_SIZE_BYTE 1000

/*******************************************************************************
* Local Types and Typedefs
*******************************************************************************/

/*******************************************************************************
* Variables
*******************************************************************************/

/**** Global *****/
/*! @brief MQTT client data. */
extern mqtt_client_t *mqtt_client;

/** incoming MQTT messages queue */
MessageBufferHandle_t subsription_subtopic;
MessageBufferHandle_t subsription_msg;

/** Strerasmbuffer for measurementdata parsing */
extern StreamBufferHandle_t xStreamBufferPCIe1;
extern StreamBufferHandle_t xStreamBufferPCIe2;

extern uint8_t topic_size ; /**< size of the topic string */

control_parameters_t *control; /**< struct with information about ongoing processes for the control task */

extern measurement_config_t *m_config;/**< struct which contains all configuration related to the */

#if defined (COLLECT_META_DATA)
transmission_meta_data_t meta_data; /**< struct for collecting meta data, for debugging purposes */
#endif
/**** Local *****/
uint8_t ucRxData_topic[100]; /**< reveived topic will be stored here as string */
uint8_t ucRxData_msg[100]; /**< reveived msg will be stored here as string */




/*******************************************************************************
* Function Prototypes
*******************************************************************************/

static void configuration_from_mqtt_topic();
void set_frequency(float frequency);
static void system_reset();
static uint32_t getAllBytesInsideStreamBuffers();

/******************************************************************************
* Code
*******************************************************************************/

/** @brief init function for the control task. Initialization of the Message Buffer, which store the incoming MQTT meassages from the broker
 * @param control
 */
void control_init(control_parameters_t *control){
	subsription_msg  = xMessageBufferCreate(TOPIC_MSG_BUFF_SIZE_BYTE);
    subsription_subtopic = xMessageBufferCreate(TOPIC_MSG_BUFF_SIZE_BYTE);
	control-> measurement_active = false;
}

void control_task (void *pvParameters){

	size_t xReceivedBytes_topic, xReceivedBytes_msg;
	const TickType_t xBlockTime = portMAX_DELAY;

	while(1){


	    /** Receive the next message from the message buffer. Wait in the Blocked
	    state (so not using any CPU processing time) for
	    a message to become available. */
	    xReceivedBytes_topic = xMessageBufferReceive( subsription_subtopic,
	                                            ( void * ) (ucRxData_topic),
	                                            sizeof( ucRxData_topic ),
	                                            xBlockTime );
		xReceivedBytes_msg = xMessageBufferReceive( subsription_msg,
													( void * ) (ucRxData_msg),
													sizeof( ucRxData_msg),
															xBlockTime);


			printf("subtopic: %s\r\n", ucRxData_topic);
			printf("msg: %s\r\n",ucRxData_msg);

			/** measurement Switching */
			if((strstr(ucRxData_topic, m_config->DUT_Names[0])  !=  0) || (strstr(ucRxData_topic, m_config->DUT_Names[1])  !=  0)){
				if ( strstr(ucRxData_topic, ON_OFF_COMMAND)  != 0 ){
					if ( strcmp(ucRxData_msg, "ON")  == 0 ){
						control_measurement_switch(ON);
					}
					else if ( strcmp(ucRxData_msg, "OFF")  == 0 ){
						control_measurement_switch(OFF);
					}
				}
			}

			/** frequency settings */
				else if ( strstr(ucRxData_topic, FREQUENCY_TOPIC)  !=  0 ){
					float frequency =	strtof(ucRxData_msg,NULL);
					printf("frequency from Config topic: %f\r\n",frequency);
					set_frequency(frequency);
				}
			/** set Time */
				else if ( strstr(ucRxData_topic, TIME_TOPIC)  !=  0 ){

					uint32_t time = atoi(ucRxData_msg);
					printf("date: %i\r\n", time);
					set_initial_TIME(time);

				}

			/** DUT Names*/
				else if ( strstr(ucRxData_topic, PCIE1_TOPIC)  != 0 ){
						 strcpy(m_config->DUT_Names[0],ucRxData_msg);

						 char on_off_topic[30];
						 /** create ON_OF topic string*/
						 sprintf(on_off_topic,"%s/%s/%s",PRE_TOPIC,m_config->DUT_Names[0],ON_OFF_COMMAND);
						 /** subscribe on the ON Off topic*/
						 printf("DUT Name for PCIe1 set to: %s\r\n",ucRxData_msg);
#if !defined (DATA_CHUNKING)
						 /** In case the Normal mode is activated the topics strings have to be updated, to not do it each publish */
						 create_MQTTtopic_for_each_case(PCIe1);
#endif
						 mqtt_subscribe_topic(on_off_topic);

					}

				else if ( strstr(ucRxData_topic, PCIE2_TOPIC)  != 0){
						/** save the DUT name for pushing the measurementdata on the same named topic */
						 strcpy(m_config->DUT_Names[1],ucRxData_msg);

						 char on_off_topic[30];
						 /** create ON_OF topic string*/
						 sprintf(on_off_topic,"%s/%s/%s",PRE_TOPIC,m_config->DUT_Names[1],ON_OFF_COMMAND);
						 /** subscribe on the ON Off topic*/
						 printf("DUT Name for PCIe2 set to: %s\r\n",ucRxData_msg);
#if !defined (DATA_CHUNKING)
						 /** In case the Normal mode is activated the topics strings have to be updated, to not do it each publish */
						 create_MQTTtopic_for_each_case(PCIe2);
#endif
						 mqtt_subscribe_topic(on_off_topic);

				}

			/** Use Case setting */
				else if ( strstr(ucRxData_topic, USE_CASE_COMMAND)  != 0 ){
					if ( strcmp(ucRxData_msg, "SINGLE")  == 0 ){
						m_config->useCase = SINGLE_SLOT;
					}

					else if ( strcmp(ucRxData_msg, "DUAL")  == 0 ){
						m_config->useCase = DUAL_SLOT;
					}
					else if ( strcmp(ucRxData_msg, "DOUBLE")  == 0 ){
						m_config->useCase = DOUBLE_SINGLE_SLOT;
					}
				}
				/** system Reset */
				else if ( strstr(ucRxData_topic, RESET_COMMAND)  != 0 ){
						if ( strcmp(ucRxData_msg, "reset")  == 0 ){
							system_reset();
									}
					}
//				vTaskDelay(1000);
	    	}

//		}

}


/**
 * @brief switching on/off the measurement by turning on/off the interrrupt which triggers the measurement
 *
 */
void control_measurement_switch(switch_status_t status){

	switch (status) {
		case ON:
			RIT_Deinit(RIT);
			pms_timer_init();
			RIT_StartTimer(RIT);
			control->measurement_active = true;
			LED1_ON();
			break;
		case OFF:
			RIT_StopTimer(RIT);
			control->measurement_active = false;
			LED1_OFF();
		default:
			break;
	}

}
void control_dynamic_task_priooreties(){
//	if (measurement_data_amt > (mqtt_send * STREAM_BUFF_TRIG_LVL )
}
uint32_t publishes_before;
void print_metadata(){



    /** all data acquired */
    uint32_t data_acquired = (meta_data.bytes_acquiredPCIe1 + meta_data.bytes_acquiredPCIe2) / STREAM_BUFF_DATA_LEN;

	printf("mqtt publish: %u",meta_data.mqtt_send);

	/** prints the number MQTT publish callbacks between two calls of the function */
	printf("	"
			"mqtt publish per 10s: %u",meta_data.mqtt_send - publishes_before);
	publishes_before = meta_data.mqtt_send;

    /** lost data is increased each time a stream buffer cant be writen, so the data are not in the send chain */
	printf("	lost data: %u ",meta_data.data_lost);

    printf("	acquired: %u",data_acquired);

    printf("	data not sent: %i\r\n ",getAllBytesInsideStreamBuffers());


}

//extern ina226_frequency_t frequencies[64];
void set_frequency(float frequency){
	printf("setting Frequency to %f\r\n",frequency);

	if ((frequency <= MAX_FREQ) &&(frequency >= 1)){
		m_config->mfrequency = frequency;

		/** first switch off the measurement, because the ina226 gets a new config */
		control_measurement_switch(OFF);

		/** completly new Config for the INA226 */
		I2C_INIT();
		pms_HardwareInit(FULL, frequency);

	}
	else{
	ina226_getAllavailibleFreqs();
	}
}

/**
 * @fn uint32_t getAllBytesInsideStreamBuffers()
 * @brief gets all bytes stored inside a Stream Buffer
 *
 * @return number of total bytes
 */
static uint32_t getAllBytesInsideStreamBuffers(){
	uint32_t retval = 0;
	retval += 	xStreamBufferBytesAvailable(xStreamBufferPCIe1);
	retval += 	xStreamBufferBytesAvailable(xStreamBufferPCIe2);
	return retval;
}

static void system_reset(){
	__NVIC_SystemReset();
}
