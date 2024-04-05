/**
 * @file pms_HardwareCheck.h
 * @author Paul Mamatis (p.mamatis@hhi.fraunhofer.de)
 * @brief PCIe Power Maesuring System
 * @version 0.1
 * @date 2022-04-06
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef INC_PMS_H_
#define INC_PMS_H_
#include "Config/pms_config.h"

#include <string.h>
#include <stdio.h>

#include "pms_measurement_defines.h"
#include "Measurement/INA226_driver/ina226.h"
#include "LPC54S018.h"
#include "fsl_i2c_freertos.h"





void pms_init();
void pms_HardwareInit(board_setup setup,double measurement_frequency);
//void pms_HardwareCheck(board_setup setup);
void pms_highestI2CFrequency();
uint16_t pms_I2Caddress_check();



#endif /* INC_PMS_H_ */
