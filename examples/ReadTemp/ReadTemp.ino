/* -----------------------------------------
 * The MIT License (MIT)
 * 
 * Copyright (c) 2021 FTTech
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * 
 * -----------------------------------------
 *  
 * ABOUT:
 *  This sketch reads the temperature sensor MAX31875 over I2C interface 
 * and outputs the data to the Serial interface
 * 
 * DETAILS: 
 *  PART NUMBER    - MAX31875R0TZS+T
 *  SLAVE ADDRESS  - 0x1001000
 *     - INT: 72
 *     - HEX: 0x48
 *  COMMUNICATION  - I2C 
 *     - SDA: Serial Data
 *     - SCL: Serial Clock
 *  DATASHEET: https://mouser.com/datasheet/2/256/MAX31875-1535991.pdf
 *  
 * -----------------------------------------
 *  
 * Please report if you find any issue when using this code so when can
 * keep improving it
 */

// Import library for I2C interface
#include <Wire.h>
#include "FTTech_SAMD51Clicks.h"

const uint32_t baud = 9600;               // Baudrate that will be used beetween FTClicks and Serial Monitor

void setup() {
  Wire.begin();

  Serial.begin(9600);
  while (!Serial);

  Serial.println(F("********************************************************"));
  Serial.println(F("FTClick(Master) <-> MAX31875(Slave)"));
  Serial.println(F("********************************************************"));

  // Write the configuration register
  MAX31875.begin();
}

void loop() {
  float temperatureC = MAX31875.readCelsius();

  Serial.print("Temperature in Celsius: ");
  Serial.print(temperatureC);
  Serial.println(" °C");

  delay(2500);
}
