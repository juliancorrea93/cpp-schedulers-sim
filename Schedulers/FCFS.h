#include <iostream>
#include <string>
#include <list>
#include <vector>
#include "Process.h"
#include "Simulation.h"
#pragma once
using namespace std;

class FCFS : Simulation {
public:
	FCFS(list<Process>, bool);
	void run();
	~FCFS();
private:
	void printCurrentStatus();
	void printSimulationResults();
	//void calculateUtil();
	list<Process> running_queue;
};