#include <FTTech_SAMD51_Clicks.h>

/****************************************************************
 * PUBLIC FUNCTIONS
*****************************************************************/

bool FTTech_SAMD51Clicks::begin()
{
  uint8_t pin = 0;

  // Initialize all defined click power and SPI pins
  for (int i = 1; i <= QNTY_CLICKS; i++)
  {
    pin = mapToClickPower(i);
    if (pin != 99) {
      pinMode(pin, OUTPUT);
      digitalWrite(pin, LOW);
    }

    pin = mapToClickSPI(i);
    if (pin != 99) {
      pinMode(pin, OUTPUT);
      digitalWrite(pin, HIGH);
    }
  }

#ifdef POWER_5V
  pinMode(POWER_5V, OUTPUT);
  digitalWrite(POWER_5V, LOW);
#endif

  getChipID();
  printBanner();

#ifdef EXTERN_LED_PIN
  pinMode(EXTERN_LED_PIN, OUTPUT);
  digitalWrite(EXTERN_LED_PIN, LOW);
  for (int i = 0; i < 10; i++){
    delay(50);
    digitalWrite(EXTERN_LED_PIN, !digitalRead(EXTERN_LED_PIN));
  }
  digitalWrite(EXTERN_LED_PIN, LOW);
#endif

  return true;
}

void FTTech_SAMD51Clicks::turnON(uint8_t click)
{
  if (validadeClick(click) == 0) {
    uint8_t pin = mapToClickPower(click);
    if (pin != 99) digitalWrite(pin, HIGH);
  }
}

void FTTech_SAMD51Clicks::turnON(void)
{
  for (int i = 1; i <= QNTY_CLICKS; i++) turnON(i);
}

void FTTech_SAMD51Clicks::turnOFF(uint8_t click)
{
  if (validadeClick(click) == 0) {
    uint8_t pin = mapToClickPower(click);
    if (pin != 99) digitalWrite(pin, LOW);
  }
}

void FTTech_SAMD51Clicks::turnOFF(void)
{
  for (int i = 1; i <= QNTY_CLICKS; i++) turnOFF(i);
}

void FTTech_SAMD51Clicks::turnON_5V(void)
{
#ifdef POWER_5V
  digitalWrite(POWER_5V, HIGH);
#endif
}

void FTTech_SAMD51Clicks::turnOFF_5V(void)
{
#ifdef POWER_5V
  digitalWrite(POWER_5V, LOW);
#endif
}

void FTTech_SAMD51Clicks::turnOFF_SPI(void)
{
  for (int i = 1; i <= QNTY_CLICKS; i++) turnOFF_SPI(i);
}

void FTTech_SAMD51Clicks::turnOFF_SPI(uint8_t click)
{
  uint8_t pin = mapToClickSPI(click);
  if (pin != 99) digitalWrite(pin, HIGH);
}

void FTTech_SAMD51Clicks::turnON_SPI(uint8_t click)
{
  uint8_t pin = mapToClickSPI(click);
  if (pin != 99) digitalWrite(pin, LOW);
}

int FTTech_SAMD51Clicks::sleepForSeconds(int secs)
{
  int sleepMS = 0;
  while (secs > 0)
  {
    int _sleepMS = Watchdog.sleep(secs * 1000);
    sleepMS += _sleepMS;
    secs -= (_sleepMS / 1000);
    if (_sleepMS == 0) break; // Avoid infinite loop
  }
  return sleepMS;
}

int FTTech_SAMD51Clicks::sleepWithComunication(int secs, int early_awekening)
{
  if (secs <= early_awekening) return sleepForSeconds(secs);
  
  int initial_sleep = secs - early_awekening;
  int ms = sleepForSeconds(initial_sleep);
  
  // Power on click 4 (Communication)
  turnON(4);
  ms += sleepForSeconds(early_awekening);
  return ms;
}

float FTTech_SAMD51Clicks::readBattery(void)
{
  float analog = analogRead(BATTERY);
  // Formula for 1/4 voltage divider (1M + 330k)
  float voltage = analog * 3.3 / 1023.0 * (_R2 + _R1) / (_R2);
  return voltage;
}

float FTTech_SAMD51Clicks::readCPUTemperature(void)
{
  return getTempc(DEFAULT_AVERAGING_SAMPLES);
}

float FTTech_SAMD51Clicks::readCPUTemperature(uint8_t averege)
{
  return getTempc(averege);
}

/*****************************************************************
 * PRIVATE FUNCTIONS
 ****************************************************************/
int8_t FTTech_SAMD51Clicks::validadeClick(uint8_t click, uint8_t max_clicks)
{
  if (click < 1 || click > max_clicks) return -1;
  return 0;
}

