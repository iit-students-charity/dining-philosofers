#pragma once

#include <windows.h>

class Fork
{
public:
	Fork();
	~Fork();
	void wait();
	void free();

private:
	HANDLE semaphore;
};
