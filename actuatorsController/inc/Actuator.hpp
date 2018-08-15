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
void Actuator::changeState(int whichState){
	this->currentState=whichState;
}
//
Actuator::Actuator(int pinNumberOpening_, int pinNumberClosing_)
	: currentState(Idle),
	pinNumberOpening(pinNumberOpening_),
	pinNumberClosing(pinNumberClosing_)
{}
//
uint8_t Actuator::getCurrentState(){
	return currentState;
}
//
void Actuator::open(){
	if(currentState==Idle){
		changeState(OpeningCycle);
		//set the relay pin (opening) to HIGH
	}
}
//
void Actuator::close(){
	if(currentState==Idle){
		changeState(ClosingCycle);
		//set the relay pin (closing) to HIGH
	}
}
//	
void Actuator::resetPins(){
	changeState(Idle);
	//set both pins to LOW
}

#endif