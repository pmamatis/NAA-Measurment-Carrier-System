/*
 * control_task.h
 *
 *  Created on: Aug 22, 2023
 *      Author: paul
 *
 * 	@brief TODO description
 */

#ifndef CONTROLLER_CONTROL_TASK_H_
#define CONTROLLER_CONTROL_TASK_H_



/*******************************************************************************
* Includes
*******************************************************************************/
#include <stdbool.h>

/*******************************************************************************
* Defines
*******************************************************************************/
typedef struct{
	bool measurement_active;
}control_parameters_t;



typedef enum {
	OFF,
	ON
}switch_status_t;




#if defined(COLLECT_META_DATA)
typedef struct transmission_meta_data_t{
	uint32_t bytes_send; 	/**< counts all bytes which are sended to MQTT broker */
	uint32_t mqtt_send; 	/**< counts all mqtt pubkishes  */

	uint32_t bytes_fromBufferPCIe1; 	/**< counts all bytes which are read out of the stream buffer */
	uint32_t bytes_fromBufferPCIe2; 	/**< counts all bytes which are read out of the stream buffer */
	uint32_t bytes_acquiredPCIe1; /**< counts all bytes which are gained by the measurement */
	uint32_t bytes_acquiredPCIe2; /**< counts all bytes which are gained by the measurement */
	uint32_t data_lost; /**< increased always a data object is lost, because the streambuffer was full*/
	uint32_t bytes_insideBuffer; /** byte amount inside all stream buffers together, is equvalent to bytes which need to be sended*/

}transmission_meta_data_t;
#endif
/*******************************************************************************
* Functions
*******************************************************************************/
void control_task (void *pvParameters);
void control_measurement_switch(switch_status_t status);
void control_init(control_parameters_t *control);
void print_metadata();


#endif /* CONTROLLER_CONTROL_TASK_H_ */
