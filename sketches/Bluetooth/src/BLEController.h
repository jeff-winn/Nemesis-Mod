#ifndef BLE_CONTROLLER_H
#define BLE_CONTROLLER_H

#include <bluefruit.h>
#include "services/BlasterService.h"
#include "services/ConfigurationService.h"

// Provides a controller for the on-board bluetooth module.
class BLEController {
    public:
        BLEController();

        ~BLEController();

        void init();
        void startAdvertising();

        void clearBonds();

        void notifyFlywheelCurrentMilliamps(uint32_t m1, uint32_t m2, bool isActive);
        void notifyBeltCurrentMilliamps(uint32_t m1, bool isActive);
    
    protected:
        bool shouldSendNotification(uint32_t lastNotificationAtMillis, uint32_t interval);

    private:
        BlasterService m_blasterService;
        ConfigurationService m_configService;
        
        BLEDis m_discoveryService;

        uint32_t m_lastFlywheelMilliampsNotifyAtMillis;
        uint32_t m_lastBeltMilliampsNotifyAtMillis;
};

extern BLEController BLE;

#endif /* BLE_CONTROLLER_H */