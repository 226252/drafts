#include "../inc/simpleCombustion.hpp"
#include <math.h>

using namespace std;

#define setCycle 1 
#define duringCycle 2  


bool simpleCombustion::isInitialized=false;
Actuator* simpleCombustion::actuator = 0;
uint8_t simpleCombustion::currentState = setCycle;
float simpleCombustion::idleTime = 0.0f;
float simpleCombustion::openCloseTime = 0.0f;

//
void simpleCombustion::changeState(uint8_t whichState){
	currentState=whichState;
}
//
void simpleCombustion::initialize(Actuator &actuator_){
	actuator = &actuator_;
	currentState=setCycle;
	isInitialized=true;
}
//
void simpleCombustion::calculateCycleTime(int16_t absoluteError){
	openCloseTime=0.02*absoluteError - 0.21;
	if(openCloseTime<0)	openCloseTime=0;

	idleTime=1777.35*pow(absoluteError, -0.89);
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
						actuator->open();
						//after 3 seconds 
						/* do this*/ actuator->resetPins();
						//after 31 seconds
						/*do this*/ changeState(setCycle);
					}
					else if (error<-100){
						actuator->close();
						//after 3 seconds 
						/* do this*/ actuator->resetPins();
						//after 31 seconds
						/*do this*/ changeState(setCycle);
					}
					else if (error>0){
						actuator->open();
						//after simpleCombustion.openCloseTime
						/* do this*/ actuator->resetPins();
						//after simpleCombustion.openCloseTime+simpleCombustion.idleTime
						/*do this*/ changeState(setCycle);	
					}
					else {
						actuator->close();	
						//after simpleCombustion.openCloseTime
						/* do this*/ actuator->resetPins();
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