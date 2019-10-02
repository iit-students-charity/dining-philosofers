#include "stdafx.h"
#include "fork.h"
#include "philosofer.h"
#include "table.h"
#include "config.h"

#include <stdio.h>
#include <vector>
#include <string>

int main()
{
	Config *config = new Config("config.xml");
	Table *table = new Table(*config);
	table->lunch();

	delete table;
	//delete config;

	system("pause");
}

//		LARGE_INTEGER time;
//		time.QuadPart = -(LOG_PERIOD * 10000000);
//		HANDLE timer = CreateWaitableTimer(NULL, TRUE, NULL);
//		SetWaitableTimer(timer, &time, 0, NULL, NULL, 0);
//		WaitForSingleObject(timer, INFINITE);
