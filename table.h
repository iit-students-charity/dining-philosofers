#pragma once

#include "philosofer.h"
#include "config.h"
#include "log.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>

#define MILLISECONDS_IN_SECOND 1000
#define DIVIDER_LENGTH 17

class Table
{
public:
	Table(Config* config, Log* log);
	~Table();
	void lunch();

private:
	std::vector<Philosofer> philosofers;
	std::vector<Fork> forks;
	std::ofstream output;
	size_t count;
	unsigned outputPeriod;
	unsigned timeOut;
	Log* log;

	void outputStates(std::ostream &stream);
	void outputHeading(std::ostream &stream);
	void outputLine(std::ostream &stream);
	void waitForOutputPeriod();
};
