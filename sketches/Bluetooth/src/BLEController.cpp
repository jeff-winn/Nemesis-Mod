#include "BLEController.h"

const uint32_t NOTIFICATION_INTERVAL_IN_MSECS = 10000; // 10 seconds
const uint32_t NOTIFICATION_INTERVAL_WHILE_ACTIVE_IN_MSECS = 1000; // 1 second

BLEController BLE = BLEController();

BLEController::BLEController() {
  m_blasterService = BlasterService();
  m_configService = ConfigurationService();

  m_discoveryService = BLEDis();
}

BLEController::~BLEController() {
}

void BLEController::init() {
  Bluefruit.begin();
  Bluefruit.setName("Nerf Nemesis MXVII-10K");
  Bluefruit.autoConnLed(false);
  
  Bluefruit.ScanResponse.addName();  
  Bluefruit.Periph.begin();

  m_discoveryService.setManufacturer("Jeff Winn");
  m_discoveryService.setModel("Nerf Nemesis MXVII-10K");
  m_discoveryService.begin();

  m_blasterService.begin();
  m_blasterService.init();

  m_configService.begin();
  m_configService.init();

  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();
  Bluefruit.Advertising.addService(m_blasterService);
  Bluefruit.Advertising.addService(m_configService);
  Bluefruit.Advertising.addName();

  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.setInterval(32, 244);
  Bluefruit.Advertising.setFastTimeout(30);
}

void BLEController::startAdvertising() {
  /* Start Advertising
    * - Enable auto advertising if disconnected
    * - Interval:  fast mode = 20 ms, slow mode = 152.5 ms
    * - Timeout for fast mode is 30 seconds
    * - Start(timeout) with timeout = 0 will advertise forever (until connected)
    * 
    * For recommended advertising interval
    * https://developer.apple.com/library/content/qa/qa1931/_index.html   
  */
  Bluefruit.Advertising.start(0);
}

void BLEController::clearBonds() {
  Bluefruit.clearBonds();
}