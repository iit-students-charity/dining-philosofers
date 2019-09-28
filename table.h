#pragma once

#include "philosofer.h"

#include <vector>
#include <iostream>
#include <iomanip>

class Table
{
public:
	Table(std::vector<Philosofer> philosofers);
	void startMeal();
	void logStates();

private:
	std::vector<Philosofer> philosofers;
	std::vector<Fork> forks;
	size_t count;
	static const int LOG_PERIOD = 1;

	void waitForLoggingPeriod();
	void printPreamble();
};