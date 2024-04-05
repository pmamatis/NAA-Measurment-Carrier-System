

#include "Measurement/I2C/pms_i2cWrapper.h"
#if defined(NORMAL_I2C)
#include <Measurement/pms_HardwareCheck.h>

#include "pin_mux.h"
#include "board.h"
#include "fsl_debug_console.h"
#include "fsl_i2c.h"
#include "Measurement/INA226_driver/ina226.h"
#include "peripherals.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define I2C_DATA_LENGTH 2 //all INA226 register contain 2 Byte

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

uint8_t g_txBuff[I2C_DATA_LENGTH];
uint8_t* g_rxBuff[I2C_HANDLER_AMT];
uint16_t rx_Buff;

bool i2c_ready[I2C_HANDLER_AMT];


status_t i2c_status; //< variable to save the status of the last I2C variable

extern struct pms_ina226 ina226_hardwareData;

/*******************************************************************************
 * Code
 ******************************************************************************/










/**
 *
 * @param lane
 * @param devAdress
 * @param regAdress
 * @return
 */
uint16_t i2c_readREG(lane_t lane,uint8_t devAdress, uint8_t regAdress){

	status_t i2c_status;
	g_rxBuff[lane][0] =0;
	g_rxBuff[lane][1] =0;


	ina226_hardwareData.transfer_struct[lane]->slaveAddress   = devAdress;
	ina226_hardwareData.transfer_struct[lane]->direction      = kI2C_Read;
	ina226_hardwareData.transfer_struct[lane]->data           = &g_rxBuff[lane][0];
	ina226_hardwareData.transfer_struct[lane]->subaddress     = regAdress;

	// wait for I2C bus being ready
		while (!i2c_ready[lane])
	{

	}
	//set ready flag to false
	i2c_ready[lane] = false;
	I2C_Type* hi2c = ina226_hardwareData.i2c_handler[lane];
	i2c_master_handle_t* handle = ina226_hardwareData.master_handle[lane];

	i2c_status = I2C_MasterTransferNonBlocking(hi2c, handle, ina226_hardwareData.transfer_struct[lane]);

//printf("read status: 0x%x\r\n",i2c_status);
	/** check if the transfer was a success */
	if (i2c_status != kStatus_Success)
		{
			PRINTF("I2C master: error during read transaction, %d\n", i2c_status);
			return 0xFF;
		}
		else{

//					PRINTF("%x\r",(uint16_t)(((g_rxBuff[0]<<8)+g_rxBuff[1])) );
//			return ((g_rxBuff[0]<<8)+g_rxBuff[1]);
			printf("%x, %x \r\n",g_rxBuff[lane][0],g_rxBuff[lane][1]);
//			printf("%x \r\n");

			return (g_rxBuff[lane][0]<<8)+g_rxBuff[lane][1];

		}
}


void i2c_writeREG(lane_t lane,uint8_t devAdress, uint8_t regAdress,uint16_t* data){



	g_txBuff[0] = 0;
	g_txBuff[1] = 0;

	ina226_hardwareData.transfer_struct[lane]->slaveAddress   = devAdress;
	ina226_hardwareData.transfer_struct[lane]->direction      = kI2C_Write;
	ina226_hardwareData.transfer_struct[lane]->subaddress     = regAdress;
	ina226_hardwareData.transfer_struct[lane]->data           = data;// TODO wird das Register richtig herum befüllt


		// wait for I2C bus being ready
			while (!i2c_ready[lane])
		{

		}
		//set ready flag to false
		i2c_ready[lane] = false;
		I2C_Type* hi2c = ina226_hardwareData.i2c_handler[lane];
		i2c_master_handle_t* handle = ina226_hardwareData.master_handle[lane];


		i2c_status = I2C_MasterTransferNonBlocking(hi2c, handle, ina226_hardwareData.transfer_struct[lane]);

		/** check if the transfer was a success */
		if (i2c_status != kStatus_Success)
		{
			PRINTF("I2C master: error during write transaction, %d\n", i2c_status);
		}
		else{
//					PRINTF("%x\r",(uint16_t)(((g_rxBuff[0]<<8)+g_rxBuff[1])) );

		}
}



void i2c_writeREG_Blocking(lane_t lane,uint8_t devAdress, uint8_t regAdress,uint16_t* data){



	g_txBuff[0] = 0;
	g_txBuff[1] = 0;

	ina226_hardwareData.transfer_struct[lane]->slaveAddress   = devAdress;
	ina226_hardwareData.transfer_struct[lane]->direction      = kI2C_Write;
	ina226_hardwareData.transfer_struct[lane]->subaddress     = regAdress;
	ina226_hardwareData.transfer_struct[lane]->data           = data;// TODO wird das Register richtig herum befüllt



		//set ready flag to false
//		i2c_ready[lane] = false;
		I2C_Type* hi2c = ina226_hardwareData.i2c_handler[lane];
		i2c_master_handle_t* handle = ina226_hardwareData.master_handle[lane];


		i2c_status = I2C_MasterTransferBlocking(hi2c, ina226_hardwareData.transfer_struct[lane]);
//		i2c_status = I2C_MasterTransferNonBlocking(hi2c, handle, &ina226_hardwareData.transfer_struct[lane]);

		/** check if the transfer was a success */
		if (i2c_status != kStatus_Success)
		{
			PRINTF("I2C master: error during write transaction, %d\n", i2c_status);
		}
		else{
//					PRINTF("%x\r",(uint16_t)(((g_rxBuff[0]<<8)+g_rxBuff[1])) );

		}
}


