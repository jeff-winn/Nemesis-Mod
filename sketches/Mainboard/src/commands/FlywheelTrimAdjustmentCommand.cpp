#include "FlywheelTrimAdjustmentCommand.h"
#include "../BitConverter.h"

FlywheelTrimAdjustmentCommand::FlywheelTrimAdjustmentCommand(uint8_t subtype, FlywheelController* controller) : FlywheelCommand(controller) {
    m_subtype = subtype;    
}

void FlywheelTrimAdjustmentCommand::handleImpl(uint8_t* data, uint16_t len) {
    auto motor = getMotor();
    auto adjustment = getAdjustmentFromPacket(data);

    m_controller->setMotorSpeedAdjustment(motor, adjustment);
}

FlywheelMotor FlywheelTrimAdjustmentCommand::getMotor() {
    switch (m_subtype) {
        case 1: {
            return FlywheelMotor::Motor1;
        }
        case 2: {
            return FlywheelMotor::Motor2;
        }
    }
}

float FlywheelTrimAdjustmentCommand::getAdjustmentFromPacket(uint8_t* data) {
    return Convert.toFloat(data);
}