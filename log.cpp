#include "stdafx.h"
#include "log.h"

#include <iomanip>
#include <process.h>
#include <time.h>

Log::Log(std::string logFilePath) : logFile(logFilePath, std::ofstream::app)
{
	stopEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	queueAccessMutex = CreateMutex(NULL, FALSE, NULL);
	thread = (HANDLE)_beginthreadex(NULL, 0, &Log::callThreadMethod, this, 0, NULL);
}

Log::~Log()
{
	SetEvent(stopEvent);
	WaitForSingleObject(thread, INFINITE);
	CloseHandle(stopEvent);
	CloseHandle(thread);
	CloseHandle(queueAccessMutex);
	logFile.close();
}

unsigned __stdcall Log::callThreadMethod(void *thisPointer)
{
	Log* log = (Log*)(thisPointer);
	log->listen();
	return 0;
}

void Log::listen()
{
	while (WaitForSingleObject(stopEvent, 0) != WAIT_OBJECT_0)
	{
		if (messages.size())
		{
			logFile << messages.back();
			messages.pop();
		}
	}
}

void Log::log(std::string message)
{
	tm now;
	time_t currentTime = time(0);
	localtime_s(&now, &currentTime);

	WaitForSingleObject(queueAccessMutex, INFINITE);
	messages.push(getHours(now) + ":" + getMinutes(now) + ":" + getSeconds(now) + " | " + message + "\n");
	ReleaseMutex(queueAccessMutex);
}

std::string Log::getHours(tm now)
{
	if (now.tm_hour < 10)
		return "0" + std::to_string(now.tm_hour);
	else
		return std::to_string(now.tm_hour);
}

std::string Log::getMinutes(tm now)
{
	if (now.tm_min < 10)
		return "0" + std::to_string(now.tm_min);
	else
		return std::to_string(now.tm_min);
}

std::string Log::getSeconds(tm now)
{
	if (now.tm_sec < 10)
		return "0" + std::to_string(now.tm_sec);
	else
		return std::to_string(now.tm_sec);
}