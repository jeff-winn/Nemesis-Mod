#ifndef ANALOG_PIN_H
#define ANALOG_PIN_H

#include "Pin.h"

// Represents a GPIO analog pin.
class AnalogPin : public Pin {
    public:
        using Pin::Pin;

        // Reads the value of the pin.
        virtual int read();

        // Writes the value to the pin.
        virtual void write(uint32_t value);
};

#endif