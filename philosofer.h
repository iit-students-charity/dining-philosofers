#pragma once

#include "fork.h"

#include <process.h>
#include <string>

class Philosofer
{
public:
	Philosofer(std::string name);
	void startReflection();
	std::string getName();
	std::string getStateString();
	void setLeftHand(Fork* fork);
	void setRightHand(Fork* fork);

private:
	std::string name;
	enum State { Thinking, WaitingForLeft, WaitingForRight, Eating } state;
	static const int SECONDS_TO_EAT = 5;
	static const int SECONDS_TO_THINK = 5;
	Fork* leftHand;
	Fork* rightHand;

	static unsigned __stdcall callThreadMethod(void *p_this);
	void reflectionCycle();
	void waitForThinking();
	void waitForEating();
	void setState(State state);
};