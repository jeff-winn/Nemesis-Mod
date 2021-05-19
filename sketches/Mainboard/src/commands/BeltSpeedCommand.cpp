#include "BeltSpeedCommand.h"

BeltSpeedCommand::BeltSpeedCommand(FeedController* controller) {
    m_controller = controller;
}

BeltSpeedCommand::~BeltSpeedCommand() {
    m_controller = NULL;
}

void BeltSpeedCommand::handleImpl(uint8_t* data, uint16_t len) {
    auto newSpeed = getSpeedFromPacket(data);
    m_controller->setSpeed(newSpeed);
}

BeltSpeed BeltSpeedCommand::getSpeedFromPacket(uint8_t* data) {
    auto value = data[0];

    switch (value) {
        case 2: {
            return BeltSpeed::Medium;            
        }
        case 255: {
            return BeltSpeed::Max;
        }
    }

    return BeltSpeed::Normal;
}