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

Config::Config(const char* pathToFile)
{
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(pathToFile);
	//	if (!result)

	this->secondsToEat = (unsigned)doc.child("config").child("secondsToEat").text().as_int();
	this->secondsToThink = (unsigned)doc.child("config").child("secondsToThink").text().as_int();
	this->logPeriod = (unsigned)doc.child("config").child("logPeriod").text().as_int();

	for (pugi::xml_node philosofer : doc.child("config").child("philosofers").children("philosofer"))
	{
		char* philosoferName = (char*)philosofer.text().as_string();
		this->philosoferNames.push_back(philosoferName);
	}
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
