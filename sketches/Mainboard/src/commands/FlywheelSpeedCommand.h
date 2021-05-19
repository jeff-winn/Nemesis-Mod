#ifndef FLYWHEEL_SPEED_COMMAND_H
#define FLYWHEEL_SPEED_COMMAND_H

#include "FlywheelCommand.h"

// Provides a command which handles flywheel speed changes.
class FlywheelSpeedCommand : public FlywheelCommand {
    public:
        using FlywheelCommand::FlywheelCommand;

    protected:
        void handleImpl(uint8_t* data, uint16_t len) override;
        FlywheelSpeed getSpeedFromPacket(uint8_t* data);
};

#endif /* FLYWHEEL_SPEED_COMMAND_H */