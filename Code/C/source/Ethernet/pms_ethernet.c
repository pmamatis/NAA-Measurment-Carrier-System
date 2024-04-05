

/**
 * @file pms_ethernet.c
 * @author Paul Mamatis
 * @version 1.0
 * @date  Jun 14, 2023
 *
 * @section DESCRIPTION
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include "Config/pms_config.h"

#if defined(ETHERNET)
#include "pms_ethernet.h"
#include "lwip/ip_addr.h"
#include "lwip/netif.h"
#include "board.h"

#include <stdio.h>
/*******************************************************************************
 * Definitions
 ******************************************************************************/


/*******************************************************************************
 * Prototypes
 ******************************************************************************/


/*******************************************************************************
 * Variables
 ******************************************************************************/

/*! @brief network interface struct, initialized in the Peripherals */
extern struct netif lwIP_netif0;
extern SemaphoreHandle_t sem_init;


/*******************************************************************************
 * Code
 ******************************************************************************/

/**
 * @brief Waits for the IP address to be assigned to the network interface.
 *        It continuously checks for a non-zero IP address and provides visual feedback.
 */
void waitForIP(){
    while (lwIP_netif0.ip_addr.addr == 0){
        // Check the IP address of the network interface

        // Wait for a short duration before checking again
        // You can adjust the delay based on your requirements
        // printf("getting IP...\r\n");
        LED1_TOGGLE(); // Toggles an LED to indicate waiting for IP
        vTaskDelay(pdMS_TO_TICKS(100)); // Delay for 100 milliseconds
        // sys_msleep(100U);
        // for (int i =0;i<100;i++);
    }


    // IP address obtained
#if defined(CONSOLE_DEBUG)
		printf("\r\nIPv4 Address     : %s\r\n", ipaddr_ntoa(&lwIP_netif0.ip_addr));
		printf("IPv4 Subnet mask : %s\r\n", ipaddr_ntoa(&lwIP_netif0.netmask));
		printf("IPv4 Gateway     : %s\r\n\r\n", ipaddr_ntoa(&lwIP_netif0.gw));
#endif

}


//extern struct netif lwIP_netif0;
/**
 * @brief Callback function called when lwIP stack initialization is completed.
 *        Currently empty and commented out.
 */
void tcpip_init_done(){
    // waitForIP();
}

#include "pms_config.h"
/**
 * @brief pre initialization function for the lwIP interface.
 *        Additional code can be placed here.
 */
void lwIP_interface_init(void){
    /* Place your code here */

    // Create a binary semaphore


};

#endif
