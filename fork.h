#pragma once

#include <windows.h>

class Fork
{
public:
	Fork(const Fork&);
	Fork();
	~Fork();
	void wait();
	void free();

private:
	HANDLE mutex;
};
