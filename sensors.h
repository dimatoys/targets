/*
 * sensors.h
 *
 *      Author: Dmitry Ryashchentsev
 */

#ifndef SENSORS_H_
#define SENSORS_H_

class TPuller {
	// keep it singleton
	//TPuller(){}
	//static TPuller* Instance();

public:
	static void SleepBy(unsigned long timeMs);
	static void Pull();
};


class TSensor {
public:
	virtual bool IsOn();

	static TSensor* NewReedSwitchSensor(unsigned int pin);
};

#endif /* SENSORS_H_ */
