#include "stdafx.h"
#include "log.h"

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
	logFile << message << std::endl;
	ReleaseMutex(mutex);
}
