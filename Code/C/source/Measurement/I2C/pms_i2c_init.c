/*
 * pms_i2c_init.c
 *
 *  Created on: Jul 27, 2023
 *      Author: paul
 *
 */



/*******************************************************************************
* Includes
*******************************************************************************/
#include "Measurement/pms_measurement_defines.h"
#include "pms_i2c_init.h"
#include "Config/pms_config.h"
#include "pms_i2c_callbacks.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "Measurement/pms_HardwareCheck.h"

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
extern pms_ina226_pcie ina226_hardwareDataPCIE[I2C_HANDLER_AMT_PCIe];
/**** Local *****/


/*******************************************************************************
* Function Prototypes
*******************************************************************************/
static void i2c_transfer_init();
/******************************************************************************
* Code
*******************************************************************************/




/**
 * @fn void I2C_INIT()
 * @brief initialisation function to bundle all i2c related initilasation stuff.
 * Have to be called in the main function before starting tasks
 *
 */
void I2C_INIT(){

/** Pin Init **/
	PIN_INIT_I2Cpins();

/** Periphal Init **/

#if defined(RTOS_I2C)
	INIT_Peripherals_I2C_RTOS();

#elif defined(NORMAL_I2C)
	INIT_Peripherals_I2C();
#endif

#if defined (HighSpeed_I2C)
	PIN_INIT_I2Cpins_HS();
	INIT_Peripherals_I2C_HS();
#endif

/** setup for most hardware information */
pms_init();

/** redirecting I2C callbacks, to avoid the auto code generation section in the periphals.c */
//PCIe1
I2C_MasterTransferCreateHandle(ina226_hardwareDataPCIE[PCIe1].i2c_handler->base, &(ina226_hardwareDataPCIE[PCIe1].i2c_handler->drv_handle), I2C_PCIE_clb, (void*)(&(ina226_hardwareDataPCIE[PCIe1])));
I2C_MasterTransferCreateHandle(ina226_hardwareDataPCIE[PCIe2].i2c_handler->base, &(ina226_hardwareDataPCIE[PCIe2].i2c_handler->drv_handle), I2C_PCIE_clb,(void*)(&(ina226_hardwareDataPCIE[PCIe2])));

i2c_transfer_init(); /**< prepares the masterX struct and enables the IRQ's for each i2c bus */
i2c_set_BaudRateALL(HIGH_FREQUNECY, 2660000);
//i2c_set_BaudRateALL(HIGH_FREQUNECY, 1000000);
//i2c_set_BaudRateALL(HIGH_FREQUNECY, 400000);


}



/**
 * @fn void i2c_transfer_init()
 * @brief init of the hardwarestruct for each PCIe Slot or SUPP with default values
 *
 */
static void i2c_transfer_init()
{

	for( lane_t lane =PCIe1; lane< I2C_HANDLER_AMT_PCIe; lane++){
        ina226_hardwareDataPCIE[lane].transfer_struct->slaveAddress   = INA226_ADDRES_12V;
        ina226_hardwareDataPCIE[lane].transfer_struct->direction      = kI2C_Read;
        ina226_hardwareDataPCIE[lane].transfer_struct->subaddress     = 0xFE;
        ina226_hardwareDataPCIE[lane].transfer_struct->subaddressSize = 1;
        ina226_hardwareDataPCIE[lane].transfer_struct->dataSize       = I2C_DATA_LENGTH;
        ina226_hardwareDataPCIE[lane].transfer_struct->flags          = kI2C_TransferDefaultFlag;
	}


}

/**
 * @fn void i2c_set_BaudRateALL(i2c_bus_type, uint32_t)
 * @brief sets the same baudrate for all I2C busses
 *
 * @param bus_type
 * @param baudRate_Bps
 */
void i2c_set_BaudRateALL(i2c_bus_type bus_type, uint32_t baudRate_Bps){


	switch(bus_type){
					case HIGH_FREQUNECY:

					    I2C_MasterSetBaudRate(ina226_hardwareDataPCIE[0].i2c_handler->base, baudRate_Bps, I2C_PCIE1_RTOS_HS_CLOCK_SOURCE);
					    I2C_MasterSetBaudRate(ina226_hardwareDataPCIE[1].i2c_handler->base, baudRate_Bps, I2C_PCIE2_RTOS_HS_CLOCK_SOURCE);
						break;
					case NORMAL_FREQUENCY:

						break;
					default:
						break;
	}
}
