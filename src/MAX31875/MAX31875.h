#ifndef _FTTECH_SAMD51_MAX31875_H_
#define _FTTECH_SAMD51_MAX31875_H_

#include "FTTech_Debug.h"

#include <Arduino.h>


/*!
 *  @brief  default I2C address
 */
#define MAX31875_ADDRESS (0x48)           // Primary I2C Address

/*!
 *  @brief Register addresses
 */
enum {
  MAX31875_REGISTER_TEMPDATA = 0x00,
  MAX31875_REGISTER_CONFIG = 0x01
};

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

    bool  init(void);


  private:
    bool initialized = false;



    // Temperature Register
    const uint8_t tempReg[2] = {MAX31875_REGISTER_TEMPDATA, 0x00};

    // Configuration Register
    const uint8_t configReg[3] = {MAX31875_REGISTER_CONFIG, 0x00, 0x66};


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
