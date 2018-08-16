#include <iostream>
#include <fstream>
#include <math.h> 
#include "../inc/simpleCombustion.hpp"

using namespace std;
	
int main(){
	uint16_t SP, PV;
	int16_t error;
	FakeActuator j1(3,6); 
	
	simpleCombustion::initialize(j1);

	j1.resetPins();
	SP=300;
	ifstream dataFile;
	ofstream outputFile;
	dataFile.open("data.txt");
	outputFile.open("output.txt");
	outputFile << "error" << ';' << "O/C_Time" << ';' << "idleTime" <<'\n';
	while (!dataFile.eof()){
		dataFile >> PV;
		error=SP-PV;
		simpleCombustion::execute(error,true);
		outputFile << error << ';' << simpleCombustion::getOpenCloseTime() << ';' << simpleCombustion::getIdleTime() <<'\n';
	}
	return 0;
}