/**
* @file TODO
* @author Paul Mamatis
* @version 1.0
* @date  Jun 14, 2023
*
* @section DESCRIPTION TODO
*/


/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "Config/pms_config.h"
#include "Config/pms_control_commands.h"

#if defined(MQTT)

#include <Ethernet/pms_mqtt_wrapper.h>
#include "lwipopts.h"

#include "fsl_silicon_id.h"
#include "lwip/api.h"
#include "lwip/tcpip.h"

#include "fsl_debug_console.h"

#include "message_buffer.h"

/** for LED switching */
#include "board.h"

/** PMS Files */
#include <Measurement/pms_measurement.h>
#include "Ethernet/pms_ethernet.h"
#include "Measurement/pms_timestamp.h"

/** Controlling */
#include "Controller/control_task.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief MQTT server host name or IP address. */
//#define MQTT_SERVER_HOST "192.168.178.33"
//#define MQTT_SERVER_HOST "192.168.1.24"
//#define MQTT_SERVER_HOST "172.24.10.168"
#define MQTT_SERVER_HOST "172.24.10.176"

/*! @brief MQTT server port number. */
#define MQTT_SERVER_PORT 1883



/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void connect_to_mqtt(void *ctx);
static void mqtt_connection_cb(mqtt_client_t *client, void *arg, mqtt_connection_status_t status);
static void mqtt_incoming_data_cb(void *arg, const u8_t *data, u16_t len, u8_t flags);
static void mqtt_incoming_publish_cb(void *arg, const char *topic, u32_t tot_len);
static void mqtt_topic_subscribed_cb(void *arg, err_t err);
static void mqtt_message_published_cb_log(void *arg, err_t err);
static void publish_message(void *ctx);

static void mqtt_message_published_cb(void *arg, err_t err);
static void generate_client_id(void);

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*! @brief MQTT client data. */
mqtt_client_t *mqtt_client;


extern SemaphoreHandle_t sem_pub;

extern SemaphoreHandle_t sem_log;


/*! @brief MQTT client ID string. */
static char client_id[(SILICONID_MAX_LENGTH * 2) + 5];

/*! @brief MQTT broker IP address. */
static ip_addr_t mqtt_addr;

/*! @brief Indicates connection to MQTT broker. */
static volatile bool connected = false;

/*! @brief MQTT client information. */
static const struct mqtt_connect_client_info_t mqtt_client_info = {
    .client_id   = (const char *)&client_id[0],
    .client_user = NULL,
    .client_pass = NULL,
    .keep_alive  = 100,
    .will_topic  = NULL,
    .will_msg    = NULL,
    .will_qos    = 0,
    .will_retain = 0,
#if LWIP_ALTCP && LWIP_ALTCP_TLS
    .tls_config = NULL,
#endif
};

/** @brief */
mqtt_msg_t mqtt_msg;


/** incoming MQTT messages queue */
extern MessageBufferHandle_t subsription_subtopic;
extern MessageBufferHandle_t subsription_msg;

#if defined (COLLECT_META_DATA)
extern transmission_meta_data_t meta_data;
#endif
/*******************************************************************************
 * Code
 ******************************************************************************/

/**
 * @brief Generates a client ID string based on the unique ID of the SoC.
 *
 */
void generate_client_id(void)
{
    uint8_t silicon_id[SILICONID_MAX_LENGTH];
    uint32_t id_len;
//    int idx = 0;
//    int i;
//
//    /* Get unique ID of SoC */
    SILICONID_GetID(&silicon_id[0], &id_len);

    char* macAddr_str = "54.27.8d";
    sprintf(macAddr_str,"%s.%x.%x.%x",macAddr_str,silicon_id[0],silicon_id[1],silicon_id[2]);
    strcpy(client_id,macAddr_str);
    printf("MAC Address: %s\r\n",client_id);

}

/*!
 * @brief Starts connecting to MQTT broker. To be called on tcpip_thread.
 */
static void connect_to_mqtt(void *ctx)
{
    LWIP_UNUSED_ARG(ctx);

    printf("Connecting to MQTT broker at %s...\r\n", ipaddr_ntoa(&mqtt_addr));

    mqtt_client_connect(mqtt_client, &mqtt_addr, MQTT_SERVER_PORT, mqtt_connection_cb,
                        LWIP_CONST_CAST(void *, &mqtt_client_info), &mqtt_client_info);


	#ifdef SEM_DEBUG
			printf("SEM DEBUG: ----GIVE Init Semaphore in connect_to_mqtt----\r\n");
			// Print the current count of the semaphore
			printf("SEM DEBUG: ----SemCount = %i----\n\r", uxSemaphoreGetCount(sem_init));
	#endif


}

