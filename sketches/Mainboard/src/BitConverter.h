#ifndef BIT_CONVERTER_H
#define BIT_CONVERTER_H

#include <Arduino.h>

// Provides methods to do binary conversions.
class BitConverter {
    public:
        // Converts the binary array to an int32_t type.
        int toInt32(const byte* address);

        // Converts the binary array to an float_t type.
        float toFloat(const byte* address);

        // Converts the value to a byte array.
        byte* toInt32Array(const int value);

        // Converts the value to a byte array.
        byte* toFloatArray(const float value);
};

// Performs conversions between data types.
extern BitConverter Convert;

#endif /* BIT_CONVERTER_H */