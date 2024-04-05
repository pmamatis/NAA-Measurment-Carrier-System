
/**
* @file pms_config.h
* @author Paul Mamatis
* @version 1.0
* @date  Jun 19, 2023
*
* @section DESCRIPTION TODO
*/
#ifndef PMS_CONFIG_H_
#define PMS_CONFIG_H_

/*************************************************
 *  Description: parts in the code get activated if the the Macro is defined. The section will be not activated when the macro is commented out.
 *  The Sections are activated and deactivated via compiler macros, so the changes only take place after rebuilding project.
 ************************************************/




/**************************************************
 * Essential Configurations
 *************************************************/

/** @brief if defined activate the Ethernet Interface */
#define ETHERNET	1

/** @brief if defined activate the MQTT connection  */
#define MQTT	1

/** @brief if defined the whole measurement is activated */
#define MEASUREMENT 1

/** I2C Config */

//#define NORMAL_I2C 1


#if !defined(NORMAL_I2C)
	#define RTOS_I2C 1

// activate Highspeed mode
#define HighSpeed_I2C 1

/** Datachunking for better MQTT performance */
//#define DATA_CHUNKING 1
/*************************************************
 *  Debug Configurations
 *************************************************/

/**@brief define if you you want to have console debug printf meassages */
#define CONSOLE_DEBUG 1

/** @brief sends debug meassages also to mqtt */
#define CONSOLE_TO_UART 1

/** @brief sends debug meassages also to UART */
//#define CONSOLE_TO_MQTT 1

/**@brief define if you want to debug semaphores via console */
//#define SEM_DEBUG	1


/**@brief define if you want to print some i2c return and write data values via console */
//#define I2C_DEBUG	1

/**@brief define if you want to get a better insight in the INA226 initialisation and measurment processes */
#define INA226_DEBUG	1

/**streambuffer debug output */
//#define STREAM_DEBUG 1

/**@brief meta data of acquired and sended bytes for timing debugging*/
#define COLLECT_META_DATA 1





/*************************************************
 *  Developing  Configurations
 *************************************************/
/** @brief Set to 1 if you want the measurment task to put static values in the queue, so you can isolate the MQTT publish mechanism */
//#define TEST_STATIC_MQTT_PAYLOAD 1

/** @brief activates the Test task, this excludes all other Tasks */
//#define TEST_TASK 1

/** check synchronity between cycle and RTC-Clock */
//#define CHECK_CLOCK_SYNC 1

#endif

#endif /* PMS_CONFIG_H_ */
