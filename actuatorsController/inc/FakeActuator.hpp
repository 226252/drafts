#ifndef Fakectuator_HPP
#define Fakectuator_HPP

#include <iostream>
#include <stdint.h>
#include "Actuator.hpp"
#define Idle 1
#define OpeningCycle 2
#define ClosingCycle 3

class FakeActuator
	: public Actuator
{
public:
	FakeActuator(int a, int b) : Actuator(a,b){}
	void open();
	void close();
	void resetPins();
};
// end of class

#endif