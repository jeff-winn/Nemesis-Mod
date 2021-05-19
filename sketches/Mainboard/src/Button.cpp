#include "Mainboard.h"
#include "Button.h"

Button::Button(uint32_t pin, bool inverted) {
    m_pin = pin;
    m_inverted = inverted;
}

Button::~Button() {
}

void Button::init() {
    MCU.pinModeSafe(m_pin, PinMode::Read);    
}

bool Button::isPressed() {    
    auto value = MCU.digitalReadSafe(m_pin);
    if (m_inverted) {
        return !value;
    }
    
    return value;
}