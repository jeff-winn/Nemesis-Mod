#ifndef INTERRUPT_PIN_H
#define INTERRUPT_PIN_H

#include "Pin.h"

// Represents a GPIO interrupt pin with a user defined callback function.
class InterruptPin : public Pin {
    public:
        using Pin::Pin;

        // Initializes the pin.
        virtual void init(InterruptCallback onInterruptCallback, InterruptMode mode);

        // Reads the value of the pin.
        virtual int read();
};

#endif