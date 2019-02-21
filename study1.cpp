#include "ExecuteInterface.h"
#include <iostream>

DECLARE_INTERFACE(Study, 01);

void Study01::Execute()
{
	std::cout << "Study01::Execute()" << std::endl;
}

