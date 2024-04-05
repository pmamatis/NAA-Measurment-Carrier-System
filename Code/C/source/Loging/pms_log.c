/*
 * pms_log.c
 *
 *  Created on: Aug 20, 2023
 *      Author: paul
 *
 * 	@brief TODO description
 */

#ifndef PMS_LOG_C_
#define PMS_LOG_C_



/*******************************************************************************
* Includes
*******************************************************************************/
#include "Config/pms_config.h"
#include "Config/pms_priorities.h"

#include "Ethernet/pms_mqtt_wrapper.h"
#include "fsl_debug_console.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include "FreeRTOS.h"
#include "message_buffer.h"
/*******************************************************************************
* Defines
*******************************************************************************/


#define MSG_BUFF_SIZE_BYTE 1000

/*******************************************************************************
* Variables
*******************************************************************************/
/** mqtt connection flag for parsing the debug measages to an MQTT broker */
extern bool mqtt_connected;

bool log_init_complete = false;

MessageBufferHandle_t log_buffer;

SemaphoreHandle_t sem_log; /**<	 handles initilisation process */


/*******************************************************************************
* Functions
*******************************************************************************/
void log_task (void *pvParameters);
void log_init();

/*******************************************************************************
* Code
*******************************************************************************/

/**
 * @fn void log_init()
 * @brief logging init, starts the log task and creates the meassage buffer, where all outputs are saved
 *
 */
void log_init(){

	log_buffer = xMessageBufferCreate(MSG_BUFF_SIZE_BYTE);
	sem_log = xSemaphoreCreateBinary();
	log_init_complete = true;
	xSemaphoreGive(sem_log);

}


/**
 * @fn void log_task(void*)
 * @brief Task to handle MQTT logging. The Task reads a meassage buffer and then invoke a mqtt publish request to the tcpip task
 *
 * @param pvParameters
 */
void log_task (void *pvParameters){


	uint8_t ucRxData[ 500 ];
	size_t xReceivedBytes;
	const TickType_t xBlockTime = portMAX_DELAY;
	uint8_t threshhold_in_byte = 1;
	uint8_t byte_counter = 0;
	while(1){

	    /** Receive the next message from the message buffer.  Wait in the Blocked
	    state (so not using any CPU processing time) for
	    a message to become available. */
	    xReceivedBytes = xMessageBufferReceive( log_buffer,
	                                            ( void * ) (ucRxData + byte_counter),
	                                            sizeof( ucRxData ),
	                                            xBlockTime );

	    if( xReceivedBytes > 0 )
	    {
	    	/** adds up all received measagges to decrease the number of invoked mqtt publish request. So one meassage has is bigger, instead of a lot of small meassages*/
	    	byte_counter = byte_counter + xReceivedBytes;
	        /* A ucRxData contains a message that is xReceivedBytes long.  Process
	        the message here.... */

	        if (mqtt_connected && (byte_counter >= threshhold_in_byte) ){
	        	xSemaphoreTake(sem_log,portMAX_DELAY);
//	            DbgConsole_SendDataReliable((uint8_t *)ucRxData, byte_counter);

	        	/** publish meassage to log topic */
	        	publish_mqtt_msg_string("log", ucRxData, byte_counter);

	        	byte_counter = 0;
	        }
	        xReceivedBytes = 0;
	    }
	}
}

/**
 * @fn int __sys_write(int, char*, int)
 * @brief printf overload to choose weather the output is to UART or to MQTT
 *
 * @param handle
 * @param buffer
 * @param size
 * @return
 */
int  __sys_write(int handle, char *buffer, int size)
{
    if (NULL == buffer)
    {
        /* return -1 if error. */
        return -1;
    }

    /* This function only writes to "standard out" and "standard err" for all other file handles it returns failure. */
    if ((handle != 1) && (handle != 2))
    {
        return -1;
    }

#if defined(CONSOLE_DEBUG)

    /* Send data. */

#if defined (CONSOLE_TO_MQTT)
    if (mqtt_connected && log_init_complete){
    /** the xMessageBufferSend function must be called in a critical section, because it is possible that
    the ____sys_write is called from different task at the same time */
    taskENTER_CRITICAL();

    xMessageBufferSend(log_buffer, buffer, size, 0);

    taskEXIT_CRITICAL();
    }
#endif

#if defined (CONSOLE_TO_UART)
    DbgConsole_SendDataReliable((uint8_t *)buffer, size);
#endif

#endif
    return 0;
}
//Function returns number of unwritten bytes if error, otherwise 0 for success




#endif /* PMS_LOG_C_ */
