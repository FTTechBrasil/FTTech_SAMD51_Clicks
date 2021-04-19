#include <FTTech_SAMD51_Clicks.h>

/****************************************************************
 * PUBLIC FUNCTIONS
*****************************************************************/

bool FTTech_SAMD51Clicks::begin(bool debug)
{
  uint8_t pin = 0;
  this->debug = debug;

  for (int i = 1; i < 5; i++)
  {
    pin = mapToClickPower(i);
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
  }

  pinMode(POWER_5V, OUTPUT);

  // Get chip unique ID
  volatile uint32_t val[4];
  volatile uint32_t *ptr1 = (volatile uint32_t *)0x008061FC;
  val[0] = *ptr1;
  volatile uint32_t *ptr = (volatile uint32_t *)0x00806010;
  val[1] = *ptr;
  ptr++;
  val[2] = *ptr;
  ptr++;
  val[3] = *ptr;

  sprintf(this->ChipID, "%8X%8X%8X%8X", val[0], val[1], val[2], val[3]);
}

void FTTech_SAMD51Clicks::turnON(uint8_t click)
{
  uint8_t pin = mapToClickPower(click);
  digitalWrite(pin, HIGH);
}

void FTTech_SAMD51Clicks::turnON(void)
{
  uint8_t pin = 0;
  for (int i = 1; i < 5; i++)
  {
    pin = mapToClickPower(i);
    pinMode(pin, OUTPUT);
    digitalWrite(pin, HIGH);
  }
}

void FTTech_SAMD51Clicks::turnOFF(uint8_t click)
{
  uint8_t pin = mapToClickPower(click);
  digitalWrite(pin, LOW);
}

void FTTech_SAMD51Clicks::turnOFF(void)
{
  uint8_t pin = 0;
  for (int i = 1; i < 5; i++)
  {
    pin = mapToClickPower(i);
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
  }
}

void FTTech_SAMD51Clicks::turnON_5V(void)
{
  digitalWrite(POWER_5V, HIGH);
}

void FTTech_SAMD51Clicks::turnOFF_5V(void)
{
  digitalWrite(POWER_5V, LOW);
}

void FTTech_SAMD51Clicks::turnOFF_SPI(void)
{
  uint8_t pin = 0;
  for (int i = 1; i < 5; i++)
  {
    pin = mapToClickSPI(i);
    pinMode(pin, OUTPUT);
    digitalWrite(pin, HIGH);
  }
}

void FTTech_SAMD51Clicks::turnOFF_SPI(uint8_t click)
{
  uint8_t pin = mapToClickSPI(click);
  pinMode(pin, OUTPUT);
  digitalWrite(pin, HIGH);
}

void FTTech_SAMD51Clicks::turnON_SPI(uint8_t click)
{
  uint8_t pin = mapToClickSPI(click);
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
}

int FTTech_SAMD51Clicks::sleepForSeconds(int secs)
{ // sleep for seconds  (maximum is 65535 seconds = 18.2 hours) 43200 = 12 hours.

  int sleepMS = 0;
  while (secs != 0)
  {
    int _sleepMS = Watchdog.sleep(secs * 1000);
    sleepMS += _sleepMS;
    secs += -_sleepMS / 1000;
  }
  return sleepMS;
}

int FTTech_SAMD51Clicks::sleepWithComunication(int secs, int early_awekening)
{
  int _sleepMS = 0;
  int _await = early_awekening;
  if (secs >= (_await + _await))
  {
    secs += -(_await + _await);
    _sleepMS += sleepForSeconds(_await);
    FTClicks.turnOFF(4);
    _sleepMS += sleepForSeconds(secs);
    FTClicks.turnON(4);
    _sleepMS += sleepForSeconds(_await);
  }
  else
  {
    _sleepMS += sleepForSeconds(secs);
  }
  return _sleepMS;
}

float FTTech_SAMD51Clicks::readLipoBattery(void)
{
  return readBattery(LIPO_BATTERY);
}

float FTTech_SAMD51Clicks::readLeadAcidBattery(void)
{
  return readBattery(LEAD_BATTERY);
}

/*****************************************************************
 * PRIVATE FUNCTIONS
 ****************************************************************/

uint8_t FTTech_SAMD51Clicks::mapToClickPower(uint8_t click)
{
  uint8_t pin = 99;
  switch (click)
  {
  case 1:
    pin = CLICK_ONE;
    break;
  case 2:
    pin = CLICK_TWO;
    break;
  case 3:
    pin = CLICK_THREE;
    break;
  case 4:
    pin = CLICK_FOUR;
    break;
  default:
    pin = 99;
    Serial.print("ERROR: Click number has to be between 1 and 4");
  }
  return pin;
}

uint8_t FTTech_SAMD51Clicks::mapToClickSPI(uint8_t click)
{
  uint8_t pin = 99;
  switch (click)
  {
  case 1:
    pin = SPI_CS_CLICK_ONE;
    break;
  case 2:
    pin = SPI_CS_CLICK_TWO;
    break;
  case 3:
    pin = SPI_CS_CLICK_THREE;
    break;
  case 4:
    pin = SPI_CS_CLICK_FOUR;
    break;
  default:
    pin = 99;
    Serial.print("ERROR: Click number has to be between 1 and 4");
  }
  return pin;
}

float FTTech_SAMD51Clicks::readBattery(uint8_t BatteryPin)
{
  float analog = analogRead(BatteryPin);
  float voltage = analog * 3.3 / 1023 * (_R2 + _R1) / (_R2);

  return voltage;
}

// instantiate static
FTTech_SAMD51Clicks FTClicks;
