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

void FakeActuator::open(){
	if(currentState==Idle){
		changeState(OpeningCycle);
		std::cout<<"opening"<< std::endl;
		//set the relay pin (opening) to HIGH
	}
}
//
void FakeActuator::close(){
	if(currentState==Idle){
		changeState(ClosingCycle);
		//set the relay pin (closing) to HIGH
		std::cout<<"closing"<< std::endl;
	}
}
//	
void FakeActuator::resetPins(){
	changeState(Idle);
	//set both pins to LOW
	std::cout<<"reseting"<< std::endl;
	std::cout<<pinNumberClosing<<pinNumberOpening<<std::endl;
}

#endif