#pragma once

#include <windows.h>

class Fork
{
public:
	Fork();
	void wait();
	void release();

private:
	HANDLE semaphore;
};