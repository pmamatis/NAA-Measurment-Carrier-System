///*
// * PMS.c
// *
// *  Created on: Mar 30, 2022
// *      Author: paul
// */
//
#include <Measurement/pms_measurement.h>
#include "Config/pms_config.h"
#include "Measurement/pms_HardwareCheck.h"
#include "INA226_driver/ina226_measurement_frequency_adjusting.h"
#include "peripherals.h"
#include "board.h"
#include "Measurement/I2C/pms_i2c_init.h"
#include "Measurement/I2C/pms_i2cWrapper_RTOS.h"
#include "pms_Timer.h"


extern pms_ina226_pcie ina226_hardwareDataPCIE[I2C_HANDLER_AMT_PCIe];





/**
 * @fn void pms_init()
 * @brief init function for filling the ina226_hardwareDataPCIE and the ina226_hardwareDataSUPP with data
 * the data is a mixture of hardware information and handler from the code generation of the IDE
 *
 */
void pms_init(){
	/** loop for hardware data which is same for every pcie lane */
	for (int i = 0; i < I2C_HANDLER_AMT_PCIe;i++){
		//I2C Adressen Zuweisung, für bessere Benutzbarkeitg
		ina226_hardwareDataPCIE[i].DevAddress[0] = INA226_ADDRES_12V;
		ina226_hardwareDataPCIE[i].DevAddress[1] = INA226_ADDRES_3V;
		ina226_hardwareDataPCIE[i].DevAddress[2] = INA226_ADDRES_3V_AUX;



		//maximaler Strom
		ina226_hardwareDataPCIE[i].Imax[0] = IMAX_PCIE_SLOT_12V;
		ina226_hardwareDataPCIE[i].Imax[1] = IMAX_PCIE_SLOT_3V3;
		ina226_hardwareDataPCIE[i].Imax[2] = IMAX_PCIE_SLOT_3V3;




		//Shunt Res
		ina226_hardwareDataPCIE[i].Shunt_Res[0] = RSHUNT_12V;
		ina226_hardwareDataPCIE[i].Shunt_Res[1] = RSHUNT_3V3;
		ina226_hardwareDataPCIE[i].Shunt_Res[2] = RSHUNT_3V3;



	}

	/** INA226 Addresses related to the Support 12V Voltage*/
	ina226_hardwareDataPCIE[1].DevAddress[3] = INA226_ADDRES_SUPP_1;
	ina226_hardwareDataPCIE[1].DevAddress[4] = INA226_ADDRES_SUPP_2;



	/** generated code and writen code linking */

	//I2C transfer structs pointer definend in the periphal init function
	ina226_hardwareDataPCIE[PCIe1].transfer_struct = &I2C_PCIE1_transfer;
	ina226_hardwareDataPCIE[PCIe2].transfer_struct = &I2C_PCIE2_transfer;

// TODO have to be organised that also normal I2C works with HighSpeed

	/** I2C handler assigning deppending on I2C mode */
#if defined(RTOS_I2C)

	#if defined (HighSpeed_I2C)
		ina226_hardwareDataPCIE[PCIe1].i2c_handler = &I2C_PCIE1_RTOS_HS_rtosHandle;
		ina226_hardwareDataPCIE[PCIe2].i2c_handler = &I2C_PCIE2_RTOS_HS_rtosHandle;
	#else
		// I2C Handler Zuweisung, für bessere Benutzbarkeit
		ina226_hardwareData.i2c_handler[PCIe1] = &I2C_PCIE1_RTOS_rtosHandle;
		ina226_hardwareData.i2c_handler[PCIe2] = &I2C_PCIE2_RTOS_rtosHandle;
	#endif
#elif defined(NORMAL_I2C)
	// I2C Handler Zuweisung, für bessere Benutzbarkeit
	ina226_hardwareData.i2c_handler[PCIe1] = I2C_PCIE1_PERIPHERAL;
	ina226_hardwareData.i2c_handler[PCIe2] = I2C_PCIE2_PERIPHERAL;
	ina226_hardwareData.i2c_handler[SUPP] = I2C_SUPP_PERIPHERAL;

	//I2C Master handler for state machine
	ina226_hardwareData.master_handle[PCIe1] = &I2C_PCIE1_handle;
	ina226_hardwareData.master_handle[PCIe2] = &I2C_PCIE2_handle;
	ina226_hardwareData.master_handle[SUPP] = &I2C_SUPP_handle;

//	//I2C transfer structs pointer definend in the periphal init function
//	ina226_hardwareData.transfer_struct[PCIe1] = &I2C_PCIE1_transfer;
//	ina226_hardwareData.transfer_struct[PCIe2] = &I2C_PCIE2_transfer;
//	ina226_hardwareData.transfer_struct[SUPP] = &I2C_SUPP_transfer;

#endif




}




