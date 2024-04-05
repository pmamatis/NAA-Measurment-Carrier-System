



#include "Measurement/I2C/pms_i2cWrapper_RTOS.h"
#if defined (RTOS_I2C)

#include "pin_mux.h"
#include "board.h"
#include "fsl_debug_console.h"
#include "fsl_i2c.h"
#include "peripherals.h"
#include "stdio.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/


/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

uint8_t g_txBuff[I2C_DATA_LENGTH];
uint8_t g_rxBuff[3][I2C_DATA_LENGTH];



status_t i2c_status; //< variable to save the status of the last I2C variable

//extern struct pms_ina226 ina226_hardwareData;
static i2c_master_transfer_t masterXfer;


extern pms_ina226_pcie ina226_hardwareDataPCIE[I2C_HANDLER_AMT_PCIe];
/*******************************************************************************
 * Code
 ******************************************************************************/


//uint16_t i2c_write


/**
 *
 */
uint16_t i2c_readREG(i2c_rtos_handle_t* hi2c,i2c_master_transfer_t* transfer_struct,uint8_t devAdress, uint8_t regAdress){
			uint8_t g_rxBuff[I2C_DATA_LENGTH];

			transfer_struct->slaveAddress   = devAdress;
			transfer_struct->direction      = kI2C_Read;
			transfer_struct->data           = g_rxBuff;
			transfer_struct->dataSize		  = I2C_DATA_LENGTH;
			transfer_struct->subaddress     = regAdress;
			transfer_struct->subaddressSize = 1;


				i2c_status = I2C_RTOS_Transfer(hi2c, transfer_struct);
//				get_i2c_status(hi2c);
				if (i2c_status != kStatus_Success)
				{
					#if (defined (I2C_DEBUG) & defined(CONSOLE_DEBUG))
						printf("I2C master: error during write transaction, %d\n\r", i2c_status);
						printf("i2c read\n:%x\r\n",(uint16_t)(((g_rxBuff[0]<<8)+g_rxBuff[1])) );
					#endif
						return 0xFF;
				}
				else{
					#if (defined (I2C_DEBUG) & defined(CONSOLE_DEBUG))
						printf("i2c read\n:%x\r\n",(uint16_t)(((g_rxBuff[0]<<8)+g_rxBuff[1])) );
						printf("i2c read\n:0:%x	1:%x\r\n",g_rxBuff[0],g_rxBuff[1]);
					#endif
					return ((g_rxBuff[0]<<8)+g_rxBuff[1]);
//					return (uint16_t*)g_rxBuff[1];

				}
}


void i2c_writeREG(i2c_rtos_handle_t* hi2c,i2c_master_transfer_t* transfer_struct,uint8_t devAdress, uint8_t regAdress,uint8_t* data){



			transfer_struct->slaveAddress   = devAdress;
			transfer_struct->direction      = kI2C_Write;
			transfer_struct->data           = data;
			transfer_struct->dataSize= I2C_DATA_LENGTH;
			transfer_struct->subaddress     = regAdress;
			transfer_struct->subaddressSize = 1;

			#if (defined (I2C_DEBUG) & defined(CONSOLE_DEBUG))
//	        printf("i2c write:\n\r	data[0]:0x%X\n\r	data[1]:0x%X\r\n",data[0],data[1]);
			#endif

				i2c_status = I2C_RTOS_Transfer(hi2c, transfer_struct);
				if (i2c_status != kStatus_Success)
				{
					#if (defined (I2C_DEBUG) & defined(CONSOLE_DEBUG))
					PRINTF("I2C master: error during write transaction, %d\n", i2c_status);
					#endif
				}
				else{
//					PRINTF("%x\r",(uint16_t)(((g_rxBuff[0]<<8)+g_rxBuff[1])) );

				}
}




void i2c_writeREGFromISR(i2c_rtos_handle_t* hi2c,i2c_master_transfer_t* transfer_struct,uint8_t devAdress, uint8_t regAdress,uint8_t* data){



			transfer_struct->slaveAddress   = devAdress;
			transfer_struct->direction      = kI2C_Write;
			transfer_struct->data           = data;
			transfer_struct->dataSize= I2C_DATA_LENGTH;
			transfer_struct->subaddress     = regAdress;
			transfer_struct->subaddressSize = 1;

			#if (defined (I2C_DEBUG) & defined(CONSOLE_DEBUG))
	        	printf("i2ci2c_isr write:\n data[0]:0x%X\r\n data[1]:0x%X\r\n",data[0],data[1]);
			#endif
				i2c_status = I2C_RTOS_TransferFromISR(hi2c, transfer_struct);
				if (i2c_status != kStatus_Success)
				{
					#if (defined (I2C_DEBUG) & defined(CONSOLE_DEBUG))
						PRINTF("I2C master: error during write transaction, %d\n", i2c_status);
					#endif
				}
				else{
//					PRINTF("%x\r",(uint16_t)(((g_rxBuff[0]<<8)+g_rxBuff[1])) );

				}
}

