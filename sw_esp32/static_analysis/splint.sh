splint \
../plant_boss/src/* \
../plant_boss/drivers/* \
../plant_boss/wrappers/* \
-unrecog +show-summary +stats \
-I ../plant_boss/inc \
-I ../plant_boss/drivers \
-I ../plant_boss/wrappers \
-I ~/esp/esp-idf/components/log/include \
-I ~/esp/esp-idf/components/freertos/FreeRTOS-Kernel/include \
-I ~/esp/esp-idf/components/esp_adc/include \
-I ~/esp/esp-idf/components/esp_common/include \
-I ~/esp/esp-idf/components/esp_hw_support/include \
-I ~/esp/esp-idf/components/nvs_flash/include \
-I ~/esp/esp-idf/components/esp_wifi/include \
-I ~/esp/esp-idf/components/esp_netif/include \
-I ~/esp/esp-idf/components/esp_http_client/include \
-I ~/esp/esp-idf/components/driver/include \
\
-I ~/esp/esp-idf/components/esp_rom/include \
-I ../plant_boss/build/config \
-I ~/esp/esp-idf/components/esp_adc/esp32/include \
-I ~/esp/esp-idf/components/hal/include \
-I ~/esp/esp-idf/components/soc/esp32/include \
-I ~/esp/esp-idf/components/freertos/esp_additions/include/freertos \
-I ~/esp/esp-idf/components/freertos/FreeRTOS-Kernel/portable/xtensa/include \
-I ~/esp/esp-idf/components/xtensa/esp32/include \
-I ~/esp/esp-idf/components/xtensa/include \
-I ~/esp/esp-idf/components/newlib/platform_include \
-I ~/esp/esp-idf/components/newlib/platform_include/sys \
-I ~/esp/esp-idf/components/esp_system/include \
-I ~/esp/esp-idf/components/heap/include \
-I ~/esp/esp-idf/components/esp_partition/include \
-I ~/esp/esp-idf/components/esp_event/include \
\
&> splint.txt

cat splint.txt