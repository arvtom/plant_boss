CPPCHECK="/home/vscode/repo/cppcheck-2.13.0/build/bin/cppcheck"
MISRA="/home/vscode/repo/cppcheck-2.13.0/addons/misra.py"
LOG_FILE="./cppcheck.txt"

FLAGS_CPPCHECK="\
    --dump
    "

FLAGS_GCC="\
    -DESP_PLATFORM -DSOC_MMU_PAGE_SIZE=CONFIG_MMU_PAGE_SIZE -DUNITY_INCLUDE_CONFIG_H -D_GNU_SOURCE -D_POSIX_READER_WRITER_LOCKS \
    -DconfigENABLE_FREERTOS_DEBUG_OCDAWARE=1 \
    -I/workspaces/plant_boss/sw_esp32/plant_boss/build/config -I/workspaces/plant_boss/sw_esp32/plant_boss/main -I/workspaces/plant_boss/sw_esp32/plant_boss/drivers -I/workspaces/plant_boss/sw_esp32/plant_boss/wrappers -I/workspaces/plant_boss/sw_esp32/plant_boss/inc -I/root/esp/esp-idf/components/newlib/platform_include -I/root/esp/esp-idf/components/freertos/FreeRTOS-Kernel/include -I/root/esp/esp-idf/components/freertos/FreeRTOS-Kernel/portable/xtensa/include -I/root/esp/esp-idf/components/freertos/esp_additions/include/freertos -I/root/esp/esp-idf/components/freertos/esp_additions/include -I/root/esp/esp-idf/components/freertos/esp_additions/arch/xtensa/include -I/root/esp/esp-idf/components/esp_hw_support/include -I/root/esp/esp-idf/components/esp_hw_support/include/soc -I/root/esp/esp-idf/components/esp_hw_support/include/soc/esp32 -I/root/esp/esp-idf/components/esp_hw_support/port/esp32/. -I/root/esp/esp-idf/components/esp_hw_support/port/esp32/private_include -I/root/esp/esp-idf/components/heap/include -I/root/esp/esp-idf/components/log/include -I/root/esp/esp-idf/components/soc/include -I/root/esp/esp-idf/components/soc/esp32 -I/root/esp/esp-idf/components/soc/esp32/include -I/root/esp/esp-idf/components/hal/esp32/include -I/root/esp/esp-idf/components/hal/include -I/root/esp/esp-idf/components/hal/platform_port/include -I/root/esp/esp-idf/components/esp_rom/include -I/root/esp/esp-idf/components/esp_rom/include/esp32 -I/root/esp/esp-idf/components/esp_rom/esp32 -I/root/esp/esp-idf/components/esp_common/include -I/root/esp/esp-idf/components/esp_system/include -I/root/esp/esp-idf/components/esp_system/port/soc -I/root/esp/esp-idf/components/esp_system/port/include/private -I/root/esp/esp-idf/components/xtensa/include -I/root/esp/esp-idf/components/xtensa/esp32/include -I/root/esp/esp-idf/components/lwip/include -I/root/esp/esp-idf/components/lwip/include/apps -I/root/esp/esp-idf/components/lwip/include/apps/sntp -I/root/esp/esp-idf/components/lwip/lwip/src/include -I/root/esp/esp-idf/components/lwip/port/include -I/root/esp/esp-idf/components/lwip/port/freertos/include -I/root/esp/esp-idf/components/lwip/port/esp32xx/include -I/root/esp/esp-idf/components/lwip/port/esp32xx/include/arch -I/root/esp/esp-idf/components/esp_ringbuf/include -I/root/esp/esp-idf/components/efuse/include -I/root/esp/esp-idf/components/efuse/esp32/include -I/root/esp/esp-idf/components/driver/include -I/root/esp/esp-idf/components/driver/deprecated -I/root/esp/esp-idf/components/driver/analog_comparator/include -I/root/esp/esp-idf/components/driver/dac/include -I/root/esp/esp-idf/components/driver/gpio/include -I/root/esp/esp-idf/components/driver/gptimer/include -I/root/esp/esp-idf/components/driver/i2c/include -I/root/esp/esp-idf/components/driver/i2s/include -I/root/esp/esp-idf/components/driver/ledc/include -I/root/esp/esp-idf/components/driver/mcpwm/include -I/root/esp/esp-idf/components/driver/parlio/include -I/root/esp/esp-idf/components/driver/pcnt/include -I/root/esp/esp-idf/components/driver/rmt/include -I/root/esp/esp-idf/components/driver/sdio_slave/include -I/root/esp/esp-idf/components/driver/sdmmc/include -I/root/esp/esp-idf/components/driver/sigma_delta/include -I/root/esp/esp-idf/components/driver/spi/include -I/root/esp/esp-idf/components/driver/temperature_sensor/include -I/root/esp/esp-idf/components/driver/touch_sensor/include -I/root/esp/esp-idf/components/driver/twai/include -I/root/esp/esp-idf/components/driver/uart/include -I/root/esp/esp-idf/components/driver/usb_serial_jtag/include -I/root/esp/esp-idf/components/driver/touch_sensor/esp32/include -I/root/esp/esp-idf/components/esp_pm/include -I/root/esp/esp-idf/components/mbedtls/port/include -I/root/esp/esp-idf/components/mbedtls/mbedtls/include -I/root/esp/esp-idf/components/mbedtls/mbedtls/library -I/root/esp/esp-idf/components/mbedtls/esp_crt_bundle/include -I/root/esp/esp-idf/components/mbedtls/mbedtls/3rdparty/everest/include -I/root/esp/esp-idf/components/mbedtls/mbedtls/3rdparty/p256-m -I/root/esp/esp-idf/components/mbedtls/mbedtls/3rdparty/p256-m/p256-m -I/root/esp/esp-idf/components/esp_app_format/include -I/root/esp/esp-idf/components/bootloader_support/include -I/root/esp/esp-idf/components/bootloader_support/bootloader_flash/include -I/root/esp/esp-idf/components/esp_partition/include -I/root/esp/esp-idf/components/app_update/include -I/root/esp/esp-idf/components/esp_mm/include -I/root/esp/esp-idf/components/spi_flash/include -I/root/esp/esp-idf/components/pthread/include -I/root/esp/esp-idf/components/esp_timer/include -I/root/esp/esp-idf/components/app_trace/include -I/root/esp/esp-idf/components/esp_event/include -I/root/esp/esp-idf/components/nvs_flash/include -I/root/esp/esp-idf/components/esp_phy/include -I/root/esp/esp-idf/components/esp_phy/esp32/include -I/root/esp/esp-idf/components/vfs/include -I/root/esp/esp-idf/components/esp_netif/include -I/root/esp/esp-idf/components/wpa_supplicant/include -I/root/esp/esp-idf/components/wpa_supplicant/port/include -I/root/esp/esp-idf/components/wpa_supplicant/esp_supplicant/include -I/root/esp/esp-idf/components/esp_coex/include -I/root/esp/esp-idf/components/esp_wifi/include -I/root/esp/esp-idf/components/esp_wifi/wifi_apps/include -I/root/esp/esp-idf/components/unity/include -I/root/esp/esp-idf/components/unity/unity/src -I/root/esp/esp-idf/components/cmock/CMock/src -I/root/esp/esp-idf/components/console -I/root/esp/esp-idf/components/http_parser -I/root/esp/esp-idf/components/esp-tls -I/root/esp/esp-idf/components/esp-tls/esp-tls-crypto -I/root/esp/esp-idf/components/esp_adc/include -I/root/esp/esp-idf/components/esp_adc/interface -I/root/esp/esp-idf/components/esp_adc/esp32/include -I/root/esp/esp-idf/components/esp_adc/deprecated/include -I/root/esp/esp-idf/components/esp_eth/include -I/root/esp/esp-idf/components/esp_gdbstub/include -I/root/esp/esp-idf/components/esp_hid/include -I/root/esp/esp-idf/components/tcp_transport/include -I/root/esp/esp-idf/components/esp_http_client/include -I/root/esp/esp-idf/components/esp_http_server/include -I/root/esp/esp-idf/components/esp_https_ota/include -I/root/esp/esp-idf/components/esp_psram/include -I/root/esp/esp-idf/components/esp_lcd/include -I/root/esp/esp-idf/components/esp_lcd/interface -I/root/esp/esp-idf/components/protobuf-c/protobuf-c -I/root/esp/esp-idf/components/protocomm/include/common -I/root/esp/esp-idf/components/protocomm/include/security -I/root/esp/esp-idf/components/protocomm/include/transports -I/root/esp/esp-idf/components/esp_local_ctrl/include -I/root/esp/esp-idf/components/espcoredump/include -I/root/esp/esp-idf/components/espcoredump/include/port/xtensa -I/root/esp/esp-idf/components/wear_levelling/include -I/root/esp/esp-idf/components/sdmmc/include -I/root/esp/esp-idf/components/fatfs/diskio -I/root/esp/esp-idf/components/fatfs/vfs -I/root/esp/esp-idf/components/fatfs/src -I/root/esp/esp-idf/components/idf_test/include -I/root/esp/esp-idf/components/idf_test/include/esp32 -I/root/esp/esp-idf/components/ieee802154/include -I/root/esp/esp-idf/components/json/cJSON -I/root/esp/esp-idf/components/mqtt/esp-mqtt/include -I/root/esp/esp-idf/components/perfmon/include -I/root/esp/esp-idf/components/spiffs/include -I/root/esp/esp-idf/components/wifi_provisioning/include \
    "

