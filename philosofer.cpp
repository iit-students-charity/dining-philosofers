#include "stdafx.h"
#include "philosofer.h"

Philosofer::Philosofer(std::string name)
{
	this->name = name;
	setState(Thinking);
}

void Philosofer::startReflection()
{
	_beginthreadex(NULL, 0, &Philosofer::callThreadMethod, this, 0, NULL);
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

void Philosofer::waitForThinking()
{
	Sleep(SECONDS_TO_THINK * 1000);
}

void Philosofer::waitForEating()
{
	Sleep(SECONDS_TO_EAT * 1000);
}

void Philosofer::setState(State state)
{
	this->state = state;
}