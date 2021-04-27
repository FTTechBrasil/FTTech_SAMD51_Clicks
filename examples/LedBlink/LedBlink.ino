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

 * Led Blink
  
 * Turns on a led for a chosen time and then turn it off for another period, repeatedly.
 * This Sketch uses the millis() function to configure the time that LED will be ON and OFF.
 * The LED will be powered by board's 3.3V output.

 * FOR THE IMPLEMENTATION YOU MUST USE A RESISTOR TO PREVENT DAMAGE TO THE LED.

 * The circuit:
  * LED
  * Resistor (300+ OHM)
  * Jumpers

 * Created 10 March 2021
 * By FTTech Developer Jhonatan Cruz

 * -----------------------------------------
*/

// Libraries
#include "FTTech_SAMD51Clicks.h"

// Set the time for LED to stay ON and OFF in milliseconds
#define   TIME_ON   2000
#define   TIME_OFF   4000

// Save last update time of the LED
unsigned long previousMillis = 0;

bool state = HIGH;

void setup() {
  /*
   * To enable the 3.3 V output you MUST use the command FTClicks.turnOn()
   * to step-up ALL clicks or the command FTClicks.turnOn(click number)
   * to step up a specific Click
  */
  FTClicks.turnON(1);  // Enable the 3.3V output of Click 1
}

void loop() {
  unsigned long currentMillis = millis();

  switch(state){
    case HIGH:
      if(currentMillis - previousMillis >= TIME_ON){
        FTClicks.turnOFF(1); // Disable the 3.3V output of Click 1
        state = LOW;
        previousMillis = currentMillis;  // Update to time of the last LED state change
      }
      break;
    case LOW:
      if(currentMillis - previousMillis >= TIME_OFF){
        FTClicks.turnON(1); // Enable the 3.3V output of Click 1
        state = HIGH;
        previousMillis = currentMillis;  // Update to time of the last LED state change
      }
      break;
  }
}
