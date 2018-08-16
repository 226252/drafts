#ifndef Actuator_HPP
#define Actuator_HPP

#include <iostream>
#include <stdint.h>
#define Idle 1
#define OpeningCycle 2
#define ClosingCycle 3

class Actuator
{
	int currentState;
	int pinNumberOpening;
	int pinNumberClosing;
	void changeState(int whichState);
	friend class FakeActuator;

public:
	
	Actuator(int pinNumberOpening_, int pinNumberClosing_);
	uint8_t getCurrentState();
	virtual void open();
	virtual void close();
	virtual void resetPins();
};
// end of class


#endif