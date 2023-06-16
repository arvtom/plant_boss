# plant_boss
The purpose of this project is to demonstrate my skills as Embedded software engineer and Technical lead. I wanted to learn SW development on ESP32 with freeRTOS, power saving techniques, requirements engineering.  

Different soil characteristics monitoring and sending to sqlite database using esp32. Raspberry pi will be used as a database, webpage on local network, notification server.

# Client / esp32 requirements

Management Rx -> system Rx.x -> Hardware (Rx.x.xHW) / software (Rx.x.xSW) requirements:  
No.      | Management | System | Hardware / Software
---      | --- | --- | ---
Rx       |   Different device operation modes.
Rx.x     ||  In normal operation mode, device wakes up every 1h, measures sensors and sends data to server.
Rx.x.xSW ||| This is default operation mode, but can be toggled by user button.
Rx.x.xSW ||| Mode is indicated with user LED blink sequence of 10Hz.
Rx.x     ||  In real time operation mode, device measures sensors and sends data to server every 1s.
Rx.x.xSW ||| This operation mode can be toggled by user button.
Rx.x     ||  User interface
Rx.x.xHW ||| User button to toggle operation modes.
Rx.x.xHW ||| User LED to indicate operation modes and errors.
Rx       |   Measure soil humidity.
Rx.x     ||  Measurement error up to 20%.
Rx.x.xSW ||| Use 12bit ADC.
Rx.x.xSW ||| Perform data averaging of 10 samples with 10 Hz sample frequency.
Rx.x.xSW ||| Calibrate humidity: measure how many grams of soil; how many grams of water was put in; allow adequate time for soil humidity to settle.
Rx.x.xHW ||| Anti-aliasing low pass filter before ADC.
Rx.x.xHW ||| Optimise PCBA design to seperate measurement and noisy areas.
Rx.x     ||  Measurement period 1h.
Rx.x.xSW ||| Use RTC timer interrupt.
Rx       |   Display actual humidity, 24h average and history in smartphone.
Rx.x     ||  Send actual humidity to database.
Rx.x     ||  Send data packet, which can be used as database entry.
Rx.x     ||  Data available only in local network.
Rx       |   Minimise data loss when server is temporarily unavailable.
Rx       |   Direct contact with humid soil should not damage the device.
Rx.x     ||  Resistance to corrosion from electrolysis.
Rx.x.xHW ||| Use capacitive sensor.
Rx.x.xHW ||| PCBA coating with water resistant material.
Rx       |   Powered by rechargable battery.
Rx.x     ||  Compensate from battery voltage. 
Rx.x.xSW ||| Define method.
Rx.x     ||  Implement voltage regulator. Optimise output voltage to use max range of battery discharge.
Rx       |   Battery life 1 year.
Rx.x     ||  Minimise current consumption.
Rx.x.xHW ||| Power down capacitive sensor between measurements.
Rx.x.xSW ||| Use MCU sleep mode.
Rx       |   BOM price up to 20 Eur.
Rx       |   Possibility to expand tracking of these parameters: temperature, UV/light, soil PH.
Rx.x     ||  Available GPIO pins.
Rx.x.xHW ||| 3x available ADC inputs.
Rx.x.xHW ||| Available SPI interface.
Rx.x.xHW ||| Available I2C interface.
Rx.x     ||  Available MCU resources.
Rx.x.xSW ||| Available flash space.
Rx.x.xSW ||| Available RAM.
Rx       |   Use good SW development practices.
Rx.x     ||  Use RTOS specific objects
Rx.x.xSW ||| Use threads, mutexes, semaphores, workqueues.
Rx.x.xSW ||| Use seperate threads for input, output, networking, memory, application tasks.
Rx.x     ||  Use principles of seperation to provide better SW flexibility.
Rx.x.xSW ||| Use seperate modules (.c/.h) for hardware parts (humidity, temperature, light sensors).
Rx       |   Error management.
Rx.x     ||  Detect errors.
Rx.x     ||  Indicate current errors for user.
Rx.x.xSW ||| Send current errors to server.
Rx.x     ||  Save current errors to NVRAM.
Rx.x     ||  Indicate current errors to server.
Rx.x     ||  If error is detected, enter safe state.
Rx.x.xSW ||| Enter sleep mode without waking up, to conserve battery.

# Server / raspberry pi requirements
Management Rx -> system Rx.x -> Hardware (Rx.x.xHW) / software (Rx.x.xSW) requirements:  
No.      | Management | System | Hardware / Software
---      | --- | --- | ---
Rx       |   Display actual humidity, 24h average and history in smartphone.
Rx.x     ||  Collect data into database.
Rx.x     ||  Recalculate 24h average and history after receiving new measurement.
Rx.x.xSW ||| Use sqlite database.
Rx.x     ||   Report if humidity reaches critical level.

# Requirement analysis
Important soil characteristics include:
* Humidity
* Temperature
* Light intensity from 400 to 700 nm
* Nitrogen, phosphorus, potassium amount
* Salinity
* PH

It was chosen to make 1st prototype with voltage regulator and li-ion battery. It is hard to evaluate battery lifetime theoretically. 2nd prototype could possibly be using directly lifepo4 battery, without voltage regulator.

Sony VTC6 18650 li-ion cell gives around 2500 mAh capacity at 3.3V cutoff, and 2875 mAh at 3V. Using 3V hardware cutoff would give 10% more battery capacity. Software cutoff / low battery notification could be sent at 3.3 V.

Possible component choices, having in mind battery voltage of 18650 li-ion cell:
* ESP32 (2.3 - 3.6V)
* HW-390 Capacitive soil moisture sensor v2.0 with 3.3V power supply modification (2 - 15 V).
* STLM20 or LM20BIM7 for temperature (2.4 - 5.5V)
* BH1750FVI (2.4 - 3.6V)

There are special voltage regulators which have low quiescent current, f.e. AP7343 as low as 35uA. This value would be quite acceptable, since it is close to esp32 deep sleep current of 5uA. With 3300mah 18650 cell in sleep mode would be around 9years life time (not evaluating wake ups).

Voltage regulator output voltage could be 2.5V (AP7343Q-25W5-7):
* It is enough for MCU and sensors with 0.1V reserve
* It is lower than battery voltage of 3 V
* It accomodates voltage regulator drop out voltage of up to 0.5V.

To measure battery voltage, voltage divider will be needed in either case, because adc reference voltage is 1.1V.

# BOM
T491A105K010AT, https://eu.mouser.com/ProductDetail/KEMET/T491A105K010AT?qs=AaRlLUpeMswm%2FLee9GNRtw%3D%3D

