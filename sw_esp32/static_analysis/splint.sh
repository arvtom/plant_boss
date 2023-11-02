splint \
../plant_boss/src/* \
../plant_boss/drivers/* \
../plant_boss/wrappers/* \
+skip-sys-headers \
-sysdirs ~/esp/esp-idf/components \
-unrecog +show-summary +stats +trytorecover \
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
&> splint.txt

cat splint.txt