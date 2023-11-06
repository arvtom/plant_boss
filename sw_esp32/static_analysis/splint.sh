splint \
../plant_boss/src/* \
-I../plant_boss/inc \
-preproc \
&> splint.txt

cat splint.txt

# ../plant_boss/drivers/* \
# ../plant_boss/wrappers/* \
# -I../plant_boss/drivers \
# -I../plant_boss/wrappers \