#ifndef CONFIGURATION_SETTINGS_H
#define CONFIGURATION_SETTINGS_H

#include <Arduino.h>

// Provides access to the configuration settings.
class ConfigurationSettings {
    public:
        // AuthenticationToken_t getAuthenticationToken();
        // void setAuthenticationToken(AuthenticationToken_t token);
        void resetAuthenticationToken();

        void setExistingPairing(bool value);
        bool hasExistingPairing();

        int getFeedNormalSpeed();
        void setFeedNormalSpeed(int value);

        int getFeedMediumSpeed();
        void setFeedMediumSpeed(int value);

        int getFeedMaxSpeed();
        void setFeedMaxSpeed(int value);

        float getFlywheelTrimVariance();
        void setFlywheelTrimVariance(float value);

        int getFlywheelKidSpeed();
        void setFlywheelKidSpeed(int value);

        int getFlywheelNormalSpeed();
        void setFlywheelNormalSpeed(int value);

        int getFlywheelLudicrousSpeed();
        void setFlywheelLudicrousSpeed(int value);

        float getFlywheelM1TrimAdjustment();
        void setFlywheelM1TrimAdjustment(float value);

        float getFlywheelM2TrimAdjustment();
        void setFlywheelM2TrimAdjustment(float value);

        bool isHopperLockEnabled();
        void setIsHopperLockEnabled(bool value);

        // Initializes the configuration settings.
        void init();

        // Defaults all of the configuration settings.
        void defaultSettings();

        // Clears the configuration settings.
        void clear();

    protected:
        bool initialized();
        void setInitialized(bool value);

        int readInt32(short address);
        void writeInt32(short address, int value);

        float readFloat(short address);
        void writeFloat(short address, float value);

        bool readBool(short address);
        void writeBool(short address, bool value);
};

// Defines the instance of configuration settings used by the hardware.
extern ConfigurationSettings Settings;

#endif /* CONFIGURATION_SETTINGS_H */