//in next version, change logic for class in order to make it possible to work with more than one actuators


#ifndef simpleCombustion_HPP
#define simpleCombustion_HPP

#include <iostream>
#include <math.h> 
#include "Actuator.hpp"
#include "FakeActuator.hpp"
using namespace std;

#define setCycle 1 
#define duringCycle 2  

class simpleCombustion
{
	Actuator& actuator;
	uint8_t currentState;
	float idleTime,openCloseTime;
	void changeState(uint8_t whichState);
	//void interrupt(); //This function could be used to interrupt ongoing cycle for example when the current temperture is much higher/lower than the temperature that was used to set the cycle
	//uint16_t lastTemp //this would be variable to hold mentioned value

public:
	simpleCombustion(Actuator &actuator_);
	void calculateCycleTime(int16_t absoluteError);
	void execute(int16_t error, bool isCycleStarted);
	float getOpenCloseTime();
	float getIdleTime();
	
};
//end of class
void simpleCombustion::changeState(uint8_t whichState){
	currentState=whichState;
}
//
simpleCombustion::simpleCombustion(Actuator &actuator_): actuator(actuator_),currentState(setCycle){}
//
void simpleCombustion::calculateCycleTime(int16_t absoluteError){
	openCloseTime=0.02*absoluteError - 0.21;
	if(openCloseTime<0)	openCloseTime=0;

	idleTime=1777.35*absoluteError - 0.89;
	if(idleTime<0)	idleTime=0;
	
}
//
void simpleCombustion::execute(int16_t error, bool isCycleStarted){
	if(isCycleStarted){
		switch(currentState){
				
				case setCycle:
					calculateCycleTime(abs(error));
					changeState(duringCycle);	
					if (error>100){
						actuator.open();
						//after 3 seconds 
						/* do this*/ actuator.resetPins();
						//after 31 seconds
						/*do this*/ changeState(setCycle);
					}
					else if (error<-100){
						actuator.close();
						//after 3 seconds 
						/* do this*/ actuator.resetPins();
						//after 31 seconds
						/*do this*/ changeState(setCycle);
					}
					else if (error>0){
						actuator.open();
						//after simpleCombustion.openCloseTime
						/* do this*/ actuator.resetPins();
						//after simpleCombustion.openCloseTime+simpleCombustion.idleTime
						/*do this*/ changeState(setCycle);	
					}
					else {
						actuator.close();	
						//after simpleCombustion.openCloseTime
						/* do this*/ actuator.resetPins();
						//after simpleCombustion.openCloseTime+simpleCombustion.idleTime
						/*do this*/ changeState(setCycle);					
					}
					break;

				case duringCycle:
					//it can do whatever here.
					break;
			}
		}
}
//
float simpleCombustion::getOpenCloseTime(){
	return openCloseTime;
}
//
float simpleCombustion::getIdleTime(){
	return idleTime;
}
#endif