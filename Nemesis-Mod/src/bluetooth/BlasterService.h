#ifndef BLASTER_SERVICE_H
#define BLASTER_SERVICE_H

#include <bluefruit.h>
#include "CustomBLEService.h"

class BlasterService : public CustomBLEService {
    public:
        BlasterService();

        void init() override;

    private:
        BLECharacteristic _flywheelSpeed;
        BLECharacteristic _flywheelM1TrimSpeed;
        BLECharacteristic _flywheelM2TrimSpeed;
        BLECharacteristic _beltSpeed;
};

#endif /* BLASTER_SERVICE_H */