#ifndef BUTTON_H
#define BUTTON_H

#include <stdint.h>

// Represents a button.
class Button {
    public:
        Button(uint32_t pin, bool inverted = false);

        virtual ~Button();

        // Initializes the button.
        virtual void init();

        // Returns a value indicating whether the button is pressed.
        virtual bool isPressed();

    private:
        uint32_t m_pin;
        bool m_inverted;
    
};

#endif /* BUTTON_H */