#include "MAX31875/MAX31875.h"
#include <Wire.h>

/****************************************************************
 * PUBLIC FUNCTIONS
*****************************************************************/

void FTTech_SAMD51_MAX31875::begin(void)
{
  uint8_t error = configTemp();
  if(error)
  {
  #if DEBUG_FTTECH_SAMD51 >= 1
    DEBUG1_FTTECH_PRINTLN(F("Couldn't initialize sensor"));
  #endif
  }else
  {
    initialized = true;
  }
}


float FTTech_SAMD51_MAX31875::readCelsius(void)
{
  if(checkInitialize())
  {
    return -100;
  }

  int tempRaw = readRaw();
  
  if(tempRaw != 0)
  {
    return tempRaw/256.0;
  }
  else {
    #if DEBUG_FTTECH_SAMD51 >= 1
    DEBUG1_FTTECH_PRINTLN(F("Temperature Raw = 0"));
    #endif
    return -100;
  }
}

/*****************************************************************
 * PRIVATE FUNCTIONS
 ****************************************************************/

uint8_t FTTech_SAMD51_MAX31875::checkInitialize(void)
{
  if(!initialized)
  {
    #if DEBUG_FTTECH_SAMD51 >= 1
    DEBUG1_FTTECH_PRINTLN(F("Module not initialied."));
    #endif
    return 1;
  }
  return 0;
}

int FTTech_SAMD51_MAX31875::readRaw(void)
{
  int tempRaw = 0;
  
  // Point to the temperature register
  Wire.beginTransmission(maxAddress);
  Wire.write(tempReg[0]);
  Wire.write(tempReg[1]);
  Wire.endTransmission();
  
  // Wait for temperature readings to happen
  delay(100);
  
  // Request 2bytes from pointed register
  Wire.requestFrom(maxAddress, 2);
  
  // Read temperature reading from sensor
  if (2 <= Wire.available()) {    // if two bytes were received
    tempRaw = Wire.read();        // receive high byte (overwrites previous reading)
    tempRaw = tempRaw << 8;       // shift high byte to be high 8 bits
    tempRaw |= Wire.read();       // receive low byte as lower 8 bits
  }
  
  // Returns the 16-bit raw temperature reading
  return tempRaw;
}

/* 
 * Configuration Register
 * 
 * Table 4. Configuration Register Definition
 *  +------------------+-----+-----+---------+--------+-----+-----------+-----------+-------------+-----+------+----------+-----+-----------------+----------+
 *  |       D15        | D14 | D13 |   D12   |  D11   | D10 |    D9     |     D8    |     D7      |  D6 | D5   |    D4    | D3  |    D2  |    D1  |    D0    |
 *  +------------------+-----+-----+---------+--------+-----+-----------+-----------+-------------+-----+------+----------+--------------+--------+----+-----+
 *  | Over Temp Status | x   | x   |    Fault Queue   |  x  | Comp/ Int | Shut Down | Data Format | Resolution | Time-out | PEC | Conversion Rate | One-Shot |
 *  +------------------+-----+-----+---------+--------+-----+-----------+-----------+-------------+-----+------+----------+-----+--------+--------+----------+
 * 
 * Conversion Rate = b11 -> 8 conversions/sec  (Datasheet) Table 5: Conversion Rate Selection
 * Resolution      = b11 -> 12 bit             (Datasheet) Table 6: Resolution Selection
 * All Other values = 0
 */
uint8_t FTTech_SAMD51_MAX31875::configTemp(void)
{
  Wire.beginTransmission(maxAddress);
  for(int i=0; i<3; i++)
  {
    bool error = write(configReg[i]);
    if(error)
      return 1;
  }
  Wire.endTransmission();
  return 0;
}

uint8_t FTTech_SAMD51_MAX31875::write(uint8_t var)
{

  uint8_t error = Wire.write(var);
  if(error)
  {
    #if DEBUG_FTTECH_SAMD51 >= 1
    DEBUG1_FTTECH_PRINTLN(F("Error when configuring module, check if I2C-Master Pullup jumper is enabled."));
    #endif
    return 1;
  }
  return 0;
}

// instantiate static
FTTech_SAMD51_MAX31875 MAX31875;
