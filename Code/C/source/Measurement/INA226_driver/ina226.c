
/**
* @file ina226.c
* @author Paul Mamatis
* @version 1.0
* @date  Jun 14, 2023
*
* @section DESCRIPTION TODO
*/


#include "Config/pms_config.h"

#include "ina226.h"
#include "fsl_i2c_freertos.h"
#include "Measurement/I2C/pms_i2cWrapper.h"
#include "Measurement/I2C/pms_i2cWrapper_RTOS.h"

#include "math.h"

#include "board.h"
#include <stdio.h>
/**
* @brief status variables
*/
extern status_t i2c_status;
uint16_t detectErrorState;


 static uint16_t receivedByteToUint16Value(uint8_t* g_rxBuff);

/**

 *
 */
/**
 * @brief Init and calibration of a INA226
 *
 * @param lane, PCIe1, PCIe2 or SUPP
 * @param devAddress
 * @param imax
 * @param rshunt
 * @param name
 * @param conf
 * @return
 */	INA226_ReturnVal ina226_init(i2c_rtos_handle_t *handle, i2c_master_transfer_t *transfer,uint16_t devAddress,double imax, double rshunt, char* name,ina226_config_data_t conf) {
	uint8_t pData[10] = {0,0,0,0,0,0,0,0,0,0};
		#if (defined(INA226_DEBUG) & defined(CONSOLE_DEBUG))
		printf("\n\r***I2C %s INIT***\n\r",name);
		#endif
			// Configuration
//			uint16_t config_data =0x4000 | conf.avg | conf.bus_time | conf.shunt_time | SBVC ;
			uint16_t config_data =0x4000 | AVG_1 | VBUSCT_588us | VSHCT_588us | SBVC ;
			pData[0] = ((uint8_t*)&config_data)[1];
			pData[1] = ((uint8_t*)&config_data)[0];
			i2c_writeREG(handle,transfer, devAddress, INA226_REG_CONFIG, pData);

			//Check Data, TODO Debug modus erstellen

			//read register to confirm right data has been writen
			uint16_t retval = i2c_readREG(handle,transfer,devAddress , INA226_REG_CONFIG);//read data

#if (defined(INA226_DEBUG) & defined(CONSOLE_DEBUG))
			printf("%s Config Register:\n set value 0x%X == 0x%X read value?\r\n",name,config_data,retval );
#endif

			//check if read data and writen data is the same
			if ((i2c_status == kStatus_Success) && (retval == config_data)){

#if (defined(INA226_DEBUG) & defined(CONSOLE_DEBUG))
				printf("%s:	Configuration success\n\r",name);
#endif
				return INA226_OK;
			}
			else{
#if (defined(INA226_DEBUG) & defined(CONSOLE_DEBUG))
				printf("%s:	Configuration failed\n\r",name);
#endif
				return INA226_ERROR;
			}
 }

			//Calibration
//			//		uint16_t calibrate_data = 2048; //
//			uint16_t calibrate_data = ina226_calibrate( imax, rshunt);
//
//			//Write Reg
//			pData[0] = ((uint8_t*)&calibrate_data)[1];
//			pData[1] = ((uint8_t*)&calibrate_data)[0];
			//	printf("pData[0]: %x\n\r pData[1]: %x\n\r",pData[0],pData[1]);
//			i2c_tmp_status = HAL_I2C_Mem_Write(hi2c, DevAddr, INA226_REG_CALIBRATION, 1,pData, 2,100);
//			i2c_writeREG(hi2c, devAddress, INA226_REG_CALIBRATION, &calibrate_data);

			// Check Data
//			HAL_I2C_Mem_Read(hi2c, DevAddr, INA226_REG_CALIBRATION, 1, pData, 2,100);

			/* DEBUG
			printf("Cal Data:%x = %x\n\r", calibrate_data,((pData[0]<<8)+pData[1]));
			 */
//
//			if ((i2c_tmp_status == HAL_OK) && (calibrate_data==((pData[0]<<8)+pData[1]))){
//			printf("%s:	Calibartion success\n\r",name);
//			}
//			else{
//				printf("%s:	Calibartion failed\n\r",name);
//				return INA226_ERROR;
//			}
//	free(pData);


//
//
//
uint16_t ina226_calibrate(double I_MAX, double R_SHUNT){
	double cal_val = 0;
	double current_LSB = I_MAX/32768; //i_max/2^15
	cal_val = 0.00512/(current_LSB * R_SHUNT);

	/*DEBUG*/
//	printf("CalVal float: %f\n\r CalVal: %i\n\r",cal_val,(uint16_t)cal_val);

	return (uint16_t)cal_val;
}
//

