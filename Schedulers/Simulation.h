#include <iostream>
#include <string>
#include <list>
#include "Process.h"
#pragma once
/*
	Simulation class is abstract class for Schedulers to be simulated.
	Running queues are set by the child
*/

class Simulation {
public:
	virtual void run() = 0;
	virtual ~Simulation(void) {};
	virtual void printCurrentStatus() = 0;
	virtual void printSimulationResults() = 0;
	//virtual void calculateUtil() = 0;
protected:
	list<Process> ready_queue;
	list<Process> io_queue;
	list<Process> complete;
	bool verbose;
	int clock = 0;
	int cpu = 0;
	float cpu_util = 0;
};
