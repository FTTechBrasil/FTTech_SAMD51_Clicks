#ifndef _FTTECH_SAMD51CLICKS_H_
#define _FTTECH_SAMD51CLICKS_H_

#include <Arduino.h>
#include <Adafruit_SleepyDog.h>
#include <MAX31875/MAX31875.h>
#include <ArduinoModbus/ArduinoModbus.h>

/**************************************************************************/
/*!
    @brief  Class that stores state and functions for interacting with
   FTTech SAMD51 Clicks hardware
*/
/**************************************************************************/

class FTTech_SAMD51Clicks {
  public:

    char ChipID[33];

    /*!  
      @brief set to OFF all Click's power and get SAMD51 unique id. 
    */
    bool begin(bool debug = false);

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
      @brief reads lipo battery on LIPO_BATTERY and return current voltage already converted
    */
    float readLipoBattery(void);

    /*!
      @brief reads lead acid battery on LEAD_BATTERY and return current voltage already converted
    */
    float readLeadAcidBattery(void);


  private:
    bool debug = false;
    uint32_t _R2 = 330000;
    uint32_t _R1 = 1000000;

    uint8_t mapToClickPower(uint8_t click);
    uint8_t mapToClickSPI(uint8_t click);

    float readBattery(uint8_t BatteryPin);

};

extern FTTech_SAMD51Clicks
    FTClicks; ///< instantiated by default

#endif
