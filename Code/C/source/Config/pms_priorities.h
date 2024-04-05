/*
 * pms_priorities.h
 *
 *  Created on: Jul 27, 2023
 *      Author: paul
 *
 * 	@brief TODO description
 * 	Priority handling of all Interrrupts and RTOS stuff
 */

#ifndef PMS_PRIORITIES_H_
#define PMS_PRIORITIES_H_



/*******************************************************************************
* Includes
**********
*******************************************************************************/
#include "FreeRTOSConfig.h"
/*******************************************************************************
* Defines
*******************************************************************************/


/*** Interrupt Prios ***
 * lower prios means MORE important */

#define I2C_INT_PRIO_High (configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY + 1) ///< must have highest priority
#define I2C_INT_PRIO_middle (I2C_INT_PRIO_High + 1)
#define I2C_INT_PRIO_low (I2C_INT_PRIO_middle + 1)
#define TIMER_PRIO (I2C_INT_PRIO_low +1)




/*** Task Prios ***
 * lower prios means LESS important */

#define INIT_TASK_PRIO configMAX_PRIORITIES
#define MEASUREMENT_TASK_PRIO 	(configMAX_PRIORITIES - 3)
#define PUSH_TASK_PRIO (MEASUREMENT_TASK_PRIO-1)
#define LOG_TASK_PRIO (PUSH_TASK_PRIO -1)
#define CONTROL_TASK_PRIO ((PUSH_TASK_PRIO -1))




/*******************************************************************************
* Functions
*******************************************************************************/



#endif /* PMS_PRIORITIES_H_ */
