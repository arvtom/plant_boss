# plant_boss
The purpose of this project is to demonstrate my skills as Embedded software engineer and Technical lead. I wanted to learn SW development on ESP32 with freeRTOS, HW/SW design techniques for battery power, requirements engineering.  

Abstract: plant environment (soil humidity, temperature, light) monitoring using custom designed battery powered esp32 device. Raspberry pi zero with custom linux is used for sqlite database, simple html webpage on local network, notification server. Telegram bot is used as UI to receive smartphone notifications and configure esp32 device.

esp32 device prototype:  
![alt text](https://github.com/arvtom/plant_boss/blob/main/pictures/pcba_1_plant_boss.png)  
![alt text](https://github.com/arvtom/plant_boss/blob/main/pictures/pcba_2_plant_boss.png)  

esp32 software architecture:  
![alt text](https://github.com/arvtom/plant_boss/blob/main/sw_esp32/architecture_plant_boss.png)  

Webpage is used to:
* Receive http post requests containing measured data from esp32
* Display measured and debug data from all esp32 devices
* Display plot of measured data
* Display settings for each esp32 device

![alt text](https://github.com/arvtom/plant_boss/blob/main/pictures/data_plant_boss.png)  
![alt text](https://github.com/arvtom/plant_boss/blob/main/pictures/plot_plant_boss.png)  
![alt text](https://github.com/arvtom/plant_boss/blob/main/pictures/settings_plant_boss.png)  


Telegram bot is used to:
* Modify esp32 device settings
* Display settings for each esp32 device
* Receive periodic notifications
* Receive high priority notifications

![alt text](https://github.com/arvtom/plant_boss/blob/main/pictures/telegram_bot_settings_1.jpg)  
![alt text](https://github.com/arvtom/plant_boss/blob/main/pictures/telegram_bot_settings_2.jpg)  

# TODOs
* Software rpi:
	* Debug custom built linux distro using buildroot. At the moment device boots up with no errors, but wifi driver is not found.
	* Notification
		* Add high priority notification when plant need to be watered. This would be processed on rpi side.
		* Add low priority notification with plant data table and plot.
	* Webpage
		* Add timestamps to plot
		* Possibility to change esp32 measurement period
		* Possibility to change esp32 battery critical voltage threshold.
		* Consider removing nginx
* Embedded software ESP32:
	* Focus on trimmed down version with proper error management.
	* Calibration constants in nvs.
	* Read device id from nvs.
	* Write and read errors from nvs.
	* Check flash crc.
	* Choose correct flash size.
	* Add possibility to change device id using telegram.
	* Add battery critical voltage detection, after which esp32 would go to sleep infinitely.
	* Error management for every object using individual bits.
	* Pointers to improve freeRTOS queue efficiency.
	* Dedicated thread sinchronization functions from freeRTOS during init.
	* Limit function and variable scope using static. Minimise global variables.
	* Use unions to access queue elements.
	* Use doxygen to check architecture and includes.
	* Architecture diagram with data flow.
	* Prevent multiple header inclusions using ifdef.
	* Sensors were tested with low, medium, high values. Now need to calibrate and test more accurately.
	* Get timer value, which stays on during sleep mode.
	* Real time / sleep modes.
	* Power from battery.
	* Current concumption optimisation.
	* Use mutexes / semaphores to protect critical code sections from other threads.
* HW changes in pcba design:
	* Reset pin does not properly work, getting SPI flash errors.
	* Choose new voltage regulator, which can supply 3V, have dropout voltage less than 0.3V and output current of 500 mA.
	* Voltage divider to measure battery voltage. Consider using mosfets, to prevent constant current draw through divider. Optimise divider series resistance.
	* Jumpers for boot strapping pins
	* Big jumper for reset (EN) pin
	* Battery holder terminals
	* Not all GPIO pins can be outputs. Change temperature and humidity vcc pins.
	* 1.27 mm connectors.
	* ESP32 placement with regard to light sensor.
	* Reverse polarity protection.
	* Protection of gpio pins, used as power supply. Consider using mosfets.
	* Consider using esp32 chip without WROOM package.
	* Consider placing humidity sensor on the same pcba.
	* Rewire external vcc to voltage regulator input
	* Low pass filters on adc inputs.
	* Series resistors on i2c to slow down edges.
	* Use possibility to route adc ref voltage to gpio pin for calibration purposes.

# Debugging using ESP-PROG
To improve reliability of debugging session, thread aware debugging should be turned off by giving additional argument to openocd call: -c 'set ESP_RTOS none'.

Full openocd command:
-s ${openocd_path}/share/openocd/scripts -c 'set ESP32_FLASH_VOLTAGE 3.3' -c 'set ESP_RTOS none' -f interface/ftdi/esp32_devkitj_v1.cfg -f target/esp32.cfg

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

Actually esp32 starts rebooting at power supply voltage lower than 2.5V. This is because lowest available brownout reset threshold voltage is 2.44 +- 0.05 V. Also ESP32-WROOM-32E-N4 contains external flash. For this reason minimal voltage for esp32 is 3V. Also current draw can be as high as 500 mA, so better voltage regulator needs to be chosen.

To measure battery voltage, voltage divider will be needed in either case, because adc reference voltage is 1.1V.

Voltage divider series resistance of 1 MOhm would mean up to 4.2 uA current. 750 kOhm and 240 kOhm will divide 4.2V battery voltage by 4, so up to 1.05 V will be applied to ADC input.

# Testing sensors and input signals
Following tests will be done with power supply voltage of 3 V.
* Light sensor
	* Low value: device is placed in completely dark space. Expected to see around 0 lx.
	* Medium value: device is placed under office lights. Expected to see around 200-500 lx.
	* High value: device is placed under direct sunlight on sunny day. Expected to see around 65000-100 000 lx depending on measurement mode.
* Temperature sensor:
	* Low value: device is placed inside fridge. Expected to see around 5-8 C temperature.
	* Medium value: device is placed in room temperature, expected to see around 21 C.
	* High value: device is placed under hot air station. Expected to see 100 C temperature.
* Humidity sensor:
	* Low value: device is placed on the table, only air surrounding sensor itself. Expected to see 0 % humidity.
	* Medium value: device is placed in flowerpot soil. Expected to see 20-60 % humidity.
	* High value: device is placed in glass of water. Expected to see 100 % humidity.
	* Minimum power supply voltage: should be as low as 2 V.
* Battery input voltage:
	* Low value: minimum 18650 li-ion cell voltage around 3 V.
	* Medium value: storage voltage around 3.7 V.
	* High value: fully charged voltage around 4.2 V.
