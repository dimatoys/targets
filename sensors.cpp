/*
 * sensors.cpp
 *
 *      Author: Dmitry ryashchentsev
 */

#include "sensors.h"

#include <Arduino.h>

/*
static TPuller* SingletonePuller = NULL;

TPuller* TPuller::Instance() {
	if (SingletonePuller == NULL) {
		SingletonePuller = new TPuller();
	}
	return SingletonePuller;
}

*/

void TPuller::SleepBy(unsigned long timeMs) {
	// don't care about overflow since the overflow loop is ~49 days
	while(millis() < timeMs) {
		Pull();
	}
}

class TReedSwitchSensor : public TSensor {
    uint8_t Pin;
  public:
    TReedSwitchSensor(uint8_t pin) {
      Pin = pin;
      pinMode(pin, INPUT_PULLUP);
    }

    bool IsOn() {
      return digitalRead(Pin) == LOW;
    }
};

TSensor* TSensor::NewReedSwitchSensor(unsigned int pin) {
	return new TReedSwitchSensor(pin);
}