/**
 * @fn uint16_t pms_I2Caddress_check()
 * @brief checks all used I2C adresses availible for INA226
 *
 * @return total number of slave adresses found for all checked I2C busses together
 */
uint16_t pms_I2Caddress_check(){
		 uint16_t retval = 0;

		#if (defined(I2C_DEBUG) & defined(CONSOLE_DEBUG))
		printf("	I2C Address check\r\n");
		#endif


		/**address check for each pcie lane */
		for (uint8_t l = 0; l < I2C_HANDLER_AMT_PCIe;l++){


			#if (defined(I2C_DEBUG) & defined(CONSOLE_DEBUG))
			printf("I2C PCIe Bus %i:\r\n	",l+1);
			#endif

			i2c_rtos_handle_t*  i2c_handler =  ina226_hardwareDataPCIE[l].i2c_handler;

			for (uint16_t j = 0x40; j <= 0x4F; j++){ ///< go through all possible I2C addresses of INA226


				if (ina226_isConnected(i2c_handler,j )== INA226_OK){


					#if (defined(I2C_DEBUG) & defined(CONSOLE_DEBUG))
					printf("%#x ",j);
					#endif
					retval ++;
				}
				else {
				}
			}
			#if (defined(I2C_DEBUG) & defined(CONSOLE_DEBUG))
			printf("\r\n");
			#endif
		}

		return retval;
}






/**
 * @brief initilization and testing of all I2C connections and INA226
 * @param setup of the PCIe-PMS-Board
 *
 */
