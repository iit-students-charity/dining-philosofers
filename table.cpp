#include "stdafx.h"
#include "table.h"
#include "config.h"

#include <chrono>

Table::Table(Config* config) : output(config->getOutputFilePath(), std::ofstream::app)
{
	count = config->getPhilosoferNames().size();
	outputPeriod = config->getOutputPeriod();
	timeOut = config->getTimeOut();
	for (size_t i = 0; i < count; i++)
	{
		Fork *fork = new Fork;
		Philosofer *philosofer = new Philosofer(config->getPhilosoferNames().at(i), (unsigned)i);
		philosofer->setSecondsToEat(config->getSecondsToEat());
		philosofer->setSecondsToThink(config->getSecondsToThink());
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
	output.close();
}

void Table::lunch()
{
	outputHeading(std::cout);
	outputHeading(output);

	for (size_t i = 0; i < count; i++)
	{
		philosofers.at(i).startReflection();
	}

	std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
	while (std::chrono::steady_clock::now() - start < std::chrono::seconds(timeOut))
	{
		outputStates(std::cout);
		outputStates(output);
		waitForOutputPeriod();
	}

	outputLine(std::cout);
	outputLine(output);

	for (size_t i = 0; i < count; i++)
	{
		philosofers.at(i).stopReflection();
	}
}

void Table::outputStates(std::ostream& stream)
{
	stream << "|";
	for (size_t i = 0; i < count; i++)
	{
		stream << " " << std::left << std::setw(15) << philosofers.at(i).getStateString() << " |";
	}
	stream << std::endl;
}

void Table::outputHeading(std::ostream& stream)
{
	outputLine(stream);
	stream << "|";
	for (size_t i = 0; i < count; i++)
	{
		stream << " " << std::left << std::setw(15) << philosofers.at(i).getName() << " |";
	}
	stream << std::endl;
	outputLine(stream);
}

void Table::outputLine(std::ostream& stream)
{
	stream << "#" << std::string((count * 17 + count - 1), '-') << "#" << std::endl;
}

void Table::waitForOutputPeriod()
{
	Sleep(outputPeriod * 1000);
}
