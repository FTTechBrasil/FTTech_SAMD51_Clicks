// Adafruit Watchdog Library Sleep Example
//
// Simple example of how to do low power sleep with the watchdog timer.
//
// Author: Tony DiCola
// Modified: FTTech on 08/2021

#include "FTTech_SAMD51_Clicks.h"

#ifdef __FTTECH_SMARTNODE_1S__
  // Version 1 of smartnode 1s doesn't have a LED_BUILTIN
  // we connect externally a LED+470Ohm to digital 4 and GND.
  #define LED_BUILTIN 4
#endif

void setup() {
  FTClicks.begin();
  Serial.begin(115200);

  while(!Serial); // wait for Arduino Serial Monitor (native USB boards)
  Serial.println(F("Adafruit Watchdog Library Sleep Demo!"));
  Serial.println();
  
  
  // For boards with "native" USB support (e.g. not using an FTDI chip or
  // similar serial bridge), Serial connection may be lost on sleep/wake,
  // and you might not see the "I'm awake" messages. Use the onboard LED
  // as an alternate indicator -- the code turns it on when awake, off
  // before going to sleep.
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH); // Show we're awake  
}

void loop() {
  Serial.println(F("Going to sleep in one second..."));
  delay(1000);
  
  // To enter low power sleep mode call Watchdog.sleep() like below
  // and the watchdog will allow low power sleep for as long as possible.
  // The actual amount of time spent in sleep will be returned (in 
  // milliseconds).
  digitalWrite(LED_BUILTIN, LOW); // Show we're asleep
  USBDevice.detach();
  int sleepMS = Watchdog.sleep();

  // Alternatively you can provide a millisecond value to specify
  // how long you'd like the chip to sleep, but the hardware only
  // supports a limited range of values so the actual sleep time might
  // be smaller.  The time spent in sleep will be returned (in
  // milliseconds).
  // int sleepMS = Watchdog.sleep(1000);  // Sleep for up to 1 second.

  // Code resumes here on wake.
  digitalWrite(LED_BUILTIN, HIGH); // Show we're awake again

  // Try to reattach USB connection on "native USB" boards (connection is
  // lost on sleep). Host will also need to reattach to the Serial monitor.
  // We recomend using it with Tera Term to read the monitor after sleeping.
  // As the attach seems not entirely reliable, we have the LED indicator fallback.
  USBDevice.attach();
  delay(1000); // minimum of 600 ms after the attach to receive something in the monitor

  Serial.print(F("I'm awake now! I slept for "));
  Serial.print(sleepMS, DEC);
  Serial.print(F(" milliseconds."));
  Serial.println();
  
}
