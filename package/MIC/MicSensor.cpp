/**
* MicSensor.cpp - Xlight MIC sensor lib
*
* Created by Umar Bhutta <umar.bh@datatellit.com>
* Copyright (C) 2015-2016 DTIT
* Full contributor list:
*
* Documentation:
* Support Forum:
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* version 2 as published by the Free Software Foundation.
*
*******************************
*
* REVISION HISTORY
* Version 1.0 - Created by Umar Bhutta <umar.bh@datatellit.com>
*
* DESCRIPTION
* 1. support PIR MIC sensor (3 pin)
* 2. MicSensor::read() functionality has been emulated from Adafruit's Mic Amplifier
*    example. Audio signal from the amp is a varying voltage. Multiple measurements
*    are taken to find the min and max (peak-to-peak) amplitude of the signal.
*		 The difference between min and max samples is computed and converted to volts.
*	3. A 50ms window is used (20Hz frequency - lower limit of human hearing).
*
**/

#include "MicSensor.h"

MicSensor::MicSensor(uint8_t pin, uint8_t type)
{
	_pin = pin;
	_type = type;
	firstreading = true;
}

void MicSensor::begin()
{
	pinMode(_pin, INPUT);
	_lastreadtime = 0;
	_lastValue = 0;
	startMillis = millis();
}

float MicSensor::getLoudnessVoltage()
{
	float loudnessVoltage = read();
	return loudnessVoltage;
}

float MicSensor::read()
{
	unsigned long currenttime;
	currenttime = millis();

	if (currenttime < _lastreadtime)
	{
		_lastreadtime = 0;
	}
	if (firstreading || ((currenttime - _lastreadtime) >= 25))
		//Mic readings will be collected in IntervalTimer function from an interrupt context, which is very fast - currently 25s.
	{
		// collect data for 50 mS
		while (currenttime - startMillis < SAMPLE_WINDOW)
		{
			sample = analogRead(_pin);
			if (sample < 1024)  // toss out bad readings
			{
				if (sample > signalMax)
				{
					signalMax = sample;  // save just the max levels
				}
				else if (sample < signalMin)
				{
					signalMin = sample;  // save just the min levels
				}
			}
		}

		firstreading = false;
		_lastreadtime = millis();

	}

	peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude
	float volts = (peakToPeak * 3.3) / 1024;  // convert to volts

	return volts;
}
