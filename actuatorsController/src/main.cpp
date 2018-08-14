#include <iostream>
#include <fstream>
#include "../inc/ActuatorControllerLogic.hpp"
#include "../inc/Actuator.hpp"
using namespace std;

int main(){
	uint16_t SP, PV;
	int16_t error;
	uint8_t pinNumber=1;
	Actuator j1(pinNumber); 
	outputHolder oH;

	SP=300;
	ifstream dataFile;
	ofstream outputFile;
	dataFile.open("data.txt");
	outputFile.open("output.txt");
	outputFile << "error" << ';' << "O/C_Time" << ';' << "idleTime" <<'\n';
	while (!dataFile.eof()){
		dataFile >> PV;
		error=SP-PV;
		oH=logic(j1,error);
		outputFile << error << ';' << oH.onTime << ';' << oH.offTime <<'\n';
	}
	return 0;
}