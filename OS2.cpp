#include "stdafx.h"
#include "fork.h"
#include "philosofer.h"
#include "table.h"

//xml

#include <stdio.h>
#include <vector>

int main()
{
	std::vector<Philosofer> philosofers;
	Philosofer *socrates = new Philosofer("Socrates");
	Philosofer *aristotle = new Philosofer("Aristotle");
	Philosofer *parmenides = new Philosofer("Parmenides");
	Philosofer *spinoza = new Philosofer("Spinoza");
	Philosofer *nietzsche = new Philosofer("Nietzsche");
	philosofers.push_back(*socrates);
	philosofers.push_back(*aristotle);
	philosofers.push_back(*parmenides);
	philosofers.push_back(*spinoza);
	philosofers.push_back(*nietzsche);

	Table table = Table(philosofers);
	table.startMeal();

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
