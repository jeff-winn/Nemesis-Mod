#ifndef CONFIGURATION_SERVICE_H
#define CONFIGURATION_SERVICE_H

#include "CustomBLEService.h"

class ConfigurationService : public CustomBLEService {
    public:
        ConfigurationService();

        void init() override;
    
    private:
        BLECharacteristic m_flywheelNormalSpeed;
        BLECharacteristic m_flywheelKidSpeed;
        BLECharacteristic m_flywheelLudicrousSpeed;
        BLECharacteristic m_flywheelTrimVariance;
        BLECharacteristic m_beltNormalSpeed;
        BLECharacteristic m_beltMediumSpeed;
        BLECharacteristic m_beltMaxSpeed;
        BLECharacteristic m_hopperLockEnabled;
};

#endif /* CONFIGURATION_SERVICE_H */