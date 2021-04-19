#include "PrintSupport.h"

#include <Arduino.h>

void printInt(int val){
    Serial.print(val);
}

void print(char* str) {
   Serial.print(str);
}

void println(char* str) {
   Serial.println(str);
}

void print_uint8_array_hex(uint8_t* str, int length){
    for(int i=0; i<length;i++)
    {
      if(str[i]<=0x0F)
        Serial.print('0');
      Serial.print(str[i], HEX);
    }
}