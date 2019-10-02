#include "stdafx.h"
#include "philosofer.h"
#include "config.h"

Philosofer::Philosofer(std::string name, unsigned placeNumber)
{
	this->placeNumber = placeNumber;
	this->name = name;
	secondsToThink = 5;
	secondsToEat = 5;
	setState(Thinking);
}

Philosofer::~Philosofer()
{
	CloseHandle(handle);
}

void Philosofer::startReflection()
{
	handle = (HANDLE)_beginthreadex(NULL, 0, &Philosofer::callThreadMethod, this, 0, NULL);
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

unsigned __stdcall Philosofer::callThreadMethod(void *p_this)
{
	Philosofer* philosofer = (Philosofer*)(p_this);
	philosofer->reflectionCycle();
	return 0;
}

void Philosofer::reflectionCycle()
{
	while (true)
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
		else {
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
}

void Philosofer::waitForThinking()
{
	Sleep(secondsToEat * 1000);
}

void Philosofer::waitForEating()
{
	Sleep(secondsToEat * 1000);
}

void Philosofer::setState(State state)
{
	this->state = state;
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
