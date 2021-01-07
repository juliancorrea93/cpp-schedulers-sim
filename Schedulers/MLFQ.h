#include <iostream>
#include <string>
#include <list>
#include <vector>
#include "Process.h"
#include "Simulation.h"
#pragma once
using namespace std;

class MLFQ : public Simulation {
public:
	MLFQ(list<Process>, bool);
	void run();
	~MLFQ();
private:
	void printCurrentStatus();
	void printSimulationResults();
	void calculateUtil();
	list<Process> round_robin1;
	list<Process> round_robin2;
	list<Process> fcfs;
	Process* focus;
	int current_proc_runtime;
};