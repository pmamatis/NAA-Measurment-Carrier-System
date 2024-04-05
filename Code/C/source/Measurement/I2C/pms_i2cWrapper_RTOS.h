/*
 * NAA_i2c.h
 *
 *  Created on: Sep 30, 2022
 *      Author: paul
 */

#ifndef PMS_I2C_RTOS_H_
#define PMS_I2C_RTOS_H_

#include "Config/pms_config.h"
#if defined(RTOS_I2C)

#include "fsl_i2c_freertos.h"
#include "Measurement/pms_measurement_defines.h"




/** I2C Functions */
void i2c_writeREG(i2c_rtos_handle_t* hi2c,i2c_master_transfer_t* transfer_struct,uint8_t devAdress, uint8_t regAdress,uint8_t* data);
uint16_t i2c_readREG(i2c_rtos_handle_t* hi2c,i2c_master_transfer_t* transfer_struct,uint8_t devAdress, uint8_t regAdress);
void get_i2c_status(I2C_Type* hi2c);
void i2c_plain_test();
status_t I2C_Command_sequence();
void i2c_setBaudRateForAll(uint32_t rate);
void I2C_Sequence_read(i2c_rtos_handle_t* hi2c,i2c_master_transfer_t* transfer_struct,uint8_t devAdress, uint8_t regAdress, uint8_t* g_rxBuff);


/** I2C Commands from interrupt Service routine */
void i2c_writeREGFromISR(i2c_rtos_handle_t* hi2c,i2c_master_transfer_t* transfer_struct,uint8_t devAdress, uint8_t regAdress,uint8_t* data);
uint16_t i2c_readREGFromISR(i2c_rtos_handle_t* hi2c,i2c_master_transfer_t* transfer_struct,uint8_t devAdress, uint8_t regAdress, uint8_t* g_rxbuff);
status_t I2C_RTOS_TransferFromISR(i2c_rtos_handle_t *handle, i2c_master_transfer_t *transfer);



#endif
#endif /* PMS_I2C_RTOS_H_ */