/*!
 * @brief Called when connection state changes. TODO abfangen wenn er nicht mit dem broker verbindet
 */
static void mqtt_connection_cb(mqtt_client_t *client, void *arg, mqtt_connection_status_t status)
{
    const struct mqtt_connect_client_info_t *client_info = (const struct mqtt_connect_client_info_t *)arg;

    connected = (status == MQTT_CONNECT_ACCEPTED);

    switch (status)
    {
        case MQTT_CONNECT_ACCEPTED:
            PRINTF("MQTT client \"%s\" connected.\r\n", client_info->client_id);
            mqtt_subscribe_topics(client);

            /** if connection is etablished, create message buffer */

           	xSemaphoreGive(sem_pub);
            break;

        case MQTT_CONNECT_DISCONNECTED:
            PRINTF("MQTT client \"%s\" not connected.\r\n", client_info->client_id);
            /* Try to reconnect 1 second later */
            sys_timeout(1000, connect_to_mqtt, NULL);
            break;

        case MQTT_CONNECT_TIMEOUT:
            PRINTF("MQTT client \"%s\" connection timeout.\r\n", client_info->client_id);
            /* Try again 1 second later */
            sys_timeout(1000, connect_to_mqtt, NULL);
            break;

        case MQTT_CONNECT_REFUSED_PROTOCOL_VERSION:
        case MQTT_CONNECT_REFUSED_IDENTIFIER:
        case MQTT_CONNECT_REFUSED_SERVER:
        case MQTT_CONNECT_REFUSED_USERNAME_PASS:
        case MQTT_CONNECT_REFUSED_NOT_AUTHORIZED_:
            PRINTF("MQTT client \"%s\" connection refused: %d.\r\n", client_info->client_id, (int)status);
            /* Try again 10 seconds later */
            sys_timeout(10000, connect_to_mqtt, NULL);
            break;

        default:
            PRINTF("MQTT client \"%s\" connection status: %d.\r\n", client_info->client_id, (int)status);
            /* Try again 10 seconds later */
            sys_timeout(10000, connect_to_mqtt, NULL);
            break;
    }

}


/*!
 * @brief Subscribe to MQTT topics.
 */
void mqtt_subscribe_topics(mqtt_client_t *client)
{
    static const char *topics[] = {CONFIG_TOPIC};
    int qos[]                   = {2};
    err_t err;
    int i;

    mqtt_set_inpub_callback(client, mqtt_incoming_publish_cb, mqtt_incoming_data_cb,
                            LWIP_CONST_CAST(void *, &mqtt_client_info));

    for (i = 0; i < ARRAY_SIZE(topics); i++)
    {
    	uint8_t* topic_str;
    	/** get topic  */
    	sprintf(topic_str, "%s/%s/#",topics[i],client_id);

    	/** add /# to the topic, to subscribe to all underlying topics of the main topic */
    	printf("topic to sucscribe: %s\r\n",topic_str);
        err = mqtt_subscribe(client, topic_str, qos[i], mqtt_topic_subscribed_cb, LWIP_CONST_CAST(void *, topics[i]));

        if (err == ERR_OK)
        {
            printf("Subscribing to the topic \"%s\" with QoS %d...\r\n", topics[i], qos[i]);
        }
        else
        {
        	printf("Failed to subscribe to the topic \"%s\" with QoS %d: %d.\r\n", topics[i], qos[i], err);
        }
    }
}

/**
 * @brief mqtt subscribe wrapper
 *
 * @param topic char pointer to topic name
 */
void mqtt_subscribe_topic(char* topic){
    LOCK_TCPIP_CORE();
	mqtt_subscribe(mqtt_client,topic, 2, mqtt_topic_subscribed_cb, LWIP_CONST_CAST(void *,topic));
	UNLOCK_TCPIP_CORE();
}




/*!
 * @brief Called when recieved incoming published message fragment.
 */
