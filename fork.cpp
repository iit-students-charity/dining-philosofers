#include "stdafx.h"
#include "fork.h"

Fork::Fork()
{
	semaphore = CreateSemaphore(NULL, 1, 1, NULL);
}

void Fork::wait()
{
	WaitForSingleObject(semaphore, INFINITE);
}

void Fork::free()
{
	ReleaseSemaphore(semaphore, 1, NULL);
}
