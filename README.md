This is to be a bonsai tree monitor. It is a work in progress, currently using an Arduino Uno, the TFT LCD screen by Arduino, and the I2C Soil Moisture Sensor by Catnip Electronics.

Libraries used include:
SD.h (bulit-in)
SPI.h (bulit-in)
TFT.h (built-in)
Wire.h (built-in)
I2CSoilMoistureSensor.h by Apollon7 (https://github.com/Apollon77/I2CSoilMoistureSensor.git)

Todo:
-Add a display for graphing of soil moisture.
-Add display for when bonsai needs to be watered.
-Add solenoid valve for watering (maybe not solenoid)

Bugs: Some NULL error when compiling, doesn't seem to affect operation