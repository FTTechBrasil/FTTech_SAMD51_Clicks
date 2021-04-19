#include "MAX31875/MAX31875.h"
#include <Wire.h>

/****************************************************************
 * PUBLIC FUNCTIONS
*****************************************************************/

void FTTech_SAMD51_MAX31875::begin(void)
{
  configTemp();
}

float FTTech_SAMD51_MAX31875::readCelsius(void)
{
  int tempRaw = readRaw();
  
  if(tempRaw != 0)
  {
    return tempRaw/256.0;
  }
  else {
    Serial.println(F("Temperature Raw = 0, did you called begin()?"));
    return 999;
  }
}

/*****************************************************************
 * PRIVATE FUNCTIONS
 ****************************************************************/

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
void FTTech_SAMD51_MAX31875::configTemp(void)
{
  Wire.beginTransmission(maxAddress);
  Wire.write(configReg[0]);
  Wire.write(configReg[1]);
  Wire.write(configReg[2]);
  Wire.endTransmission();
}

// instantiate static
FTTech_SAMD51_MAX31875 MAX31875;
