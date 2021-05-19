#include <Adafruit_FRAM_I2C.h>
#include "ConfigurationSettings.h"
#include "BitConverter.h"

const short HAS_EXISTING_PAIRING_ADDR = 0x02;
const short OPERATOR_TOKEN_LENGTH_ADDR = 0x10;
const short OPERATOR_TOKEN_ADDR = 0x11;
const short FEED_NORMAL_SPEED_ADDR = 0x100;
const short FEED_MEDIUM_SPEED_ADDR = 0x104;
const short FEED_MAX_SPEED_ADDR = 0x108;
const short FLYWHEEL_KID_SPEED_ADDR = 0x112;
const short FLYWHEEL_NORMAL_SPEED_ADDR = 0x116;
const short FLYWHEEL_LUDICROUS_SPEED_ADDR = 0x120;
const short FLYWHEEL_TRIM_VARIANCE_ADDR = 0x124;
const short FLYWHEEL_M1_TRIM_ADJUSTMENT_ADDR = 0x128;
const short FLYWHEEL_M2_TRIM_ADJUSTMENT_ADDR = 0x132;
const short IS_HOPPER_LOCK_ENABLED_ADDR = 0x136;

ConfigurationSettings Settings = ConfigurationSettings();

// Defines the FRAM module for persistent data storage.
Adafruit_FRAM_I2C framDriver = Adafruit_FRAM_I2C();

void ConfigurationSettings::init() {
    framDriver.begin();

    if (!initialized()) {
        defaultSettings();
        resetAuthenticationToken();

        setInitialized(true);
    }
}

bool ConfigurationSettings::initialized() {
    return framDriver.read8(0x1) != 0;
}

void ConfigurationSettings::setInitialized(bool value) {
    framDriver.write8(0x1, (value ? 0xFF : 0x00));
}

void ConfigurationSettings::defaultSettings() {
    setExistingPairing(false);
    setIsHopperLockEnabled(true);

    setFeedNormalSpeed(100);
    setFeedMediumSpeed(175);
    setFeedMaxSpeed(400);

    setFlywheelKidSpeed(195);
    setFlywheelNormalSpeed(215);
    setFlywheelLudicrousSpeed(400);
    setFlywheelTrimVariance(0.1F);
    setFlywheelM1TrimAdjustment(1.0F);
    setFlywheelM2TrimAdjustment(1.0F);
}

void ConfigurationSettings::clear() {
    for (int addr = 0; addr < 32000; addr++) {
        framDriver.write8(addr, 0x00);
    }
}

bool ConfigurationSettings::hasExistingPairing() {
    return framDriver.read8(HAS_EXISTING_PAIRING_ADDR) != 0x00;
}

void ConfigurationSettings::setExistingPairing(bool value) {
    uint8_t raw = 0x00;
    if (value) {
        raw = 0xFF;
    }

    framDriver.write8(HAS_EXISTING_PAIRING_ADDR, raw);
}

void ConfigurationSettings::resetAuthenticationToken() {
    for (uint16_t addr = OPERATOR_TOKEN_ADDR; addr < FEED_NORMAL_SPEED_ADDR; addr++) {
        framDriver.write8(addr, 0x00);
    }
}

int ConfigurationSettings::getFeedNormalSpeed() {
    return readInt32(FEED_NORMAL_SPEED_ADDR);
}

void ConfigurationSettings::setFeedNormalSpeed(int value) {
    writeInt32(FEED_NORMAL_SPEED_ADDR, value);
}

int ConfigurationSettings::getFeedMediumSpeed() {
    return readInt32(FEED_MEDIUM_SPEED_ADDR);
}

void ConfigurationSettings::setFeedMediumSpeed(int value) {
    writeInt32(FEED_MEDIUM_SPEED_ADDR, value);
}

int ConfigurationSettings::getFeedMaxSpeed() {
    return readInt32(FEED_MAX_SPEED_ADDR);
}

void ConfigurationSettings::setFeedMaxSpeed(int value) {    
    writeInt32(FEED_MAX_SPEED_ADDR, value);
}

int ConfigurationSettings::getFlywheelKidSpeed() {
    return readInt32(FLYWHEEL_KID_SPEED_ADDR);
}

void ConfigurationSettings::setFlywheelKidSpeed(int value) {
    writeInt32(FLYWHEEL_KID_SPEED_ADDR, value);
}

int ConfigurationSettings::getFlywheelNormalSpeed() {
    return readInt32(FLYWHEEL_NORMAL_SPEED_ADDR);
}

void ConfigurationSettings::setFlywheelNormalSpeed(int value) {    
    writeInt32(FLYWHEEL_NORMAL_SPEED_ADDR, value);
}

int ConfigurationSettings::getFlywheelLudicrousSpeed() {
    return readInt32(FLYWHEEL_LUDICROUS_SPEED_ADDR);
}

void ConfigurationSettings::setFlywheelLudicrousSpeed(int value) {
    writeInt32(FLYWHEEL_LUDICROUS_SPEED_ADDR, value);
}

float ConfigurationSettings::getFlywheelTrimVariance() {
    return readFloat(FLYWHEEL_TRIM_VARIANCE_ADDR);
}

void ConfigurationSettings::setFlywheelTrimVariance(float value) {
    writeFloat(FLYWHEEL_TRIM_VARIANCE_ADDR, value);
}

float ConfigurationSettings::getFlywheelM1TrimAdjustment() {
    return readFloat(FLYWHEEL_M1_TRIM_ADJUSTMENT_ADDR);
}

void ConfigurationSettings::setFlywheelM1TrimAdjustment(float value) {
    writeFloat(FLYWHEEL_M1_TRIM_ADJUSTMENT_ADDR, value);
}

float ConfigurationSettings::getFlywheelM2TrimAdjustment() {
    return readFloat(FLYWHEEL_M2_TRIM_ADJUSTMENT_ADDR);
}

void ConfigurationSettings::setFlywheelM2TrimAdjustment(float value) {
    writeFloat(FLYWHEEL_M2_TRIM_ADJUSTMENT_ADDR, value);
}

bool ConfigurationSettings::isHopperLockEnabled() {
    return readBool(IS_HOPPER_LOCK_ENABLED_ADDR);
}

void ConfigurationSettings::setIsHopperLockEnabled(bool value) {
    writeBool(IS_HOPPER_LOCK_ENABLED_ADDR, value);
}

bool ConfigurationSettings::readBool(short address) {
    auto value = readInt32(address);
    return value != 0;
}

void ConfigurationSettings::writeBool(short address, bool value) {
    uint32_t rawValue = 0;
    if (value) {
        rawValue = 1;
    }

    writeInt32(address, rawValue);
}

int ConfigurationSettings::readInt32(short address) {
    byte raw[4];

    for (auto index = 0; index < 4; index++) {
        raw[index] = framDriver.read8(address + index);
    }

    return Convert.toInt32(raw);
}

void ConfigurationSettings::writeInt32(short address, int value) {
    byte* raw = Convert.toInt32Array(value);

    for (auto index = 0; index < 4; index++) {
        framDriver.write8(address + index, raw[index]);
    }

    delete[] raw;
}

float ConfigurationSettings::readFloat(short address) {
    byte raw[4];

    for (auto index = 0; index < 4; index++) {
        raw[index] = framDriver.read8(address + index);
    }

    return Convert.toFloat(raw);
}

void ConfigurationSettings::writeFloat(short address, float value) {
    byte* raw = Convert.toFloatArray(value);

    for (auto index = 0; index < 4; index++) {
        framDriver.write8(address + index, raw[index]);
    }

    delete[] raw;
}