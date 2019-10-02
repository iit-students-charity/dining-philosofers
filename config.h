#pragma once

#include <vector>
#include <string>

class Config
{
public:
	Config();
	Config(const char* source);
	unsigned getLogPeriod();
	unsigned getSecondsToEat();
	unsigned getSecondsToThink();
	unsigned getTimeOut();
	std::string getLogFilePath();
	std::vector<std::string> getPhilosoferNames();

private:
	unsigned logPeriod;
	unsigned secondsToEat;
	unsigned secondsToThink;
	unsigned timeOut;
	std::string logFilePath;
	std::vector<std::string> philosoferNames;
};
