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
 
 * DHT22
                                                                                           - DHT22 PINOUT -
 * Reads the DHT22 Sensor, prints the result to the Serial Monitor.                          ___________
 * This Sketch uses the DHT.h library to read the sensor parameters.                        /  |_|_|_|  \
 * The sensor will be powered by board's 5V output.                                         |__|_|_|_|__|
                                                                                            |  |_|_|_|  |
 * The circuit:                                                                             |__|_|_|_|__|
   * HUMIDITY AND TEMPERATURE SENSOR (MODEL DHT22)                                          |__|_|_|_|__|
   * JUMPERS                                                                                   | | | |
                                                                                             5V  |    GND
 * You can download the DHT library at https://github.com/adafruit/DHT-sensor-library          DATA

 * Created 10 March 2021
 * By FTTech Developer Jhonatan Cruz

 * -----------------------------------------
*/

//Libraries
#include <DHT.h>
#include "FTTech_SAMD51_Clicks.h"

#define DHTPIN 5      // Digital pin used by DHT22
#define DHTTYPE DHT22 // Define the sensor model (DHT22 / AM2302)

// Setup DHT Object
DHT dht(DHTPIN, DHTTYPE);

void setup(){
  /*
   * To enable the 5V output you MUST use the command FTClicks.turnOn_5V()
   * then use the command FTClicks.turnOn() to step-up all clicks OR use
   * the command FTClicks.turnOn(click number) to step up a specific Click
  */
  FTClicks.turnON_5V(); // Enable 5V output
  FTClicks.turnON(1);   // Enable the 3.3V output of Click 1
  dht.begin();          // DHT initial setup
  Serial.begin(9600);
  while(!Serial);       // Awaits serial communication
}

void loop(){
  
  Serial.print("Umidade: " + (String)dht.readHumidity() + "%"); Serial.print(" / Temperatura: "); Serial.print(dht.readTemperature(), 0); Serial.println("ºC");
  delay(2000); // Print every 2 seconds
}
