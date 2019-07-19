#ifndef __Sensor_H
#define __Sensor_H

#include <Arduino.h>

class Ult{
private:
	int Echo, Trig;
public:
	Ult(int echo, int trig);
  	float Range();
};


//光电类
class  Infr {
private:
	int outputPin;
public:
	Infr(int pin);
	bool GetValue();
};

#endif //!__Sensor_H