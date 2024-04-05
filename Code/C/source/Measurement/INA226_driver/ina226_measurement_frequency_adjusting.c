
/**
* @file ina226_measurement_frequency_adjusting.c
* @author Paul Mamatis
* @version 1.0
* @date  Jun 14, 2023
*
* @section DESCRIPTION TODO
*/



#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include "ina226_measurement_frequency_adjusting.h"


#define CONV_TIME_AMT 8		/**< number of values for bus and shunt voltage conversion time */
#define AVG_VALUES_AMT 8	/**< number of values for average configuration */

//double convTimefreq[] ={121, 240, 472, 909, 1700, 3012, 4901, 7142};/**< conversion time as frequency */
double convTimefreq[] ={7142, 4901, 3012, 1700, 909, 472, 240, 121};/**< conversion time as frequency */
double avg[] = {1, 4, 16, 64, 128, 256, 512, 1024};	/** average numbers as double */
INA226_VBUSCT_t vbusctArray[] = {
       VBUSCT_140us,
       VBUSCT_204us,
       VBUSCT_332us,
       VBUSCT_588us,
       VBUSCT_1100us,
       VBUSCT_2116us,
       VBUSCT_4156us,
       VBUSCT_8244us
   };
INA226_VSHCT_t vshctArray[] = {
        VSHCT_140us,
        VSHCT_204us,
        VSHCT_332us,
        VSHCT_588us,
        VSHCT_1100us,
        VSHCT_2116us,
        VSHCT_4156us,
        VSHCT_8244us
    };
INA226_NoA_t noaArray[] = {
      AVG_1,
      AVG_4,
      AVG_16,
      AVG_64,
      AVG_128,
      AVG_256,
      AVG_512,
      AVG_1024
  };


ina226_frequency_t frequencies[64];

/** Get the closest possible frequency to the desired one.
 * @attention getAllavailibleFreqs must have called before, otherwise the ina226_frequency_t frequencies is not filled.
 * @param measurement_frequency, desired frequency
 * @return index of the closest frequency which is bigger than the desired one
 */
uint8_t ina226_getClosestFreq(float measurement_frequency){
	int i = 0;
	if (measurement_frequency  < MAX_FREQ){
		while(measurement_frequency > frequencies[i].frequency){
			i++;
		}
#if defined(CONSOLE_DEBUG)
		printf("matching frequency for  %f Hz is %f Hz\n\r",measurement_frequency, frequencies[i].frequency);
#endif
		return i;
	}
	else {
#if (defined(INA226_DEBUG) & defined(CONSOLE_DEBUG))
		printf("ina226: given measurment frequency too high\r\n Setting default value\r\n");
#endif
		return 0xFF;
	}

}
/** fills the ina226_frequency_t frequencies[] with all available frequency calculated from conversion time in combination with avaraging
 *
 */
void ina226_getAllavailibleFreqs(){


	 int z = 0;
	 // get all availible frequencies by multiplying conversion times with average values
	 for (int i =0; i<CONV_TIME_AMT ;i++){
		 for (int j =0; j< AVG_VALUES_AMT ;j++){
			 frequencies[z].frequency = convTimefreq[i]/avg[j];
			 frequencies[z].config.avg = noaArray[j];
			 frequencies[z].config.shunt_time= vshctArray[i];
			 frequencies[z].config.bus_time= vbusctArray[i];
//			 printf("%f\r\n",frequencies[z].frequency);
			 z++;
		 }

	 }
	 uint8_t size = z;
	 //sort the array
	    for (int i = 0; i < size - 1; i++) {

	        for (int j = 0; j < size - i - 1; j++) {
	            if (frequencies[j].frequency  > frequencies[j+1].frequency)  {
//	            	printf("%i,%i: %f > %f\r\n",i,j,freq[j],freq[j+1]);
	                // Swap the elements if they are in the wrong order
	            	ina226_frequency_t temp = frequencies[j];
	            	frequencies[j]= frequencies[j + 1];
	            	frequencies[j+1] = temp;
	            }
	        }
	    }
	    uint8_t buffer[1000];
	    sprintf(buffer,"available frequencies in Hz:\n");
	    for (int i = 0; i < size; i++) {
	        sprintf(buffer,"%f | ", frequencies[i].frequency);
	    }
	    sprintf(buffer,"\n");
	    printf("%s\r\n",buffer);

}


