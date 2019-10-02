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
	log.close();
}

void Table::startMeal()
{
	for (size_t i = 0; i < count; i++)
	{
		philosofers.at(i).startReflection();
	}

	logPreamble(std::cout);
	logPreamble(log);
	while (true)
	{
		logStates(std::cout);
		logStates(log);
		waitForLoggingPeriod();
	}
}

void Table::logStates(std::ostream& stream)
{
	stream << "|";
	for (size_t i = 0; i < count; i++)
	{
		stream << " " << std::left << std::setw(15) << philosofers.at(i).getStateString() << " |";
	}
	stream << std::endl;
}

void Table::logPreamble(std::ostream& stream)
{
	stream << "#" << std::string((count * 17 + count - 1), '-') << "#" << std::endl << "|";
	for (size_t i = 0; i < count; i++)
	{
		stream << " " << std::left << std::setw(15) << philosofers.at(i).getName() << " |";
	}
	stream << std::endl << "#" << std::string((count * 17 + count - 1), '-') << "#" << std::endl;
}

void Table::waitForLoggingPeriod()
{
	Sleep(logPeriod * 1000);
}
