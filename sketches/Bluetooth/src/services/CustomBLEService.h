#ifndef CUSTOM_BLE_SERVICE_H
#define CUSTOM_BLE_SERVICE_H

#include <bluefruit.h>

class CustomBLEService : public BLEService {
    public:
        CustomBLEService(BLEUuid uuid);

        virtual void init();
};

#endif /* CUSTOM_BLE_SERVICE_H */