extern ina226_frequency_t frequencies[64];
void pms_HardwareInit(board_setup setup,double measurement_frequency){
	char pos[5][10]={("12V"),("3V3"),("AUX"),("SuppJ4"),("SuppJ5")};
	char name[30];

	/**Check configurations*/
	uint8_t numOfMeasurements = 10; ///< number of test measurements for the shunt voltage

	double busTh = 2.5; ///< bus-reconition-voltage threshhold

	uint8_t t_wait = 3; ///< rest-time between test measuremnt

#if defined(CONSOLE_DEBUG)
	printf("PMS Hardware Check \r\n");
#endif

#if (defined(INA226_DEBUG) & defined(CONSOLE_DEBUG))
	pms_I2Caddress_check();
#endif


	//Board Setup
	int test_amt; ///< number of INA226 to be tested for each PCIe slot

	switch (setup) {
	case FULL:
		test_amt = INA226_PCIe_AMT;
		break;
	case LESS:
		test_amt = 2;
	default:
		break;
	}



	//set up availible frequency
	ina226_getAllavailibleFreqs();
	uint8_t freq_index = ina226_getClosestFreq(measurement_frequency);
	/** set also the measurement interrupt frequency */
	uint64_t cal_val = (uint64_t)(frequencies[freq_index].frequency );
	uint64_t rit_freq = RIT_SOURCE_CLOCK/cal_val;
	RIT_SetTimerCompare(RIT, rit_freq);


	//Set up config data for ina226
	for (int i = 0; i < I2C_HANDLER_AMT_PCIe;i++){
		ina226_hardwareDataPCIE[i].config = frequencies[freq_index].config;
	}

	//check PCIe ina226
	for (lane_t lane = PCIe1; lane < I2C_HANDLER_AMT_PCIe;lane++){

		i2c_rtos_handle_t *handle = ina226_hardwareDataPCIE[lane].i2c_handler;
		i2c_master_transfer_t *transfer = ina226_hardwareDataPCIE[lane].transfer_struct;
		ina226_config_data_t config = ina226_hardwareDataPCIE[lane].config;


		/** in case the PCIe2 I2C bus contains the Supp INA226 the following if-clause needs to be activated TODO compiler ifdef implementing  */
		if (lane == PCIe2){
			test_amt = INA226_PCIe_AMT + INA226_SUPP_AMT;
		}

		for (int j = 0;j < test_amt;j++){

			uint16_t devAddress = ina226_hardwareDataPCIE[lane].DevAddress[j];
			double imax = ina226_hardwareDataPCIE[lane].Imax[j];
			double rshunt = ina226_hardwareDataPCIE[lane].Shunt_Res[j];

			INA226_ReturnVal checkCon;

			#if (defined(INA226_DEBUG) & defined(CONSOLE_DEBUG))
			sprintf(name,"PCIe%i %s",lane+1,pos[j]);
			#endif
			uint8_t fail_counter = 0; ///<

			checkCon = ina226_isConnected(handle, devAddress);
			if (checkCon == INA226_OK){
				//INA226 connected and answers to read/write request with ACK, so it is possible to call the init and config function.


//				LED1_ON();
				//initilisation of an INA226
				INA226_ReturnVal init = ina226_init(handle, transfer,devAddress, imax, rshunt, name,config);
				if (init == INA226_OK){

					LED2_ON();
					//check if bus voltage is applied to the ina226

//					uint16_t busV = ina226_GetBusVoltage(handle, transfer, devAddress);
//					uint16_t busV =  i2c_readREG(handle, transfer, devAddress, INA226_REG_BUS_VOLT);
					if (ina226_busToVoltage( i2c_readREG(handle, transfer, devAddress, INA226_REG_BUS_VOLT) ) > busTh){

						//check if the Shunt voltage is in a given range, if it exeds maximum value it is an indicator for soldering problems at the IN+ and IN+ pins of ina226
						uint16_t shuntV[numOfMeasurements];
						for (int k = 0; k < numOfMeasurements;k++){
							shuntV[k] =  i2c_readREG(handle, transfer, devAddress, INA226_REG_SHUNT_VOLT);
							if (shuntV[k] == 0x7FFF){
								fail_counter++;
							}
						}
						if (fail_counter == numOfMeasurements){
#if (defined(INA226_DEBUG) & defined(CONSOLE_DEBUG))
							printf("%s:	Check Shunt Resistor or INA226 Measurement Pins connection (PIN9, PIN10)\n\r",name);
#endif
						}
						else {
#if (defined(INA226_DEBUG) & defined(CONSOLE_DEBUG))
							printf("%s:	OK \r\n",name);
#endif
						}



					}
					else {
#if (defined(INA226_DEBUG) & defined(CONSOLE_DEBUG))
						printf("%s:	No Bus Voltage\n\r",name);
#endif
					}
				}
				else {
#if (defined(INA226_DEBUG) & defined(CONSOLE_DEBUG))
					printf("%s:	Init Failed \r\n",name);
#endif
				}
			}
			else{
#if (defined(INA226_DEBUG) & defined(CONSOLE_DEBUG))
				printf("%s:	NOT Connected \r\n", name);
#endif
			}
		}
	}
	LED3_ON();
}
/**
 * @fn void pms_highestI2CFrequency()
 * @brief function was used to find the highst I2C Frequency
 *
 */
void pms_highestI2CFrequency(){
	uint32_t baudRate_Bps_HS = 1e6;
	uint32_t last_functional_baudRate = 1e6;
	uint8_t maxfreqFound =0;
	uint16_t checkval = 0;
	uint16_t fail_counter, counter_threshhold = 10;

	while(!maxfreqFound){

		//Set Baudrate
		i2c_set_BaudRateALL(HIGH_FREQUNECY,baudRate_Bps_HS);

		//Check if slaves are reachable
		checkval = pms_I2Caddress_check();

			//check for fail and raise counter

			uint8_t total_slave_amt = INA226_PCIe_AMT*I2C_HANDLER_AMT_PCIe+INA226_SUPP_AMT * I2C_HANDLER_AMT_SUPP;
			if (checkval != (total_slave_amt)){
				fail_counter ++;
				printf("frequency failed: %u\r\n",baudRate_Bps_HS);
			}
			else {
				//save working baudrate
				last_functional_baudRate  =  baudRate_Bps_HS;

				//start i2c and get start time
				printf("Baudrate: %u\r\n",baudRate_Bps_HS);
			}

		//raise baudrate
		baudRate_Bps_HS+= 5e3;

		//check if final frequency was reached
		if (fail_counter == counter_threshhold){
			i2c_set_BaudRateALL(HIGH_FREQUNECY,last_functional_baudRate);
			maxfreqFound = 1;
		}


	}
}

