#include <FTTech_SAMD51_Clicks.h>

/****************************************************************
 * PUBLIC FUNCTIONS
*****************************************************************/

bool FTTech_SAMD51Clicks::begin()
{

  uint8_t pin = 0;

  for (int i = 1; i <= QNTY_CLICKS; i++)
  {
    pin = mapToClickPower(i);
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);

    pin = mapToClickSPI(i);
    pinMode(pin, OUTPUT);
    digitalWrite(pin, HIGH);
  }

  pinMode(POWER_5V, OUTPUT);
  digitalWrite(POWER_5V, LOW);

  getChipID();

  printBanner();

  #if DEBUG_FTTECH_SAMD51 >= 2
      DEBUG2_FTTECH_PRINTLN(F("Unique ID: "), this->ChipID);
  #endif

  return true;
}

void FTTech_SAMD51Clicks::turnON(uint8_t click)
{
  if (validadeClick(click) == 0) {
    uint8_t pin = mapToClickPower(click);
    digitalWrite(pin, HIGH);
  }
}

void FTTech_SAMD51Clicks::turnON(void)
{
  for (int i = 1; i <= QNTY_CLICKS; i++)
  {
    turnON(i);
  }
}

void FTTech_SAMD51Clicks::turnOFF(uint8_t click)
{
  if (validadeClick(click) == 0) {
    uint8_t pin = mapToClickPower(click);
    digitalWrite(pin, LOW);
  }
}

void FTTech_SAMD51Clicks::turnOFF(void)
{
  for (int i = 1; i <= QNTY_CLICKS; i++)
  {
    turnOFF(i);
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
  for (int i = 1; i <= QNTY_CLICKS-1; i++)
  {
    turnOFF_SPI(i);
  }
}

void FTTech_SAMD51Clicks::turnOFF_SPI(uint8_t click)
{
  if (validadeClick(click, QNTY_CLICKS-1) == 0) {
    uint8_t pin = mapToClickSPI(click);
    digitalWrite(pin, HIGH);
  }
}

void FTTech_SAMD51Clicks::turnON_SPI(uint8_t click)
{
  if (validadeClick(click, QNTY_CLICKS-1) == 0) {
    uint8_t pin = mapToClickSPI(click);
    digitalWrite(pin, LOW);
  }
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
    FTClicks.turnOFF(CLICK_20PIN);
    _sleepMS += sleepForSeconds(secs);
    FTClicks.turnON(CLICK_20PIN);
    _sleepMS += sleepForSeconds(_await);
  }
  else
  {
    _sleepMS += sleepForSeconds(secs);
  }
  return _sleepMS;
}

float FTTech_SAMD51Clicks::readBattery(void)
{
  float analog = analogRead(BATTERY);
  float voltage = analog * 3.3 / 1023 * (_R2 + _R1) / (_R2);

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
  if (click < 1 || click > max_clicks) {
    #if DEBUG_FTTECH_SAMD51 >= 1
      DEBUG2_FTTECH_PRINTLN(F("Click number has to be between 1 and QNTY_CLICKS. Received: "), click);
	  #endif
    return -1;
  }else{
    return 0;
  }
}


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
#ifdef __FTTECH_SMARTNODE_3S__ 
  case 3:
    pin = CLICK_THREE;
    break;
#endif
  }
  return pin;
}

uint8_t FTTech_SAMD51Clicks::mapToClickSPI(uint8_t click)
{
  uint8_t pin = 99;
  switch (click)
  {
  case 1:
    pin = SS1;
    break;
  case 2:
    pin = SS2;
    break;
#ifdef __FTTECH_SMARTNODE_3S__
  case 3:
    pin = SS3;
    break;
#endif
  }
  return pin;
}

void FTTech_SAMD51Clicks::initPowerPins(void)
{
  uint8_t pin = 0;

  for (int i = 1; i <= QNTY_CLICKS; i++)
  {
    pin = mapToClickPower(i);
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
  }

  pinMode(POWER_5V, OUTPUT);
  digitalWrite(POWER_5V, LOW);
}

void FTTech_SAMD51Clicks::initSPIPins(void)
{
  uint8_t pin = 0;

  for (int i = 1; i <= QNTY_CLICKS; i++)
  {
    pin = mapToClickSPI(i);
    pinMode(pin, OUTPUT);
    digitalWrite(pin, HIGH);
  }
}

