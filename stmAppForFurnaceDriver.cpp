#include <stdio.h>
#include <iostream>
#include <math.h> 
using namespace std;

static uint8_t switchState;
static uint16_t SP=400; //temp. zadana
static uint16_t PV; //temp. aktualna
static int16_t error; //uchyb  
static bool isCycleStarted; //jakas flaga by wiedziec czy juz jest automat włączony
#define checkError 1
#define setCycle 2
#define idle 3


void openActuator(uint16_t openTime, uint16_t idleTime){
	//stan wysoki na pin otwierania
	//wywolaj funkcje resetActuatorsPins() po openTime
	//wywolaj funkcje zmiana witchState po openTime+idleTime
	switchState=idle;
}

void closeActuator(uint16_t closeTime, uint16_t idleTime){
	//stan wysoki na pin zamykania
	//wywolaj funkcje resetActuatorsPins() po closeTime 
	//wywolaj funkcje zmiana witchState po closeTime+idleTime
	switchState=idle;
}

void resetActuatorsPins(){
	//stan niski pinów jowent na zero
}

void stateSwitcher(uint8_t wichState){
	switchState=wichState;
}

double openCloseTime(uint16_t absoluteError){ //można poszerzyć funkcje o współczynniki funkcji jako parametry  
	double t;
	t=0.02*absoluteError - 0.21;
	cout << "openCloseTime" << endl;
	cout << t << endl;
	return t;
}

double idleTime(uint16_t absoluteError){ // to samo co wyżej
	double t;
	t=1777.35 * pow(absoluteError,2) -0.89;
	cout << "idleTime" << endl;
	cout << t << endl;
	return t;
}



int main()
{
    switchState = 1; //zainicjowac zmienna
	while(1){
		
		if(!isCycleStarted){
			
			switch(switchState){
				case checkError:
					cout <<	"error: ";
					cin >> error;
					//error=SP-PV;
					switchState=setCycle;
					break;
				
				case setCycle:
					
					if (error>100){
						openActuator(3,28);
					}
					else if (error<-100){
						closeActuator(3,28);
					}
					else if (error>0){
						openActuator(openCloseTime(abs(error)),idleTime(abs(error)));
					}
					else {
						closeActuator(openCloseTime(abs(error)),idleTime(abs(error)));	
					}
					break;
				
				case idle:
					//stan bezczynnosci nic tutaj nie robi i sie nie meczy
					cout  << "jestem bezczynny" << endl; 
					switchState=1;
					break;
			}
		}
	}
	return 0;
}
