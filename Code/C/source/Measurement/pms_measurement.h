/*
 * measurement_task.h
 *
 *  Created on: May 25, 2023
 *      Author: Paul Mamatis
 */

#ifndef MEASUREMENT_PMS_MEASUREMENT_H_
#define MEASUREMENT_PMS_MEASUREMENT_H_


#include "Measurement/INA226_driver/ina226.h"
#include "pms_HardwareCheck.h"
#include "pms_timestamp.h"

/** Task Prio definend in pms_priorities
#define MEASUREMENT_TASK_PRIO 	(configMAX_PRIORITIES - 3)
*/


#define STREAM_BUFF_DATA_LEN sizeof(measurement_data_t)
#if defined (DATA_CHUNKING)
#define STREAM_BUFF_TRIG_LVL 3 /**< amount of data objects being read in one readcycle */
#else
#define STREAM_BUFF_TRIG_LVL 1 /**< amount of data objects being read in one readcycle */
#endif
#define STREAM_BUFF_TRIG_LVL_BYTE (STREAM_BUFF_TRIG_LVL * STREAM_BUFF_DATA_LEN)	/**> limit of data amount until the Streambuffer is read */
#define STREAM_BUFF_LEN (20*STREAM_BUFF_TRIG_LVL)
#define STREAM_BUFF_SIZE (STREAM_BUFF_DATA_LEN * STREAM_BUFF_LEN)	/**> max amount of data inside the streambuffer */
#define STREAM_BUFF_READ_MAX_LEN (STREAM_BUFF_DATA_LEN * STREAM_BUFF_TRIG_LVL )

#define MEASUREMENT_DATA_FORMAT 0x1 /**< dataformat identifier */


#pragma pack(push,4) /*smaller saving format for better transfer performance */
/** contains all measurements for one power-lane at a certain moment */
typedef struct measurement_data_t{
	int64_t timestamp;
//	timestamp_t timestamp;
	ina226_results_t results;
}measurement_data_t;
#pragma pack(pop)

typedef enum {
	BUS_VOLT = 0,
	SHUNT_VOLT
}voltage_kind_t;

void measurement_init();
void measurementFromISR();
void printMeasurementData(measurement_data_t data, char* name);
void initStream();




#endif /* MEASUREMENT_PMS_MEASUREMENT_H_ */
