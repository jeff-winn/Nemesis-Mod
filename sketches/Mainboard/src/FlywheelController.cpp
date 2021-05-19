#include <stddef.h>
#include "ConfigurationSettings.h"
#include "FlywheelController.h"
#include "Mainboard.h"

FlywheelController Flywheels = FlywheelController();

FlywheelController::FlywheelController() {
    m_driver = DualG2HighPowerMotorShield18v18(9, -1, 5, -1, -1, 10, -1, 6, -1, -1);
}

void FlywheelController::init() {
    m_driver.init();
    m_driver.calibrateCurrentOffsets();
    m_driver.disableDrivers();

    setSpeed(FlywheelSpeed::Normal);
    
    MCU.delaySafe(1);
}

unsigned int FlywheelController::getMotorCurrentMilliamps(FlywheelMotor motor) {
    switch (motor) {
        case FlywheelMotor::Motor1: {
            return m_driver.getM1CurrentMilliamps();
        }
        case FlywheelMotor::Motor2: {
            return m_driver.getM2CurrentMilliamps();
        }
    }

    return 0;
}

void FlywheelController::onStart() {
    m_driver.enableDrivers();
    updateDrivers();
}

void FlywheelController::updateDrivers() {
    m_m1Speed = calculateMotorSpeed(FlywheelMotor::Motor1);
    m_m2Speed = calculateMotorSpeed(FlywheelMotor::Motor2);
    m_driver.setSpeeds(m_m1Speed, m_m2Speed);
    
    MCU.delaySafe(1);
}

int FlywheelController::calculateStepFromValue(int value) {
    return value / 4;
}

int FlywheelController::calculateMotorSpeed(FlywheelMotor motor) {
    auto maximumSpeed = determineMotorMaximumSpeed();
    
    auto limiter = calculateLimiterForSpeed(maximumSpeed);
    auto adjustment = getMotorSpeedAdjustment(motor);
    
    return (maximumSpeed - limiter) + (limiter * adjustment);
}

int FlywheelController::calculateLimiterForSpeed(int speed) {
    return speed * Settings.getFlywheelTrimVariance();
}

int FlywheelController::determineMotorMaximumSpeed() {
    switch (m_speed) {
        case FlywheelSpeed::Kid: {
            return Settings.getFlywheelKidSpeed();
        }
        case FlywheelSpeed::Normal: {
            return Settings.getFlywheelNormalSpeed();
        }
        case FlywheelSpeed::Ludicrous: {
            return Settings.getFlywheelLudicrousSpeed();
        }
    }

    return 0;
}

float FlywheelController::getMotorSpeedAdjustment(FlywheelMotor motor) {
    switch (motor) {
        case FlywheelMotor::Motor1: {
            return Settings.getFlywheelM1TrimAdjustment();
        }
        case FlywheelMotor::Motor2: {
            return Settings.getFlywheelM2TrimAdjustment();
        }
    }

    return 1;
}

void FlywheelController::onStop() {
    auto minimum = min(m_m1Speed, m_m2Speed);
    auto step = calculateStepFromValue(minimum);

    m_driver.setSpeeds(0, 0);
    m_driver.disableDrivers();

    MCU.delaySafe(1);
    m_m1Speed = 0;
    m_m2Speed = 0;
}

FlywheelSpeed FlywheelController::getSpeed() {
    return m_speed;
}

void FlywheelController::setSpeed(FlywheelSpeed speed) {
    m_speed = speed;

    if (isRunning()) {
        updateDrivers();
    }
}

void FlywheelController::setMotorSpeedAdjustment(FlywheelMotor motor, float adjustment) {
    if (adjustment < 0) {
        return;
    }

    switch (motor) {
        case FlywheelMotor::Motor1: {
            Settings.setFlywheelM1TrimAdjustment(adjustment);
            break;
        }
        case FlywheelMotor::Motor2: {
            Settings.setFlywheelM2TrimAdjustment(adjustment);
            break;
        }
    }

    if (isRunning()) {
        updateDrivers();
    }
}