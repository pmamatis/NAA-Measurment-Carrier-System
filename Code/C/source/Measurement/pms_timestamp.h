/*
 * pms_timestamp.h
 *
 *  Created on: Aug 12, 2023
 *      Author: paul
 *
 * 	@brief TODO description
 */

#ifndef MEASUREMENT_RTC_H_
#define MEASUREMENT_RTC_H_



/*******************************************************************************
* Includes
*******************************************************************************/
#include "stdint.h"
/*******************************************************************************
* Defines
*******************************************************************************/


//#pragma pack(push,2)
typedef struct timestamp_t{
	uint32_t seconds;
	uint32_t microseconds;
}timestamp_t;
//#pragma pack(pop)



/*******************************************************************************
* Functions
*******************************************************************************/

void timestamp_init(void);
timestamp_t getTimestamp();

double getTimestamp_DOUBLE();
//timestamp_t getTimestamp_INT();
int64_t getTimestamp_INT(); //TODO


void set_initial_TIME(uint32_t time);




#endif /* MEASUREMENT_RTC_H_ */