uint16_t i2c_readREGFromISR(i2c_rtos_handle_t* hi2c,i2c_master_transfer_t* transfer_struct,uint8_t devAdress, uint8_t regAdress, uint8_t* g_rxBuff){

//			uint8_t g_rxBuff[I2C_DATA_LENGTH];
			transfer_struct->slaveAddress   = devAdress;
			transfer_struct->direction      = kI2C_Read;
			transfer_struct->data           = g_rxBuff;
			transfer_struct->dataSize		  = I2C_DATA_LENGTH;
			transfer_struct->subaddress     = regAdress;
			transfer_struct->subaddressSize = 1;


				i2c_status = I2C_RTOS_TransferFromISR(hi2c, transfer_struct);
				if (i2c_status != kStatus_Success)
				{
#if (defined(I2C_DEBUG) & defined(CONSOLE_DEBUG))
					printf("I2C master: error during read transaction, %d\n\r", i2c_status);
#endif
					return 0xFF;
				}
				else{
					#if (defined (I2C_DEBUG) & defined(CONSOLE_DEBUG))
//						printf("i2c_isr read\n:%x\r\n",(uint16_t)(((g_rxBuff[0]<<8)+g_rxBuff[1])) );
					#endif
					return kStatus_Success;

				}
}





/**
 * @brief functions reads status register of given i2c handler and prints debug meassages
 */
void get_i2c_status(I2C_Type* hi2c){
	//get state of i2c bus from i2c status register
//	uint32_t master_state =hi2c->base->STAT ;
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




/*!
 * @brief Performs I2C transfer from inside an Interrrupt .
 *
 * This function performs an I2C transfer according to data given in the transfer structure.
 *
 * param handle The RTOS I2C handle.
 * param transfer Structure specifying the transfer parameters.
 * return status of the operation.
 */
status_t I2C_RTOS_TransferFromISR(i2c_rtos_handle_t *handle, i2c_master_transfer_t *transfer)
{
    status_t status;

    /* Lock resource mutex */
    while (xSemaphoreTakeFromISR(handle->mutex, pdFALSE) != pdTRUE);

    status = I2C_MasterTransferNonBlocking(handle->base, &handle->drv_handle, transfer);
    if (status != kStatus_Success)
    {
        (void)xSemaphoreGiveFromISR(handle->mutex,pdFALSE);
        return status;
    }

    /* Wait for transfer to finish */

     xSemaphoreTakeFromISR(handle->semaphore, pdFALSE);
//    while( xSemaphoreTakeFromISR(handle->semaphore, pdFALSE)  != pdPASS);

    /* Unlock resource mutex */
    (void)xSemaphoreGiveFromISR(handle->mutex,pdFALSE);

    /* Return status captured by callback function */
    return handle->async_status;
}

/**
 * @fn status_t I2C_Sequence_read(i2c_rtos_handle_t*, i2c_master_transfer_t*)
 * @brief is a non-blocking I2C read Register command which doesn't wait for semaphore. Semaphore handling has to be made around this function.
 * main purpose of this function is to be used for a sequence of i2c read commands
 *
 * @param handle
 * @param transfer
 * @return
 */
void I2C_Sequence_read(i2c_rtos_handle_t* hi2c,i2c_master_transfer_t* transfer_struct,uint8_t devAdress, uint8_t regAdress, uint8_t* g_rxBuff)
{
				status_t i2c_status;

				transfer_struct->slaveAddress   = devAdress;
				transfer_struct->direction      = kI2C_Read;
				transfer_struct->data           = g_rxBuff;
				transfer_struct->dataSize		  = I2C_DATA_LENGTH;
				transfer_struct->subaddress     = regAdress;
				transfer_struct->subaddressSize = 1;


				i2c_status =  I2C_MasterTransferNonBlocking(hi2c->base, &hi2c->drv_handle, transfer_struct);
					if (i2c_status != kStatus_Success)
					{
	#if (defined(I2C_DEBUG) & defined(CONSOLE_DEBUG))
						printf("I2C master: error during read transaction, %d\n\r", i2c_status);
	#endif
//						get_i2c_status(hi2c->base);
//						return 0xFF;

					}
					else{
						#if (defined (I2C_DEBUG) & defined(CONSOLE_DEBUG))
//							printf("i2c_isr read\n:%x\r\n",(uint16_t)(((g_rxBuff[0]<<8)+g_rxBuff[1])) );
						#endif
//						return kStatus_Success;

					}

}



#endif
