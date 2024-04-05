/*
 * measurement_task.c
 *
 *  Created on: May 25, 2023
 *      Author: paul
 */


#include "Config/pms_config.h"

/** std-libs*/
#include <stdbool.h>

/** FreeROTS includes */
#include <Measurement/pms_HardwareCheck.h>
#include <Measurement/pms_measurement.h>
#include "FreeRTOS.h"
#include "queue.h"
#include "stream_buffer.h"

/** I2C includes */
#include "Measurement/INA226_driver/ina226.h"
#include "peripherals.h"
#include "Measurement/I2C/pms_i2cWrapper.h"
#include "Measurement/I2C/pms_i2cWrapper_RTOS.h"
#include "pms_Timer.h"
#include "Measurement/I2C/pms_i2c_init.h"

/** Controlling */
#include "Controller/control_task.h"


/*******************************************************************************
 * Definitions
 ******************************************************************************/


/* Task priorities. */

/*******************************************************************************
 * Variables
 ******************************************************************************/
/** I2C */
pms_ina226_pcie ina226_hardwareDataPCIE[I2C_HANDLER_AMT_PCIe];/**< objects containing all neccessary information for I2C communication and measuring purposes */
measurement_data_t data[I2C_HANDLER_AMT_ALL];/**< memory where the measurement data is placed after the I2C read */



/** Semaphores */
extern SemaphoreHandle_t sem_init; /**<	 handles initilisation process */


/** Streambuffer, buffers the measurement data in order to send them to a MQTT broker */

StreamBufferHandle_t xStreamBufferPCIe1;
StreamBufferHandle_t xStreamBufferPCIe2;



/**Measurment*/
bool i2c_from_isr = false; /**> flag for unlocking minor adjustments in the i2c callback */



/** User Configuration */
measurement_config_t *m_config;/**< struct which contains all configuration related to the */


#if defined (COLLECT_META_DATA)
extern transmission_meta_data_t meta_data;
#endif


/*******************************************************************************
 * Prototypes
 ******************************************************************************/

void addToStream();
void addToStreamISR();
static void checkNUXI();
static void staticRegisterValueRead();
static uint16_t receivedByteToUint16Value(uint8_t* g_rxBuff);
static void transformdata();

/*******************************************************************************
 * Code
 ******************************************************************************/


void initStream(){


/** Streambuffer for PCIe1 */
	    /* Create a stream buffer that can hold 100 bytes and uses the
	     * functions defined using the sbSEND_COMPLETED() and
	     * sbRECEIVE_COMPLETED() macros as send and receive completed
	     * callback functions. The memory used to hold both the stream
	     * buffer structure and the data in the stream buffer is
	     * allocated dynamically. */


	    xStreamBufferPCIe1 = xStreamBufferCreate( STREAM_BUFF_SIZE, STREAM_BUFF_TRIG_LVL_BYTE );

	    if( xStreamBufferPCIe1 == NULL )
	    {
	        /* There was not enough heap memory space available to create the
	        stream buffer. */
#if defined(CONSOLE_DEBUG)
	    	printf("Stream Buffer Creation failed \r\n");
#endif

	    }
	    else
	    {
#if defined(CONSOLE_DEBUG)
	    	printf("Created Stream Buffer \r\n");
#endif
	        /* The stream buffer was created successfully and can now be used. */

	    }

/** STreambuffer for PCIe2 */
	    xStreamBufferPCIe2 = xStreamBufferCreate( STREAM_BUFF_SIZE,
	    		STREAM_BUFF_TRIG_LVL_BYTE );
	    if( xStreamBufferPCIe2 == NULL )
	    {
	        /* There was not enough heap memory space available to create the
	        stream buffer. */
#if defined(CONSOLE_DEBUG)
	    	printf("Stream Buffer Creation failed \r\n");
#endif

	    }
	    else
	    {
#if defined(CONSOLE_DEBUG)
	    	printf("Created Stream Buffer \r\n");
#endif
	        /* The stream buffer was created successfully and can now be used. */

	    }
}



/**
 * @brief adds measurement values to the Queue
 * @param data measurment result
 */
