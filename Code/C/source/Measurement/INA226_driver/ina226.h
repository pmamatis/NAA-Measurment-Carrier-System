
/**
* @file ina226.h
* @author Paul Mamatis
* @version 1.0
* @date  Jun 14, 2023
*
* @section DESCRIPTION TODO
*/


#ifndef __INA226_H__
#define __INA226_H__


#include <stdint.h>
#include <stdio.h>
#include "fsl_i2c_freertos.h"
#include "Measurement/pms_measurement_defines.h"




/**CONFIGURATION REGISTER MASKS END */







uint16_t ina226_calibrate(double I_MAX, double R_SHUNT);



#if defined(RTOS_I2C)
INA226_ReturnVal ina226_isConnected(i2c_rtos_handle_t* hi2c_rtos, uint16_t devAddress);
#elif defined(NORMAL_I2C)
	INA226_ReturnVal ina226_isConnected(I2C_Type* hi2c, uint16_t devAddress);
#endif


INA226_ReturnVal ina226_init(i2c_rtos_handle_t *handle, i2c_master_transfer_t *transfer,uint16_t devAddress,double imax, double rshunt, char* name,ina226_config_data_t conf) ;
uint16_t ina226_GetBusVoltage(i2c_rtos_handle_t *handle, i2c_master_transfer_t *transfer, uint16_t busAddress);
uint16_t ina226_GetShuntVoltage(i2c_rtos_handle_t *handle, i2c_master_transfer_t *transfer, uint16_t busAddress);



/**
* @brief Result to Number
*/
float ina226_shuntToVoltage(uint16_t shuntResult);
float ina226_busToVoltage(uint16_t shuntResult);
float ina226_currentToAmpere(uint16_t currentResult);
float ina226_powerToWatt(uint16_t powerResult);

void ina226_GetCurrent(struct ina226_results_t* result);



#endif
