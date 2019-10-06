#include "stdafx.h"
#include "table.h"
#include "config.h"

#include <conio.h>
#include <vector>
#include <string>

int main()
{
	Config *config = new Config("config.xml");
	Table *table = new Table(config);

	table->lunch();

	delete table;
	delete config;

	std::cout << std::endl << "Program finished, press any key to exit." << std::endl;
	_getch();
}
