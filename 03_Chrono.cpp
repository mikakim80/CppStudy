#include "ExecuteInterface.h"
#include <iostream>

DECLARE_INTERFACE(Chrono, 03);

void Chrono03::Execute()
{
	std::cout << "Chrono03::Execute()" << std::endl;
}