void addToStreamISR(){
	int byte_count;
//	printMeasurementData(*(&data[PCIe1]), "PCIe");
	switch(m_config->useCase) {
		case SINGLE_SLOT:
			byte_count = xStreamBufferSendFromISR(xStreamBufferPCIe1, &data[PCIe1], STREAM_BUFF_DATA_LEN,pdFALSE);



//			printf("byte_count: %i\r\n",byte_count);
			if ( byte_count != STREAM_BUFF_DATA_LEN) {
#if defined (COLLECT_META_DATA)
				meta_data.data_lost++;

#endif
					// Failed to send data to the queue
					#if defined(STREAM_DEBUG)
						printf("Failed to push data of PCIE1 into Stream\r\n");
					#endif
			}
			break;


		default:

			/** sends measurement data of PCIe1 into stream buffer */
			byte_count = xStreamBufferSendFromISR(xStreamBufferPCIe1, &data[PCIe1], STREAM_BUFF_DATA_LEN,pdFALSE);

#if defined (COLLECT_META_DATA)
			meta_data.bytes_acquiredPCIe1 +=byte_count;
#endif

			/** detects if the there are less writen bytes into the strreambvuffer tahn a whole measurement data package, so something went wrong */
			if ( byte_count != STREAM_BUFF_DATA_LEN) {
					#if defined (COLLECT_META_DATA)
					meta_data.data_lost++;
					#endif

					// Failed to send data to the queue

					#if defined(STREAM_DEBUG)
						printf("Failed to push data of PCIE1 into Stream\r\n");
					#endif
			}

			/** sends measurement data of PCIe1 into stream buffer */
			byte_count = xStreamBufferSendFromISR(xStreamBufferPCIe2, &data[PCIe2], STREAM_BUFF_DATA_LEN,pdFALSE);

			#if defined (COLLECT_META_DATA)
						meta_data.bytes_acquiredPCIe2 +=byte_count;
			#endif

			/** detects if the there are less writen bytes into the strreambvuffer tahn a whole measurement data package, so something went wrong */
			if ( byte_count != STREAM_BUFF_DATA_LEN) {

					#if defined (COLLECT_META_DATA)
					meta_data.data_lost++;
					#endif
					// Failed to send data to the queue
					#if defined(STREAM_DEBUG)
						printf("Failed to push data of PCIE2 into Stream\r\n");
					#endif
			}

			break;


	}
}




/**
 * wrapper for all initialisation functions for the measurment process
 */
void measurement_init(){
#if defined(CONSOLE_DEBUG)
	printf("**begin: measurement init**\r\n");
#endif
	I2C_INIT();
	pms_HardwareInit(FULL,m_config->mfrequency); /**< initilisation and configuration of the INA226 */

#if defined(CONSOLE_DEBUG)
	printf("**end: measurement init\r\n**");
#endif
}








/** @brief variable to count the measurement data */
unsigned int measurement_data_amt = 0;

/**
 * @fn void measurementFromISR()
 * @brief
 *
 */
