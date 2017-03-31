/*
 * sensors.cpp
 *
 *      Author: Dmitry ryashchentsev
 */

#include "sensors.h"

#include <Arduino.h>

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
