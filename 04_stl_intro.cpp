#include "ExecuteInterface.h"
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <iterator>
#include <functional>

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

void 삽입반복자()
{
	NUtil::PrintDivider("삽입반복자");

	std::vector<int> vi1 = { 1, 2, 3, 4, 5 };
	std::vector<int> vi2;

	// back_inserter 템플릿 함수는 전달된 컨테이너로 back_inserter_iterator 템플릿 클래스를 생성하고, 
	// copy 안의 대입 연산자에서는 컨테이너를 품은 back_inserter_iterator 클래스의 대입 연산자에서 push_back()을 호출한다.
	std::copy(vi1.rbegin(), vi1.rend(), std::back_inserter(vi2));
	//for (auto elem : vi2)
	//{
	//	std::cout << elem << " ";
	//}
	std::copy(vi2.begin(), vi2.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;
	NUtil::PrintElements(vi2, "PrintElementsTest");
}

class CPrint
{
public:
	static void Print(int i) { std::cout << i << " "; }
};

void 알고리즘_간단테스트()
{
	NUtil::PrintDivider("알고리즘_간단테스트");

	std::vector<int> vi1 = { 1, 2, 3, 4, 5 };
	std::for_each(vi1.begin(), vi1.end(), [](int i) { std::cout << i << " "; });
	std::cout << std::endl;
	// bind에 명시적으로 함수 주소(&)를 전달해야 하는지 불확실함. 둘 다 정상 동작함.
	//std::for_each(vi1.begin(), vi1.end(), std::bind(CPrint::Print, std::placeholders::_1));
	std::for_each(vi1.begin(), vi1.end(), std::bind(&CPrint::Print, std::placeholders::_1));
	std::cout << std::endl;
}

void ClassName::Execute()
{
	NUtil::PrintDivider("Stl04::Execute()");
	맵테스트();
	//범위기반for문테스트();
	//Const이터레이터();
	삽입반복자();
	알고리즘_간단테스트();
}


