#include "src/BLEController.h"
#include "src/Callbacks.h"

void setup() {	
	// SetBluetoothCommandReceivedCallback()
	
	BLE.init();
	BLE.startAdvertising();
}

void loop() {
	delay(100);
}