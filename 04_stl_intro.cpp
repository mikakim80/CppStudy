#include "ExecuteInterface.h"
#include <iostream>
#include <map>

DECLARE_INTERFACE(StlIntro, 04);

void 맵테스트()
{
	NUtil::PrintDivider("맵테스트");

	std::map<int, int> iimap { {1, 1}, {2, 2}, {3, 3} };

	// 범위 기반 for 루프
	// Recognizes containers that have .begin() and .end().
	// 그러므로 value의 수정이 가능하다.
	for (auto& elem : iimap)
	{
		elem.second += 1;
	}

	for (auto& elem : iimap)
	{
		std::cout << elem.first << ": " << elem.second << std::endl;
	}
}

void ClassName::Execute()
{
	NUtil::PrintDivider("Stl04::Execute()");
	맵테스트();
}


