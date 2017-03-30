/*
 * motorsImp.h
 *
 *      Author: Dmitry Ryashchentsev
 */

#ifndef MOTORSIMP_H_
#define MOTORSIMP_H_

#include "motors.h"

#include <Arduino.h>
//C:\Program Files (x86)\Arduino\hardware\teensy\avr\libraries\Servo
#include <Servo.h>

class TStepper : public TPositionMotor {
    uint8_t PinA1;
    uint8_t PinB1;
    uint8_t PinA2;
    uint8_t PinB2;

    int Position;
    unsigned long DelayMs;
    unsigned long LastMoveMs;

    const uint8_t States[4][4] = {{LOW, HIGH, LOW, HIGH},
                                  {HIGH, LOW, LOW, HIGH},
                                  {HIGH, LOW, HIGH, LOW},
                                  {LOW, HIGH, HIGH, LOW}};

    void WritePosition();

  public:

    TStepper(uint8_t pinA1,
    		 uint8_t pinB1,
			 uint8_t pinA2,
			 uint8_t pinB2,
			 unsigned long delayMs) {
      PinA1 = pinA1;
      PinB1 = pinB1;
      PinA2 = pinA2;
      PinB2 = pinB2;

      //60L * 1000L / number_of_steps / whatSpeed;
      DelayMs = delayMs;
      Position = 0;

      pinMode(PinA1, OUTPUT);
      pinMode(PinB1, OUTPUT);
      pinMode(PinA2, OUTPUT);
      pinMode(PinB2, OUTPUT);

      ReleasePower();
    }

    void MoveTo(int position);
    void ReleasePower();
};

class TServo : public TPositionMotor {
    unsigned long DelayMs;
    unsigned long CompleteTimeMs;
    int TargetPosition;
    uint8_t Pin;
    Servo ServoAccess;
  public:
    TServo(uint8_t pin, unsigned long delayMs) {
      Pin = pin;
      DelayMs = delayMs;
      TargetPosition = 0;
      CompleteTimeMs = 0;
    }

    void MoveTo(int position);
    void ReleasePower();
};

#endif /* MOTORSIMP_H_ */
