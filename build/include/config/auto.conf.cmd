deps_config := \
	/Users/johnmathew/esp/esp-idf/components/app_trace/Kconfig \
	/Users/johnmathew/esp/esp-idf/components/aws_iot/Kconfig \
	/Users/johnmathew/esp/esp-idf/components/bt/Kconfig \
	/Users/johnmathew/esp/esp-idf/components/driver/Kconfig \
	/Users/johnmathew/esp/esp-idf/components/esp32/Kconfig \
	/Users/johnmathew/esp/esp-idf/components/esp_adc_cal/Kconfig \
	/Users/johnmathew/esp/esp-idf/components/esp_http_client/Kconfig \
	/Users/johnmathew/esp/esp-idf/components/espmqtt/Kconfig \
	/Users/johnmathew/esp/esp-idf/components/ethernet/Kconfig \
	/Users/johnmathew/esp/esp-idf/components/fatfs/Kconfig \
	/Users/johnmathew/esp/esp-idf/components/freertos/Kconfig \
	/Users/johnmathew/esp/esp-idf/components/heap/Kconfig \
	/Users/johnmathew/esp/esp-idf/components/libsodium/Kconfig \
	/Users/johnmathew/esp/esp-idf/components/log/Kconfig \
	/Users/johnmathew/esp/esp-idf/components/lwip/Kconfig \
	/Users/johnmathew/Documents/Cavli_Wireless/HubbleThings/P32-Series/hubble-stack-P32/main/Kconfig \
	/Users/johnmathew/esp/esp-idf/components/mbedtls/Kconfig \
	/Users/johnmathew/esp/esp-idf/components/mdns/Kconfig \
	/Users/johnmathew/esp/esp-idf/components/openssl/Kconfig \
	/Users/johnmathew/esp/esp-idf/components/pthread/Kconfig \
	/Users/johnmathew/esp/esp-idf/components/spi_flash/Kconfig \
	/Users/johnmathew/esp/esp-idf/components/spiffs/Kconfig \
	/Users/johnmathew/esp/esp-idf/components/tcpip_adapter/Kconfig \
	/Users/johnmathew/esp/esp-idf/components/vfs/Kconfig \
	/Users/johnmathew/esp/esp-idf/components/wear_levelling/Kconfig \
	/Users/johnmathew/esp/esp-idf/Kconfig.compiler \
	/Users/johnmathew/esp/esp-idf/components/bootloader/Kconfig.projbuild \
	/Users/johnmathew/esp/esp-idf/components/esptool_py/Kconfig.projbuild \
	/Users/johnmathew/esp/esp-idf/components/partition_table/Kconfig.projbuild \
	/Users/johnmathew/esp/esp-idf/Kconfig

include/config/auto.conf: \
	$(deps_config)


$(deps_config): ;
