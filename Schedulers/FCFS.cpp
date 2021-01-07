#include <iostream>
#include <string>
#include <list>
#include "Process.h"
#include "FCFS.h"

using namespace std;

FCFS::FCFS(list<Process> process_list, bool verbose_mode) {
	ready_queue = process_list;
	verbose = verbose_mode;
}
void FCFS::run() {
	while ((ready_queue.empty() && running_queue.empty() && io_queue.empty()) == false) {
		//if running queue is empty get next process, if not proceed to decrement burst
		if (running_queue.empty() && !ready_queue.empty()) {
			running_queue.push_back(ready_queue.front());
			//checks if this is the first time the process has been given the CPU
			if (running_queue.front().isFirstRunTime()) {
				running_queue.front().setResponse(clock);
			}
			ready_queue.pop_front();
			running_queue.front().decBurst();
		}
		else if (!running_queue.empty()) {
			//checks to see if current burst is done, if yes push to IO, if not decrement the burst
			if (running_queue.front().isBurstDone()) {
				//checks if complete
				if (running_queue.front().isComplete()) {
					running_queue.front().setExit(clock);
					complete.push_back(running_queue.front());
					running_queue.pop_front();
				}
				else {
					io_queue.push_back(running_queue.front());
					running_queue.pop_front();
				}
			}
			else {
				running_queue.front().decBurst();
			}
		}

		if (!io_queue.empty()) {
			list<Process>::iterator it = io_queue.begin();
			do {
				if (it->isBurstDone()) {
					if (it->isComplete()) {
						it->setExit(clock);
						complete.push_back(*it);
					}
					else {
						ready_queue.push_back(*it);
					}
					it = io_queue.erase(it);
				}
				else {
					it->decBurst();
					++it;
				}
			} while (it != io_queue.end());
		}
		if (!ready_queue.empty()) {
			for (list<Process>::iterator it = ready_queue.begin(); it != ready_queue.end(); ++it) {
				it->incrementReadyTime();
			}
		}
		if (verbose) {
			printCurrentStatus();
		}
		clock++;
	}
	printSimulationResults();
}
void FCFS::printCurrentStatus() {
	
	cout << "_________________________________________________________________________________" << endl;
	cout << "Clock: " + to_string(clock) << endl;
	cout << "CPU running instructions on: ";

	for (list<Process>::iterator it = running_queue.begin(); it != running_queue.end(); ++it) {
		cout << it->getName() << endl;
	}

	cout << endl << "Processes waiting for the CPU:";

	for (list<Process>::iterator it = ready_queue.begin(); it != ready_queue.end(); ++it) {
		cout << " " + it->getName();
	}

	cout << endl << "Processes in IO:";
	for (list<Process>::iterator it = io_queue.begin(); it != io_queue.end(); ++it) {
		cout << " " + it->getName();
	}


	cout << endl << "Processes completed:";

	for (list<Process>::iterator it = complete.begin(); it != complete.end(); ++it) {
		cout << " " + it->getName();
	}

	cout << "_________________________________________________________________________________" << endl;
}
void FCFS::printSimulationResults() {
	cout << "FCFS Scheduling Algorithm" << endl;
	cout << "_________________________________________________________________________________" << endl;
	for (list<Process>::iterator it = complete.begin(); it != complete.end(); ++it) {
		cout << it->toString();
	}
	cout << "_________________________________________________________________________________" << endl;
}
FCFS::~FCFS() {
	delete this;
}