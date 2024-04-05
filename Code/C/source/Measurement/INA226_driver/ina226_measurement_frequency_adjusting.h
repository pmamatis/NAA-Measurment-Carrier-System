
/**
* @file ina226_measurement_frequency_adjusting.h
* @author Paul Mamatis
* @version 1.0
* @date  Jun 14, 2023
*
* @section DESCRIPTION TODO
*/


#ifndef MEASUREMENT_INA226_DRIVER_INA226_MEASUREMENT_FREQUENCY_ADJUSTING_H_
#define MEASUREMENT_INA226_DRIVER_INA226_MEASUREMENT_FREQUENCY_ADJUSTING_H_

#include "ina226.h"


#define MAX_FREQ 7142 		/** maximal availible frequency given through ina226 configuration*/

typedef struct {
	float frequency;
	ina226_config_data_t config;
	INA226_VBUSCT_t vbusct;
	INA226_VSHCT_t vshct;
	INA226_NoA_t noa;
    int remainder;
} ina226_frequency_t;



void ina226_getAllavailibleFreqs();
uint8_t ina226_getClosestFreq(float measurement_frequency);


#endif /* MEASUREMENT_INA226_DRIVER_INA226_MEASUREMENT_FREQUENCY_ADJUSTING_H_ */
