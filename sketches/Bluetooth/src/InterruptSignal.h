#ifndef INTERRUPT_SIGNAL_H

class InterruptSignal {
	public:
		InterruptSignal(uint32_t pin, bool flagLed = false);

		void signal();
		void reset();

		void init();

	private:
		uint32_t m_pin;
		bool m_flagLed;
};

#endif /* INTERRUPT_SIGNAL_H */