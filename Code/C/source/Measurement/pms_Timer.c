


#include <Measurement/pms_measurement.h>
#include <Measurement/pms_Timer.h>


/** Measurement includes */
#include "pms_HardwareCheck.h"
#include "I2C/pms_i2cWrapper_RTOS.h"

/** Timer includes */
#include "fsl_rit.h"
#include "fsl_clock.h"

/** Peripheral includes */
#include "pin_mux.h"
#include "board.h"
#include  "fsl_debug_console.h"

#include <stdio.h>
#include <stdbool.h>
/*******************************************************************************
 * Definitions
 ******************************************************************************/



/*******************************************************************************
 * Variables
 ******************************************************************************/
void measurementFromISR();




extern measurement_data_t data[3];
extern pms_ina226_pcie ina226_hardwareDataPCIE[I2C_HANDLER_AMT_PCIe];
extern  measurement_config_t *m_config;/**< struct which contains all configuration related to the measurement */

/*******************************************************************************
 * Code
 ******************************************************************************/



/**
 * Timer Interrupt
 */
extern measurement_data_t data[I2C_HANDLER_AMT_ALL];








/**
 * Sets up the Timer-Interrrupt for the INA226-Measurement
 */
void pms_timer_init(){
    /* Structure of initialize RIT */
    rit_config_t ritConfig;

    RIT_GetDefaultConfig(&ritConfig);

    /* Init rit module */
    RIT_Init(RIT, &ritConfig);


	uint64_t rit_freq = RIT_SOURCE_CLOCK/((uint64_t)(m_config->mfrequency));
	RIT_SetTimerCompare(RIT, rit_freq);

    /** Set to enable the Counter register auto clear to zero when the counter value equals the set period. */
    RIT_SetCountAutoClear(RIT, true);

    /** Enable at the NVIC */
    EnableIRQ(RIT_IRQ_ID);

}

void MEASUREMENT_RIT_HANDLER(void)
{
//	time2 = *((uint32_t*)0xE0001004);
    RIT_ClearStatusFlags(RIT, kRIT_TimerFlag);
//
	measurementFromISR();


//    int x = *((uint32_t*)0xE0001004);
//  printf("ticks:  %f \r\n" ,(time1-time2)/180e6);
    __DSB();

}
