#ifndef FLYWHEEL_COMMAND_H
#define FLYWHEEL_COMMAND_H

#include "../Command.h"
#include "../FlywheelController.h"

// Provides a command which handles changes to the flywheel assembly.
class FlywheelCommand : public Command {
    public:
        FlywheelCommand(FlywheelController* controller);

        ~FlywheelCommand() override;

    protected:
        FlywheelController* m_controller;
};

#endif /* FLYWHEEL_COMMAND_H */