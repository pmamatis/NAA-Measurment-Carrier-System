/*
 * init_task.h
 *
 *  Created on: Jun 13, 2023
 *      Author: paul
 */

#ifndef INIT_TASK_H_
#define INIT_TASK_H_


/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief Stack size of the initialization thread. */
#define INIT_THREAD_STACKSIZE (configMINIMAL_STACK_SIZE + 5*1024)

/*! @brief Priority of the temporary lwIP initialization thread. */
#define INIT_TASK_PRIO configMAX_PRIORITIES


/*******************************************************************************
 * Prototypes
 ******************************************************************************/
void init_task(void *pvParameters);
void setInterrruptPriorities();


#endif /* INIT_TASK_H_ */
