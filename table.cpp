#include "stdafx.h"
#include "table.h"
#include "config.h"

#include <chrono>

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

void Table::lunch()
{
	logHeading(std::cout);
	logHeading(log);

	for (size_t i = 0; i < count; i++)
	{
		philosofers.at(i).startReflection();
	}

	std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
	while (std::chrono::steady_clock::now() - start < std::chrono::seconds(2))
	{
		logStates(std::cout);
		logStates(log);
		waitForLoggingPeriod();
	}

	for (size_t i = 0; i < count; i++)
	{
		philosofers.at(i).stopReflection();
	}

	logLine(std::cout);
	logLine(log);
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

void Table::logHeading(std::ostream& stream)
{
	logLine(stream);
	stream << "|";
	for (size_t i = 0; i < count; i++)
	{
		stream << " " << std::left << std::setw(15) << philosofers.at(i).getName() << " |";
	}
	stream << std::endl;
	logLine(stream);
}

void Table::logLine(std::ostream& stream)
{
	stream << "#" << std::string((count * 17 + count - 1), '-') << "#" << std::endl;
}

void Table::waitForLoggingPeriod()
{
	Sleep(logPeriod * 1000);
}
