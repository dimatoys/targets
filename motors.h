/*
 * motors.h
 *
 *      Author: Dmitry Ryashchentsev
 */

#ifndef MOTORS_H_
#define MOTORS_H_

#include "sensors.h"

class TPositionMotor {
  public:
    virtual void MoveTo(int position);
    virtual void ReleasePower();

    static TPositionMotor* NewStepperMotor(unsigned int pinA1,
    		                               unsigned int pinB1,
						                   unsigned int pinA2,
						                   unsigned int pinB2,
						                   unsigned long delayMs);

    static TPositionMotor* NewServoMotor(unsigned int pin,
    		                             unsigned long delayMs);
};

#endif /* MOTORS_H_ */
