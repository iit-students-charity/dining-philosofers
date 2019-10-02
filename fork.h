#pragma once

#include <windows.h>

class Fork
{
public:
	Fork();
	void wait();
	void free();

private:
	HANDLE semaphore;
};
