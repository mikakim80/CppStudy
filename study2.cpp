#include "ExecuteInterface.h"
#include <iostream>

DECLARE_INTERFACE(Study, 2);

void Study2::Execute()
{
	std::cout << "Study2::Execute()" << std::endl;
}

