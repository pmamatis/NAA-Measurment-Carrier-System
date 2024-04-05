/*
 * init_task.c
 *
 *  Created on: Jun 13, 2023
 *      Author: paul
 */



/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <Measurement/pms_measurement.h>
#include "pms_config.h"

//Tasks
#include "init_task.h"
#include "Config/pms_priorities.h"
#include "Controller/control_task.h"

//Board
#include "board.h"
#include "peripherals.h"

//Ethernet
#include "lwipopts.h"
#include "Ethernet/pushData_task.h"
#include "Ethernet/pms_mqtt_wrapper.h"
#include "Loging/pms_log.h"


//Measurement
#include "Measurement/pms_timestamp.h"

//Timer
#include "Measurement/pms_Timer.h"


/*******************************************************************************
 * Definitions
 ******************************************************************************/



/*******************************************************************************
 * Variables
 ******************************************************************************/



extern SemaphoreHandle_t sem_pub; /**< Semaphore to handle the publish process */
extern measurement_config_t *m_config; /**< struct which contains all configuration related to the */
bool mqtt_connected = false;/**< mqtt connection status */
extern mqtt_client_t *mqtt_client;
extern control_parameters_t *control;
/*******************************************************************************
 * Prototypes
 ******************************************************************************/



/*******************************************************************************
 * Code
 ******************************************************************************/

/**
 * @brief task to perform the initialization of all FreeRTOS parts
 */
void init_task(void *pvParameters){


#if defined(CONSOLE_DEBUG)
	printf("***start Initilalisation***\r\n");
#endif

		setInterrruptPriorities();
		timestamp_init();

/**MQTT must be activated in the pms_config header to run the initialization*/
#if  defined(MQTT) && defined(ETHERNET)
		printf("init: MQTT init\r\n");

		sem_pub = xSemaphoreCreateBinary();
#if (defined(SEM_DEBUG) & defined(CONSOLE_DEBUG))
		printf("SEM DEBUG: ----Create Publish Semaphore in init_task----\r\n");
		// Print the current count of the semaphore
		printf("SEM DEBUG: ----SemCount = %i----\n\r", uxSemaphoreGetCount(sem_init));
#endif

		mqtt_init();


/** wait for semaphore which is given in the mqtt connection callback */
		xSemaphoreTake(sem_pub,portMAX_DELAY);
#if (defined(SEM_DEBUG) & defined(CONSOLE_DEBUG))
	printf("SEM DEBUG: ----TAKE publish Semaphore in init_task, mqtt is now connected----\r\n");
	// Print the current count of the semaphore
	printf("SEM DEBUG: ----SemCount = %i----\n\r", uxSemaphoreGetCount(sem_init));
#endif


		mqtt_connected = true;

		xSemaphoreGive(sem_pub);

		printf("init: Logging Init\r\n");
/** initilize mqtt logging */
		log_init();

/** starting logging Task */
		printf("init: starting logging Task\r\n");
		if (xTaskCreate(log_task, "log_task", LOG_TASK_STACKSIZE, NULL,LOG_TASK_PRIO, NULL) !=
			pdPASS)
		{
			PRINTF("Failed to create log task");
			while (1)
				;
		}


/** MQTT is deactivated but Ethernet is needed */
#elif defined(ETHERNET)
			waitForIP();
#else


		#if (defined(SEM_DEBUG) & defined(CONSOLE_DEBUG))
			printf("SEM DEBUG: ----GIVE Init Semaphore after creation, MQTT and Ethernet are deactivated----\r\n");
			// Print the current count of the semaphore
			printf("SEM DEBUG: ----SemCount = %i----\n\r", uxSemaphoreGetCount(sem_init));
		#endif

#endif

/** initilize software controller */
		printf("init: controller init\r\n");
		control_init(control);

		printf("init: start controller Task\r\n");

		if (xTaskCreate(control_task, "control_task", configMINIMAL_STACK_SIZE + 1024, NULL, CONTROL_TASK_PRIO, NULL) !=
			pdPASS)
		{
			printf("Failed to create measurement task");
			while (1)
				;
		}

/** Measurement Init */
#if defined(MEASUREMENT)


	#if defined(TEST_STATIC_MQTT_PAYLOAD)

		printf("\n\n\r!!!! CAUTION: STATIC MQTT PAYLOAD ENABLED !!!!\n\n\r");
		m_config->useCase = TEST_STATIC_MQTT ;
	#endif
		initStream();
		pms_timer_init();
		measurement_init();

		/** LED2 indicates that init is ready */
		LED2_ON();

#endif



#if (defined(SEM_DEBUG) & defined(CONSOLE_DEBUG))
		printf("SEM DEBUG: ----DELETE Init Semaphore in init_task----\r\n");
#endif





#if	defined(CONSOLE_DEBUG)
		printf("***End Initilalisation***\r\n");
#endif


#if  defined(MQTT)

	if (xTaskCreate(pushData_task, "pushData_task", configMINIMAL_STACK_SIZE + 1024, NULL, PUSH_TASK_PRIO, NULL) !=
		pdPASS)
	{
		printf("Failed to create push task");
		while (1)
			;
	}


#endif



	vTaskDelete(NULL);
	for( ;; );

}
/**
 * @fn void setInterrruptPrioritieyys()
 * @brief Sets the priorities of all Interrupts. Priorities are given in pms_priorities.h
 *
 */
void setInterrruptPriorities(){
	/** Timer INterrrupt */
	  NVIC_SetPriority(RTC_IRQn, TIMER_PRIO);
	  NVIC_SetPriority(RIT_IRQ_ID, TIMER_PRIO);

	/** I2C Interrupt Settings */
#if defined (RTOS_I2C)
	  NVIC_SetPriority(I2C_SUPP_RTOS_FLEXCOMM_IRQN, I2C_INT_PRIO_low);
	  NVIC_SetPriority(I2C_PCIE2_RTOS_FLEXCOMM_IRQN, I2C_INT_PRIO_middle);
	  NVIC_SetPriority(I2C_PCIE1_RTOS_FLEXCOMM_IRQN, I2C_INT_PRIO_middle);

#endif
#if defined (NORMAL_I2C)
#endif
#if defined (HighSpeed_I2C)
	  NVIC_SetPriority(I2C_PCIE1_RTOS_HS_FLEXCOMM_IRQN, I2C_INT_PRIO_High);
	  NVIC_SetPriority(I2C_PCIE2_RTOS_HS_FLEXCOMM_IRQN, I2C_INT_PRIO_middle);
#endif

}