static void mqtt_incoming_data_cb(void *arg, const u8_t *data, u16_t len, u8_t flags)
{
    int i;
    uint8_t buffer[len+1];
    for (i = 0; i < len; i++){
    	buffer[i] = data[i];
    }

    /** adding \0 do the msg string */
    buffer[len] = 0;


xMessageBufferSendFromISR(subsription_msg,buffer,(len+1),pdFALSE);
//    LWIP_UNUSED_ARG(arg);
//    for (i = 0; i < len; i++)
//    {
//        if (isprint(data[i]))
//        {
//            PRINTF("%c", (char)data[i]);
//        }
//        else
//        {
//            PRINTF("\\x%02x", data[i]);
//        }
//    }
//
//    if (flags & MQTT_DATA_FLAG_LAST)
//    {
//        PRINTF("\"\r\n");
//    }

}




/*!
 * @brief Called when there is a message on a subscribed topic.
 */
static void mqtt_incoming_publish_cb(void *arg, const char *topic, u32_t tot_len)
{
    LWIP_UNUSED_ARG(arg);
    uint8_t len = strlen(topic);
    xMessageBufferSendFromISR(subsription_subtopic,topic,len,pdFALSE);
//    printf("Received %u bytes from the topic \"%s\": \"", tot_len, topic);


}

/*!
 * @brief Called when subscription request finishes.
 */
static void mqtt_topic_subscribed_cb(void *arg, err_t err)
{
    const char *topic = (const char *)arg;

    if (err == ERR_OK)
    {
        PRINTF("Subscribed to the topic \"%s\".\r\n", topic);
    }
    else
    {
        PRINTF("Failed to subscribe to the topic \"%s\": %d.\r\n", topic, err);
    }

//    publish_mqtt_msg_string("Config", client_id, 30);
}

unsigned int mqtt_send;
/*!
 * @brief Called when publish request finishes.
 */
timestamp_t timestamp ;


static void mqtt_message_published_cb(void *arg, err_t err)
{
    const char *topic = (const char *)arg;

#if defined (COLLECT_META_DATA)
    meta_data.mqtt_send++;
#endif

    xSemaphoreGiveFromISR(sem_pub,pdFALSE);

    if (err != ERR_OK){
    	PRINTF("Failed to publish to the topic \"%s\": %d.\r\n", topic, err);
    }

}


static void mqtt_message_published_cb_log(void *arg, err_t err)
{
    const char *topic = (const char *)arg;

    if (err != ERR_OK){
    	PRINTF("Failed to publish to the topic \"%s\": %d.\r\n", topic, err);
    }

    xSemaphoreGiveFromISR(sem_log,pdFALSE);

#ifdef SEM_DEBUG
		printf("SEM DEBUG: ----GIVE publish Semaphore in mqtt_message_published_cb  ----\r\n");
		// Print the current count of the semaphore
		printf("SEM DEBUG: ----SemCount = %i----\n\r", uxSemaphoreGetCount(sem_init));
#endif
}



/*!
 * @brief Publishes a message. To be called on tcpip_thread.
 */
static void publish_message(void* ctx)
{

	/*ctx is the variable passed from tcpip_callback function,
	 with the following implementation it is unused because a static struct is defined and filled with the meassage information somewhere else */
    LWIP_UNUSED_ARG(ctx);
    //TODO was mache ich mit mqtt_message_published_cb?
mqtt_publish(mqtt_client, mqtt_msg.topic, mqtt_msg.payload_ptr, mqtt_msg.length, MQTT_QoS, 0, mqtt_message_published_cb, mqtt_msg.topic);
}

/*!
 * @brief Publishes a message. To be called on tcpip_thread.
 */
static void publish_message_log(void* ctx)
{

	/*ctx is the variable passed from tcpip_callback function,
	 with the following implementation it is unused because a static struct is defined and filled with the meassage information somewhere else */
    LWIP_UNUSED_ARG(ctx);
    //TODO was mache ich mit mqtt_message_published_cb?
mqtt_publish(mqtt_client, mqtt_msg.topic, mqtt_msg.payload_ptr, mqtt_msg.length, 2, 0, mqtt_message_published_cb_log, mqtt_msg.topic);
}





/**
 * @fn void publish_mqtt_msg_measurement(char*, measurement_data_t*)
 * @brief function to push a chunk of measurment data to a bmqtt broker
 *
 * @param topic
 * @param payload
 */

#if defined (DATA_CHUNKING)
typedef struct advanced_payload_t{
	uint32_t Chunks;
	measurement_data_t* payload;
}advanced_payload_t;
advanced_payload_t advanced_payload;

