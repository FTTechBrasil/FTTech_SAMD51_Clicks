#include <Arduino.h>

#ifdef __cplusplus
extern "C" {
#endif
    void printInt(int val);
    void print(char* str);
    void println(char* str);
    void print_uint8_array_hex(uint8_t* str, int length);
#ifdef __cplusplus
     }
#endif