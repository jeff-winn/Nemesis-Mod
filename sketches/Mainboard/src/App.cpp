#include "App.h"
#include "Button.h"
#include "CommandFactory.h"
#include "ConfigurationSettings.h"
#include "FeedController.h"
#include "FlywheelController.h"
#include "Mainboard.h"

const uint32_t SYSTEM_OFF_IN_MSECS = 600000; // 10 minutes
const uint32_t REV_BUTTON_PIN = 13;
const uint32_t FIRING_BUTTON_PIN = 12;
const uint32_t HOPPER_LOCK_BUTTON_PIN = 19;

App Application = App();
Button RevTrigger = Button(REV_BUTTON_PIN);
Button FiringTrigger = Button(FIRING_BUTTON_PIN);
Button HopperLock = Button(HOPPER_LOCK_BUTTON_PIN);

App::App() {
    m_commandFactory = CommandFactory();
    m_isAuthorized = true;
    m_firing = false;
}

void App::run() {
    while (true) {
        if (shouldAllowRevvingFlywheels()) {
            revFlywheels();

            while (shouldAllowRevvingFlywheels()) {
                if (shouldAllowFiringRounds()) {
                    if (!isAlreadyFiring()) {
                        startFiring();
                    }
                }
                else {
                    stopFiring();
                }

                MCU.delaySafe(10);
            }

            stopFiring();
            stopFlywheels();
        }

        MCU.delaySafe(50);
    }
}

void App::revFlywheels() {
    Flywheels.start();
}

bool App::isAlreadyFiring() {
    return m_firing;
}

void App::startFiring() {
    m_firing = true;
    Belt.start();
}

void App::stopFiring() {
    Belt.stop();

    m_firing = false;
}

void App::stopFlywheels() {
    Flywheels.stop();
}

bool App::shouldAllowRevvingFlywheels() {
    return isAuthorized() && !isLockedOut() && RevTrigger.isPressed();
}

bool App::shouldAllowFiringRounds() {
    return isAuthorized() && !isLockedOut() && FiringTrigger.isPressed();
}

bool App::isLockedOut() {
    return Settings.isHopperLockEnabled() && !HopperLock.isPressed();    
}

bool App::isAuthorized() {
    return m_isAuthorized;
}

// Receives notifications whenever a bluetooth command has been received. 
void OnBluetoothCommandReceivedCallback(uint8_t type, uint8_t* data, uint16_t len, uint8_t subtype) {
    Application.onRemoteCommandReceived(type, data, len, subtype);
}

void App::init() {
    Settings.init(); 
    Flywheels.init();
    Belt.init();

    FiringTrigger.init();
    RevTrigger.init();
    HopperLock.init();
}

void App::onRemoteCommandReceived(uint8_t type, uint8_t* data, uint16_t len, uint8_t subtype) {   
    auto command = m_commandFactory.createCommand(type, subtype);
    if (command) {
        auto requiresAuthorization = command->requiresAuthorization();
        if (!requiresAuthorization || (requiresAuthorization && isAuthorized())) {
            command->handle(data, len);
        }
        
        delete command;
    }
}

void App::authenticate() {
    m_isAuthorized = true;
}

void App::revokeAuthorization() {
    m_isAuthorized = false;
}

void App::clear() {
    Settings.clear();

    resetCore();
}

void App::reset() {
    Settings.resetAuthenticationToken();
    Settings.defaultSettings();

    resetCore();
}

void App::resetCore() {
    revokeAuthorization();
}