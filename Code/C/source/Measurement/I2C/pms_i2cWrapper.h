/*
 * NAA_i2c.h
 *
 *  Created on: Sep 30, 2022
 *      Author: paul
 */

#ifndef PMS_I2C_H_
#define PMS_I2C_H_


#include "Config/pms_config.h"
#if defined(NORMAL_I2C)
#include "fsl_i2c_freertos.h"
#include "pms_HardwareCheck.h"
#define i2c_task_PRIORITY (configMAX_PRIORITIES - 2)



// I2C Functions
uint16_t i2c_readREG(lane_t lane,uint8_t devAdress, uint8_t regAdress);
//uint16_t i2c_readREG(i2c_rtos_handle_t* hi2c,uint8_t devAdress, uint8_t regAdress);
//void i2c_writeREG(i2c_rtos_handle_t* hi2c,uint8_t devAdress, uint8_t regAdress,uint8_t* data);

void i2c_writeREG(lane_t lane,uint8_t devAdress, uint8_t regAdress,uint16_t* data);//< optimized for readiing ina226 register
void i2c_writeREG_Blocking(lane_t lane,uint8_t devAdress, uint8_t regAdress,uint16_t* data);
#if defined(RTOS_I2C)
void get_i2c_status(i2c_rtos_handle_t* hi2c);
#elif defined(NORMAL_I2C)
void get_i2c_status(I2C_Type* hi2c);

void I2C_PCIE1_clb(I2C_Type *base, i2c_master_handle_t *handle, status_t completionStatus, void *userData);
void I2C_PCIE2_clb(I2C_Type *base, i2c_master_handle_t *handle, status_t completionStatus, void *userData);
void I2C_SUPP_clb(I2C_Type *base, i2c_master_handle_t *handle, status_t completionStatus, void *userData);
#endif

void i2c_plain_test();

//HAL_I2C_Mem_Read(i2c_handler, BUS_ADRESS, REGISTER, I2C_MEMADD_SIZE_8BIT, pData, LENGTH,TIMEOUT);
//void naa_i2c_transfer_init(void);
//void naa_i2c_dma_REGread(I2C_Type* hi2c,i2c_master_dma_handle_t* hdma,uint8_t regAdress);
#endif
#endif /* PMS_I2C_H_ */
