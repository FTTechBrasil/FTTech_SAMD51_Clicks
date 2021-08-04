#include "FTTech_SAMD51_Clicks.h"


void setup() {  
  Serial.begin(9600);
  while(!Serial)
    ;

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