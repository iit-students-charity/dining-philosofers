#pragma once

#include "philosofer.h"
#include "config.h"

#include <vector>
#include <iostream>
#include <iomanip>

class Table
{
public:
	Table(Config config);
	~Table();
	void startMeal();
	void logStates();

private:
	std::vector<Philosofer> philosofers;
	std::vector<Fork> forks;
	unsigned logPeriod;
	size_t count;

	void waitForLoggingPeriod();
	void printPreamble();
};
