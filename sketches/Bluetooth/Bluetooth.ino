#include <Wire.h>
#include "src/BLEController.h"
#include "src/Callbacks.h"
#include "src/InterruptSignal.h"

const uint8_t I2C_ADDRESS = 0xA1;
const uint32_t INTERRUPT_PIN = 13; // The pin to be signaled when data is waiting for transfer.

InterruptSignal IRQ = InterruptSignal(INTERRUPT_PIN, true);

void setup() {
	pinMode(INTERRUPT_PIN, OUTPUT);

	Wire.begin(I2C_ADDRESS);
	Wire.onRequest(OnWireDataRequested);

	// SetBluetoothCommandReceivedCallback()
	IRQ.init();
	
	BLE.init();
	BLE.startAdvertising();
}

void loop() {
	IRQ.signal();

	delay(1000);

	IRQ.reset();
	
	delay(1000);
}

// Callback which executes when the I2C master device requests the data held for transmission.
void OnWireDataRequested() {
}