void measurementFromISR(){
//	printf("in measurment int\r\n");
	/** Measurment Interrrupt variables */
	/** first handler*/
	i2c_rtos_handle_t *handle = ina226_hardwareDataPCIE[0].i2c_handler;
	i2c_master_transfer_t *transfer = ina226_hardwareDataPCIE[0].transfer_struct;

	/** second handler*/
	i2c_rtos_handle_t *handle2 = ina226_hardwareDataPCIE[1].i2c_handler;
	i2c_master_transfer_t *transfer2 = ina226_hardwareDataPCIE[1].transfer_struct;

	/** I2C sensor addresses */
	uint16_t devAddress, devAddress2;

	int64_t timestamp;

	/** shuntresistance for current conversions */
	double shunt_res_pcie1,shunt_res_pcie2;

	/** store variable for the i2c read */
	uint16_t received_bytes[PCIe_SLOTS_AMT][INA226_PCIe_AMT][I2C_READ_REGISTER_AMT];/** variable to store the read register bytes, in order to be converted to readable values */


	/** activates the adjustments in the I2C callback for ISR, this is mainly endian problem prevention */
	i2c_from_isr = true;

		switch (m_config->useCase) {
			case SINGLE_SLOT:
				for (uint8_t i = 0; i < INA226_PCIe_AMT; i++){
						 uint16_t devAddress = ina226_hardwareDataPCIE[0].DevAddress[i];
					 	 i2c_readREGFromISR(handle,transfer, devAddress, INA226_REG_BUS_VOLT,(uint8_t*)&(data[PCIe1].results.busVoltage[i]));
//					 	 data[PCIe1].unixTimeStamp = getTimestamp();

				}
				measurement_data_amt ++;
				break;
			case DOUBLE_SINGLE_SLOT:


				/** go through all power supply lanes */
				for (uint8_t i = 0; i < INA226_PCIe_AMT; i++){

					uint16_t devAddress = ina226_hardwareDataPCIE[0].DevAddress[i];


					/** new attempt, convert the bytes to float and so to readable values. Afterwards send them to mqtt-task */
					I2C_Sequence_read(handle,transfer, devAddress, INA226_REG_BUS_VOLT,(uint8_t*) &(received_bytes[PCIe1][i][BUS_VOLT]));
					I2C_Sequence_read(handle2,transfer2, devAddress, INA226_REG_BUS_VOLT,(uint8_t*) &(received_bytes[PCIe2][i][BUS_VOLT]));


					timestamp = getTimestamp_INT();

					data[PCIe1].timestamp = timestamp;
					data[PCIe2].timestamp = timestamp;

					//wait until the first read is finished
					while(xSemaphoreTakeFromISR(handle->semaphore,pdFALSE)!= pdTRUE);

					/** start new i2c read */
					I2C_Sequence_read(handle,transfer, devAddress, INA226_REG_SHUNT_VOLT,(uint8_t*) &(received_bytes[PCIe1][i][SHUNT_VOLT]));
					I2C_Sequence_read(handle2,transfer2, devAddress, INA226_REG_SHUNT_VOLT,(uint8_t*) &(received_bytes[PCIe2][i][SHUNT_VOLT]));

					/** Bus volatge register is read, so values can be transformed to float	*/
					data[PCIe1].results.busVoltage[i] = receivedByteToUint16Value((uint8_t* )&received_bytes[PCIe1][i][BUS_VOLT]) * BUSVOLT_LSB;
					data[PCIe2].results.busVoltage[i] = receivedByteToUint16Value((uint8_t* )&received_bytes[PCIe2][i][BUS_VOLT]) * BUSVOLT_LSB;

					/**wait until the  second read is finished */
					while(xSemaphoreTakeFromISR(handle->semaphore,pdFALSE)!= pdTRUE);

					/** get shunt resistor values for current calculation */
					shunt_res_pcie1 = ina226_hardwareDataPCIE[PCIe1].Shunt_Res[i];
					shunt_res_pcie2 = ina226_hardwareDataPCIE[PCIe2].Shunt_Res[i];

					/** current calculation, converting register value to shuntvoltage and then devide it through the shunt resistance, I = U/R */
					data[PCIe1].results.current[i] = ((receivedByteToUint16Value((uint8_t* )&received_bytes[PCIe1][i][SHUNT_VOLT]) * SHUNTVOLT_LSB)) / shunt_res_pcie1;
					data[PCIe2].results.current[i] = ((receivedByteToUint16Value((uint8_t* )&received_bytes[PCIe2][i][SHUNT_VOLT]) * SHUNTVOLT_LSB)/ shunt_res_pcie2);

					/** power calculations */
					data[PCIe1].results.power[i] = data[PCIe1].results.current[i] * data[PCIe1].results.busVoltage[i];
					data[PCIe2].results.power[i] = data[PCIe2].results.current[i] * data[PCIe2].results.busVoltage[i];



				}
				measurement_data_amt +=2;
				break;
			case DUAL_SLOT:

				for (uint8_t i = 0; i < INA226_PCIe_AMT; i++){

						uint16_t devAddress = ina226_hardwareDataPCIE[0].DevAddress[i];

						I2C_Sequence_read(handle,transfer, devAddress, INA226_REG_BUS_VOLT,(uint8_t*)&(data[PCIe1].results.busVoltage[i]));
						if (i < INA226_SUPP_AMT){
							devAddress2 = ina226_hardwareDataPCIE[1].DevAddress[i+3];
							I2C_Sequence_read(handle2,transfer2, devAddress2, INA226_REG_BUS_VOLT,(uint8_t*)&(data[PCIe2].results.busVoltage[i]));
						}

						/**wait until the first read is finished */
						while(xSemaphoreTakeFromISR(handle->semaphore,pdFALSE)!= pdTRUE);

						if (i <INA226_SUPP_AMT){
//							I2C_Sequence_read(handle2,transfer2, devAddress2, INA226_REG_SHUNT_VOLT,(uint8_t*)&(data[PCIe2].results.shuntVoltage[i]));
						}
						/**wait until the first read is finished */
						while(xSemaphoreTakeFromISR(handle->semaphore,pdFALSE)!= pdTRUE);

				}
				measurement_data_amt +=2;
				break;
#ifdef TEST_STATIC_MQTT_PAYLOAD
			case TEST_STATIC_MQTT:


				for (uint8_t i = 0; i < INA226_PCIe_AMT; i++){

					uint16_t devAddress = ina226_hardwareDataPCIE[0].DevAddress[i];


					I2C_Sequence_read(handle,transfer, devAddress, INA226_REG_MANUFAC_ID,(uint8_t*)&(data[PCIe1].results.busVoltage[i]));
					I2C_Sequence_read(handle2,transfer2, devAddress, INA226_REG_MANUFAC_ID,(uint8_t*)&(data[PCIe2].results.busVoltage[i]));

					timestamp = getTimestamp();
					data[PCIe1].unixTimeStamp = timestamp;
					data[PCIe2].unixTimeStamp = timestamp;


					//wait until the first read is finished
					while(xSemaphoreTakeFromISR(handle->semaphore,pdFALSE)!= pdTRUE);

			/**					/**read shunt-voltage registe */
					I2C_Sequence_read(handle,transfer, devAddress, INA226_REG_ID,(uint8_t*)&( data[PCIe1].results.shuntVoltage[i]));
					I2C_Sequence_read(handle2,transfer2, devAddress, INA226_REG_ID,(uint8_t*)&(data[PCIe2].results.shuntVoltage[i]));

					/**wait until the first read is finished */
					while(xSemaphoreTakeFromISR(handle->semaphore,pdFALSE)!= pdTRUE);


				}
				break;
#endif
			default:
				break;
	}

		/** deactivates the flag, in case another i2c command is made outside the ISR */
		i2c_from_isr = false;
		/** Sends the measurement data of all measured sensors for one timestamp intzo the buffer */
		addToStreamISR();
//		printMeasurementData(data[PCIe1], "PCIe1");
//		printMeasurementData(data[PCIe2], "PCIe2");
}


