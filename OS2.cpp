#include "stdafx.h"
#include "table.h"
#include "config.h"

#include <conio.h>
#include <iostream>
#include <vector>
#include <string>

int main()
{
	Config *config = new Config("config.xml");
	Table *table = new Table(*config);

	table->lunch();

	delete table;
	delete config;

	_getch();
}
