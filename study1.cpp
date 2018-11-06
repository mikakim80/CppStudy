#include "ExecuteInterface.h"
#include <iostream>

DECLARE_INTERFACE(Study, 1);

void Study1::Execute()
{
	std::cout << "Study1::Execute()" << std::endl;
}

