#ifndef BELT_SPEED_COMMAND_H
#define BELT_SPEED_COMMAND_H

#include "../Command.h"
#include "../FeedController.h"

// Provides a command to change the belt speed.
class BeltSpeedCommand : public Command {
    public:
        BeltSpeedCommand(FeedController* controller);

        ~BeltSpeedCommand() override;

    protected:
        void handleImpl(uint8_t* data, uint16_t len) override;
        BeltSpeed getSpeedFromPacket(uint8_t* data);

    private:
        FeedController* m_controller;
};

#endif /* BELT_SPEED_COMMAND_H */