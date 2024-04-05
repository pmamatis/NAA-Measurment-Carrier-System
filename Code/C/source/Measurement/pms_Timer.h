/*
 * NAA_Timer.h
 *
 *  Created on: Sep 8, 2022
 *      Author: paul
 */

#ifndef NAA_TIMER_H_
#define NAA_TIMER_H_
#include <stdint.h>


#define RIT_IRQ_ID RIT_IRQn


/* Get source clock for RIT driver */
#define RIT_SOURCE_CLOCK CLOCK_GetFreq(kCLOCK_CoreSysClk)

#define MEASUREMENT_RIT_HANDLER  RIT_IRQHandler
/* Definition of the timer period in number of ticks */
#define RIT_DEVIDER (1500) // 1k Hz bei clock 180 MHz, is also the measurement frequency
//#define RIT_DEVIDER 10
#define RIT_TICKS_PER_MINUTE (RIT_SOURCE_CLOCK/RIT_DEVIDER)


void pms_timer_init();
void RIT_IRQHandler(void);





#endif /* NAA_TIMER_H_ */