void FTTech_SAMD51Clicks::getChipID(void)
{
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

float FTTech_SAMD51Clicks::convertDecToFrac(uint8_t val) {
  float float_val = (float)val;
  if (val < 10) {
    return (float_val / 10.0);
  } else if (val < 100) {
    return (float_val / 100.0);
  } else {
    return (float_val / 1000.0);
  }
}


float FTTech_SAMD51Clicks::calculateTemperature(uint16_t TP, uint16_t TC) {
  // Datasheet Page 1441, in the 45.6.3.1 Device Temperature Measurement
  uint32_t TLI = (*(uint32_t *)FUSES_ROOM_TEMP_VAL_INT_ADDR & FUSES_ROOM_TEMP_VAL_INT_Msk) >> FUSES_ROOM_TEMP_VAL_INT_Pos;
  uint32_t TLD = (*(uint32_t *)FUSES_ROOM_TEMP_VAL_DEC_ADDR & FUSES_ROOM_TEMP_VAL_DEC_Msk) >> FUSES_ROOM_TEMP_VAL_DEC_Pos;
  float TL = TLI + convertDecToFrac(TLD);

  uint32_t THI = (*(uint32_t *)FUSES_HOT_TEMP_VAL_INT_ADDR & FUSES_HOT_TEMP_VAL_INT_Msk) >> FUSES_HOT_TEMP_VAL_INT_Pos;
  uint32_t THD = (*(uint32_t *)FUSES_HOT_TEMP_VAL_DEC_ADDR & FUSES_HOT_TEMP_VAL_DEC_Msk) >> FUSES_HOT_TEMP_VAL_DEC_Pos;
  float TH = THI + convertDecToFrac(THD);

  uint16_t VPL = (*(uint32_t *)FUSES_ROOM_ADC_VAL_PTAT_ADDR & FUSES_ROOM_ADC_VAL_PTAT_Msk) >> FUSES_ROOM_ADC_VAL_PTAT_Pos;
  uint16_t VPH = (*(uint32_t *)FUSES_HOT_ADC_VAL_PTAT_ADDR & FUSES_HOT_ADC_VAL_PTAT_Msk) >> FUSES_HOT_ADC_VAL_PTAT_Pos;

  uint16_t VCL = (*(uint32_t *)FUSES_ROOM_ADC_VAL_CTAT_ADDR & FUSES_ROOM_ADC_VAL_CTAT_Msk) >> FUSES_ROOM_ADC_VAL_CTAT_Pos;
  uint16_t VCH = (*(uint32_t *)FUSES_HOT_ADC_VAL_CTAT_ADDR & FUSES_HOT_ADC_VAL_CTAT_Msk) >> FUSES_HOT_ADC_VAL_CTAT_Pos;


  // From SAMD51 datasheet: section 45.6.3.1 (page 1327)
  return (TL * VPH * TC - VPL * TH * TC - TL * VCH * TP + TH * VCL * TP) / (VCL * TP - VCH * TP - VPL * TC + VPH * TC);
}


float FTTech_SAMD51Clicks::getTempc(uint8_t averaging) {
  // enable and read 2 ADC temp sensors, 12-bit res
  volatile uint16_t ptat;
  volatile uint16_t ctat;
  // Datasheet Page 1441, in the 45.6.3.1 Device Temperature Measuremen
  SUPC->VREF.reg |= SUPC_VREF_TSEN | SUPC_VREF_ONDEMAND | SUPC_VREF_VREFOE;

  uint8_t ss_ctrlb_ressel = ADC0->CTRLB.bit.RESSEL; // Saved State of ADC0->CTRLB.bit.RESSEL
  uint8_t ss_adc_avgctrl = ADC0->AVGCTRL.reg; // Saved State of ADC->AVGCTRL.reg
  
  if(averaging == AVERAGING_SAMPLES_1){
    // Datasheet Page 1435, in the 45.6.2.6 ADC Resolution
    ADC0->CTRLB.bit.RESSEL = ADC_CTRLB_RESSEL_12BIT_Val; // Lets set 12-bit resolution in the CTRLB register.
  }else{
    ADC0->CTRLB.bit.RESSEL = ADC_CTRLB_RESSEL_16BIT_Val; // For averaging mode output
  }

  // Page 1438, in the 45.6.2.10 Averaging 
  switch(averaging) {
    case AVERAGING_SAMPLES_1: 
      ADC0->AVGCTRL.reg = 0;
      break;
    case AVERAGING_SAMPLES_2: 
      ADC0->AVGCTRL.reg = ADC_AVGCTRL_SAMPLENUM_2 | ADC_AVGCTRL_ADJRES(0x1);
      break;
    case AVERAGING_SAMPLES_4: 
      ADC0->AVGCTRL.reg = ADC_AVGCTRL_SAMPLENUM_4 | ADC_AVGCTRL_ADJRES(0x2);
      break;
    case AVERAGING_SAMPLES_8: 
      ADC0->AVGCTRL.reg = ADC_AVGCTRL_SAMPLENUM_8 | ADC_AVGCTRL_ADJRES(0x3);
      break;
    case AVERAGING_SAMPLES_16: 
      ADC0->AVGCTRL.reg = ADC_AVGCTRL_SAMPLENUM_16 | ADC_AVGCTRL_ADJRES(0x4);
      break;
    case AVERAGING_SAMPLES_32: 
      ADC0->AVGCTRL.reg = ADC_AVGCTRL_SAMPLENUM_32 | ADC_AVGCTRL_ADJRES(0x4);
      break;
    case AVERAGING_SAMPLES_64: 
      ADC0->AVGCTRL.reg = ADC_AVGCTRL_SAMPLENUM_64 | ADC_AVGCTRL_ADJRES(0x4);
      break;
    case AVERAGING_SAMPLES_128: 
      ADC0->AVGCTRL.reg = ADC_AVGCTRL_SAMPLENUM_128 | ADC_AVGCTRL_ADJRES(0x4);
      break;
    case AVERAGING_SAMPLES_256: 
      ADC0->AVGCTRL.reg = ADC_AVGCTRL_SAMPLENUM_256 | ADC_AVGCTRL_ADJRES(0x4);
      break;
    case AVERAGING_SAMPLES_512: 
      ADC0->AVGCTRL.reg = ADC_AVGCTRL_SAMPLENUM_512 | ADC_AVGCTRL_ADJRES(0x4);
      break;
    case AVERAGING_SAMPLES_1024: 
      ADC0->AVGCTRL.reg = ADC_AVGCTRL_SAMPLENUM_1024 | ADC_AVGCTRL_ADJRES(0x4);
      break;
  }
  while (ADC0->SYNCBUSY.reg & ADC_SYNCBUSY_AVGCTRL); //wait for sync

  // Datasheet Page 1435, in the 45.6.2.6 ADC Resolution  Datasheet Page 1441, in the 45.6.3.1 Device Temperature Measurement:
  // Datasheet Page 1455, in the 45.8.4 Input Control  "Which temperature sensor is requested by the ADC is selected by writing to the Positive MUX Input Selection
  ADC0->INPUTCTRL.bit.MUXPOS = ADC_INPUTCTRL_MUXPOS_PTAT;

  while (ADC0->SYNCBUSY.reg & ADC_SYNCBUSY_CTRLB);      //wait for sync
  while (ADC0->SYNCBUSY.reg & ADC_SYNCBUSY_INPUTCTRL ); //wait for sync

  // Datasheet Page 1434, in the 45.6.2.2 Enabling, Disabling, and Resetting:
  // Lets enable the ADC and SYNC it like we did before.
  ADC0->CTRLA.bit.ENABLE = 0x01;             // Enable ADC
  while ( ADC0->SYNCBUSY.reg & ADC_SYNCBUSY_ENABLE ); //wait for sync


  // Datasheet Page 1447, in the 45.6.6 Events
  // Start conversion and wait for sync as it is Write-Synchronized
  ADC0->SWTRIG.bit.START = 1;
  while ( ADC0->SYNCBUSY.reg & ADC_SYNCBUSY_ENABLE ); //wait for sync

  // Datasheet Page 1447, in the 45.6.6 Events
  // Clear the Data Ready flag
  ADC0->INTFLAG.reg = ADC_INTFLAG_RESRDY;

  // Start conversion again, since The first conversion after the reference is changed must not be used.
  ADC0->SWTRIG.bit.START = 1;
  while (ADC0->INTFLAG.bit.RESRDY == 0);  // Waiting for conversion to complete
  ptat = ADC0->RESULT.reg;

  // Change to CTAT like we did for PTAT (ADC_INPUTCTRL_MUXPOS_PTAT)
  ADC0->INPUTCTRL.bit.MUXPOS = ADC_INPUTCTRL_MUXPOS_CTAT;
  while ( ADC0->SYNCBUSY.reg & ADC_SYNCBUSY_INPUTCTRL ); //wait for sync
  
  // Start conversion
  ADC0->SWTRIG.bit.START = 1;
  while ( ADC0->SYNCBUSY.reg & ADC_SYNCBUSY_ENABLE ); //wait for sync

  // Clear the Data Ready flag
  ADC0->INTFLAG.reg = ADC_INTFLAG_RESRDY;

  // Start conversion again, since The first conversion after the reference is changed must not be used.
  ADC0->SWTRIG.bit.START = 1;
  while (ADC0->INTFLAG.bit.RESRDY == 0);  // Waiting for conversion to complete
  ctat = ADC0->RESULT.reg;

  ADC0->CTRLA.bit.ENABLE = 0x00;             // Disable ADC
  while ( ADC0->SYNCBUSY.reg & ADC_SYNCBUSY_ENABLE ); //wait for sync

  // return it back previus definition
  ADC0->CTRLB.bit.RESSEL = ss_ctrlb_ressel;  
  ADC0->AVGCTRL.reg = ss_adc_avgctrl;
  while (ADC0->SYNCBUSY.reg & ADC_SYNCBUSY_CTRLB); //wait for sync
  while (ADC0->SYNCBUSY.reg & ADC_SYNCBUSY_AVGCTRL); //wait for sync

  return calculateTemperature(ptat, ctat);
}


// instantiate static
FTTech_SAMD51Clicks FTClicks;
