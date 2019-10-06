#pragma once

#include <vector>
#include <string>

class Config
{
public:
	Config();
	Config(const char* source);
	unsigned getOutputPeriod();
	unsigned getSecondsToEat();
	unsigned getSecondsToThink();
	unsigned getTimeOut();
	std::string getLogFilePath();
	std::string getOutputFilePath();
	std::vector<std::string> getPhilosoferNames();

private:
	unsigned outputPeriod;
	unsigned secondsToEat;
	unsigned secondsToThink;
	unsigned timeOut;
	std::string logFilePath;
	std::string outputFilePath;
	std::vector<std::string> philosoferNames;
};
