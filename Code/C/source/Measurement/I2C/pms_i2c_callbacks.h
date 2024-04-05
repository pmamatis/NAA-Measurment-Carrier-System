/*
 * pms_i2c_callbacks.h
 *
 *  Created on: Jul 27, 2023
 *      Author: paul
 *
 * 	@brief TODO description
 */

#ifndef MEASUREMENT_PMS_I2C_CALLBACKS_H_
#define MEASUREMENT_PMS_I2C_CALLBACKS_H_



/*******************************************************************************
* Includes
*******************************************************************************/
//#include "LPC54S018.h"
#include "fsl_i2c.h"
#include "fsl_i2c_freertos.h"
/*******************************************************************************
* Defines
*******************************************************************************/

/*******************************************************************************
* Functions
*******************************************************************************/
void I2C_PCIE_clb(I2C_Type *base, i2c_master_handle_t *handle, status_t completionStatus, void *userData);


#endif /* MEASUREMENT_PMS_I2C_CALLBACKS_H_ */
