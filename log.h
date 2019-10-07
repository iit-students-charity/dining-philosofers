#pragma once

#include <windows.h>
#include <string>
#include <fstream>
#include <queue>
#include <string>

class Log
{
public:
	Log(std::string logFilePath);
	~Log();
	void log(std::string message);
	
private:
	HANDLE thread;
	HANDLE queueAccessMutex;
	HANDLE stopEvent;
	std::ofstream logFile;
	std::queue<std::string> messages;

	static unsigned __stdcall callThreadMethod(void *thisPointer);
	void listen();
	std::string getHours(tm now);
	std::string getMinutes(tm now);
	std::string getSeconds(tm now);
};
