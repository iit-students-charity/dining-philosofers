#include "stdafx.h"
#include "table.h"
#include "config.h"


Table::Table(Config config) : log(config.getLogFilePath(), std::ofstream::app)
{
	count = config.getPhilosoferNames().size();
	logPeriod = config.getLogPeriod();
	for (size_t i = 0; i < count; i++)
	{
		Fork *fork = new Fork;
		Philosofer *philosofer = new Philosofer(config.getPhilosoferNames().at(i), (unsigned)i);
		philosofer->setSecondsToEat(config.getSecondsToEat());
		philosofer->setSecondsToThink(config.getSecondsToThink());
		philosofers.push_back(*philosofer);
		forks.push_back(*fork);
	}
	for (size_t i = 0; i < count; i++)
	{
		philosofers.at(i).setLeftHand(&forks.at(i));
		philosofers.at(i).setRightHand(&forks.at((i + 1) % count));
	}
}

Table::~Table()
{
	philosofers.clear();
	forks.clear();
}

void Table::startMeal()
{
	for (size_t i = 0; i < count; i++)
	{
		philosofers.at(i).startReflection();
	}

	logPreamble();
	while (true)
	{
		logStates();
		waitForLoggingPeriod();
	}
}

void Table::logStates()
{
	statesToConsole();
	statesToFile();
}

void Table::statesToConsole()
{
	std::cout << "|";
	for (size_t i = 0; i < count; i++)
	{
		std::cout << " " << std::left << std::setw(15) << philosofers.at(i).getStateString() << " |";
	}
	std::cout << std::endl;
}

void Table::statesToFile()
{
	log << "|";
	for (size_t i = 0; i < count; i++)
	{
		log << " " << std::left << std::setw(15) << philosofers.at(i).getStateString() << " |";
	}
	log << std::endl;
}

void Table::waitForLoggingPeriod()
{
	Sleep(logPeriod * 1000);
}

void Table::logPreamble()
{
	preambleToConsole();
	preambleToFile();
}

void Table::preambleToConsole()
{
	std::cout << "#" << std::string((count * 17 + count - 1), '-') << "#" << std::endl << "|";
	for (size_t i = 0; i < count; i++)
	{
		std::cout << " " << std::left << std::setw(15) << philosofers.at(i).getName() << " |";
	}
	std::cout << std::endl << "#" << std::string((count * 17 + count - 1), '-') << "#" << std::endl;
}

void Table::preambleToFile()
{
	log << "#" << std::string((count * 17 + count - 1), '-') << "#" << std::endl << "|";
	for (size_t i = 0; i < count; i++)
	{
		log << " " << std::left << std::setw(15) << philosofers.at(i).getName() << " |";
	}
	log << std::endl << "#" << std::string((count * 17 + count - 1), '-') << "#" << std::endl;
}