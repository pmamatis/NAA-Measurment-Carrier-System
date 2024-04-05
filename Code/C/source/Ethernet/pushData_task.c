
/**
* @file pushData_task.c
* @author Paul Mamatis
* @version 1.0
* @date  Jun 17, 2023
*
* @section DESCRIPTION TODO
*/



/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "Config/pms_config.h"
#if defined(MQTT)

#include  "pushData_task.h"
#include <Measurement/pms_measurement.h>
#include "Ethernet/pms_mqtt_wrapper.h"
#include "Measurement/pms_HardwareCheck.h"
#include "Measurement/INA226_driver/ina226.h"
#include "stream_buffer.h"
#include "Controller/control_task.h"

#include "Ethernet/pms_byte_swap.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/**@brief amount of results which should be passed from ina226 to mqtt, in this case shunt volt and bus volt*/
#define RESULT_AMT 2

/*******************************************************************************
 * Prototypes
 ******************************************************************************/


/*******************************************************************************
 * Variables
 ******************************************************************************/

measurement_payload payload;

/** Stream Variables */
measurement_data_t mqtt_send_buffer[PCIe_SLOTS_AMT][STREAM_BUFF_TRIG_LVL];
extern StreamBufferHandle_t xStreamBufferPCIe1;
extern StreamBufferHandle_t xStreamBufferPCIe2;

/** @brief binary Semaphore to handle mqtt publishing */
SemaphoreHandle_t sem_pub;


/** User Configuration */
extern measurement_config_t *m_config;/**< struct which contains all configuration related to the */

/** topic strinfgs */

/** array contaioning all topics */
char topics[PCIe_SLOTS_AMT][INA226_PCIe_AMT][100];


char* boardnames[2] ={"PCIe1","PCIe2"};

/** @brief contains the names of the measured supply busses, for generating a fitting mqtt topic. sJ4 and sJ5 are the support supply plugs, the names are choosen to fit the size of 3 chars per topic */
char topic_array_device[INA226_PCIe_AMT + INA226_SUPP_AMT][MQTT_MSG_SUBTOPIC_STRLEN_D+1] = {("12V"),("3V3"),("AUX"),("sJ4"),("sJ5")};
/** @brief contains the nams of each lane which can be measured, to generate a fitting mqtt topic*/
char topic_array_lane[PCIe_SLOTS_AMT + SUPP_AMT][MQTT_MSG_SUBTOPIC_STRLEN_L+1] = {("PCIe1"),("PCIe2"),("Supp")};


#if defined (COLLECT_META_DATA)
extern transmission_meta_data_t meta_data;
#endif
/*******************************************************************************
 * Code
 ******************************************************************************/


void pushData_task (void *pvParameters){

	measurement_data_t pvBuffer;
	printf("In Push Task\r\n");


#ifdef SEM_DEBUG
		printf("SEM DEBUG: ----GIVE publish Semaphore first time after creation----\r\n");
		// Print the current count of the semaphore
		printf("SEM DEBUG: ----SemCount = %i----\n\r", uxSemaphoreGetCount(sem_pub));
#endif

	while(1){

		char* topic_name;
		uint8_t slot_amt;


		/** wait for MQTT callback to be ready, also makes certain taht no data is dead from the Streambuffer and then not used */
		xSemaphoreTake(sem_pub, portMAX_DELAY);

		/** task waits as long as BOTH, pcie1 and pcie2 have enough data inside streambuffer and then continious with the processing */
		if (m_config->useCase != SINGLE_SLOT){
			/** get measurement data from streambuffer for pcie1*/
			uint16_t x = xStreamBufferReceive(xStreamBufferPCIe1, mqtt_send_buffer[0], STREAM_BUFF_READ_MAX_LEN, portMAX_DELAY);

			#if defined (COLLECT_META_DATA)
			meta_data.bytes_fromBufferPCIe1 += x;
			#endif

			/** get measurement data from streambuffer for pcie1*/
			uint16_t y = xStreamBufferReceive(xStreamBufferPCIe2, mqtt_send_buffer[1], STREAM_BUFF_READ_MAX_LEN, portMAX_DELAY);

			#if defined (COLLECT_META_DATA)
			meta_data.bytes_fromBufferPCIe2 += y;
			#endif

			/** setting counting variable to maximum for upcoming for-loop */
			slot_amt = PCIe_SLOTS_AMT;
		}
		/** Task waits only for pcie1 data */
		else if (m_config->useCase == SINGLE_SLOT){
			/** get measurement data from streambuffer for pcie1*/
			uint16_t x = xStreamBufferReceive(xStreamBufferPCIe1, mqtt_send_buffer[0], STREAM_BUFF_READ_MAX_LEN, portMAX_DELAY);

			/** setting counting variable to 1 for upcoming for-loop */
			slot_amt = 1;
		}
		/** give Semaphore back in order to start pushing */
		xSemaphoreGive(sem_pub);




#if defined (DATA_CHUNKING)
		if(m_config->HighSpeedmode){

				publish_mqtt_msg_measurement(m_config->DUT_Names[0], mqtt_send_buffer[0]);



//
//				if (m_config->useCase == DUAL_SLOT) topic_name = "SUPP";
//
//				else if (m_config->useCase == DOUBLE_SINGLE_SLOT) topic_name = "PCIe2";

				xSemaphoreTake(sem_pub, portMAX_DELAY);
				publish_mqtt_msg_measurement(m_config->DUT_Names[1], mqtt_send_buffer[1]);
		}
		else{

		}







#else
		/** go trhough all pcie slots , Supp and PCIe2 are excluding each other so are stored in the same place */
		for (int j = 0; j < slot_amt; j++){

			/** measureement data is stored in a more compact way, but each power-rail should get a single topics, so they need to be unpackedd */
			for (int i = 0;i < INA226_PCIe_AMT; i++){

				/** maybe it needs to wait here for mqtt callback via Semaphore TODO*/
				/** wait for MQTT callback */
				xSemaphoreTake(sem_pub, portMAX_DELAY);

				/** constructing payload */
				payload.version = MEASUREMENT_DATA_FORMAT;
				payload.timestamp = swap_int64(mqtt_send_buffer[j][0].timestamp);
//				payload.timestamp_s = mqtt_send_buffer[j][0].timestamp.seconds;
//				payload.timestamp_us = mqtt_send_buffer[j][0].timestamp.microseconds;
				payload.bus_voltage = mqtt_send_buffer[j][0].results.busVoltage[i];
				payload.current = mqtt_send_buffer[j][0].results.current[i];
				payload.power = mqtt_send_buffer[j][0].results.power[i];
				swap_uint32(&(payload.version));
				swap_uint32((uint32_t*)&(payload.bus_voltage));
				swap_uint32((uint32_t*)&(payload.current));
				swap_uint32((uint32_t*)&(payload.power));

				/** publish msg */
				publish_mqtt_msg_measurement(topics[j][i], &payload);


				}
			}
#endif
}


	vTaskDelete(NULL);
}



/**
 * @brief fills the msg_pcie and msg_supp struct with topic strings for each origin of a voltage value
 * @details needs to be called just once, the purpose is to reduce proccessing overhead for pushing messages to the mqtt broker
 */
void create_MQTTtopic_for_each_case(lane_t slot){


		for (int j = 0; j < INA226_PCIe_AMT; j++){

			sprintf((topics[slot][j]) ,"%s/%s/data/%s",PRE_TOPIC,m_config->DUT_Names[slot],topic_array_device[j]);
//			printf("topic: %s\n\r",topics[i][j]);

		}

}

#endif
