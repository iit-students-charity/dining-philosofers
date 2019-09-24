#include "stdafx.h"
#include <windows.h>
#include <stdio.h>
#include <process.h>
#include <string>
#include <vector>
#include <iostream>

unsigned __stdcall reflect(void* pArguments)
{
	HANDLE hTimer = NULL;
	LARGE_INTEGER liDueTime;

	liDueTime.QuadPart = -50000000LL;
	hTimer = CreateWaitableTimer(NULL, TRUE, NULL);
	SetWaitableTimer(hTimer, &liDueTime, 0, NULL, NULL, 0);
	WaitForSingleObject(hTimer, INFINITE);






	_endthreadex(0);
	return 0;
}

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
	Fork* leftHand = nullptr;
	Fork* rightHand = nullptr;
	bool isEating = false;
	unsigned handle;

	static unsigned __stdcall startReflectionThread(void *p_this)
	{
		Philosofer* p_foo = static_cast<Philosofer*>(p_this);
		p_foo->reflect();
		return 0;
	}

	void reflect()
	{
		HANDLE hTimer = NULL;
		LARGE_INTEGER liDueTime;

		liDueTime.QuadPart = -50000000LL;
		hTimer = CreateWaitableTimer(NULL, TRUE, NULL);
		SetWaitableTimer(hTimer, &liDueTime, 0, NULL, NULL, 0);
		WaitForSingleObject(hTimer, INFINITE);

		_endthreadex(0);
	}

public:
	Philosofer(std::string name) 
	{
		this->name = name;
	}
	
	void startReflection()
	{
		handle = _beginthreadex(NULL, 0, &Philosofer::startReflectionThread, this, 0, NULL);
	}
};



class Table
{
	std::vector<Philosofer> philosofers;
	std::vector<Fork> forks;

public:
	Table(std::vector<Philosofer> philosofers) 
	{
		this->philosofers = philosofers;
		for (size_t i = 0; i < philosofers.size(); i++)
		{
			forks.push_back(Fork(i));
		}
		for (size_t i = 0; i < philosofers.size(); i++)
		{
			philosofers.at(i).startReflection();
		}
		// start philosofers
		// while true log state every second
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

	//HANDLE hThread, hThread2;
	//unsigned threadID;

	//hThread = (HANDLE)_beginthreadex(NULL, 0, &reflect, NULL, 0, &threadID);
	//hThread2 = (HANDLE)_beginthreadex(NULL, 0, &reflect, NULL, 0, &threadID);

	//WaitForSingleObject(hThread, INFINITE);
	//printf("%d\n", Counter);

	//CloseHandle(hThread);

	system("pause");
}