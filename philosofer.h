#pragma once

#include "fork.h"

#include <process.h>
#include <string>

class Philosofer
{
public:
	Philosofer(std::string name, unsigned placeNumber);
	~Philosofer();
	void startReflection();
	void stopReflection();
	std::string getName();
	std::string getStateString();
	void setLeftHand(Fork* fork);
	void setRightHand(Fork* fork);
	void setSecondsToEat(unsigned secondsToEat);
	void setSecondsToThink(unsigned secondsToThink);

private:
	enum State { Thinking, WaitingForLeft, WaitingForRight, Eating } state;
	std::string name;
	unsigned placeNumber;
	unsigned secondsToEat;
	unsigned secondsToThink;
	Fork* leftHand;
	Fork* rightHand;
	HANDLE thread;
	HANDLE stopEvent;

	static unsigned __stdcall callThreadMethod(void *p_this);
	void reflectionCycle();
	void waitForThinking();
	void waitForEating();
	void setState(State state);
	bool isPlaceNumberOdd();
};
