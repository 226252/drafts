//in next version, change logic for class in order to make it possible to work with more than one actuators


#ifndef ActuatorControllerLogic_HPP
#define ActuatorControllerLogic_HPP

#include <iostream>
#include <math.h> 
#include "Actuator.hpp"
using namespace std;

#define setCycle 1 //state which conrols actuators
#define duringCycle 2  
uint8_t switchState=setCycle; //global variable //this will be the only state being used during tests beacuse we only need time periods

struct outputHolder //simple struct created for tests, it will be used to hold cycle times in logic function 
					//it can only be used to hold state so problem with many logic functions is no more a problem (to do on next iteration)
{
	float onTime, offTime;
};

bool isCycleStarted=true; //Global variable that is used to dermine if the automatic cycle is turned on

float calculateOpenCloseTime(uint16_t absoluteError){   
	float t;
	t=0.02*absoluteError - 0.21;
	//cout oriented debbuging
		//cout<< "absoluteError: " << absoluteError << endl;
		//cout << "openCloseTime: ";
		//cout << t << endl;
	//
	if(t<0)	t=0;
	
	return t;
}

float calculateIdleTime(uint16_t absoluteError){ 
	float t;
	t=1777.35 * pow(absoluteError,2) -0.89;
	//cout oriented debbuging
		//cout<< "absoluteError: " << absoluteError << endl;
		//cout << "idleTime: ";
		//cout << t << endl;
	//
	if(t<0)	t=0;
	
	return t;
}

outputHolder logic(Actuator & Actuator, int16_t error){
	outputHolder x; //for tests
	
	if(isCycleStarted){
			
		switch(switchState){
				
				case setCycle:
					
					if (error>100){
						Actuator.openActuator(3,28);
						//for tests
						x.onTime=3;
						x.offTime=28;
						//
					}
					else if (error<-100){
						Actuator.closeActuator(3,28);
						//for tests
						x.onTime=3;
						x.offTime=28;
						//
					}
					else if (error>0){
						Actuator.openActuator(calculateOpenCloseTime(abs(error)),calculateIdleTime(abs(error)));
						//for tests
						x.onTime=calculateOpenCloseTime(abs(error));
						x.offTime=calculateIdleTime(abs(error));
						//
					}
					else {
						Actuator.closeActuator(calculateOpenCloseTime(abs(error)),calculateIdleTime(abs(error)));	
						//for tests
						x.onTime=calculateOpenCloseTime(abs(error));
						x.offTime=calculateIdleTime(abs(error));
						//
					}
					break;

					if(Actuator.getCurrentState()==OpeningCycle || Actuator.getCurrentState()==ClosingCycle){
						switchState=duringCycle;
					}else{
						cout <<  "something went terribly wrong" << endl; 
					}
				case duringCycle:
					if(Actuator.getCurrentState()==Idle){
						//switchState=setCycle; //commented for test measures
					}
					break;
			}
		}
	return x;
}

#endif