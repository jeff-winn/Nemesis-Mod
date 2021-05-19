#ifndef COMMAND_H
#define COMMAND_H

#include <stdint.h>

// Provides a base class for commands.
class Command {
    public:       
        virtual ~Command();

        // Indicates whether the command requires authorization to handle.
        virtual bool requiresAuthorization();

        // Handles the packet.
        void handle(uint8_t* data, uint16_t len);

    protected:
        virtual void handleImpl(uint8_t* data, uint16_t len);
        virtual bool validate(uint8_t* data, uint16_t len);
};

#endif /* COMMAND_H */