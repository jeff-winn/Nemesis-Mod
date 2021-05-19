#ifndef G2_HIGH_POWER_MOTOR_SHIELD_H
#define G2_HIGH_POWER_MOTOR_SHIELD_H

#include <Arduino.h>

class G2HighPowerMotorShield
{
  public:
    // CONSTRUCTORS
    G2HighPowerMotorShield();
    G2HighPowerMotorShield(unsigned char SLEEP,
                           unsigned char DIR,
                           unsigned char PWM,
                           unsigned char FAULT,
                           unsigned char CS);

    // PUBLIC METHODS
    void init();
    void setSpeed(int speed); // Set speed.
    unsigned char getFault(); // Get fault reading.
    void flip(boolean flip); // Flip the direction of the speed.
    void enableDriver(); // Enables the MOSFET driver.
    void disableDriver(); // Puts the MOSFET driver into sleep mode.
    unsigned int getCurrentReading();
    void calibrateCurrentOffset();
    unsigned int getCurrentMilliamps(int gain);

  protected:
    unsigned int _offset;

  private:
    unsigned char _PWM;
    static const unsigned char _PWM_TIMER1_PIN = 9;
    unsigned char _SLEEP;
    unsigned char _DIR;
    unsigned char _FAULT;
    unsigned char _CS;
    static boolean _flip;
};

class G2HighPowerMotorShield18v17 : public G2HighPowerMotorShield {
  public:
    using G2HighPowerMotorShield::G2HighPowerMotorShield;
    unsigned int getCurrentMilliamps();
};

#endif /* G2_HIGH_POWER_MOTOR_SHIELD_H */