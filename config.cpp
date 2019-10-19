#include "stdafx.h"
#include "config.h"

#include "libs/pugixml/src/pugixml.hpp"

Config::Config(const char* source, Log* log)
{
	this->log = log;

	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(source);

	if (result.status == 1)
	{
		std::string sourceString = std::string(source);
		log->log("Config error. Cannot open " + sourceString);
		log->log("Program exited due to config error");
		delete log;
		delete this;
		exit(1);
	}

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

	validate();
}

void Config::validate()
{
	bool error = false;

	if (secondsToEat < 1)
	{
		log->log("Config error. SecondsToEat tag should present and be 1 or more");
		error = true;
	}

	if (secondsToThink < 1)
	{
		log->log("Config error. SecondsToThink tag should present and be 1 or more");
		error = true;
	}

	if (outputPeriod < 1)
	{
		log->log("Config error. OutputPeriod tag should present and be 1 or more");
		error = true;
	}

	if (timeOut < 1)
	{
		log->log("Config error. Timeout tag should present and be 1 or more");
		error = true;
	}

	if (outputFilePath == "")
	{
		log->log("Config error. outputFilePath tag should present");
		error = true;
	}

	if (philosoferNames.size() < 1)
	{
		log->log("Config error. Philosofers tag should contain at least 1 philosofer tag");
		error = true;
	}

	for (std::string philosoferName : philosoferNames)
	{
		if (philosoferName == "")
		{
			log->log("Config error. Each philosofer should have a name");
			error = true;
			break;
		}
	}

	if (error)
	{
		log->log("Program exited due to config error");
		exit(1);
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
