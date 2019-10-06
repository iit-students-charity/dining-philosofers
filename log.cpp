#include "stdafx.h"
#include "log.h"

#include <iomanip>
#include <time.h>

Log::Log(std::string logFilePath) : logFile(logFilePath, std::ofstream::app)
{
	mutex = CreateMutex(NULL, FALSE, NULL);
}

Log::~Log()
{
	logFile.close();
	CloseHandle(mutex);
}

void Log::log(std::string message)
{
	WaitForSingleObject(mutex, INFINITE);

	tm now;
	time_t currentTime = time(0);
	localtime_s(&now, &currentTime);

	logFile << getHours(now) << ":" << getMinutes(now) << ":" << getSeconds(now) << " | ";
	logFile << message << std::endl;

	ReleaseMutex(mutex);
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