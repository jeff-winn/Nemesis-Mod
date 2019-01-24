#include "App.h"

App::App() {
    m_enabled = false;
}

void App::init() {
    m_flywheelController = new FlywheelController();
    m_flywheelController->init(FlywheelMotor::Motor1, 9, 8);
    m_flywheelController->init(FlywheelMotor::Motor2, 7, 6);

    m_revTrigger = new Button();
    m_revTrigger->init(12);
}

void App::run() {
    while (true) {
        if (m_revTrigger->isPressed()) {
            startAll();
        }
        else {
            stopAll();
        }
    }
}

void App::startAll() {
    m_flywheelController->startAll();
}

void App::stopAll() {
    m_flywheelController->stopAll();
}