#if defined(RTOS_I2C)
INA226_ReturnVal ina226_isConnected(i2c_rtos_handle_t* hi2c_rtos, uint16_t devAddress){
	I2C_Type* hi2c = hi2c_rtos->base;


#elif defined(NORMAL_I2C)
	INA226_ReturnVal ina226_isConnected(I2C_Type* hi2c, uint16_t devAddress){
#endif
	//send an i2c start sequence followed by slave address in combination with write command

	status_t retVal = I2C_MasterStart(hi2c, devAddress,kI2C_Read );//TODO muss gestestet werden

	uint32_t master_state =hi2c->STAT ;
	uint32_t timeout =0;
	uint32_t timeout_max = 1e5;


	bool i2c_pending = master_state&I2C_STAT_MSTPENDING_MASK;

	//Wait  until i2c status register changed from 0 to 1, 0 means in progress, 1 means pending

	while( ( !(i2c_pending) ) && (timeout != timeout_max) ){
		master_state =hi2c->STAT ;
		i2c_pending = master_state&I2C_STAT_MSTPENDING_MASK;
		timeout++;
	}
	if (timeout == timeout_max){

#if (defined(INA226_DEBUG) & defined(CONSOLE_DEBUG))
		printf("I2C: i2C status timeout while %x connection check\r\n",devAddress);
#endif
	}
	//check if i2c is not busy
	if (retVal == kStatus_Success){

//		printf("%x, %x\n",(master_state & I2C_STAT_MSTSTATE_MASK) >> I2C_STAT_MSTSTATE_SHIFT, I2C_STAT_MSTPENDING(master_state)   );

		//get state of i2c bus from i2c status register
		master_state = (master_state & I2C_STAT_MSTSTATE_MASK) >> I2C_STAT_MSTSTATE_SHIFT;
		/*check if state is 0x01 (transmit ready), means :Transmit ready. Data can be transmitted (Master Transmitter mode).
		Address plus Write was previously sent and Acknowledged by slave. page 476 table 461, LPC54S0xx User Manuual*/
		if (master_state == 0x01  ){
			I2C_MasterStop(hi2c);
			return INA226_OK;
		}
		// 0x3 means: NACK Address. Slave did not acknowleged  address.
		else if (master_state == 0x3) {
			return INA226_ERROR;
		}

	}
	else if (retVal == kStatus_Busy){
	#if (defined(INA226_DEBUG) & defined(CONSOLE_DEBUG))
		printf("I2C busy, check pullup resistors\n\r");
	#endif

		return INA226_ERROR;
	}

	#if (defined(INA226_DEBUG) & defined(CONSOLE_DEBUG))
		get_i2c_status(hi2c);
		printf("i2c status: 0x%x, unknown error\n\r",retVal);
	#endif
	return INA226_ERROR;
}

uint16_t ina226_setConvTime(uint16_t measurement_frequecy){
	uint16_t retVal=0;
	if (measurement_frequecy <=121){
			return retVal|VSHCT_8244us|VBUSCT_8244us;
	}
	else if(measurement_frequecy <= 240 ){	/**< 1/8244us*/
			return retVal|VSHCT_4156us|VBUSCT_4156us;
	}
	else if(measurement_frequecy <= 472 ){	/**< 1/2116us*/
				return retVal|VSHCT_2116us|VBUSCT_2116us;
		}
	else if(measurement_frequecy <= 909 ){	/**< 1/1100us*/
			return retVal|VSHCT_1100us|VBUSCT_1100us;
	}
	else if(measurement_frequecy <= 1700 ){	/**< 1/588us*/
			return retVal|VSHCT_588us|VBUSCT_588us;
	}
	else if(measurement_frequecy <= 3012 ){	/**< 1/332us*/
		return retVal|VSHCT_332us|VBUSCT_332us;
	}
	else if(measurement_frequecy <= 4901 ){	/**< 1/204us*/
		return retVal|VSHCT_204us|VBUSCT_204us;
	}
	else if (  measurement_frequecy <= 7142 ){/**< 1/140us*/
		return retVal|VSHCT_140us|VBUSCT_140us;
	}
	else if(measurement_frequecy > 7142){
		printf("measurement frequency must be under 7142\n\r");
	}
}

uint16_t ina226_setAvg(uint16_t measurement_frequecy){
	uint8_t potenz = 8;
	div_t avg[potenz];

	for (uint8_t i = 0; i < potenz; i++){
		 avg[i] = div(measurement_frequecy,powf(2,(float)i));
	}

}




uint16_t ina226_GetBusVoltage(i2c_rtos_handle_t *handle, i2c_master_transfer_t *transfer, uint16_t busAddress){
	uint16_t result=0;
	result = i2c_readREG(handle,transfer, busAddress, INA226_REG_BUS_VOLT);

	return result;
}


uint16_t ina226_GetShuntVoltage(i2c_rtos_handle_t *handle, i2c_master_transfer_t *transfer, uint16_t busAddress){
	uint16_t result=0;
	result = i2c_readREG(handle,transfer, busAddress, INA226_REG_SHUNT_VOLT);

	return result;
}

//Result to double Functions
float ina226_shuntToVoltage(uint16_t shuntResult){
	float voltage = 0;
	voltage = (float)(shuntResult)*SHUNTVOLT_LSB;
	return voltage;
}

float ina226_busToVoltage(uint16_t busResult){
	float voltage = 0;
	voltage = ((float) busResult)*BUSVOLT_LSB;
	return voltage;
}

float ina226_currentToAmpere(uint16_t currentResult){
	float ampere=0;
	ampere =(int16_t) currentResult *1e-3;
	return ampere;
}

float ina226_powerToWatt(uint16_t powerResult){
	float power = 0;
	power = powerResult;
	return power;
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