uint8_t FTTech_SAMD51Clicks::mapToClickPower(uint8_t click)
{
  switch (click)
  {
#ifdef CLICK_ONE
    case 1: return CLICK_ONE;
#endif
#ifdef CLICK_TWO
    case 2: return CLICK_TWO;
#endif
#ifdef CLICK_THREE
    case 3: return CLICK_THREE;
#endif
#ifdef CLICK_FOUR
    case 4: return CLICK_FOUR;
#endif
    default: return 99;
  }
}

uint8_t FTTech_SAMD51Clicks::mapToClickSPI(uint8_t click)
{
  switch (click)
  {
#ifdef SS1
    case 1: return SS1;
#endif
#ifdef SS2
    case 2: return SS2;
#endif
#ifdef SS3
    case 3: return SS3;
#endif
    default: return 99;
  }
}

void FTTech_SAMD51Clicks::getChipID(void)
{
  volatile uint32_t val[4];
  volatile uint32_t *ptr1 = (volatile uint32_t *)0x008061FC;
  val[0] = *ptr1;
  volatile uint32_t *ptr = (volatile uint32_t *)0x00806010;
  val[1] = *ptr;
  ptr++; val[2] = *ptr;
  ptr++; val[3] = *ptr;
  sprintf(this->ChipID, "%8X%8X%8X%8X", val[0], val[1], val[2], val[3]);
}

float FTTech_SAMD51Clicks::convertDecToFrac(uint8_t val) {
  float f = (float)val;
  if (val < 10) return (f / 10.0);
  if (val < 100) return (f / 100.0);
  return (f / 1000.0);
}

float FTTech_SAMD51Clicks::calculateTemperature(uint16_t TP, uint16_t TC) {
  uint32_t TLI = (*(uint32_t *)0x00800100 & 0x000000FF);
  uint32_t TLD = (*(uint32_t *)0x00800100 & 0x0000FF00) >> 8;
  float TL = TLI + convertDecToFrac(TLD);
  uint32_t THI = (*(uint32_t *)0x00800104 & 0x000000FF);
  uint32_t THD = (*(uint32_t *)0x00800104 & 0x0000FF00) >> 8;
  float TH = THI + convertDecToFrac(THD);
  uint16_t VPL = (*(uint32_t *)0x00800108 & 0x0000FFFF);
  uint16_t VPH = (*(uint32_t *)0x00800108 & 0xFFFF0000) >> 16;
  uint16_t VCL = (*(uint32_t *)0x0080010C & 0x0000FFFF);
  uint16_t VCH = (*(uint32_t *)0x0080010C & 0xFFFF0000) >> 16;
  return (TL * VPH * TC - VPL * TH * TC - TL * VCH * TP + TH * VCL * TP) / (VCL * TP - VCH * TP - VPL * TC + VPH * TC);
}

float FTTech_SAMD51Clicks::getTempc(uint8_t averaging) {
  SUPC->VREF.reg |= SUPC_VREF_TSEN | SUPC_VREF_ONDEMAND | SUPC_VREF_VREFOE;
  uint8_t ss_ctrlb = ADC0->CTRLB.bit.RESSEL;
  uint8_t ss_avg = ADC0->AVGCTRL.reg;
  ADC0->CTRLB.bit.RESSEL = (averaging == 0) ? 0x0 : 0x1;
  ADC0->AVGCTRL.reg = (averaging > 0) ? (averaging | 0x40) : 0; 
  while (ADC0->SYNCBUSY.reg & 0x0C);
  ADC0->INPUTCTRL.bit.MUXPOS = 0x18; // PTAT
  while (ADC0->SYNCBUSY.reg & 0x05);
  ADC0->CTRLA.bit.ENABLE = 0x01;
  while (ADC0->SYNCBUSY.reg & 0x02);
  ADC0->SWTRIG.bit.START = 1;
  while (ADC0->SYNCBUSY.reg & 0x02);
  ADC0->INTFLAG.reg = 0x01;
  ADC0->SWTRIG.bit.START = 1;
  while (ADC0->INTFLAG.bit.RESRDY == 0);
  uint16_t ptat = ADC0->RESULT.reg;
  ADC0->INPUTCTRL.bit.MUXPOS = 0x19; // CTAT
  while (ADC0->SYNCBUSY.reg & 0x04);
  ADC0->INTFLAG.reg = 0x01;
  ADC0->SWTRIG.bit.START = 1;
  while (ADC0->INTFLAG.bit.RESRDY == 0);
  uint16_t ctat = ADC0->RESULT.reg;
  ADC0->CTRLA.bit.ENABLE = 0x00;
  while (ADC0->SYNCBUSY.reg & 0x02);
  ADC0->CTRLB.bit.RESSEL = ss_ctrlb;
  ADC0->AVGCTRL.reg = ss_avg;
  return calculateTemperature(ptat, ctat);
}

FTTech_SAMD51Clicks FTClicks;