SOURCES="\
    ../plant_boss/drivers \
    ../plant_boss/wrappers \
    ../plant_boss/src \
    ../plant_boss/main
    "

HEADERS="
    -I ../plant_boss/drivers \
    -I ../plant_boss/wrappers \
    -I ../plant_boss/inc \
    -I ../plant_boss/main \
    -I ~/esp/esp-idf/components/log/include \
    -I ~/esp/esp-idf/components/freertos/FreeRTOS-Kernel/include/freertos
    "

# Print static analyser version
$CPPCHECK --version &> $LOG_FILE
printf "\n\n" &>> $LOG_FILE

# Execute cppcheck static analysis
$CPPCHECK \
    $FLAGS_CPPCHECK \
    $SOURCES \
    &>> $LOG_FILE
printf "\n\ncppcheck finished\n\n" &>> $LOG_FILE

# Execute MISRA static analysis
$CPPCHECK --dump $SOURCES
python3 $MISRA \
    /workspaces/plant_boss/sw_esp32/plant_boss/drivers/*.dump \
    /workspaces/plant_boss/sw_esp32/plant_boss/wrappers/*.dump \
    /workspaces/plant_boss/sw_esp32/plant_boss/src/*.dump \
    /workspaces/plant_boss/sw_esp32/plant_boss/main/*.dump \
    &>> $LOG_FILE
printf "\n\nmisra finished\n\n" &>> $LOG_FILE

cat $LOG_FILE