splint \
../plant_boss/src/* \
../plant_boss/drivers/* \
../plant_boss/wrappers/* \
+skip-sys-headers \
-sysdirs ~/esp/esp-idf/components \
-unrecog +show-summary +stats -preproc \
-I ../plant_boss/inc \
-I ../plant_boss/drivers \
-I ../plant_boss/wrappers \
&> splint.txt

cat splint.txt