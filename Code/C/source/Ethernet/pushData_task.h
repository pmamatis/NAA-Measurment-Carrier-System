/**
* @file TODO
* @author Paul Mamatis
* @version 1.0
* @date  Jun 14, 2023
*
* @section DESCRIPTION TODO
*/


#ifndef ETHERNET_PUSHDATA_TASK_H_
#define ETHERNET_PUSHDATA_TASK_H_



#if defined(MQTT)

#include <stdint.h>
#include "Measurement/pms_measurement_defines.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define MQTT_CLIENT_ID SYSTEM_NAME /**< individual BoardID used as mqtt client ID */
#define MQTT_MSG_SUBTOPIC_STRLEN_D 3 /**< length of sub topic str, to distinguish sended values by supply bus */
#define MQTT_MSG_SUBTOPIC_STRLEN_L 5 /**< length of sub topic str, to distinguish sended values by measured lane*/
#define MQTT_MSG_SUBTOPIC_STRLEN_R 3 /**< length of sub topic str, to distinguish sended values by Register*/




/** Task Prio definend in pms_priorities
#define PUSH_TASK_PRIO MEASUREMENT_TASK_PRIO-1
*/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
void pushData_task(void *pvParameters);
void create_MQTTtopic_for_each_case(lane_t slot);
#endif

#endif /* ETHERNET_PUSHDATA_TASK_H_ */
