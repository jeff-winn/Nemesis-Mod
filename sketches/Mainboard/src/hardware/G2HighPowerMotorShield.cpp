#include "G2HighPowerMotorShield.h"

boolean G2HighPowerMotorShield::_flip = false;

// Constructors ////////////////////////////////////////////////////////////////
G2HighPowerMotorShield::G2HighPowerMotorShield() {  
}

G2HighPowerMotorShield::G2HighPowerMotorShield(unsigned char SLEEP,
                                               unsigned char DIR,
                                               unsigned char PWM,
                                               unsigned char FAULT,
                                               unsigned char CS)
{
  _SLEEP = SLEEP;
  _FAULT = FAULT;
  _DIR = DIR;
  _PWM = PWM;
  _CS = CS;
}

// Public Methods //////////////////////////////////////////////////////////////
void G2HighPowerMotorShield::init()
{
  pinMode(_SLEEP, OUTPUT);
  pinMode(_PWM, OUTPUT);
  pinMode(_FAULT, INPUT_PULLUP);
  pinMode(_CS, INPUT);
  pinMode(_DIR, OUTPUT);

#ifdef G2HIGHPOWERMOTORSHIELD_TIMER1_AVAILABLE
  if (_M1PWM == _M1PWM_TIMER1_PIN && _M2PWM == _M2PWM_TIMER1_PIN)
  {
    // Timer 1 configuration
    // prescaler: clockI/O / 1
    // outputs enabled
    // phase-correct PWM
    // top of 400
    //
    // PWM frequency calculation
    // 16MHz / 1 (prescaler) / 2 (phase-correct) / 400 (top) = 20kHz
    TCCR1A = 0b10100000;
    TCCR1B = 0b00010001;
    ICR1 = 400;
  }
#endif
}
// Set speed for motor 1, speed is a number betwenn -400 and 400
void G2HighPowerMotorShield::setSpeed(int speed)
{
  unsigned char reverse = 0;

  if (speed < 0)
  {
    speed = -speed;  // Make speed a positive quantity
    reverse = 1;  // Preserve the direction
  }
  if (speed > 400)  // Max PWM dutycycle
    speed = 400;

#ifdef G2HIGHPOWERMOTORSHIELD_TIMER1_AVAILABLE
  if (_M1PWM == _M1PWM_TIMER1_PIN && _M2PWM == _M2PWM_TIMER1_PIN)
  {
    OCR1A = speed;
  }
  else
  {
    analogWrite(_M1PWM, speed * 51 / 80); // map 400 to 255
  }
#else
  analogWrite(_PWM, speed * 51 / 80); // map 400 to 255
#endif

  if (reverse ^ _flip) // flip if speed was negative or _flipM1 setting is active, but not both
  {
    digitalWrite(_DIR, HIGH);
  }
  else
  {
    digitalWrite(_DIR, LOW);
  }
}

// Return error status for motor 1
unsigned char G2HighPowerMotorShield::getFault()
{
  return !digitalRead(_FAULT);
}

void G2HighPowerMotorShield::flip(boolean flip)
{
  G2HighPowerMotorShield::_flip = flip;
}

// Enables the MOSFET driver for M1.
void G2HighPowerMotorShield::enableDriver()
{
  digitalWrite(_SLEEP, HIGH);
}

// Puts the MOSFET driver for M1 into sleep mode.
void G2HighPowerMotorShield::disableDriver()
{
  digitalWrite(_SLEEP, LOW);
}

unsigned int G2HighPowerMotorShield::getCurrentReading()
{
  return analogRead(_CS);
}

// Set voltage offset of M1 current reading at 0 speed.
void G2HighPowerMotorShield::calibrateCurrentOffset()
{
  setSpeed(0);
  enableDriver();
  delay(1);
  G2HighPowerMotorShield::_offset = getCurrentReading();
}

// Return M1 current value in milliamps using the gain value for the specific version.
unsigned int G2HighPowerMotorShield::getCurrentMilliamps(int gain)
{
  // 5V / 1024 ADC counts / gain mV per A
  // The 24v14, 18v18 and 24v18 results in 244 mA per count.
  // The 18v22 results in 488 mA per count.
  unsigned int mAPerCount = 5000000/1024/gain;
  int reading = (getCurrentReading() - G2HighPowerMotorShield::_offset);
  if (reading > 0)
  {
    return reading * mAPerCount;
  }
  return 0;
}
// Return M1 current value in milliamps for 18v22 version.
unsigned int G2HighPowerMotorShield18v17::getCurrentMilliamps()
{
  return G2HighPowerMotorShield::getCurrentMilliamps(10);
}