#include "stdafx.h"
#include "config.h"

#include "libs/pugixml/src/pugixml.hpp"
#include "libs/pugixml/src/pugixml.cpp"

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

Config::Config(const char* source)
{
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(source);

	secondsToEat = (unsigned)doc.child("config").child("secondsToEat").text().as_int();
	secondsToThink = (unsigned)doc.child("config").child("secondsToThink").text().as_int();
	logPeriod = (unsigned)doc.child("config").child("logPeriod").text().as_int();
	timeOut = (unsigned)doc.child("config").child("timeOut").text().as_int();
	logFilePath = doc.child("config").child("logFile").text().as_string();

	for (pugi::xml_node philosofer : doc.child("config").child("philosofers").children("philosofer"))
	{
		std::string philosoferName = philosofer.text().as_string();
		philosoferNames.push_back(philosoferName);
	}
}

unsigned Config::getLogPeriod()
{
	return logPeriod;
}

unsigned Config::getTimeOut()
{
	return timeOut;
}

unsigned Config::getSecondsToEat()
{
	return secondsToEat;
}

unsigned Config::getSecondsToThink()
{
	return secondsToThink;
}

std::string Config::getLogFilePath()
{
	return logFilePath;
}

std::vector<std::string> Config::getPhilosoferNames()
{
	return philosoferNames;
}
