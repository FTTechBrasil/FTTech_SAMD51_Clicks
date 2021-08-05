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
 *  This sketch reads the temperature sensor within the SAMD51. For more information, 
 * read the datasheet on section 45.6.3.1 Device Temperature Measurement
 * 
 * The FTClicks.readCPUTemperature() has two methods, one void and another one that 
 * receives the number of samples to calculate an average. This average is calculated
 * within the MCU. You can use the parameters below or use empty () for default of 1 sample.
 * 0  -> 1    sample
 * 1  -> 2    samples
 * 2  -> 4    samples
 * 3  -> 8    samples
 * 4  -> 16   samples
 * 5  -> 32   samples
 * 6  -> 64   samples
 * 7  -> 128  samples
 * 8  -> 256  samples
 * 9  -> 512  samples
 * 10 -> 1024 samples
 * Also, feel free to use the DEFINE according to the number of samples above, like
 * AVERAGING_SAMPLES_1 for 1 sample and AVERAGING_SAMPLES_256 for 256 samples.
 * For more information about the average proccess, read the datasheet on section 45.6.2.10 Averaging.
 *  
 * -----------------------------------------
 *  
 * Please report if you find any issue when using this code so when can
 * keep improving it
 */

#include "FTTech_SAMD51_Clicks.h"

void setup() {
  FTClicks.begin();
  Serial.begin(115200);

  while (!Serial) delay(10);
  Serial.println(F("++++++++++++++++++++++++++++++++++++++++++++++++++"));
  Serial.println(F("FTTech - MCU's Temperature"));
  Serial.println(F("++++++++++++++++++++++++++++++++++++++++++++++++++"));
}

void loop() {
  for(uint8_t idx=AVERAGING_SAMPLES_1; idx<=AVERAGING_SAMPLES_1024; idx++){
    Serial.print(F("Temperature (avg of "));
    Serial.print(pow(2, idx));
    Serial.print(F(" samples): ")); 
    Serial.print(FTClicks.readCPUTemperature(idx)); Serial.println(F(" C"));
    delay(100);
  }

  Serial.println(F(" "));
  delay(1000);
}