#include "../inc/Actuator.hpp"

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