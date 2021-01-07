#include <iostream>
#include <string>
#include <list>
using namespace std;
#pragma once
class Process {
public:
	Process(list<int>, string);
	void incrementReadyTime();
	int calculateTurnaround();
	bool isComplete();
	bool isBurstDone();
	string getName();
	bool isFirstRunTime();
	int getExit();
	int getPriority();
	void setExit(int);
	void setPriority(int);
	void setResponse(int);
	string toString();
	void decBurst();
	int getCurrentBurst();
private:
	list<int> bursts;
	string process_name;
	int time_in_ready;
	int response_time;
	int exit;
	int priority;
};