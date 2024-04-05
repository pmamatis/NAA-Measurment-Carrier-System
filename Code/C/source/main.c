/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**  Standard C Included Files */
#include <Measurement/pms_measurement.h>
#include <string.h>

/** Config file **/
#include "pms_config.h"
#include "Config/pms_priorities.h"


/** FreeRTOS kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "semphr.h"

/**  SDK Included Files */
#include "pin_mux.h"
#include "peripherals.h"
#include "board.h"
#include "fsl_debug_console.h"
#include "fsl_i2c.h"
#include "fsl_i2c_freertos.h"

/** Power-Measurement-System include Files */
#include "Measurement/INA226_driver/ina226.h"
#include "Measurement/pms_HardwareCheck.h"
#include "Measurement/I2C/pms_i2cWrapper.h"
#include "Measurement/I2C/pms_i2cWrapper_RTOS.h"
#include "Measurement/INA226_driver/ina226_measurement_frequency_adjusting.h"
#include "init_task.h"
#include "Measurement/pms_Timer.h"
#include "Measurement/I2C/pms_i2c_init.h"
#include "Measurement/pms_timestamp.h"
/** MQTT Includes */
#include "Ethernet/pushData_task.h"
#include "Ethernet/pms_mqtt_wrapper.h"
#include "Loging/pms_log.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/



/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/






/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/


SemaphoreHandle_t xMutex; /**< init Mutex */

extern SemaphoreHandle_t sem_init;/**< Binary semaphore to block thread until valid IPv4 address is obtained from DHCP*/
extern measurement_config_t *m_config;/**< struct which contains all configuration related to the */
extern pms_ina226_pcie ina226_hardwareDataPCIE[2];


#if defined (CHECK_CLOCK_SYNC)
extern uint32_t seconds,seconds_before,microseconds,microseconds_before,tick_passed;
extern double time_passed ;
#endif
/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/



/*******************************************************************************
 * Code
 ******************************************************************************/
/** @brief Test-Task for development purposes*/
extern bool mqtt_connected;
void Test_task(void *pvParameters){

	m_config->useCase =DOUBLE_SINGLE_SLOT;
	setInterrruptPriorities();
	timestamp_init();

//	mqtt_init();
//	log_init();

//	mqtt_connected = true;
//	uint32_t seconds = RTC->COUNT;
////	uint32_t seconds_before = RTC->COUNT;
////	uint32_t microseconds  =KIN1_GetCycleCounter();
//	uint32_t microseconds_before  =KIN1_GetCycleCounter();
//	uint32_t tick_passed = 0;
//	double time_passed = 0;
	while(1)
	{
//		seconds = RTC->COUNT;
//		if (seconds > seconds_before){
//			microseconds  =KIN1_GetCycleCounter();
//			tick_passed = microseconds-microseconds_before;
////			time_passed = tick_passed/
////			printf("cycle ticks passed in 1 second: %u\r\n",() );
//			printf("cycle ticks passed in 1 second: %u\r\n",(microseconds-microseconds_before) );
//			seconds_before = RTC->COUNT;
//			microseconds_before  =KIN1_GetCycleCounter();
//		}
//		printf("Hello \r\n");

//		vTaskDelay(1000);

	}
	vTaskDelete(NULL);
}



int main(void)
{
    /** Init functions for the µC hardware */                                                                                                                                                                                                                  	PIN_INIT_SWD_DEBUGPins();
	BOARD_PIN_INIT_LED();
	BOARD_BootClockPLL180M();
	INIT_Peripherals();
	BOARD_PIN_INIT_DEBUGConsole();
	INIT_Peripherals_DEBBUG();



#if defined(ETHERNET)
	/** Init functions for ethernet */
	PIN_INIT_ENETPins();
	INIT_Periphals_Ethernet();
#endif


#if defined(CONSOLE_DEBUG)
	printf("\r\n==PCIe Measurment System Start==\r\n");
	printf("size of measurement_t: %i\r\n",sizeof(measurement_data_t));
#endif
//
#if  defined(CONSOLE_DEBUG)
		printf("init: create mqtt topics\r\n");
#endif
/** Test task, can be acivated in the pms_config. Excludes all other tasks */
#if defined (TEST_TASK)
		if (xTaskCreate(Test_task, "Test_task", INIT_THREAD_STACKSIZE, NULL,INIT_TASK_PRIO, NULL) !=
	        pdPASS)
	    {
	        PRINTF("Failed to create slave task");
	        while (1)
	            ;
	    }
#else

/** default configurations*/
		m_config = malloc(sizeof(measurement_config_t));
//		m_config->useCase = DUAL_SLOT;
		m_config->useCase = DOUBLE_SINGLE_SLOT;
//		m_config->useCase = SINGLE_SLOT;
#if defined (DATA_CHUNKING)
		m_config->HighSpeedmode = 1;
		m_config->mfrequency = 1000;
#else
		m_config->mfrequency = 300;
#endif


/** Init Task, this will do initilisation and then start the chosen task
 * Entry point for FreeRTOS
 * */
if (xTaskCreate(init_task, "init_task", INIT_THREAD_STACKSIZE, NULL,INIT_TASK_PRIO, NULL) !=
	pdPASS)
{
	PRINTF("Failed to create slave task");
	while (1)
		;
}


#endif

#if defined (CHECK_CLOCK_SYNC)
/* check delay between RTC and cycle Counter */
seconds = RTC->COUNT;
seconds_before = RTC->COUNT;
microseconds  =KIN1_GetCycleCounter();
microseconds_before  =KIN1_GetCycleCounter();
tick_passed = 0;
time_passed = 0;
#endif
    vTaskStartScheduler();
    for (;;)
        ;
}



