#ifndef _FTTECH_SAMD51CLICKS_H_
#define _FTTECH_SAMD51CLICKS_H_

#include "FTTech_Debug.h"

#include <Arduino.h>
#include <Adafruit_SleepyDog.h>
#include <MAX31875/MAX31875.h>


/**************************************************************************/
/*!
    @brief  Class that stores state and functions for interacting with
   FTTech SAMD51 Clicks hardware
*/
/**************************************************************************/

#define SIZE_OF_ARRAY(arr)                      { sizeof(arr)/sizeof(arr[0]); }

#define FTTECH_VERSION "1.3.3"

#ifdef __FTTECH_SMARTNODE_3S__
  #define QNTY_CLICKS 4
  #define CLICK_20PIN 4
#else
  #define QNTY_CLICKS 2
  #define CLICK_20PIN 2
#endif

#define AVERAGING_SAMPLES_1    0
#define AVERAGING_SAMPLES_2    1
#define AVERAGING_SAMPLES_4    2
#define AVERAGING_SAMPLES_8    3
#define AVERAGING_SAMPLES_16   4
#define AVERAGING_SAMPLES_32   5
#define AVERAGING_SAMPLES_64   6
#define AVERAGING_SAMPLES_128  7
#define AVERAGING_SAMPLES_256  8
#define AVERAGING_SAMPLES_512  9
#define AVERAGING_SAMPLES_1024 10

#define DEFAULT_AVERAGING_SAMPLES AVERAGING_SAMPLES_1
/**
  Datasheet Page 58, in the 9.5 NVM Software Calibration Area Mapping:
  "The NVM Software Calibration Area for temperature calibration parameters can not be written.
  The NVM Software Calibration Area for temperature calibration parameters can be read at address 0x00800100"

  In the path: `C:\Users\myUserName\AppData\Local\Arduino15\packages\adafruit\tools\CMSIS-Atmel\1.2.1\CMSIS\Device\ATMEL\samd51\include\samd51j20a.h`
  we can find the `NVMCTRL_TEMP_LOG_W0` defined as mentioned: 0x00800100. 
*/
#define NVMCTRL_TEMP_LOG NVMCTRL_TEMP_LOG_W0


class FTTech_SAMD51Clicks {
  public:

    char ChipID[33];

    /*!  
      @brief set to OFF all Click's power and get SAMD51 unique id. 
    */
    bool begin();

    /*!
      @brief set the specific click power to ON. Enable 3.3V
      to enable 5V you will ALSO need to use ON_5V.
      @param click the click id. You can find it written on the board.
    */
    void turnON(uint8_t click);

    /*!
      @brief set ALL click power pins to ON. Enable 3.3V
      to enable 5V you will ALSO need to use ON_5V.
    */
    void turnON(void);

    /*!
      @brief set the specific click power to OFF. Disable 3.3 and 5 V Output
      @param click  click id. You can find it written on the board.
    */
    void turnOFF(uint8_t click);

    /*!
      @brief set ALL click power pins to OFF. Disable 3.3 and 5 V Output
    */
    void turnOFF(void);

    /*!
      @brief set the 5V to ON. 
    */
    void turnON_5V(void);

    /*!
      @brief set the 5V to OFF. 
    */
    void turnOFF_5V(void);

    /*!
      @brief set ALL CS pins to HIGH, to disable the SPI slaves comunicaton.
    */
    void turnOFF_SPI(void);

    /*!
      @brief set specific CS pin to HIGH, to disable the SPI slave comunicaton.
      @param click the click id. You can find it written on the board.
    */
    void turnOFF_SPI(uint8_t click);

    /*!
      @brief set specific CS pin to LOW, to enable the SPI slave comunicaton.
      @param click the click id. You can find it written on the board.
    */
    void turnON_SPI(uint8_t click);

    /*!
      @brief Set the board to sleep for some amount of seconds.
      @param secs the total time that the board should sleep for.
      @warning Interrups will wake the board up, like when using
      attachInterrupt().
    */
    int sleepForSeconds(int secs);

    /*!
      @brief Set the board to sleep for some amount of seconds but let the 
      power on click four (4) for a while longer and wakes it up a while before
      because some comunication needs time to get in the network, so it will 
      enable the comunication click to do this while the rest is "sleeping"
      @param secs the total time that the board should sleep for.
      @param early_awekening the total seconds that the click 4 should be 
      awaked before the cpu and the time that it will still be powered the
      CPU sleeps. Default = 8 seconds
      @warning Interrups will wake the board up, like when using
      attachInterrupt().
    */
    int sleepWithComunication(int secs, int early_awekening = 8);

    /*!
      @brief reads battery on BATTERY and return current voltage already converted
    */
    float readBattery(void);

    float readCPUTemperature(void);
    float readCPUTemperature(uint8_t averege);


    void printBanner() {
      LOG1_FTTECH_PRINTLN(F(
        " ______   ______   ______   ______     ______     __  __" FTTECH_NEWLINE    
        "/\\  ___\\ /\\__  _\\ /\\__  _\\ /\\  ___\\   /\\  ___\\   /\\ \\_\\ \\" FTTECH_NEWLINE    
        "\\ \\  __\\ \\/_/\\ \\/ \\/_/\\ \\/ \\ \\  __\\   \\ \\ \\____  \\ \\  __ \\" FTTECH_NEWLINE 
        " \\ \\_\\      \\ \\_\\    \\ \\_\\  \\ \\_____\\  \\ \\_____\\  \\ \\_\\ \\_\\" FTTECH_NEWLINE
        "  \\/_/       \\/_/     \\/_/   \\/_____/   \\/_____/   \\/_/\\/_/  v" FTTECH_VERSION
      ));
    }

  private:
    uint32_t _R2 = 330000;
    uint32_t _R1 = 1000000;

    /*! 
    @def Validade if click parameter is within acceptable range
    @return:
       0: No problem
      -1: Parameter out of range
    */
    int8_t validadeClick(uint8_t click, uint8_t max_clicks = QNTY_CLICKS);
    uint8_t mapToClickPower(uint8_t click);
    uint8_t mapToClickSPI(uint8_t click);

    void initPowerPins(void);
    void initSPIPins(void);
    void getChipID(void);

    float convertDecToFrac(uint8_t val);
    float calculateTemperature(uint16_t TP, uint16_t TC);
    float getTempc(uint8_t averaging);

};

extern FTTech_SAMD51Clicks
    FTClicks; ///< instantiated by default

#endif
