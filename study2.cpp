#include "ExecuteInterface.h"
#include <iostream>

DECLARE_INTERFACE(Study, 02);

void Study02::Execute()
{
	std::cout << "Study02::Execute()" << std::endl;
}

