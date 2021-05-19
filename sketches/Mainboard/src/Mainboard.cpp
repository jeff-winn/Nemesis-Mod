#include <Arduino.h>
#include "Mainboard.h"

Mainboard MCU = Mainboard();

void Mainboard::delaySafe(unsigned long milliseconds) {
    delay(milliseconds);
}

int Mainboard::analogReadSafe(uint32_t pin) {
    return analogRead(pin);
}

void Mainboard::analogWriteSafe(uint32_t pin, uint32_t value) {
    analogWrite(pin, value);
}

int Mainboard::digitalReadSafe(uint32_t pin) {
    return digitalRead(pin);
}

void Mainboard::digitalWriteSafe(uint32_t pin, uint32_t value) {
    digitalWrite(pin, value);
}

void Mainboard::pinModeSafe(uint32_t pin, PinMode mode) {
    uint32_t modeId;

    switch (mode) {
        case PinMode::Read: {
            modeId = INPUT;
            break;
        }
        case PinMode::Write: {
            modeId = OUTPUT;
            break;
        }
    }

    pinMode(pin, modeId);
}

void Mainboard::waitforEventSafe(uint32_t pin, uint8_t mode) {
}