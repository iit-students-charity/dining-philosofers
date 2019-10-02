#include "stdafx.h"
#include "config.h"

Config::Config()
{
	logPeriod = 1;
	secondsToEat = 5;
	secondsToThink = 5;
	philosoferNames.push_back("Socrates");
	philosoferNames.push_back("Aristotle");
	philosoferNames.push_back("Parmenides");
	philosoferNames.push_back("Spinoza");
	philosoferNames.push_back("Nietzsche");
}

Config::Config(std::string fileName)
{
	logPeriod = 1;
	secondsToEat = 5;
	secondsToThink = 5;
	philosoferNames.push_back("Socrates");
	philosoferNames.push_back("Aristotle");
	philosoferNames.push_back("Parmenides");
	philosoferNames.push_back("Spinoza");
	philosoferNames.push_back("Nietzsche");
}

unsigned Config::getLogPeriod()
{
	return logPeriod;
}

unsigned Config::getSecondsToEat()
{
	return secondsToEat;
}

unsigned Config::getSecondsToThink()
{
	return secondsToThink;
}

std::vector<std::string> Config::getPhilosoferNames()
{
	return philosoferNames;
}
