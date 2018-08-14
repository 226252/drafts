#ifndef Actuator_HPP
#define Actuator_HPP

#include <stdint.h>
#define Idle 1
#define OpeningCycle 2
#define ClosingCycle 3

class Actuator
{
	uint8_t currentState;
	uint8_t pinNumber;
	void changeState(uint8_t whichState);

public:
	Actuator(uint8_t pinNumber);
	~Actuator();
	uint8_t getCurrentState();
	void openActuator(uint16_t openTime, uint16_t idleTime);
	void closeActuator(uint16_t closeTime, uint16_t idleTime);
	void resetActuatorsPin();

};
// end of class
void Actuator::changeState(uint8_t whichState){
	this->currentState=whichState;
}
//
Actuator::Actuator(uint8_t pinNumber){
	this->currentState = Idle;
	this->pinNumber = pinNumber;
}
//
uint8_t Actuator::getCurrentState(){
	return currentState;
}
//
void Actuator::openActuator(uint16_t openTime, uint16_t idleTime){
	if(currentState==Idle){
		changeState(OpeningCycle);
		//set the relay pin (opening) to HIGH
		//call resetActuatorsPin after the openTime
		//call changeState after openTime+idleTime
		changeState(Idle); //only for test purpose
	}		
}
//
void Actuator::closeActuator(uint16_t closeTime, uint16_t idleTime){
	if(currentState==Idle){
		changeState(ClosingCycle);
		//set the relay pin (closing) to HIGH
		//call resetActuatorsPin after the closeTime
		//call changeState after closeTime+idleTime
		changeState(Idle); //only for test purpose
	}
}
//	
void Actuator::resetActuatorsPin(){
	//here goes code for reseting pins connected with relay
}

#endif