/*
 * sensors.cpp
 *
 *      Author: Dmitry ryashchentsev
 */

#include <Arduino.h>

class TReedSwitchSensor : TSensor {
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

static TSensor* TSensor::NewReedSwitchSensor(unsigned int pin) {
	return new TReedSwitchSensor(pin);
}
