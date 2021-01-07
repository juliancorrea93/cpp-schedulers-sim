#include <iostream>
#include <string>
#include <list>
#include <vector>
#include "Process.h"
#include "Simulation.h"
#pragma once
using namespace std;

class SJF : public Simulation {
public:
	SJF(list<Process>, bool);
	void run();
	~SJF();
private:
	void printCurrentStatus();
	void printSimulationResults();
	//void calculateUtil();
	list<Process> running_queue;
};