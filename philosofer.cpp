#include "stdafx.h"
#include "philosofer.h"
#include "config.h"

Philosofer::Philosofer(std::string name, unsigned placeNumber, Log* log)
{
	this->name = name;
	this->placeNumber = placeNumber;
	this->log = log;
	secondsToThink = 5;
	secondsToEat = 5;
	stopEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	state = Thinking;
}

void Philosofer::startReflection()
{
	thread = (HANDLE)_beginthreadex(NULL, 0, &Philosofer::callThreadMethod, this, 0, NULL);
}

void Philosofer::stopReflection()
{
	log->log(name + ": setting stop event");

	SetEvent(stopEvent);
	WaitForSingleObject(thread, INFINITE);
	CloseHandle(thread);
	CloseHandle(stopEvent);
}

std::string Philosofer::getName()
{
	return name;
}

std::string Philosofer::getStateString()
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
	default:
		return NULL;
	};
}

void Philosofer::setLeftHand(Fork* fork)
{
	leftHand = fork;
}

void Philosofer::setRightHand(Fork* fork)
{
	rightHand = fork;
}

unsigned __stdcall Philosofer::callThreadMethod(void *thisPointer)
{
	Philosofer* philosofer = (Philosofer*)(thisPointer);
	philosofer->reflectionLoop();
	return 0;
}

void Philosofer::reflectionLoop()
{
	log->log(name + ": starting reflection loop");

	while (WaitForSingleObject(stopEvent, 0) != WAIT_OBJECT_0)
	{
		setState(Thinking);
		waitForThinking();

		if (isPlaceNumberOdd()) 
		{
			setState(WaitingForLeft);
			leftHand->wait();

			setState(WaitingForRight);
			rightHand->wait();
		}
		else 
		{
			setState(WaitingForRight);
			rightHand->wait();

			setState(WaitingForLeft);
			leftHand->wait();
		}

		setState(Eating);
		waitForEating();

		leftHand->free();
		rightHand->free();
	}

	log->log(name + ": process exited correctly");
}

void Philosofer::waitForThinking()
{
	log->log(name + ": awaiting thinking, " + std::to_string(secondsToThink) + " seconds left");
	Sleep(secondsToThink * MILLISECONDS_IN_SECOND);
}

void Philosofer::waitForEating()
{
	log->log(name + ": awaiting eating, " + std::to_string(secondsToEat) + " seconds left");
	Sleep(secondsToEat * MILLISECONDS_IN_SECOND);
}

void Philosofer::setState(State state)
{
	this->state = state;
	log->log(name + ": state updated to " + getStateString());
}

bool Philosofer::isPlaceNumberOdd()
{
	return (placeNumber % 2) != 0;
}

void Philosofer::setSecondsToEat(unsigned secondsToEat)
{
	this->secondsToEat = secondsToEat;
}

void Philosofer::setSecondsToThink(unsigned secondsToThink)
{
	this->secondsToThink = secondsToThink;
}
