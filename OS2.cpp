#include "stdafx.h"
#include "fork.h"
#include "philosofer.h"
#include "table.h"
#include "config.h"

// xml

#include <stdio.h>
#include <vector>
#include <string>

int main()
{
	Config *config = new Config("config.xml");

	Table *table = new Table(*config);
	table->startMeal();

	system("pause");
}

//      CloseHandle(hThread);


//		LARGE_INTEGER time;
//		time.QuadPart = -(LOG_PERIOD * 10000000);
//		HANDLE timer = CreateWaitableTimer(NULL, TRUE, NULL);
//		SetWaitableTimer(timer, &time, 0, NULL, NULL, 0);
//		WaitForSingleObject(timer, INFINITE);


// names from file
// каждый берёт сначала меньший номер, а кладёт наоборот
/// или
// чётные берут сначала левую филку, нечётные правую
