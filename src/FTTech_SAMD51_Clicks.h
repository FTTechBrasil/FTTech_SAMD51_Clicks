#ifndef _FTTECH_SAMD51CLICKS_H_
#define _FTTECH_SAMD51CLICKS_H_

#include "FTTech_Debug.h"
#include <Arduino.h>
#include <Adafruit_SleepyDog.h>
#include <MAX31875/MAX31875.h>

/**************************************************************************/
/*!
    @brief  Class for interacting with FTTech SAMD51 Clicks hardware.
    Pin mapping is now handled by the board variant.
*/
/**************************************************************************/

// Use definitions from variant.h if available, otherwise fallback
#ifndef QNTY_CLICKS
  #define QNTY_CLICKS 4
#endif

#ifndef BATTERY
  #define BATTERY A8
#endif

#ifndef CLICK_20PIN
  #define CLICK_20PIN 4
#endif

#define FTTECH_VERSION "1.3.8"

// Averaging Samples Macros
#define AVERAGING_SAMPLES_1    0
#define AVERAGING_SAMPLES_2    1
#define AVERAGING_SAMPLES_4    2
#define AVERAGING_SAMPLES_8    3
#define AVERAGING_SAMPLES_16   4
#define AVERAGING_SAMPLES_32   5
#define AVERAGING_SAMPLES_64   6
#define AVERAGING_SAMPLES_128  7
#define AVERAGING_SAMPLES_256  8
#define AVERAGING_SAMPLES_512  9
#define AVERAGING_SAMPLES_1024 10

#define DEFAULT_AVERAGING_SAMPLES AVERAGING_SAMPLES_1
#define NVMCTRL_TEMP_LOG NVMCTRL_TEMP_LOG_W0

class FTTech_SAMD51Clicks {
  public:
    char ChipID[33];

    bool begin();
    void turnON(uint8_t click);
    void turnON(void);
    void turnOFF(uint8_t click);
    void turnOFF(void);
    void turnON_5V(void);
    void turnOFF_5V(void);
    void turnOFF_SPI(void);
    void turnOFF_SPI(uint8_t click);
    void turnON_SPI(uint8_t click);
    int sleepForSeconds(int secs);
    int sleepWithComunication(int secs, int early_awekening = 8);
    float readBattery(void);
    float readCPUTemperature(void);
    float readCPUTemperature(uint8_t averege);

    void printBanner() {
      LOG1_FTTECH_PRINTLN(F(
        " ______   ______   ______   ______     ______     __  __" FTTECH_NEWLINE    
        "/\\  ___\\ /\\__  _\\ /\\__  _\\ /\\  ___\\   /\\  ___\\   /\\ \\_\\ \\" FTTECH_NEWLINE    
        "\\ \\  __\\ \\/_/\\ \\/ \\/_/\\ \\/ \\ \\  __\\   \\ \\ \\____  \\ \\  __ \\" FTTECH_NEWLINE 
        " \\ \\_\\      \\ \\_\\    \\ \\_\\  \\ \\_____\\  \\ \\_____\\  \\ \\_\\ \\_\\" FTTECH_NEWLINE
        "  \\/_/       \\/_/     \\/_/   \\/_/_____/   \\/_/_____/   \\/_/\\/_/  v" FTTECH_VERSION
      ));
    }

  private:
    uint32_t _R2 = 330000;
    uint32_t _R1 = 1000000;

    int8_t validadeClick(uint8_t click, uint8_t max_clicks = QNTY_CLICKS);
    uint8_t mapToClickPower(uint8_t click);
    uint8_t mapToClickSPI(uint8_t click);

    void initPowerPins(void);
    void initSPIPins(void);
    void getChipID(void);

    float convertDecToFrac(uint8_t val);
    float calculateTemperature(uint16_t TP, uint16_t TC);
    float getTempc(uint8_t averaging);
};

extern FTTech_SAMD51Clicks FTClicks;

#endif
