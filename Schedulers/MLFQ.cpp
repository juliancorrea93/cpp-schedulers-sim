
#include <iostream>
#include <string>
#include <list>
#include "Process.h"
#include "MLFQ.h"

using namespace std;

MLFQ::MLFQ(list<Process> process_list, bool verbose_mode) {
	ready_queue = process_list;
	verbose = verbose_mode;
	focus = NULL;
}
void MLFQ::run() {
	while ((ready_queue.empty() && round_robin1.empty() && round_robin2.empty() && fcfs.empty() && io_queue.empty()) == false) {
		if ((round_robin1.empty() || round_robin2.empty() || fcfs.empty()) && ready_queue.empty() == false) {
			if (round_robin1.empty() && ready_queue.front().getPriority() == 3) {
				round_robin1.push_back(ready_queue.front());
				ready_queue.pop_front();
				if (round_robin1.front().isFirstRunTime()) {
					round_robin1.front().setResponse(clock);
				}
			}
			else if (round_robin2.empty() && ready_queue.front().getPriority() == 2) {
				round_robin2.push_back(ready_queue.front());
				ready_queue.pop_front();
				if (round_robin2.front().isFirstRunTime()) {
					round_robin2.front().setResponse(clock);
				}
			}
			else if (fcfs.empty() && ready_queue.front().getPriority() == 1) {
				fcfs.push_back(ready_queue.front());
				ready_queue.pop_front();
				if (fcfs.front().isFirstRunTime()) {
					fcfs.front().setResponse(clock);
				}
			}
		}
		

		if (!round_robin1.empty()) {
			if (focus != &round_robin1.front()) {
				current_proc_runtime = 0;
				focus = &round_robin1.front();
			}
			if (round_robin1.front().isBurstDone() && !round_robin1.front().isComplete()) {
				io_queue.push_back(round_robin1.front());
				round_robin1.pop_front();
			}
			else {
				list<Process>::iterator it = round_robin1.begin();
				do {
					if (it->isBurstDone()) {
						if (it->isComplete()) {
							it->setExit(clock);
							complete.push_back(*it);
						}
						else {
							ready_queue.push_back(*it);
						}
						it = round_robin1.erase(it);
					}
					else if (current_proc_runtime >= 5) {
						if (verbose == true) {
							cout << "Process " + it->getName() + " has been moved to lower priority" << endl;
						}
						it->setPriority(2);
						current_proc_runtime = 0;
						ready_queue.push_back(*it);
						it = round_robin1.erase(it);
					}
					else {
						it->decBurst();
						current_proc_runtime++;
						++it;
					}
				} while (it != round_robin1.end());
			}
		}
		else if (!round_robin2.empty()) {
			if (focus != &round_robin2.front()) {
				current_proc_runtime = 0;
				focus = &round_robin2.front();
			}
			if (round_robin2.front().isBurstDone() && !round_robin2.front().isComplete()) {
				io_queue.push_back(round_robin2.front());
				round_robin2.pop_front();
			}
			else {
				list<Process>::iterator it = round_robin2.begin();
				do {
					if (it->isBurstDone()) {
						if (it->isComplete()) {
							it->setExit(clock);
							complete.push_back(*it);
						}
						else {
							ready_queue.push_back(*it);
						}
						it = round_robin2.erase(it);
					}
					else if (current_proc_runtime >= 10) {
						if (verbose == true) {
							cout << "Process " + it->getName() + " has been moved to lower priority" << endl;
						}
						it->setPriority(1);
						current_proc_runtime = 0;
						ready_queue.push_back(*it);
						it = round_robin2.erase(it);
					}
					else {
						it->decBurst();
						current_proc_runtime++;
						++it;
					}
				} while (it != round_robin2.end());
			}
		}
		else if (!fcfs.empty()) {
			if (focus != &fcfs.front()) {
				current_proc_runtime = 0;
				focus = &fcfs.front();
			}
			if (fcfs.front().isBurstDone() && !fcfs.front().isComplete()) {
				io_queue.push_back(fcfs.front());
				fcfs.pop_front();
			}
			else {
				list<Process>::iterator it = fcfs.begin();
				do {
					if (it->isBurstDone()) {
						if (it->isComplete()) {
							it->setExit(clock);
							complete.push_back(*it);
						}
						else {
							ready_queue.push_back(*it);
						}
						it = fcfs.erase(it);
					}
					else {
						it->decBurst();
						current_proc_runtime++;
						++it;
					}
				} while (it != fcfs.end());
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
		if (!fcfs.empty() || !round_robin1.empty() || !round_robin2.empty()) {
			cpu++;
		}
	}
	printSimulationResults();
}
void MLFQ::printCurrentStatus() {
	cout << "_________________________________________________________________________________" << endl;
	cout << "Clock: " + to_string(clock) << endl;
	cout << "Round robin 1 processes: ";

	for (list<Process>::iterator it = round_robin1.begin(); it != round_robin1.end(); ++it) {
		cout << it->getName() << endl;
	}

	cout << endl << "Round robin 2 processes: ";

	for (list<Process>::iterator it = round_robin2.begin(); it != round_robin2.end(); ++it) {
		cout << it->getName() << endl;
	}

	cout << endl << "FCFS processes: ";

	for (list<Process>::iterator it = fcfs.begin(); it != fcfs.end(); ++it) {
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
void MLFQ::printSimulationResults() {
	cout << "MLFQ Scheduling Algorithm" << endl;
	cout << "_________________________________________________________________________________" << endl;
	for (list<Process>::iterator it = complete.begin(); it != complete.end(); ++it) {
		cout << it->toString();
	}
	cout << "_________________________________________________________________________________" << endl;
}
MLFQ::~MLFQ() {
	delete this;
}