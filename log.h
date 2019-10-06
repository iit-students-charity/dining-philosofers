#pragma once

#include <windows.h>
#include <string>
#include <fstream>

class Log
{
public:
	Log(std::string logFilePath);
	~Log();
	void log(std::string message);
	
private:
	HANDLE mutex;
	std::ofstream logFile;

	std::string getHours(tm now);
	std::string getMinutes(tm now);
	std::string getSeconds(tm now);
};
