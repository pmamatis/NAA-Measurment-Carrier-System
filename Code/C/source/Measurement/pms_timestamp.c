/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "Config/pms_config.h"
#include "pms_timestamp.h"
#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "board.h"
#include "fsl_rtc.h"
#include "fsl_clock.h"
#include <stdbool.h>
#include <stdio.h>
#include "Controller/control_task.h"
#include "lwip/apps/sntp.h"
#include "pms_Timer.h"
#include <stdlib.h>
#include <math.h>
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/** DWT (Data Watchpoint and Trace) registers, only exists on ARM Cortex with a DWT unit */
#define KIN1_DWT_CONTROL             (*((volatile uint32_t*)0xE0001000))  /*!< DWT Control register */

#define KIN1_DWT_CYCCNTENA_BIT       (1UL<<0) /*!< CYCCNTENA bit in DWT_CONTROL register */

#define KIN1_DWT_CYCCNT              (*((volatile uint32_t*)0xE0001004)) /*!< DWT Cycle Counter register */

#define KIN1_DEMCR                   (*((volatile uint32_t*)0xE000EDFC)) /*!< DEMCR: Debug Exception and Monitor Control Register */

#define KIN1_TRCENA_BIT              (1UL<<24)  /*!< Trace enable bit in DEMCR register */

#define KIN1_InitCycleCounter() \
  KIN1_DEMCR |= KIN1_TRCENA_BIT  /*!< TRCENA: Enable trace and debug block DEMCR (Debug Exception and Monitor Control Register */

#define KIN1_ResetCycleCounter() \
  KIN1_DWT_CYCCNT = 0 /*!< Reset cycle counter */

#define KIN1_EnableCycleCounter() \
  KIN1_DWT_CONTROL |= KIN1_DWT_CYCCNTENA_BIT  /*!< Enable cycle counter */

#define KIN1_DisableCycleCounter() \
  KIN1_DWT_CONTROL &= ~KIN1_DWT_CYCCNTENA_BIT /*!< Disable cycle counter */

#define KIN1_GetCycleCounter() \
  KIN1_DWT_CYCCNT /*!< Read cycle counter register */

#define TIMESTAMP_RES (1000000UL) /**< resolution of the timestamp, 1000 = milli seconds, 10000 = 100µs, 1000000 = µs etc.  */
//#define TIMESTAMP_RES (1UL) /**< resolution of the timestamp, 1000 = milli seconds, 10000 = 100µs, 1000000 = µs etc.  */

#define CYCLE_COUNTER_MAX_VAL 4294967296 /**< cycle counter max value resulting from 32 bit */

#define CYCLE_CLOCK_TRUE_FREQUENCY 179650000 /** measured frequency */


#define  CYCLE_CLOCK_FREQUENCY  CLOCK_GetFreq(kCLOCK_CoreSysClk) /**< vendor given frequency*/



/** SNTP */
#define SNTP_SERVER_NAME "fritz.box"

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

volatile bool busyWait;
double timestamp_dividend;
uint32_t time_ref_for_milli;
uint32_t starttime;

extern control_parameters_t *control;
/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * @brief ISR for Alarm interrupt
 *
 * This function changes the state of busyWait.
 */
extern unsigned int mqtt_send;

#if defined (CHECK_CLOCK_SYNC)
uint32_t seconds,seconds_before,microseconds,microseconds_before,tick_passed;
double time_passed = 0;
#endif
int count = 0;
void RTC_IRQHandler(void)
{

	uint8_t sec = 1;
    if (RTC_GetStatusFlags(RTC) & kRTC_AlarmFlag)
    {
        busyWait = false;

        /* Clear alarm flag */
        RTC_ClearStatusFlags(RTC, kRTC_AlarmFlag);
    }
#if defined (CHECK_CLOCK_SYNC)
		microseconds  =KIN1_GetCycleCounter();
		tick_passed = microseconds-microseconds_before;
//			time_passed = tick_passed/
//			printf("cycle ticks passed in 1 second: %u\r\n",() );
		printf("cycle ticks passed in 1 second: %u\r\n",(microseconds-microseconds_before) );
		seconds_before = RTC->COUNT;
		microseconds_before  =KIN1_GetCycleCounter();
#endif

    /* Set alarm time in seconds */
    RTC_SetSecondsTimerMatch(RTC, 	(RTC->COUNT)+1);



    count++;
    if ((count%10 ==0)&&((control->measurement_active) == true)){
        print_metadata();
        count = 0;
    }



    SDK_ISR_EXIT_BARRIER;
}


void set_initial_TIME(uint32_t time){
    printf("rtc; set initial Time to: %i", time);
    RTC_EnableTimer(RTC, false);

    /* Set RTC time to default */
    RTC->COUNT = time;

    /* Start the RTC time counter */
    RTC_EnableTimer(RTC, true);
    RTC_SetSecondsTimerMatch(RTC, 	(RTC->COUNT)+1);
}



/*!
 * @brief starts the RTC clock, the count value of the RTC register increases every second
 */
