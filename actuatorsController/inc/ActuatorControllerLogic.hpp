//in next version, change logic for class in order to make it possible to work with more than one actuators


#ifndef ActuatorControllerLogic_HPP
#define ActuatorControllerLogic_HPP

#include <iostream>
#include <math.h> 
#include "Actuator.hpp"
using namespace std;

#define checkError 1 //state in which error is being check
#define setCycle 2 //state which conrols actuators
#define duringCycle 3  

bool isCycleStarted=true; //Global variable that is used to dermine if the automatic cycle is turned on

double calculateOpenCloseTime(uint16_t absoluteError){   
	double t;
	t=0.02*absoluteError - 0.21;
	cout << "openCloseTime: ";
	cout << t << endl;
	return t;
}

double calculateIdleTime(uint16_t absoluteError){ 
	double t;
	t=1777.35 * pow(absoluteError,2) -0.89;
	cout << "idleTime: ";
	cout << t << endl;
	return t;
}

void logic(Actuator & Actuator, uint16_t SP, uint16_t PV){
	uint8_t switchState;
	int error;
	if(!isCycleStarted){
			
			switch(switchState){
				case checkError:
					error=SP-PV;
					switchState=setCycle;
					break;
				
				case setCycle:
					
					if (error>100){
						Actuator.openActuator(3,28);
					}
					else if (error<-100){
						Actuator.closeActuator(3,28);
					}
					else if (error>0){
						Actuator.openActuator(calculateOpenCloseTime(abs(error)),calculateIdleTime(abs(error)));
					}
					else {
						Actuator.closeActuator(calculateOpenCloseTime(abs(error)),calculateIdleTime(abs(error)));	
					}
					break;

					if(Actuator.getCurrentState()==OpeningCycle || Actuator.getCurrentState()==ClosingCycle){
						switchState=duringCycle;
					}else{
						cout <<  "something went terribly wrong" << endl;
					}
				case duringCycle:
					if(Actuator.getCurrentState()==Idle){
						switchState=checkError;
					}
					break;
			}
		}

}

#endif