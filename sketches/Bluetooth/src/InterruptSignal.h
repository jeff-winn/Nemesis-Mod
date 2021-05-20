#ifndef INTERRUPT_SIGNAL_H

// A mechanism which is capable of signaling the master device there is data pending transfer.
class InterruptSignal {
	public:
		InterruptSignal(uint32_t pin, bool flagLed = false);

		// Signals the interrupt.
		void signal();

		// Resets the interrupt.
		void reset();

		// Initializes the interrupt.
		void init();

	private:
		uint32_t m_pin;
		bool m_flagLed;
};

#endif /* INTERRUPT_SIGNAL_H */