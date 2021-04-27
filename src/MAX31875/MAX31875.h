#ifndef _FTTECH_SAMD51_MAX31875_H_
#define _FTTECH_SAMD51_MAX31875_H_

#include "FTTech_Debug.h"

#include <Arduino.h>

/**************************************************************************/
/*!
    @brief  Class that stores state and functions for interacting with
   FTTech SAMD51 Clicks hardware
*/
/**************************************************************************/

class FTTech_SAMD51_MAX31875 {    
  public:

    /*!
      @brief configure sensor to read temperature
    */
    void begin(void);

    /*!
      @brief reads temperature and return it in Celsius
    */
    float readCelsius(void);


  private:
    bool initialized = false;

    // Slave and Register Addresses
    const uint8_t maxAddress = 0x48;          // (Datasheet) Table 1. I2C Slave Addresses
    const uint8_t tempRegAddress = 0x00;      // (Datasheet) Table 2. Register Functions and POR States
    const uint8_t configRegAddress = 0x01;    // (Datasheet) Table 2. Register Functions and POR States

    // Temperature Register
    const uint8_t tempReg[2] = {tempRegAddress, 0x00};

    // Configuration Register
    const uint8_t configReg[3] = {configRegAddress, 0x00, 01100110};


    /*!
      @brief reads temperature and return 16-bit raw temperature reading
    */
    int readRaw(void);

    /*!
      @brief This function send configuration setup to MAX sensor according to configReg
    */
    void configTemp(void);
    

    uint8_t  checkInitialize(void);

};

extern FTTech_SAMD51_MAX31875
    MAX31875; ///< instantiated by default

#endif
