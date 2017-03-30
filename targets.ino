#include "motors.h"
#include "sensors.h"

class TTarget {
  
    TPositionMotor& Motor;
    int Low;
    int High;
    TSensor& Sensor;
  
  public:
    TTarget(TPositionMotor& motor, int low, int high, TSensor& sensor) {
      Motor = motor;
      Low = low;
      High = high;
      Sensor = sensor;

      Motor.MoveTo(Low);
      Motor.ReleasePower();
    }

    bool NeedToLift() {
      return Sensor.IsOn();
    }

    void Lift();
};

void TTarget::Lift() {
  Motor.MoveTo(High);
  Motor.MoveTo(Low);
  Motor.ReleasePower();
}


void Sleep(unsigned long ms) {
  unsigned long complete = millis() + ms;
  while(millis() < complete);
}

// Pins

const uint8_t SERNSOR_1 = 12;
const uint8_t SERNSOR_2 = 7;
const uint8_t SERNSOR_3 = 19;
const uint8_t SERNSOR_4 = 18;
const uint8_t SERNSOR_5 = 17;

const uint8_t STEPPER_A1_1 = 9;
const uint8_t STEPPER_B1_1 = 8;
const uint8_t STEPPER_A2_1 = 11;
const uint8_t STEPPER_B2_1 = 10;

const uint8_t SERVO_PIN_2 = 4;
const uint8_t SERVO_PIN_3 = 23;
const uint8_t SERVO_PIN_4 = 22;
const uint8_t SERVO_PIN_5 = 21;

const unsigned long STEPPER_STEP_DELAY_MS = 15; 
const unsigned long SERVO_POSITION_DELAY_MS = 5;

const int POSITIOM_LOW_1 = 0;
const int POSITIOM_HIGH_1 = 65;

const int POSITIOM_LOW_2 = 25;
const int POSITIOM_HIGH_2 = 135;

const int POSITIOM_LOW_3 = 20;
const int POSITIOM_HIGH_3 = 125;

const int POSITIOM_LOW_4 = 36;
const int POSITIOM_HIGH_4 = 135;

const int POSITIOM_LOW_5 = 10;
const int POSITIOM_HIGH_5 = 115;

TStepper stepper1(STEPPER_A1_1, STEPPER_B1_1, STEPPER_A2_1, STEPPER_B2_1, STEPPER_STEP_DELAY_MS);
TReedSwitchSensor sensor1(SERNSOR_1);
TTarget target1(stepper1, POSITIOM_LOW_1, POSITIOM_HIGH_1, sensor1);

TServo servo2(SERVO_PIN_2, SERVO_POSITION_DELAY_MS);
TReedSwitchSensor sensor2(SERNSOR_2);
TTarget target2(servo2, POSITIOM_LOW_2, POSITIOM_HIGH_2, sensor2);

TServo servo3(SERVO_PIN_3, SERVO_POSITION_DELAY_MS);
TReedSwitchSensor sensor3(SERNSOR_3);
TTarget target3(servo3, POSITIOM_LOW_3, POSITIOM_HIGH_3, sensor3);

TServo servo4(SERVO_PIN_4, SERVO_POSITION_DELAY_MS);
TReedSwitchSensor sensor4(SERNSOR_4);
TTarget target4(servo4, POSITIOM_LOW_4, POSITIOM_HIGH_4, sensor4);

TServo servo5(SERVO_PIN_5, SERVO_POSITION_DELAY_MS);
TReedSwitchSensor sensor5(SERNSOR_5);
TTarget target5(servo5, POSITIOM_LOW_5, POSITIOM_HIGH_5, sensor5);

const int MAX_TARGETS = 20;
TTarget& targets[MAX_TARGETS];
int num_targets = 0;

void setup() {

    randomSeed(analogRead(0));
  
    targets[num_targets++] = target1;
    targets[num_targets++] = target2;
    targets[num_targets++] = target3;
    targets[num_targets++] = target4;
    targets[num_targets++] = target5;
}


void loop() {

    int num_to_lift = 0;
    TTarget& lift[MAX_TARGETS];

    for (int i = 0; i < num_targets; i++) {
      if(targets[i].NeedToLift()) {
        lift[num_to_lift++] = targets[i];
      }
    }

    if (num_to_lift > 0) {
      lift[random(num_to_lift)].Lift();
    }

    Sleep(1000);

/*
      pinMode(8, OUTPUT);
      pinMode(9, OUTPUT);
      pinMode(10, OUTPUT);
      pinMode(11, OUTPUT);
      digitalWrite(8, LOW);
      digitalWrite(9, LOW);
      digitalWrite(10, LOW);
      digitalWrite(11, LOW);
*/
}

