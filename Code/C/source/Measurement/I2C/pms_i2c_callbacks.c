/*
 * pms_i2c_callbacks.c
 *
 *  Created on: Jul 27, 2023
 *      Author: paul
 *
 */



/*******************************************************************************
* Includes
*******************************************************************************/
#include "pms_i2c_callbacks.h"
#include "Measurement/pms_measurement_defines.h"
#include <stdio.h>
#include "Config/pms_config.h"
#include "semphr.h"
#include <stdbool.h>
/*******************************************************************************
* Defines
*******************************************************************************/
/*******************************************************************************
* Local Types and Typedefs
*******************************************************************************/

/*******************************************************************************
* Variables
*******************************************************************************/

/**** Global *****/
extern bool i2c_from_isr;
/**** Local *****/


/*******************************************************************************
* Function Prototypes
*******************************************************************************/
static void RTOS_CallbackFromISR(I2C_Type *base, i2c_master_handle_t *drv_handle, status_t status, void *userData);
void getI2CtrueFrequency();
uint16_t receivedByteToUint16Value(uint8_t* g_rxBuff);
/******************************************************************************
* Code
*******************************************************************************/

/**
 * @fn void RTOS_CallbackFromISR(I2C_Type*, i2c_master_handle_t*, status_t, void*)
 * @brief  function to called inside the I2C Callback if the I2C communication is connected to RTOS, e.g. gives semaphore if the transaction is finished so another transaction command can be started
 *
 * @param base
 * @param drv_handle
 * @param status
 * @param userData
 */
static void RTOS_CallbackFromISR(I2C_Type *base, i2c_master_handle_t *drv_handle, status_t status, void *userData)
{
    i2c_rtos_handle_t *handle = (i2c_rtos_handle_t *)userData;
    BaseType_t reschedule;
    handle->async_status = status;
    (void)xSemaphoreGiveFromISR(handle->semaphore, &reschedule);
    portYIELD_FROM_ISR(reschedule);
}


/**
 * @fn void I2C_PCIE_clb(I2C_Type*, i2c_master_handle_t*, status_t, void*)
 * @brief I2C Transfer Callback, called after each I2C transmission
 *
 * @param base
 * @param handle
 * @param completionStatus
 * @param userData
 */
void I2C_PCIE_clb(I2C_Type *base, i2c_master_handle_t *handle, status_t completionStatus, void *userData){

	pms_ina226_pcie *hardware_data = ((pms_ina226_pcie*)userData);
	i2c_rtos_handle_t* i2c_handler = hardware_data->i2c_handler;



#if defined (RTOS_I2C)
	/** RTOS related stuff is made here */

	RTOS_CallbackFromISR(base, handle, completionStatus,i2c_handler);
#else
	if(i2c_from_isr){
		uint16_t *buffer =  hardware_data->transfer_struct->data;
		*buffer= receivedByteToUint16Value(hardware_data->transfer_struct->data);
	}
#endif

}

/**
 * @fn void receivedByteToUint16Value(uint8_t*)
 * @brief received data is big endian, so if the value is interpreted as uint16_t value the MSB needs to shifted
 *
 * @param g_rxBuff pointer to received data
 */
uint16_t receivedByteToUint16Value(uint8_t* g_rxBuff){
   return  (g_rxBuff[0]  << 8) + g_rxBuff[1] ;
}

