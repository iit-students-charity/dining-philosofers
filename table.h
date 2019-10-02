#pragma once

#include "philosofer.h"
#include "config.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>

class Table
{
public:
	Table(Config config);
	~Table();
	void startMeal();

private:
	std::vector<Philosofer> philosofers;
	std::vector<Fork> forks;
	std::ofstream log;
	unsigned logPeriod;
	size_t count;

	void logStates();
	void logPreamble();
	void statesToConsole();
	void statesToFile();
	void preambleToConsole();
	void preambleToFile();
	void waitForLoggingPeriod();
};
