#include "BitConverter.h"

BitConverter Convert;

int BitConverter::toInt32(const byte* address) {
    int result = 0;
    
    for (int index = 4; index >= 0; index--) {
        result += address[index] << (index * 8);
    }

    return result;
}

byte* BitConverter::toByteArray(const int value) {
    byte* result = new byte[4];

    for (int index = 0; index < 4; index++) {
        result[index] = (value >> (index * 8)) & 0xFF;
    }

    return result;
}