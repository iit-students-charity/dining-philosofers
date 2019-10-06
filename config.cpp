#include "stdafx.h"
#include "config.h"

#include "libs/pugixml/src/pugixml.hpp"
#include "libs/pugixml/src/pugixml.cpp"

Config::Config(const char* source, Log* log)
{
	this->log = log;

	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(source);

	secondsToEat = (unsigned)doc.child("config").child("secondsToEat").text().as_int();
	secondsToThink = (unsigned)doc.child("config").child("secondsToThink").text().as_int();
	outputPeriod = (unsigned)doc.child("config").child("outputPeriod").text().as_int();
	timeOut = (unsigned)doc.child("config").child("timeOut").text().as_int();
	outputFilePath = doc.child("config").child("outputFile").text().as_string();

	for (pugi::xml_node philosofer : doc.child("config").child("philosofers").children("philosofer"))
	{
		std::string philosoferName = philosofer.text().as_string();
		philosoferNames.push_back(philosoferName);
	}
}

unsigned Config::getOutputPeriod()
{
	return outputPeriod;
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

std::string Config::getOutputFilePath()
{
	return outputFilePath;
}

std::vector<std::string> Config::getPhilosoferNames()
{
	return philosoferNames;
}
