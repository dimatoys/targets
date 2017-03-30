/*
 * sensors.h
 *
 *      Author: Dmitry Ryashchentsev
 */

#ifndef SENSORS_H_
#define SENSORS_H_

#include <Arduino.h>

class TSensor {
public:
	virtual bool IsOn();
};

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

#endif /* SENSORS_H_ */
