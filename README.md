# FTTech SAMD51 Clicks Arduino Library

Arduino's IDE Library to make our SAMD51 easier to use. Improved usability with common commands and parameters, better interface to sleeping methods and powering sensors.

Currently supports the following hardware:

*  FTTech SAMD51 Clicks board.

## Updates

* 1.2.1 Added board flag and examples
* 1.1.0 Minor improvements in modularity
* 1.0.0 First Release
* 0.8.0 Added [ArduinoModbus](https://github.com/arduino-libraries/ArduinoModbus) with RS485 contructor to RTUClient
* 0.7.0 Removed XBee and created another lib for it to improve modularity and reduce code complexity.
* 0.6.0 Improved XBee-Arduino package delivery by adding serial.flush();
* 0.5.0 Added several methods related to XBee-Arduino (they start with XBee)
* 0.4.0 Added dependency on [XBee-Arduino by Andrew Rapp](https://github.com/andrewrapp/xbee-arduino) to support XBee comuication
* 0.3.0 Added two methods related to Adafruit SleepyDog (sleepForSeconds, sleepWithComunication)
* 0.2.0 Added dependency on [Adafruit SleepyDog Library](https://github.com/adafruit/Adafruit_SleepyDog) to support sleeping and watchdog
* 0.1.0 Initial Release
