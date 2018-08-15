#include <iostream>
#include <fstream>
#include "../inc/simpleCombustion.hpp"

int main(){
	uint16_t SP, PV;
	int16_t error;
	FakeActuator j1(3,6); 
	simpleCombustion process1(j1);
	
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
		process1.execute(error,true);
		outputFile << error << ';' << process1.getOpenCloseTime() << ';' << process1.getIdleTime() <<'\n';
	}
	return 0;
}