void timestamp_init(void)
{
    uint32_t sec;
    uint32_t currSeconds;
    uint8_t index;
    rtc_datetime_t date;

    /* Enable the RTC 32K Oscillator */
    SYSCON->RTCOSCCTRL |= SYSCON_RTCOSCCTRL_EN_MASK;


    /* Init RTC */
    RTC_Init(RTC);

//    PRINTF("RTC example: set up time to wake up an alarm\r\n");

    /* Set a start date time and start RT TODO must be sychronised with server*/
    date.year   = 2023U;
    date.month  = 8U;
    date.day    = 12;
    date.hour   = 19U;
    date.minute = 0;
    date.second = 0;
    /* RTC time counter has to be stopped before setting the date & time in the TSR register */

    /* Configure and start the SNTP client */
//    sntp_setoperatingmode(SNTP_OPMODE_POLL);
//    sntp_setservername(0, SNTP_SERVER_NAME);
//    sntp_init();


    RTC_EnableTimer(RTC, false);

    /* Set RTC time to default */
    RTC_SetDatetime(RTC, &date);

    /* When working under Normal Mode, the interrupt is controlled by NVIC. */
    EnableIRQ(RTC_IRQn);


    /* Start the RTC time counter */
    RTC_EnableTimer(RTC, true);
    RTC_SetSecondsTimerMatch(RTC, 	(RTC->COUNT)+1);

    /** INit cycle counter */
    uint32_t cycles; /* number of cycles */

    KIN1_InitCycleCounter(); /* enable DWT hardware */
    KIN1_ResetCycleCounter(); /* reset cycle counter */
    KIN1_EnableCycleCounter(); /* start counting */
    timestamp_dividend = (CYCLE_CLOCK_FREQUENCY)/TIMESTAMP_RES; /**< norm the clock value to the desired time resolution, in this case 100µs and bring in the true measured frequency of the Main Clock*/
//    timestamp_dividend = (CYCLE_CLOCK_FREQUENCY * 1.001)/TIMESTAMP_RES; /**< norm the clock value to the desired time resolution, in this case 100µs and bring in the true measured frequency of the Main Clock*/
    starttime =  KIN1_GetCycleCounter();
	time_ref_for_milli = KIN1_GetCycleCounter();


}



timestamp_t timestamp_before;
/**
 * @fn timestamp_t getTimestamp()
 * @brief gives a measurement a timestamp
 *
 * @return
// */
//timestamp_t getTimestamp_INT() //TODO
int64_t getTimestamp_INT() //TODO
{

	uint32_t microseconds;
	timestamp_t retval;
	int64_t retval_int64;


	/** get seconds from RTC */
	retval.seconds = RTC->COUNT;
	retval_int64 = (uint32_t)(RTC->COUNT);
	retval_int64 = retval_int64*1000000;

	/** if next second begins, set a new the mico second reference */
	if (retval.seconds > timestamp_before.seconds){

		/**Set counter value reference for measuring time in microseconds, resets every second*/
		time_ref_for_milli = KIN1_GetCycleCounter();
	}


	/**get microseconds from cycle clock */
	/** have to be uint, to igonre carry if the time_ref_for_milli is bigger tahn the actual value */
	microseconds  =(KIN1_GetCycleCounter() - time_ref_for_milli);
	double micro_cal = ((double)microseconds);
	micro_cal = (micro_cal)/(timestamp_dividend);
	/** rounding */
	if (fmod(micro_cal,1) > 0.5)
	{
		micro_cal = ceil(micro_cal);
	}
	else
	{
		micro_cal = floor(micro_cal);
	}

	/** zero based counting */
	retval.microseconds  = (uint32_t)(micro_cal-1);




	/** prevent microseconds to exeed a whole second, can happen because of unsychronity of cycle counter and RTC */
	if (retval.microseconds >= TIMESTAMP_RES){
		retval.microseconds = TIMESTAMP_RES -1; //TODO
	}
//	printf("seconds:	%i\r\n",retval.seconds);
//	printf("microseconds:	%i\r\n",retval.microseconds);
	timestamp_before.seconds = retval.seconds;
	timestamp_before.microseconds = retval.microseconds;
	retval_int64 = retval_int64 + retval.microseconds;
//	printf("timestamp:	%i\r\n",retval_int64);

//	return retval;
	return retval_int64;
}


double getTimestamp_DOUBLE()
{

	double  microseconds;
	uint32_t seconds;
	double retval;


	/** get seconds from RTC */
	seconds= (RTC->COUNT);


	/** if next second begins, set a new the mico second reference */
	if (seconds > timestamp_before.seconds){

		/**Set counter value reference for measuring time in microseconds, resets every second*/
		time_ref_for_milli = KIN1_GetCycleCounter();
	}



	/**get microseconds from cycle clock */
	microseconds  = (double)(KIN1_GetCycleCounter() - time_ref_for_milli);
	/** counter value to microseconds */
	microseconds = (microseconds)/(timestamp_dividend);

	//TODO check the result if its correct
	retval = (double)seconds + microseconds;




	timestamp_before.seconds = seconds;
	timestamp_before.microseconds = microseconds;

	return retval;
}



