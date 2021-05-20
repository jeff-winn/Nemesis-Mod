#include <Wire.h>
#include "src/BLEController.h"
#include "src/Callbacks.h"
#include "src/InterruptSignal.h"

const uint8_t I2C_ADDRESS = 0xA1;
InterruptSignal Interrupt = InterruptSignal(13, true); // The interrupt which will signal there is data pending transfer.

void setup() {
	Wire.begin(I2C_ADDRESS);
	Wire.onRequest(OnWireDataRequested);

	// SetBluetoothCommandReceivedCallback()
	Interrupt.init();
	
	BLE.init();
	BLE.startAdvertising();
}

void loop() {
	Interrupt.signal();

	delay(1000);

	Interrupt.reset();
	
	delay(1000);
}

// Callback which executes when the I2C master device requests the data held for transmission.
void OnWireDataRequested() {
}