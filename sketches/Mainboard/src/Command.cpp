#include "Command.h"

Command::~Command() {
}

void Command::handle(uint8_t* data, uint16_t len) {
    if (!validate(data, len)) {
        return;
    }

    handleImpl(data, len);
}

bool Command::validate(uint8_t* data, uint16_t len) {
    return true;
}

void Command::handleImpl(uint8_t* data, uint16_t len) {
}

bool Command::requiresAuthorization() {
    return true;
}