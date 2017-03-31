#include "motors.h"

#include <string.h>

class TTarget {
  
    TPositionMotor* Motor;
    int Low;
    int High;
    TSensor* Sensor;
    unsigned long DropTimeMs;
  
  public:

    bool LiftInProgress;

    TTarget(TPositionMotor* motor,
    		int low,
			int high,
			TSensor* sensor) {
      Motor = motor;
      Low = low;
      High = high;
      Sensor = sensor;
      DropTimeMs = 0;
      LiftInProgress = false;

      Motor->MoveTo(Low);
      Motor->ReleasePower();
    }

    void PullSensor() {
    	if (Sensor->IsOn()) {
    		if (DropTimeMs == 0 ) {
    			// just dropped
    			DropTimeMs = millis();
    		}
    	} else {
    		// set it here, because target can be lifted manually
    		DropTimeMs = 0;
    	}
    }

    unsigned long DroppedTimeMs() {
    	if (DropTimeMs > 0) {
    		return millis() - DropTimeMs;
    	} else {
    		return 0;
    	}
    }

    void Lift();
};

const int MAX_TARGETS = 20;

class TStatistics {
	unsigned long LastPullingTime;
	unsigned long StandTimes[MAX_TARGETS + 1];
public:

	void Reset();
	void Update(unsigned int numStanding);
};

void TStatistics::Reset() {
	memset(&StandTimes, 0, sizeof(StandTimes));
	LastPullingTime = millis();
}

void TStatistics::Update(unsigned int numStanding) {
	unsigned long pullingTimeMs = millis();
	StandTimes[numStanding] += pullingTimeMs - LastPullingTime;
	LastPullingTime = pullingTimeMs;
}

void TTarget::Lift() {
	// do not count lifting time as a stand one
	LiftInProgress = true;
	Motor->MoveTo(High);
	Motor->MoveTo(Low);
	Motor->ReleasePower();
	LiftInProgress = false;
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

const unsigned long MIN_DROP_TIME_MS = 2000;
const unsigned long LOOP_DELAY_MS = 1000;

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

TTarget target1(TPositionMotor::NewStepperMotor(STEPPER_A1_1,
		                                         STEPPER_B1_1,
												 STEPPER_A2_1,
												 STEPPER_B2_1,
												 STEPPER_STEP_DELAY_MS),
		        POSITIOM_LOW_1,
				POSITIOM_HIGH_1,
				TSensor::NewReedSwitchSensor(SERNSOR_1));

TTarget target2(TPositionMotor::NewServoMotor(SERVO_PIN_2,
		                                       SERVO_POSITION_DELAY_MS),
		        POSITIOM_LOW_2,
				POSITIOM_HIGH_2,
				TSensor::NewReedSwitchSensor(SERNSOR_2));

TTarget target3(TPositionMotor::NewServoMotor(SERVO_PIN_3,
		                                       SERVO_POSITION_DELAY_MS),
		        POSITIOM_LOW_3,
				POSITIOM_HIGH_3,
				TSensor::NewReedSwitchSensor(SERNSOR_3));

TTarget target4(TPositionMotor::NewServoMotor(SERVO_PIN_4,
		                                       SERVO_POSITION_DELAY_MS),
		        POSITIOM_LOW_4,
				POSITIOM_HIGH_4,
				TSensor::NewReedSwitchSensor(SERNSOR_4));

TTarget target5(TPositionMotor::NewServoMotor(SERVO_PIN_5,
		                                       SERVO_POSITION_DELAY_MS),
		        POSITIOM_LOW_5,
				POSITIOM_HIGH_5,
				TSensor::NewReedSwitchSensor(SERNSOR_5));

TTarget* targets[MAX_TARGETS];
int num_targets = 0;
TStatistics standingStatistics;

void setup() {

    randomSeed(analogRead(0));
  
    targets[num_targets++] = &target1;
    targets[num_targets++] = &target2;
    targets[num_targets++] = &target3;
    targets[num_targets++] = &target4;
    targets[num_targets++] = &target5;

    standingStatistics.Reset();
    TPuller::Pull();
}

void TPuller::Pull() {

	unsigned int numStandingTargets = 0;
	for (int i = 0; i < num_targets; ++i) {
		TTarget* target = targets[i];
		target->PullSensor();
		if (target->DroppedTimeMs() == 0 && !target->LiftInProgress) {
			++numStandingTargets;
		}
    }
	standingStatistics.Update(numStandingTargets);
}

TTarget* lift[MAX_TARGETS];

void loop() {

	auto loopStartMs = millis();

    int num_to_lift = 0;
    for (int i = 0; i < num_targets; i++) {
      if(targets[i]->DroppedTimeMs() > MIN_DROP_TIME_MS) {
        lift[num_to_lift++] = targets[i];
      }
    }

    if (num_to_lift > 0) {
      lift[random(num_to_lift)]->Lift();
    }

    TPuller::SleepBy(loopStartMs + LOOP_DELAY_MS);
}

