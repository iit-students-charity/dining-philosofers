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
	void lunch();

private:
	std::vector<Philosofer> philosofers;
	std::vector<Fork> forks;
	std::ofstream log;
	size_t count;
	unsigned logPeriod;
	unsigned timeOut;

	void logStates(std::ostream &stream);
	void logHeading(std::ostream &stream);
	void logLine(std::ostream &stream);
	void waitForLoggingPeriod();
};
