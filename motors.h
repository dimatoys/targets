/*
 * motors.h
 *
 *      Author: Dmitry Ryashchentsev
 */

#ifndef MOTORS_H_
#define MOTORS_H_

#include <Arduino.h>

//C:\Program Files (x86)\Arduino\hardware\teensy\avr\libraries\Servo
#include <Servo.h>

class TPositionMotor {
  public:
    virtual void MoveTo(int position);
    virtual void ReleasePower();
};


class TStepper : public TPositionMotor {
    uint8_t PinA1;
    uint8_t PinB1;
    uint8_t PinA2;
    uint8_t PinB2;

    int Position;
    unsigned long Delay;
    unsigned long LastMoveMs;

    const uint8_t States[4][4] = {{LOW, HIGH, LOW, HIGH},
                                  {HIGH, LOW, LOW, HIGH},
                                  {HIGH, LOW, HIGH, LOW},
                                  {LOW, HIGH, HIGH, LOW}};

    void WritePosition();

  public:

    TStepper(uint8_t a1, uint8_t b1, uint8_t a2, uint8_t b2, unsigned long delay) {
      PinA1 = a1;
      PinB1 = b1;
      PinA2 = a2;
      PinB2 = b2;

      //60L * 1000L / number_of_steps / whatSpeed;
      Delay = delay;
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
    unsigned int Delay;
    unsigned long CompleteTimeMs;
    int TargetPosition;
    uint8_t Pin;
    Servo ServoAccess;
  public:
    TServo(uint8_t pin, unsigned int delay) {
      Pin = pin;
      Delay = delay;
      TargetPosition = 0;
      CompleteTimeMs = 0;
    }

    void MoveTo(int position);
    void ReleasePower();
};


#endif /* MOTORS_H_ */
