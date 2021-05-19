#include "BitConverter.h"

BitConverter Convert;

union int32_bytes_t {
    byte raw[4];
    int value;
};

union float_bytes_t {
    byte raw[4];
    float value;
};

int BitConverter::toInt32(const byte* address) {
    int output;

    *((byte*)(&output) + 3) = address[3];
    *((byte*)(&output) + 2) = address[2];
    *((byte*)(&output) + 1) = address[1];
    *((byte*)(&output) + 0) = address[0];

    return output;
}

byte* BitConverter::toInt32Array(const int value) {
    int32_bytes_t r;
    r.value = value;

    byte* result = new byte[4];

    for (int index = 0; index < 4; index++) {
        result[index] = r.raw[index];
    };

    return result;
}

float BitConverter::toFloat(const byte* address) {
    float output;

    *((byte*)(&output) + 3) = address[3];
    *((byte*)(&output) + 2) = address[2];
    *((byte*)(&output) + 1) = address[1];
    *((byte*)(&output) + 0) = address[0];

    return output;
}

byte* BitConverter::toFloatArray(const float value) {
    float_bytes_t r;
    r.value = value;

    byte* result = new byte[4];

    for (int index = 0; index < 4; index++) {
        result[index] = r.raw[index];
    };

    return result;
}