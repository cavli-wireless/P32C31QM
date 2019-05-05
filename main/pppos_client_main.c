#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event_loop.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "freertos/semphr.h"

#include "driver/uart.h"

#include "netif/ppp/pppos.h"
#include "netif/ppp/ppp.h"
#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include "lwip/netdb.h"
#include "lwip/dns.h"
#include "lwip/pppapi.h"

#include "mbedtls/platform.h"
#include "mbedtls/net.h"
#include "mbedtls/esp_debug.h"
#include "mbedtls/ssl.h"
#include "mbedtls/entropy.h"
#include "mbedtls/ctr_drbg.h"
#include "mbedtls/error.h"
#include "mbedtls/certs.h"

#include <esp_event.h>
// #include <esp_wifi.h>

#include "apps/sntp/sntp.h"
#include "cJSON.h"

#include "libGSM.h"

#include "lwip/api.h"
#include "lwip/err.h"
#include "lwip/netdb.h"

#include "mqtt_client.h"

static const char *TAG = "MQTTS_SAMPLE";

// const int CONNECTED_BIT = BIT0;

static esp_err_t mqtt_event_handler(esp_mqtt_event_handle_t event)
{
    esp_mqtt_client_handle_t client = event->client;
    int msg_id;
	const char *baseTopic = getIccid();
	const char *deviceRegMsg = "{'deviceStatus':'online'}";
    ESP_LOGI(TAG, "DEVICE ICCID: %s", getIccid());
    ESP_LOGI(TAG, "DEVICE IMEI: %s", getImei());
    // your_context_t *context = event->context;
    switch (event->event_id) {
        case MQTT_EVENT_CONNECTED:
            ESP_LOGI(TAG, "MQTT_EVENT_CONNECTED");
            msg_id = esp_mqtt_client_subscribe(client, baseTopic, 0);
            ESP_LOGI(TAG, "sent subscribe successful, msg_id=%d", msg_id);
            break;
        case MQTT_EVENT_DISCONNECTED:
            ESP_LOGI(TAG, "MQTT_EVENT_DISCONNECTED");
            break;
        case MQTT_EVENT_SUBSCRIBED:
            ESP_LOGI(TAG, "MQTT_EVENT_SUBSCRIBED, msg_id=%d", event->msg_id);
            msg_id = esp_mqtt_client_publish(client, baseTopic, deviceRegMsg, 0, 0, 0);
            ESP_LOGI(TAG, "sent publish successful, msg_id=%d", msg_id);
            break;
        case MQTT_EVENT_UNSUBSCRIBED:
            ESP_LOGI(TAG, "MQTT_EVENT_UNSUBSCRIBED, msg_id=%d", event->msg_id);
            break;
        case MQTT_EVENT_PUBLISHED:
            ESP_LOGI(TAG, "MQTT_EVENT_PUBLISHED, msg_id=%d", event->msg_id);
            break;
        case MQTT_EVENT_DATA:
            ESP_LOGI(TAG, "MQTT_EVENT_DATA");
            printf("TOPIC=%.*s\r\n", event->topic_len, event->topic);
            printf("DATA=%.*s\r\n", event->data_len, event->data);
            break;
        case MQTT_EVENT_ERROR:
            ESP_LOGI(TAG, "MQTT_EVENT_ERROR");
            break;
    }
    return ESP_OK;
}

static void mqtt_app_start()
{
    const esp_mqtt_client_config_t mqtt_cfg = {
        .uri = "mqtts://b-d4e31c95-fa8c-49c0-8212-24cda1549afe-1.mq.eu-west-1.amazonaws.com",
        .port = 8883,
        .username = "ht_mqtt",
        .password = "xdgeRES6Je7zdcqq",
		.client_id = getImei(),
        // for mqtt over ssl
        // .uri = "mqtt://api.emitter.io:8080", //for mqtt over tcp
        // .uri = "ws://api.emitter.io:8080", //for mqtt over websocket
        // .uri = "wss://api.emitter.io:443", //for mqtt over websocket secure
        .event_handle = mqtt_event_handler,
    };

    ESP_LOGI(TAG, "[APP] Free memory: %d bytes", esp_get_free_heap_size());
    esp_mqtt_client_handle_t client = esp_mqtt_client_init(&mqtt_cfg);
    esp_mqtt_client_start(client);
}

void app_main() {

    if (ppposInit() == 0) {
		ESP_LOGE("PPPoS EXAMPLE", "ERROR: GSM not initialized, HALTED");
		while (1) {
			vTaskDelay(1000 / portTICK_RATE_MS);
		}
	} 
	if (ppposStatus() == 1) {
		ESP_LOGE("PPPoS EXAMPLE", "INFO: PPP Connection Established");
		ESP_LOGI(TAG, "[APP] Startup..");
		ESP_LOGI(TAG, "[APP] Free memory: %d bytes", esp_get_free_heap_size());
		ESP_LOGI(TAG, "[APP] IDF version: %s", esp_get_idf_version());

		esp_log_level_set("*", ESP_LOG_INFO);
		esp_log_level_set("MQTT_CLIENT", ESP_LOG_VERBOSE);
		esp_log_level_set("TRANSPORT_TCP", ESP_LOG_VERBOSE);
		esp_log_level_set("TRANSPORT_SSL", ESP_LOG_VERBOSE);
		esp_log_level_set("TRANSPORT", ESP_LOG_VERBOSE);
		esp_log_level_set("OUTBOX", ESP_LOG_VERBOSE);

		nvs_flash_init();
		mqtt_app_start();

	} else if (ppposStatus() == 89) {
		ESP_LOGE("PPPoS EXAMPLE", "INFO: Modem IDLE for connection request");
	} else if (ppposStatus() == 98) {
		ESP_LOGE("PPPoS EXAMPLE", "INFO: Initializing PPP Connection");
	} else {
		ESP_LOGE("PPPoS EXAMPLE", "INFO: No Internet Connection");
	}
}