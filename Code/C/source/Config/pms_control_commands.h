/*
 * pms_control_commands.h
 *
 *  Created on: Aug 23, 2023
 *      Author: paul
 *
 * 	@brief TODO description
 */

#ifndef PMS_CONTROL_COMMANDS_H_
#define PMS_CONTROL_COMMANDS_H_



/*******************************************************************************
* Includes
*******************************************************************************/
/*******************************************************************************
* Defines
*******************************************************************************/


/** Configuration topics */
#define CONFIG_TOPIC "Config"
#define PRE_TOPIC "devices"

/** Sub topics */
#define LOG_TOPIC  "Log"
#define USE_CASE_COMMAND "UseCase"
#define RESET_COMMAND "Reset"
#define FREQUENCY_TOPIC "Frequency"
#define PCIE1_TOPIC  "PCIe1_DUT_Name"
#define PCIE2_TOPIC  "PCIe2_DUT_Name"
#define TIME_TOPIC "Time"

/** DUT Topics */
#define ON_OFF_COMMAND "ON_OFF"
#define MEAUSREMENT_DATA_TOPIC "Data"
/*******************************************************************************
* Functions
*******************************************************************************/



#endif /* PMS_CONTROL_COMMANDS_H_ */
