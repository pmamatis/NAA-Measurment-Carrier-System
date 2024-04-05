/*
 * pms_log.h
 *
 *  Created on: Aug 20, 2023
 *      Author: paul
 *
 * 	@brief TODO description
 */



/*******************************************************************************
* Includes
*******************************************************************************/
/*******************************************************************************
* Defines
*******************************************************************************/
/*! @brief Stack size of the temporary lwIP initialization thread. */
#define LOG_TASK_STACKSIZE (configMINIMAL_STACK_SIZE + 2048)
/*******************************************************************************
* Local Types and Typedefs
*******************************************************************************/

/*******************************************************************************
* Variables
*******************************************************************************/

/**** Global *****/

/**** Local *****/


/*******************************************************************************
* Function Prototypes
*******************************************************************************/
int  __sys_write(int handle, char *buffer, int size);
void log_task (void *pvParameters);
void log_init();

/******************************************************************************
* Code
*******************************************************************************/


