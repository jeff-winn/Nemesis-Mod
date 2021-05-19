#include "FlywheelCommand.h"

FlywheelCommand::FlywheelCommand(FlywheelController* controller) {
    m_controller = controller;
}

FlywheelCommand::~FlywheelCommand() {
    m_controller = NULL;
}