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
 *  This sketch uses the Adafruit SleepyDog Library to sleep for custom seconds
 *  
 * -----------------------------------------
 *  
 * Please report if you find any issue when using this code so when can
 * keep improving it
 */

#include "FTTech_SAMD51_Clicks.h"

#ifdef __FTTECH_SMARTNODE_1S__
  // Version 1 of smartnode 1s doesn't have a LED_BUILTIN
  // we connect externally a LED+470Ohm to digital 4 and GND.
  #define LED_BUILTIN 4
#endif

static const uint8_t sleep_time_seconds = 7;

void setup() {
  FTClicks.begin();
  Serial.begin(115200);

  while (!Serial) delay(10);
  Serial.println(F("++++++++++++++++++++++++++++++++++++++++++++++++++"));
  Serial.println(F("FTTech - Sleep Cuastom Seconds"));
  Serial.println(F("++++++++++++++++++++++++++++++++++++++++++++++++++"));
}

void loop() {
  Serial.println(F("Going to sleep in one second..."));
  delay(1000);

  digitalWrite(LED_BUILTIN, LOW);
  USBDevice.detach();
  uint32_t sleepMS = FTClicks.sleepForSeconds(sleep_time_seconds);
  USBDevice.attach();
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000); // minimum of 600 ms after the attach to receive something in the monitor

  Serial.print(F("I'm awake now! I slept for "));
  Serial.print(sleepMS, DEC);
  Serial.print(F(" milliseconds.\n"));
  Serial.println();
}