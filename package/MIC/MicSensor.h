//  MicSensor.h - Xlight MIC sensor lib

#ifndef MicSensor_h
#define MicSensor_h

#include "application.h"

class MicSensor {
private:
	uint8_t _pin;
	uint8_t _type;
	bool firstreading;
	unsigned long _lastreadtime;
	uint16_t _lastValue;

	uint8_t peakToPeak = 0;   // peak-to-peak level
	uint8_t signalMax = 0;
	uint8_t signalMin = 1024;
	const uint8_t SAMPLE_WINDOW = 50; // Sample window width in mS (50 mS = 20Hz)
	uint8_t sample;
	unsigned long startMillis;  // Start of sample window

	bool pirState = 0;

	float read();

public:
	MicSensor(uint8_t pin, uint8_t type = 0);
	void begin();
	float getLoudnessVoltage();
};

#endif /* MicSensor_h */
