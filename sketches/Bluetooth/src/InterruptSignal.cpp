#include <Arduino.h>
#include "InterruptSignal.h"

InterruptSignal::InterruptSignal(uint32_t pin, bool flagLed) {
	m_pin = pin;
	m_flagLed = flagLed;
}

void InterruptSignal::init() {
	pinMode(m_pin, OUTPUT);
}

void InterruptSignal::signal() {
	digitalWrite(m_pin, HIGH);
	
	if (m_flagLed) {
		digitalWrite(LED_RED, HIGH);
	}
}

void InterruptSignal::reset() {	
	digitalWrite(m_pin, LOW);

	if (m_flagLed) {
		digitalWrite(LED_RED, LOW);
	}
}