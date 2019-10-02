#pragma once

#include <vector>
#include <string>

class Config
{
public:
	Config();
	Config(std::string fileName);
	unsigned getLogPeriod();
	unsigned getSecondsToEat();
	unsigned getSecondsToThink();
	std::vector<std::string> getPhilosoferNames();

private:
	unsigned logPeriod;
	unsigned secondsToEat;
	unsigned secondsToThink;
	std::vector<std::string> philosoferNames;
};