void i2c_plain_test(){

//	g_rxBuff[0] = 0;
//	g_rxBuff[1] = 0;
//    ina226_hardwareData.transfer_struct[lane]1.slaveAddress   = INA226_ADDRES_3V;
//    ina226_hardwareData.transfer_struct[lane]1.direction      = kI2C_Read;
//    ina226_hardwareData.transfer_struct[lane]1.subaddress     = 0xFE;
//    ina226_hardwareData.transfer_struct[lane]1.subaddressSize = 1;
//    ina226_hardwareData.transfer_struct[lane]1.data           = g_rxBuff;
//    ina226_hardwareData.transfer_struct[lane]1.dataSize       = I2C_DATA_LENGTH;
//    ina226_hardwareData.transfer_struct[lane]1.flags          = kI2C_TransferDefaultFlag;
//


//    I2C_Type *base = I2C_PCIe2_rtosHandle.base;
//    I2C_MasterStart(base, INA226_ADDRES_3V,kI2C_Read);
//    get_i2c_status(&I2C_PCIe2_rtosHandle);
//    I2C_MasterReadBlocking(base, g_rxBuff, 2,kI2C_TransferRepeatedStartFlag);
//    i2c_status = I2C_MasterReadBlocking(base, g_rxBuff, 2,kI2C_TransferDefaultFlag);
//    I2C_MasterWriteBlocking(base, &(ina226_hardwareData.transfer_struct[lane]1.subaddress)  , 1,kI2C_TransferRepeatedStartFlag );
//    get_i2c_status(&I2C_PCIe2_rtosHandle);
//    I2C_MasterReadBlocking(base, rxBuff, rxSize, flags)
////    i2c_status = I2C_RTOS_Transfer(&I2C_PCIe2_rtosHandle, &ina226_hardwareData.transfer_struct[lane]1);
//	if (i2c_status != kStatus_Success)
//	{
//		PRINTF("I2C master: error during write transaction, %d\n", i2c_status);
//		PRINTF("%x\r",(uint16_t)(((g_rxBuff[0]<<8)+g_rxBuff[1])) );
//	}
//	else{
//					PRINTF("%x\r",(uint16_t)(((g_rxBuff[0]<<8)+g_rxBuff[1])) );
//
//	}
}




/*
 * @brief functions reads status register of given i2c handler and prints debug meassages
 */

void get_i2c_status(I2C_Type* hi2c){
	//get state of i2c bus from i2c status register
	uint32_t master_state =hi2c->STAT ;

	master_state = (master_state & I2C_STAT_MSTSTATE_MASK) >> I2C_STAT_MSTSTATE_SHIFT;
	/*check if state is 0x01 (transmit ready), means :Transmit ready. Data can be transmitted (Master Transmitter mode).
	Address plus Write was previously sent and Acknowledged by slave. page 476 table 461, LPC54S0xx User Manuual*/
	switch (master_state) {
		case 0x0:
				printf("IDLE\r\n");
				break;
		case 0x1:
				printf("address and read was acknowledged by slave\n\r");
				break;
		case 0x2:
				printf("address and write was acknowledged by slave\n\r");
				break;
		case 0x3:
				printf("slave NACK address\n\r");
				break;
		case 0x4:
				printf("slave NACK transmited Data\n\r");
				break;
		default:
			break;
	}
}

void I2C_PCIE1_clb(I2C_Type *base, i2c_master_handle_t *handle, status_t completionStatus, void *userData){
    /* Signal transfer success when received success status. */
    if (completionStatus == kStatus_Success)
    {
        i2c_ready[PCIe1]= true;
//        printf("ready\r\n");
    }
    else{
    	get_i2c_status(base);
        printf("busy\r\n");
    }
}
void I2C_PCIE2_clb(I2C_Type *base, i2c_master_handle_t *handle, status_t completionStatus, void *userData){
    if (completionStatus == kStatus_Success)
    {
        i2c_ready[PCIe2]= true;
//        printf("ready\r\n");
    }
    else
        printf("busy\r\n");
}
void I2C_SUPP_clb(I2C_Type *base, i2c_master_handle_t *handle, status_t completionStatus, void *userData){
    if (completionStatus == kStatus_Success)
    {
        i2c_ready[SUPP]= true;
//        printf("ready\r\n");
    }
    else
        printf("busy\r\n");
}

#endif
