CPPCHECK="/home/arvydas/repo/cppcheck-2.13.0/build/bin/cppcheck"
LOG_FILE="./cppcheck.txt"

FLAGS="\
    --enable=all \
    "

$CPPCHECK --version &> $LOG_FILE

$CPPCHECK \
    $FLAGS \
    ../plant_boss/drivers \
    ../plant_boss/wrappers \
    ../plant_boss/src \
    ../plant_boss/main \
    &>> $LOG_FILE

cat $LOG_FILE