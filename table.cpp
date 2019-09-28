#include "stdafx.h"
#include "table.h"

Table::Table(std::vector<Philosofer> philosofers)
{
	count = philosofers.size();
	this->philosofers = philosofers;
	for (size_t i = 0; i < count; i++)
	{
		Fork *fork = new Fork;
		forks.push_back(*fork);
	}
	for (size_t i = 0; i < count; i++)
	{
		this->philosofers.at(i).setLeftHand(&forks.at(i));
		this->philosofers.at(i).setRightHand(&forks.at((i + 1) % count));
	}
}

void Table::startMeal()
{
	for (size_t i = 0; i < count; i++)
	{
		philosofers.at(i).startReflection();
	}

	printPreamble();
	while (true)
	{
		logStates();
		waitForLoggingPeriod();
	}
}

void Table::logStates()
{
	std::cout << "|";
	for (size_t i = 0; i < count; i++)
	{
		std::cout << " " << std::left << std::setw(15) << philosofers.at(i).getStateString() << " |";
	}
	std::cout << std::endl;
}

std::vector<Philosofer> philosofers;
std::vector<Fork> forks;
size_t count;
static const int LOG_PERIOD = 1;

void Table::waitForLoggingPeriod()
{
	Sleep(LOG_PERIOD * 1000);
}

void Table::printPreamble()
{
	std::cout << "#" << std::string((count * 17 + count - 1), '-') << "#" << std::endl << "|";
	for (size_t i = 0; i < count; i++)
	{
		std::cout << " " << std::left << std::setw(15) << philosofers.at(i).getName() << " |";
	}
	std::cout << std::endl << "#" << std::string((count * 17 + count - 1), '-') << "#" << std::endl;
}
