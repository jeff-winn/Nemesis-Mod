#include "App.h"
#include "BLEController.h"
#include "Button.h"
#include "Callbacks.h"
#include "CommandFactory.h"
#include "ConfigurationSettings.h"
#include "FeedController.h"
#include "FlywheelController.h"
#include "Mainboard.h"

const uint32_t SYSTEM_OFF_IN_MSECS = 600000; // 10 minutes
const uint32_t REV_BUTTON_PIN = 16;
const uint32_t FIRING_BUTTON_PIN = 15;
const uint32_t HOPPER_LOCK_BUTTON_PIN = 29;

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
    sendAmperesNotifications();
    
    if (shouldAllowRevvingFlywheels()) {
        revFlywheels();

        while (shouldAllowRevvingFlywheels()) {
            sendAmperesNotifications();

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

    waitForRevTriggerToBePressed();
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

void App::waitForRevTriggerToBePressed() {
    MCU.delaySafe(50);
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

    SetBluetoothCommandReceivedCallback(OnBluetoothCommandReceivedCallback);
    BLE.init();
    BLE.startAdvertising();

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
    // auto existingToken = Settings.getAuthenticationToken();

    // if (token.length > 0 && existingToken.length == 0) {
    //     // The user has not stored the authentication data yet, update it.
    //     Settings.setAuthenticationToken(token);        
    // }
    // else if (existingToken.length != token.length) {
    //     authorized = false;
    // }
    // else if (existingToken.length > 0) {
    //     for (byte index = 0; index < existingToken.length; index++) {
    //         authorized &= existingToken.data[index] == token.data[index];
    //     }
    // }

    m_isAuthorized = true;
}

void App::revokeAuthorization() {
    m_isAuthorized = false;
}

void App::sendAmperesNotifications() {
    auto flywheel1 = Flywheels.getMotorCurrentMilliamps(FlywheelMotor::Motor1);
    auto flywheel2 = Flywheels.getMotorCurrentMilliamps(FlywheelMotor::Motor2);
    BLE.notifyFlywheelCurrentMilliamps(flywheel1, flywheel2, RevTrigger.isPressed());

    auto feed = Belt.getMotorCurrentMilliamps();
    BLE.notifyBeltCurrentMilliamps(feed, FiringTrigger.isPressed());
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
    BLE.clearBonds();
}