/*
 * pms_measurement_types.h
 *
 *  Created on: Jul 3, 2023
 *      Author: paul mamatis
 *      @brief this header contains all nedded defines and typedef for the measurement process.
 */

#ifndef MEASUREMENT_PMS_MEASUREMENT_DEFINES_H_
#define MEASUREMENT_PMS_MEASUREMENT_DEFINES_H_


#include <stdint.h>
#include "fsl_i2c_freertos.h"
#include "Config/pms_config.h"

/*******************************************************
 * PCB related defines
 ******************************************************/
#define PCIe_SLOTS_AMT 2 /**< amount of PCIe Slots on one PCB */

#define I2C_DEVICE_AMT 8 /**<  amount of all INA226 Devices on PCB */

#define INA226_PCIe_AMT 3 /**< amount of ina226 devices for each PCIe slot */

#define SUPP_AMT 1 	/**< amount of ATX-Support-Pairs (12V) on one PCB*/

#define INA226_SUPP_AMT 2 	/**< amount of ina226 devies for ATX SUPP */


/**
 * Shunt Resistances for the voltage measurement
 */
#define RSHUNT_12V_SUPP 4e-3 /**< Shunt-Widerstand for 12V Support (PCIe) */


#define RSHUNT_12V 10e-3 /**< Shunt-Widerstand für 12V (PCIe) */

#define RSHUNT_3V3 25e-3 /**< Shunt-Widerstand 3V3 (3V3 und 3V3_AUX) */

/**
 *
 * @defgroup PCIe_Imax PCIe max current in A
 * @brief max current for each power lane
 * @ingroup PCIe_Characteristics
 * @{
 */
#define  IMAX_PCIE_SLOT_12V 5.5 /**< in A */
#define  IMAX_PCIE_SLOT_3V3 3  /**< in A */
#define  IMAX_PCIE_SUPP	12.5  /**< in A */

/** @} */


/**
* @brief Device Adresses, TODO müssen angepasst werden
*/
#define INA226_ADDRES_12V	    0x40     //Adress in the case of A1 and A0 are connected to GND, see INA226 Datasheet
#define	INA226_ADDRES_3V		0x44
#define INA226_ADDRES_3V_AUX	0x45
#define INA226_ADDRES_SUPP_1    0x41
#define INA226_ADDRES_SUPP_2    0x42


/**
* @brief Maximal Current
*/
#define IMAX_12V 	8.192
#define IMAX_3V  	3.272
#define IMAX_3V_AUX 0.409



/*******************************************************
 * INA226 related defines
 ******************************************************/
/**
* @brief Register Adresses, R = read only, R/W = read/write
*/
#define INA226_REG_CONFIG      0x00 //R/W
#define INA226_REG_SHUNT_VOLT  0x01 //R
#define INA226_REG_BUS_VOLT    0x02 //R
#define INA226_REG_POWER       0x03	//R
#define INA226_REG_CURRENT     0x04	//R
#define INA226_REG_CALIBRATION 0x05 //R/W
#define INA226_REG_MASK_ENABLE 0x06 //R/W
#define INA226_REG_ALERT_LIMIT 0x07 //R/W

#define INA226_REG_MANUFAC_ID  0xFE //R
#define INA226_REG_ID          0xFF //R




/**
* @brief LSB for Shunt- and Bus-Voltage register
*/
#define SHUNTVOLT_LSB 25e-7 //in V
#define BUSVOLT_LSB   1.25e-3 //in V





/**
 * @brief INA226 Status return values
 */
typedef enum{
	INA226_OK = 0,
	INA226_ERROR =1
}INA226_ReturnVal;

/**CONFIGURATION REGISTER MASKS BEGIN */
/**
* @brief Mask for for RESET command in the configuration Register, written to the bit 15
*/
#define INA226_MASK_RESET	   (uint16_t) 0b10000000000000000



/**
* @brief Mask for numbers of averages in the configuration Register, written to the bits 9 to 11
*/
typedef enum {
	AVG_1   = 0b0000000000000000, // default value
	AVG_4   = 0b0000001000000000,
	AVG_16  = 0b0000010000000000,
	AVG_64  = 0b0000011000000000,
	AVG_128 = 0b0000100000000000,
	AVG_256 = 0b0000101000000000,
	AVG_512 = 0b0000110000000000,
	AVG_1024= 0b0000111000000000
}INA226_NoA_t;


/**
* @brief Mask for Bus Voltage Conversion Time in the configuration Register, written to the bits 6 to 8
* @param: time in micro seconds
*/
typedef enum{
	VBUSCT_140us  = 0b0000000000000000,
	VBUSCT_204us  = 0b0000000000100000,
	VBUSCT_332us  = 0b0000000001000000,
	VBUSCT_588us  = 0b0000000001100000,
	VBUSCT_1100us = 0b0000000010000000, //default value
	VBUSCT_2116us = 0b0000000010100000,
	VBUSCT_4156us = 0b0000000011000000,
	VBUSCT_8244us = 0b0000000011100000
}INA226_VBUSCT_t;


