#include "stdafx.h"
#include "table.h"
#include "config.h"
#include "log.h"

#include <conio.h>
#include <vector>
#include <string>

int main(int argc, char *argv[])
{
	Log *log = new Log(argv[2]);
	Config *config = new Config(argv[1], log);
	Table *table = new Table(config, log);

	table->lunch();

	delete table;
	delete config;
	delete log;

	std::cout << std::endl << "Program finished, press any key to exit." << std::endl;
	_getch();
}
