/*
 * motors.cpp
 *
 *      Author: Dmitry Ryashchentsev
 */

#include "motorsImp.h"

static TPositionMotor* TPositionMotor::NewStepperMotor(unsigned int pinA1,
    		                                           unsigned int pinB1,
						                               unsigned int pinA2,
						                               unsigned int pinB2,
						                               unsigned long delayMs) {

	return new TStepper(pinA1, pinB1, pinA2, pinB2, delayMs);
}

static TPositionMotor* NewServoMotor(unsigned int pin,
		                             unsigned long delayMs) {
	return new TServo(pin, delayMs);
}

void TStepper::WritePosition() {
    auto state = States[(Position % 4 + 4) % 4];
    while(millis() - LastMoveMs < DelayMs);
    digitalWrite(PinA1, state[0]);
    digitalWrite(PinB1, state[1]);
    digitalWrite(PinA2, state[2]);
    digitalWrite(PinB2, state[3]);
    LastMoveMs = millis();
}

void TStepper::MoveTo(int position) {
  while (position != Position) {
    Position += position < Position ? -1: 1;
    WritePosition();
  }
}

void TStepper::ReleasePower() {
    digitalWrite(PinA1, LOW);
    digitalWrite(PinB1, LOW);
    digitalWrite(PinA2, LOW);
    digitalWrite(PinB2, LOW);
    LastMoveMs = millis();
}


void TServo::MoveTo(int position) {
    if (!ServoAccess.attached()) {
      ServoAccess.attach(Pin);
    }

    while(millis() < CompleteTimeMs);
    ServoAccess.write(position);
    CompleteTimeMs = millis() + abs(TargetPosition - position) * DelayMs;
    TargetPosition = position;
}

void TServo::ReleasePower() {
    if (ServoAccess.attached()) {
      while(millis() < CompleteTimeMs);
      ServoAccess.detach();
    }
}

