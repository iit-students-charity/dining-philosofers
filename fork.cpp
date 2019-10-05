#include "stdafx.h"
#include "fork.h"

Fork::Fork()
{
	mutex = CreateMutex(NULL, FALSE, NULL);
}

Fork::Fork(const Fork& object)
{
	mutex = CreateMutex(NULL, FALSE, NULL);
}

Fork::~Fork()
{
	CloseHandle(mutex);
}

void Fork::wait()
{
	WaitForSingleObject(mutex, INFINITE);
}

void Fork::free()
{
	ReleaseMutex(mutex);
}