/**
* @brief Mask for Shunt Voltage Conversion Time in the configuration Register, written to the bits 3 to 5
* @param: time in micro seconds
*/
typedef enum{
	VSHCT_140us  = 0b0000000000000000,
	VSHCT_204us  = 0b0000000000000100,
	VSHCT_332us  = 0b0000000000001000,
	VSHCT_588us  = 0b0000000000001100,
	VSHCT_1100us = 0b0000000000010000, //default value
	VSHCT_2116us = 0b0000000000010100,
	VSHCT_4156us = 0b0000000000011000,
	VSHCT_8244us = 0b0000000000011100
}INA226_VSHCT_t;

/**
* @brief Mask for Operating Mode in the configuration Register, written to the bits 0 to 2
*/
typedef enum{
	PWDO = 0b0000000000000000,/**<Power-Down*/
	SVT  = 0b0000000000000001,/**<Shunt Voltage Triggered*/
	BVT  = 0b0000000000000010,/**<Bus Voltage Triggered*/
	SBVT = 0b0000000000000011,/**<Bus and Shunt Voltage Triggered*/
	PWDO2= 0b0000000000000100,/**<Power-Down*/
	SVC  = 0b0000000000000101,/**<Shunt Voltage Continious*/
	BVC  = 0b0000000000000110,/**<Bus Voltage Continious*/
	SBVC = 0b0000000000000111,/**<Bus and Shunt Voltage Continious*/
}INA226_OM_t;





/*******************************************************
 * Software related defines
 ******************************************************/

#define I2C_HANDLER_AMT_PCIe 2 /**< amount of I2C Handler assingned to a PCIe slot*/
#define I2C_HANDLER_AMT_SUPP 1 /**< amount of I2C Handler assigned to Support Voltage */
#define I2C_HANDLER_AMT_ALL (I2C_HANDLER_AMT_PCIe + I2C_HANDLER_AMT_SUPP) /**< amount of all I2C Handler */

#define I2C_DATA_LENGTH 2 //all INA226 register contain 2 Byte
#define I2C_READ_REGISTER_AMT 2 /**< asmount of register to read */


typedef enum{
	FULL = 0,
	LESS
}board_setup;


/**
 * enum for easy handling the three different lanes which should be measured
 */
typedef enum{
	PCIe1 = 0,
	PCIe2,
	SUPP,
}lane_t;





typedef enum{
	SINGLE_SLOT= 0,
#ifdef TEST_STATIC_MQTT_PAYLOAD
	TEST_STATIC_MQTT,
#endif
	DOUBLE_SINGLE_SLOT,
	DUAL_SLOT,
	PCIe_SUPP
}pms_measurement_config_t;


/**
 * struct to store the configuration data for ina226, this is used in the initilaisation process
 */
typedef struct ina226_config_data_t{
	INA226_NoA_t avg;			/**< number of averages for each measurement*/
	INA226_VBUSCT_t bus_time; 	/**< Bus voltage measurement conversion time*/
	INA226_VSHCT_t	shunt_time; /**< Shunt Voltage measurement conversion time*/
}ina226_config_data_t;



/**
 * @brief Struct für eine PCIe-Lane mit allen notwendigen Information um die Mess-Sensorik (INA226) ueber I2C anzusprechen
 *
 */
typedef struct pms_ina226_pcie
{
#if defined(RTOS_I2C)
	i2c_rtos_handle_t* i2c_handler;	/**< [0] =PCIe1 , [1] = PCIe2, [2] = SUPP */
#elif defined(NORMAL_I2C)
	I2C_Type* i2c_handler;	/**< [0] =PCIe1 , [1] = PCIe2, [2] = SUPP */
	i2c_master_handle_t* master_handle[I2C_HANDLER_AMT]; /**< handler for i2c state machine */

#endif
	i2c_master_transfer_t* transfer_struct;  /**< structs for each lane which contains the transfer information, like slave address, register address and so on */
	uint16_t DevAddress[INA226_PCIe_AMT + INA226_SUPP_AMT];				 		/**< [0] = J4, [1] = J5 ; Referenz zu Jumpern auf dem PCB */
	double	 Shunt_Res[INA226_PCIe_AMT];				 		/**< Shunt-Resistance for PCIe-Supp Stecker*/
	double	 Imax[INA226_PCIe_AMT];				/**< Maximaler Strom der PCIe Slots , [0] = 12V, [1] =3V3 , [2] = 3V3_AUX  */
	ina226_config_data_t config;			/**< config data for each group of INA226 */
}pms_ina226_pcie;



/**
 * @brief struct to store the measurement result, each object has as much entrys per result kind as much measurement ICs are on one voltage bus
 */
typedef struct ina226_results_t{
	float busVoltage[INA226_PCIe_AMT];
	float current[INA226_PCIe_AMT];
	float power[INA226_PCIe_AMT];
}ina226_results_t;

typedef struct measurement_config_t{
	uint8_t useCase;
	uint8_t HighSpeedmode;
	char DUT_Names[2][10];
	float mfrequency;
	TickType_t mTicks_PCIe[PCIe_SLOTS_AMT];
	TickType_t mTicks_Supp;
}measurement_config_t;



typedef enum {
	HIGH_FREQUNECY = 0,
	NORMAL_FREQUENCY
}i2c_bus_type;

#endif /* MEASUREMENT_PMS_MEASUREMENT_DEFINES_H_ */
