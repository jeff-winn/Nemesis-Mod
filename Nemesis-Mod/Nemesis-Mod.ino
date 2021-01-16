#include <Arduino.h>
#include "src/App.h"
#include "src/Button.h"
#include "src/Mainboard.h"

const uint16_t CLEAR_HOLD_IN_MSECS = 30000;  // 30 seconds
const uint16_t RESET_HOLD_IN_MSECS = 5000;   // 5 seconds
const uint32_t RESET_BUTTON_PIN = 28;

Button ResetButton = Button(RESET_BUTTON_PIN, true);

void setup() {    
    ResetButton.init();
    Application.init();
}

void loop() {
    if (ResetButton.isPressed()) {
        handleResetAttempt();
    }
    else {
        Application.run();
    }
}

void handleResetAttempt() {    
    auto started = millis();
    while (ResetButton.isPressed()) {
        MCU.delaySafe(50);
    }

    auto successful = false;
    auto diff = millis() - started;

    if (diff >= CLEAR_HOLD_IN_MSECS) {
        Application.clear();
    }
    else if (diff >= RESET_HOLD_IN_MSECS) {
        Application.reset();
    }
}