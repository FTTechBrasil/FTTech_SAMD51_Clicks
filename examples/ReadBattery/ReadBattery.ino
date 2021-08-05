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
 *  This sketch reads the battery pin, that is an analog input connected to a 
 * voltage divider.
 * 
 * -----------------------------------------
 *  
 * Please report if you find any issue when using this code so when can
 * keep improving it
 */

#include "FTTech_SAMD51_Clicks.h"

void setup() {  
  Serial.begin(9600);
  while(!Serial) delay(10);

  Serial.println("\r\nReading Battery Example");

  analogReadResolution(12);
}


void loop() {
  uint16_t batteryBin = analogRead(BATTERY);

  Serial.print("\r\nBattery [qnt] (0-4095): ");
  Serial.println(batteryBin);

  Serial.print("Battery [V] (0-Vcc): ");
  Serial.println(batteryBin*3.3/4095, 3);

  Serial.print("Battery [V] (0-VBat): ");
  Serial.println(batteryBin*14.19/4095, 3);

  delay(1000);
}