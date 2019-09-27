#include "stdafx.h"
#include <windows.h>
#include <stdio.h>
#include <process.h>
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>

struct Fork
{
	int number;
	HANDLE semaphore;
		
	Fork(int number)
	{
		this->number = number;
		semaphore = CreateSemaphore(NULL, 1, 1, NULL);
	}
};

class Philosofer
{
	std::string name;
	enum State { thinking, waiting_for_left, waiting_for_right, eating } state;
	static const int SECONDS_TO_EAT = 5;
	static const int SECONDS_TO_THINK = 5;
	Fork* leftHand;
	Fork* rightHand;

	unsigned handle;

	static unsigned __stdcall startReflectionThread(void *p_this)
	{
		Philosofer* philosofer = static_cast<Philosofer*>(p_this);
		philosofer->reflect();
		return 0;
	}

	void reflect()
	{
		while (true) 
		{
			setState(thinking);
			waitForThinking();

			setState(waiting_for_left);
			WaitForSingleObject(leftHand->semaphore, INFINITE);

			setState(waiting_for_right);
			WaitForSingleObject(rightHand->semaphore, INFINITE);

			setState(eating);
			waitForEating();

			ReleaseSemaphore(leftHand->semaphore, 1, NULL);
			ReleaseSemaphore(rightHand->semaphore, 1, NULL);
		}
		_endthreadex(0);
	}

	void waitForThinking() 
	{
		LARGE_INTEGER time;
		time.QuadPart = -(SECONDS_TO_THINK * 10000000);
		HANDLE timer = CreateWaitableTimer(NULL, TRUE, NULL);
		SetWaitableTimer(timer, &time, 0, NULL, NULL, 0);
		WaitForSingleObject(timer, INFINITE);
	}

	void waitForEating()
	{
		LARGE_INTEGER time;
		time.QuadPart = -(SECONDS_TO_EAT * 10000000);
		HANDLE timer = CreateWaitableTimer(NULL, TRUE, NULL);
		SetWaitableTimer(timer, &time, 0, NULL, NULL, 0);
		WaitForSingleObject(timer, INFINITE);
	}

	void setState(State state)
	{
		this->state = state;
	}

public:
	Philosofer(std::string name) 
	{
		this->name = name;
		setState(thinking);
	}
	
	void startReflection()
	{
		handle = _beginthreadex(NULL, 0, &Philosofer::startReflectionThread, this, 0, NULL);
	}

	std::string getName()
	{
		return name;
	}

	std::string getStateString()
	{
		switch (state)
		{
		case thinking:
			return "thinking";
		case eating:
			return "eating";
		case waiting_for_left:
			return "waiting left";
		case waiting_for_right:
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
};

class Table
{
	std::vector<Philosofer> philosofers;
	std::vector<Fork> forks;
	size_t count;
	static const int LOG_PERIOD = 1;

	void waitForLoggingPeriod()
	{
		LARGE_INTEGER time;
		time.QuadPart = -(LOG_PERIOD * 10000000);
		HANDLE timer = CreateWaitableTimer(NULL, TRUE, NULL);
		SetWaitableTimer(timer, &time, 0, NULL, NULL, 0);
		WaitForSingleObject(timer, INFINITE);
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

public:
	Table(std::vector<Philosofer> philosofers) 
	{
		count = philosofers.size();
		this->philosofers = philosofers;
		for (size_t i = 0; i < count; i++)
		{
			Fork *fork = new Fork(i);
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

//CloseHandle(hThread);
