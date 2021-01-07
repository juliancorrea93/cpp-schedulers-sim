#include <iostream>
#include <string>
#include <list>
#include "Process.h"
#include "FCFS.h"
#include "SJF.h"
#include "MLFQ.h"

using namespace std;

int main(void) {
	Process p1 = Process({ 5, 27, 3, 31, 5, 43, 4, 18, 6, 22, 4, 26, 3, 24, 4 }, "p1");
	Process p2 = Process({ 4, 48, 5, 44, 7, 42, 12, 37, 9, 76, 4, 41, 9, 31, 7, 43, 8 }, "p2");
	Process p3 = Process({ 8, 33, 12, 41, 18, 65, 14, 21, 4, 61, 15, 18, 14, 26, 5, 31, 6 }, "p3");
	Process p4 = Process({ 3, 35, 4, 41, 5, 45, 3, 51, 4, 61, 5, 54, 6, 82, 5, 77, 3 }, "p4");
	Process p5 = Process({ 16, 24, 17, 21, 5, 36, 16, 26, 7, 31, 13, 28, 11, 21, 6, 13, 3, 11, 4 }, "p5");
	Process p6 = Process({ 11, 22, 4, 8, 5, 10, 6, 12, 7, 14, 9, 18, 12, 24, 15, 30, 8 }, "p6");
	Process p7 = Process({ 14, 46, 17, 41, 11, 42, 15, 21, 4, 32, 7, 19, 16, 33, 10 }, "p7");
	Process p8 = Process({ 4, 14, 5, 33, 6, 51, 14, 73, 16, 87, 6 }, "p8");

	list<Process> processes;
	processes.push_back(p1);
	processes.push_back(p2);
	processes.push_back(p3);
	processes.push_back(p4);
	processes.push_back(p5);
	processes.push_back(p6);
	processes.push_back(p7);
	processes.push_back(p8);

	FCFS f = FCFS(processes, false);
	f.run();

	SJF s = SJF(processes, false);
	s.run();

	MLFQ m = MLFQ(processes, false);
	m.run();
}