/*
 * sensors.h
 *
 *      Author: Dmitry Ryashchentsev
 */

#ifndef SENSORS_H_
#define SENSORS_H_

class TSensor {
public:
	virtual bool IsOn();

	static TSensor* NewReedSwitchSensor(unsigned int pin);
};

#endif /* SENSORS_H_ */