void publish_mqtt_msg_measurement(char* topic, measurement_data_t  *payload)
{

	/** get topic string ptr, make sure topic ptr is referencing to a static string */
    mqtt_msg.topic = topic;

	/** get length of data in bytes, mqtt sends byte-wise */
	mqtt_msg.length =  sizeof(measurement_data_t) * STREAM_BUFF_TRIG_LVL;
//	mqtt_msg.length =  sizeof(advanced_payload.Chunks)+ sizeof(measurement_data_t) * STREAM_BUFF_TRIG_LVL;

	/** adding the number of chunks on top of everypayload */
	advanced_payload.Chunks = STREAM_BUFF_TRIG_LVL;
	advanced_payload.payload = payload;

	/** set ptr for mqtt_publish which is called in the tcpip thread via the following tcpip_callback  */
//	mqtt_msg.payload_ptr = (void*) &advanced_payload;
	mqtt_msg.payload_ptr = (void*) payload;

//	for (int i = 0; i < (sizeof(measurement_data_t)/4)*STREAM_BUFF_TRIG_LVL;i++){
//		float number = (float)(*((float*)payload + (i)));
//		printf("%f\r\n",number);
//	}
//	printf("\r\n");

	/** call publish_message inside tcpip thread via callback */
	err_enum_t err = tcpip_callback(publish_message,NULL);
	if (err != ERR_OK)
	{
		PRINTF("Failed to invoke publishing of a message on the tcpip_thread: %d.\r\n", err);
	}
}
#else
void publish_mqtt_msg_measurement(char* topic, measurement_payload  *payload)
{

	/** get topic string ptr, make sure topic ptr is referencing to a static string */
    mqtt_msg.topic = topic;

	/** get length of data in bytes, mqtt sends byte-wise */
	mqtt_msg.length =  sizeof(measurement_payload);

	/** set ptr for mqtt_publish which is called in the tcpip thread via the following tcpip_callback  */
	mqtt_msg.payload_ptr = (void*) payload;

	/** call publish_message inside tcpip thread via callback */
	err_enum_t err = tcpip_callback(publish_message,NULL);
	if (err != ERR_OK)
	{
		PRINTF("Failed to invoke publishing of a message on the tcpip_thread: %d.\r\n", err);
	}
}
#endif


/**
 * TODO implemtier DAS
 * @param topic
 * @param payload
 */
void publish_mqtt_msg_string(char* topic,char* payload, size_t size ){

	/** get topic string ptr, make sure topic ptr is referencing to a static string */
    mqtt_msg.topic = topic;

	/** get length of data in bytes, mqtt sends byte-wise */
	mqtt_msg.length =  size;

	/** set ptr for mqtt_publish which is called in the tcpip thread via the following tcpip_callback  */
	mqtt_msg.payload_ptr = (void*) payload;
	/** call publish_message inside tcpip thread via callback */
	err_enum_t err = tcpip_callback(publish_message_log,NULL);
	if (err != ERR_OK)
	{
		PRINTF("Failed to invoke publishing of a message on the tcpip_thread: %d.\r\n", err);
	}
}
/**
 * initilasition function, should only be called from inside a task
 */
void mqtt_init(){
	//init MQTT
		waitForIP();
		LED1_ON();
//


	    generate_client_id();

	    LOCK_TCPIP_CORE();
	    mqtt_client = mqtt_client_new();
	    UNLOCK_TCPIP_CORE();

	    if (mqtt_client == NULL)
	    {
	        PRINTF("mqtt_client_new() failed.\r\n");
	        while (1)
	        {
	        }
	    }

	    /*
	         * Check if we have an IP address or host name string configured.
	         * Could just call netconn_gethostbyname() on both IP address or host name,
	         * but we want to print some info if goint to resolve it.
	         */
	    err_t err;
	    if (ipaddr_aton(MQTT_SERVER_HOST, &mqtt_addr) && IP_IS_V4(&mqtt_addr))
	        {
	            /* Already an IP address */
	            err = ERR_OK;
	        }
		else
		{
			/* Resolve MQTT broker's host name to an IP address */
			PRINTF("Resolving \"%s\"...\r\n", MQTT_SERVER_HOST);
//			err = netconn_gethostbyname(MQTT_SERVER_HOST, &mqtt_addr);
		}

		if (err == ERR_OK)
		{
			/* Start connecting to MQTT broker from tcpip_thread */
			err = tcpip_callback(connect_to_mqtt, NULL);
			if (err != ERR_OK)
			{
				PRINTF("Failed to invoke broker connection on the tcpip_thread: %d.\r\n", err);

			}
		}
		else
		{
			PRINTF("Failed to obtain IP address: %d.\r\n", err);

		}




}


#endif
