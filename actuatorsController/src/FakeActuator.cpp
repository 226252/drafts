#include "../inc/FakeActuator.hpp"

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