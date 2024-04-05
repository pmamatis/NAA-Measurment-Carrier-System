
/**
* @file pms_ethernet.h
* @author Paul Mamatis
* @version 1.0
* @date  Jun 14, 2023
*
* @section DESCRIPTION TODO
*/
#ifndef ETHERNET_PMS_ETHERNET_H_
#define ETHERNET_PMS_ETHERNET_H_

#if defined(ETHERNET)
void tcpip_init_done();
void lwIP_interface_init(void);
void waitForIP();
#endif
#endif /* ETHERNET_PMS_ETHERNET_H_ */
