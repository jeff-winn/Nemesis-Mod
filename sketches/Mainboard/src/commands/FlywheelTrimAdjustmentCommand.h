#ifndef FLYWHEEL_TRIM_ADJUSTMENT_COMMAND_H
#define FLYWHEEL_TRIM_ADJUSTMENT_COMMAND_H

#include "../Command.h"
#include "FlywheelCommand.h"

// Provides a command which handles flywheel trim adjustment changes.
class FlywheelTrimAdjustmentCommand : public FlywheelCommand {
    public:
        FlywheelTrimAdjustmentCommand(uint8_t subtype, FlywheelController* controller);

    protected:
        void handleImpl(uint8_t* data, uint16_t len) override;

        FlywheelMotor getMotor();
        float getAdjustmentFromPacket(uint8_t* data);        

    private:
        uint8_t m_subtype;
};

#endif /* FLYWHEEL_TRIM_ADJUSTMENT_COMMAND_H */