/**
 * @fn void printMeasurementData(measurement_data_t, char*)
 * @brief function to print a data measurement object, for better overview
 *
 * @param data measurement object
 * @param name name of the lane where the measurement took place
 */
void printMeasurementData(measurement_data_t data, char* name)
{

	printf("Measurement data %s:\n\r",name);
	for (int i = 0; i < INA226_PCIe_AMT;i++){
		float voltage = data.results.busVoltage[i];
		float current = data.results.current[i];
		float power = data.results.power[i];

		printf("V: %f[V]	I:%f [A]	P: %f[W]	 \r\n",voltage, current, power);

		}

//	printf("	timestamp: %f [s]\r\n",data.unixTimeStamp);

}

/**
 * @fn void receivedByteToUint16Value(uint8_t*)
 * @brief received data is big endian, so if the value is interpreted as uint16_t value the MSB needs to shifted
 *
 * @param g_rxBuff pointer to received data
 */
static uint16_t receivedByteToUint16Value(uint8_t* g_rxBuff){
   return  (g_rxBuff[0]  << 8) + g_rxBuff[1] ;
}





/**
 * @fn void checkNUXI()
 * @brief easy to read hex values to get the rigth byte order
 *
 */
static void checkNUXI(){
			data[PCIe1].results.busVoltage[0] = 0x1A2B;
			data[PCIe1].results.busVoltage[1] = 0x3C4D;
			data[PCIe1].results.busVoltage[2] = 0x5E6F;

//			data[PCIe1].results.shuntVoltage[0] = 0x0123;
//			data[PCIe1].results.shuntVoltage[1] = 0x4567;
//			data[PCIe1].results.shuntVoltage[2] = 0x89AB;
//
//			data[PCIe2].results.busVoltage[0] = 0x1A2B;
//			data[PCIe2].results.busVoltage[1] = 0x3C4D;
//			data[PCIe2].results.busVoltage[2] = 0x5E6F;
//
//			data[PCIe2].results.shuntVoltage[0] = 0x0123;
//			data[PCIe2].results.shuntVoltage[1] = 0x4567;
//			data[PCIe2].results.shuntVoltage[2] = 0x89AB;
//
//			data[PCIe1].unixTimeStamp.seconds = 0xFEDCBA98 ;
//			data[PCIe2].unixTimeStamp.seconds = 0xFEDCBA98 ;
//			data[PCIe1].unixTimeStamp.microseconds = 0x7654 ;
//			data[PCIe2].unixTimeStamp.microseconds = 0x7654 ;

}


