splint \
\
-preproc \
-unrecog \
\
-Dadc_cali_handle_t=int \
-Dadc_oneshot_chan_cfg_t=int \
-Dadc_cali_line_fitting_config_t=int \
-DSemaphoreHandle_t=int \
-DQueueHandle_t=int \
-DTaskHandle_t=int \
-DUBaseType_t=int \
-Dnvm_contents_t=int \
\
../plant_boss/src/* \
\
-I../plant_boss/inc \
\
&> splint.txt

cat splint.txt

# ../plant_boss/drivers/* \
# ../plant_boss/wrappers/* \
# -I../plant_boss/drivers \
# -I../plant_boss/wrappers \

# -D=int \