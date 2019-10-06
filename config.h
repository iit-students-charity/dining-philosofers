#pragma once

#include "log.h"

#include <vector>
#include <string>

class Config
{
public:
	Config(const char* source, Log* log);
	unsigned getOutputPeriod();
	unsigned getSecondsToEat();
	unsigned getSecondsToThink();
	unsigned getTimeOut();
	std::string getOutputFilePath();
	std::vector<std::string> getPhilosoferNames();

private:
	unsigned outputPeriod;
	unsigned secondsToEat;
	unsigned secondsToThink;
	unsigned timeOut;
	std::string outputFilePath;
	std::vector<std::string> philosoferNames;
	Log* log;
};
