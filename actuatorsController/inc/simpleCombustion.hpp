//in next version, change logic for class in order to make it possible to work with more than one actuators


#ifndef simpleCombustion_HPP
#define simpleCombustion_HPP
#include "Actuator.hpp"
#include "FakeActuator.hpp"


class simpleCombustion
{	
private:
	static Actuator* actuator;
	static bool isInitialized;
	static uint8_t currentState;
	static float idleTime,openCloseTime;
	static void changeState(uint8_t whichState);
	//void interrupt(); //This function could be used to interrupt ongoing cycle for example when the current temperture is much higher/lower than the temperature that was used to set the cycle
	//uint16_t lastTemp //this would be variable to hold mentioned value
	simpleCombustion();
public:
	static void initialize(Actuator& actuator);
	static void calculateCycleTime(int16_t absoluteError);
	static void execute(int16_t error, bool isCycleStarted);
	static float getOpenCloseTime();
	static float getIdleTime();
	
};

#endif