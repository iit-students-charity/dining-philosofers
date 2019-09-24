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
	Fork* leftHand = nullptr;
	Fork* rightHand = nullptr;

	unsigned handle;

	static unsigned __stdcall startReflectionThread(void *p_this)
	{
		Philosofer* philosofer = static_cast<Philosofer*>(p_this);
		philosofer->reflect();
		return 0;
	}

	void reflect()
	{
		setState(thinking);
		waitForThinking();

		// try left and(or?) right fork and update status

		setState(eating);
		waitForEating();

		// release semaphores (in forks)

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
			forks.push_back(Fork(i));
		}
		for (size_t i = 0; i < count; i++)
		{
			philosofers.at(i).setLeftHand(&forks.at(i));
			philosofers.at(i).setRightHand(&forks.at((i + 1) % count));
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
	std::vector<Philosofer> philosofers 
	{
		Philosofer("Socrates"),
		Philosofer("Aristotle"),
		Philosofer("Parmenides"),
		Philosofer("Spinoza"),
		Philosofer("Nietzsche")
	};
	Table table = Table(philosofers);
	table.startMeal();

	system("pause");
}

//CloseHandle(hThread);
