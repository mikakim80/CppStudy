#include "ExecuteInterface.h"
#include <iostream>
#include <map>

DECLARE_INTERFACE(StlIntro, 04);

class RangeBasedForTest
{
public:
	int* begin() { return arr; }
	int* end() { return &arr[10]; }

	const int* begin() const { return arr; }
	const int* end() const { return &arr[10]; }

	const int* cbegin() const { return begin(); }
	const int* cend() const { return end(); }

private:
	int arr[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
};

void 범위기반for문테스트()
{
	NUtil::PrintDivider("범위기반for문테스트");

	// const_iterator begin() const와 const_iterator cbegin() const은 동일하다. 하지만 범위기반for루프에서는 begin() const를 요구한다.
	const RangeBasedForTest testInstance;
	for (auto& elem : testInstance)
	{
		std::cout << elem << std::endl;
	}
}

void 맵테스트()
{
	NUtil::PrintDivider("맵테스트");

	std::map<int, int> iimap { {1, 1}, {2, 2}, {3, 3} };

	// 범위 기반 for 루프
	// Recognizes containers that have .begin() and .end().
	// 반복자를 반환하므로 value의 수정이 가능하다.
	for (auto& elem : iimap)
	{
		elem.second += 1;
	}

	for (auto& elem : iimap)
	{
		std::cout << elem.first << ": " << elem.second << std::endl;
	}
}

void Const이터레이터()
{
	NUtil::PrintDivider("Const이터레이터");

	const std::map<int, int> cMap;

	// const_iterator begin() const와 const_iterator cbegin() const은 동일하다. 하지만 범위기반for루프에서는 begin() const를 요구한다.
	for (auto& elem : cMap)
	{
	}
}

void ClassName::Execute()
{
	NUtil::PrintDivider("Stl04::Execute()");
	맵테스트();
	//범위기반for문테스트();
	Const이터레이터();
}


