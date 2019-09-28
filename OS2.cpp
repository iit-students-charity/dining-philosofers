#include "stdafx.h"
#include <windows.h>
#include <stdio.h>
#include <process.h>
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>

class Fork
{
public:
	Fork()
	{
		semaphore = CreateSemaphore(NULL, 1, 1, NULL);
	}

	void wait()
	{
		WaitForSingleObject(semaphore, INFINITE);
	}

	void release()
	{
		ReleaseSemaphore(semaphore, 1, NULL);
	}

private:
	HANDLE semaphore;
};

class Philosofer
{
public:
	Philosofer(std::string name)
	{
		this->name = name;
		setState(Thinking);
	}

	void startReflection()
	{
		_beginthreadex(NULL, 0, &Philosofer::callThreadMethod, this, 0, NULL);
	}

	std::string getName()
	{
		return name;
	}

	std::string getStateString()
	{
		switch (state)
		{
		case Thinking:
			return "thinking";
		case Eating:
			return "eating";
		case WaitingForLeft:
			return "waiting left";
		case WaitingForRight:
			return "waiting right";
		};
	}

	void setLeftHand(Fork* fork)
	{
		leftHand = fork;
	}

	void setRightHand(Fork* fork)
	{
		rightHand = fork;
	}

private:
	std::string name;
	enum State { Thinking, WaitingForLeft, WaitingForRight, Eating } state;
	static const int SECONDS_TO_EAT = 5;
	static const int SECONDS_TO_THINK = 5;
	Fork* leftHand;
	Fork* rightHand;

	static unsigned __stdcall callThreadMethod(void *p_this)
	{
		Philosofer* philosofer = (Philosofer*)(p_this);
		philosofer->reflectionCycle();
		return 0;
	}

	void reflectionCycle()
	{
		while (true) 
		{
			setState(Thinking);
			waitForThinking();

			setState(WaitingForLeft);
			leftHand->wait();

			setState(WaitingForRight);
			rightHand->wait();

			setState(Eating);
			waitForEating();

			leftHand->release();
			rightHand->release();
		}
	}

	void waitForThinking()
	{
		Sleep(SECONDS_TO_THINK * 1000);
	}

	void waitForEating()
	{
		Sleep(SECONDS_TO_EAT * 1000);
	}

	void setState(State state)
	{
		this->state = state;
	}
};

class Table
{
public:
	Table(std::vector<Philosofer> philosofers)
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

	void startMeal()
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

	void logStates()
	{
		std::cout << "|";
		for (size_t i = 0; i < count; i++)
		{
			std::cout << " " << std::left << std::setw(15) << philosofers.at(i).getStateString() << " |";
		}
		std::cout << std::endl;
	}

private:
	std::vector<Philosofer> philosofers;
	std::vector<Fork> forks;
	size_t count;
	static const int LOG_PERIOD = 1;

	void waitForLoggingPeriod()
	{
		Sleep(LOG_PERIOD * 1000);
	}

	void printPreamble()
	{
		std::cout << "#" << std::string((count * 17 + count - 1), '-') << "#" << std::endl << "|";
		for (size_t i = 0; i < count; i++)
		{
			std::cout << " " << std::left << std::setw(15) << philosofers.at(i).getName() << " |";
		}
		std::cout << std::endl << "#" << std::string((count * 17 + count - 1), '-') << "#" << std::endl;
	}
};

int main()
{
	std::vector<Philosofer> philosofers;
	Philosofer *socrates = new Philosofer("Socrates");
	Philosofer *aristotle = new Philosofer("Aristotle");
	Philosofer *parmenides = new Philosofer("Parmenides");
	Philosofer *spinoza = new Philosofer("Spinoza");
	Philosofer *nietzsche = new Philosofer("Nietzsche");
	philosofers.push_back(*socrates);
	philosofers.push_back(*aristotle);
	philosofers.push_back(*parmenides);
	philosofers.push_back(*spinoza);
	philosofers.push_back(*nietzsche);

	Table table = Table(philosofers);
	table.startMeal();

	system("pause");
}

//      CloseHandle(hThread);


//		LARGE_INTEGER time;
//		time.QuadPart = -(LOG_PERIOD * 10000000);
//		HANDLE timer = CreateWaitableTimer(NULL, TRUE, NULL);
//		SetWaitableTimer(timer, &time, 0, NULL, NULL, 0);
//		WaitForSingleObject(timer, INFINITE);


// names from file
// каждый берёт сначала меньший номер, а кладёт наоборот
/// или
// чётные берут сначала левую филку, нечётные правую
