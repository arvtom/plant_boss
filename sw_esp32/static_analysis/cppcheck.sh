CPPCHECK="/home/arvydas/repo/cppcheck-2.13.0/build/bin/cppcheck"
LOG_FILE="./cppcheck.txt"

FLAGS="\
    --enable=all \
    --suppress=unusedFunction \
    --cppcheck-build-dir=./cppcheck_cache \
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
    -I ../plant_boss/inc
    -I ~/esp/esp-idf/components/log/include \
    -I ~/esp/esp-idf/components/freertos/FreeRTOS-Kernel/include/freertos
    "

# Print static analyser version
$CPPCHECK --version &> $LOG_FILE

# Execute static analysis
$CPPCHECK \
    $FLAGS \
    $HEADERS \
    $SOURCES \
    &>> $LOG_FILE

cat $LOG_FILE