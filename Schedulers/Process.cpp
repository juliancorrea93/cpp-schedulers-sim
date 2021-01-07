#include <iostream>
#include <string>
#include <list>
#include "Process.h"

using namespace std;

Process::Process(list<int> list, string name) {
	bursts = list;
	process_name = name;
	time_in_ready = 0;
	response_time = -1;
	exit = -1;
	priority = 3;
}
void Process::incrementReadyTime() {
	time_in_ready++;
}
int Process::calculateTurnaround() {
	return exit; //In this example all enter ready at 0, so set to exit time
}
bool Process::isComplete() {
	return bursts.empty();
}
bool Process::isBurstDone() {
	if (isComplete()) {
		return true;
	}
	else {
		if (bursts.front() == 0) {
			bursts.pop_front();
			return true;
		}
		else {
			return false;
		}
	}
}
string Process::getName() {
	return process_name;
}
bool Process::isFirstRunTime() {
	if (response_time < 0) {
		return true;
	}
	return false;
}
int Process::getExit() {
	return exit;
}
int Process::getPriority() {
	return priority;
}
void Process::setExit(int time) {
	exit = time;
}
void Process::setPriority(int time) {
	priority = time;
}
void Process::setResponse(int time) {
	response_time = time;
}
string Process::toString() {
	return "Name: " + process_name + " Response Time: " + to_string(response_time) + " Waiting Time: " + to_string(time_in_ready) + " Turnaround Time: " + to_string(exit) + "\n";
}
void Process::decBurst() {
	bursts.front()--;
}
int Process::getCurrentBurst() {
	return bursts.front();
}