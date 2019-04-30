#include "ExecuteInterface.h"
#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

DECLARE_INTERFACE(Iterator, 06);

void 임시_이터레이터_연산()
{
	NUtil::PrintDivider("임시 이터레이터 연산");

	std::vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8 };
	std::random_shuffle(v.begin(), v.end());
	NUtil::PrintElements(v);
	std::sort(++v.begin(), v.end());			// ms의 c++ 구현에서는 array, vector의 반복자는 클래스 타입이므로 임시 변수에 대하여 ++ 연산이 적용 가능하다.
	std::sort(std::next(v.begin()), v.end());	// 하지만 포터블하게 std::next() 유틸리티 함수를 권장한다.
	NUtil::PrintElements(v);

	std::array<int, 10> a = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
	std::random_shuffle(a.begin(), a.end());
	NUtil::PrintElements(a);
	std::sort(++a.begin(), a.end());
	NUtil::PrintElements(a);
}

class CInsertTest
{
public:
	CInsertTest(int i)
		: m_v{i}
	{
		std::cout << "기본 생성자" << std::endl;
	}

	~CInsertTest()
	{
		std::cout << "소멸자" << std::endl;
	}

	CInsertTest(const CInsertTest& c)
		: m_v(c.m_v)
	{
		std::cout << "복사 생성자" << std::endl;
	}

	CInsertTest(CInsertTest&& c)
		: m_v(std::move(c.m_v))
	{
		std::cout << "이동 생성자" << std::endl;
	}

	CInsertTest& operator=(const CInsertTest& c)
	{
		std::cout << "복사 대입연산자" << std::endl;
		m_v = c.m_v;
		return *this;
	}

	CInsertTest& operator=(CInsertTest&& c)
	{
		std::cout << "이동 대입연산자" << std::endl;
		m_v = std::move(c.m_v);
		return *this;
	}

private:
	std::vector<int> m_v;
};

void 생성삽입()
{
	NUtil::PrintDivider("생성삽입");

	CInsertTest c1(1);
	//CInsertTest c2(2);

	//c1 = c2;
	//c1 = std::move(c2);

	std::vector<CInsertTest> v;
	v.reserve(100);
	std::cout << "1" << std::endl;
	v.push_back(1);						// 임시 객체가 생성된다. 최적화 과정에서 임시 객체 없이 동작할 거라 예상했으나, 아니다. 그랬으면 emplace가 만들어지지 않았겠지.
	std::cout << "2" << std::endl;
	v.push_back(c1);					// 이동 대입이 된다.
	std::cout << "3" << std::endl;
	v.emplace_back(1);					// 바로 생성한다. 임시 객체가 생성되지 않는다. c++11 이후에는 이쪽을 주로 사용하는 것을 권장한다.
	std::cout << "end" << std::endl;
}

void 삽입자()
{
	NUtil::PrintDivider("삽입자");

	std::vector<int> v;
	std::back_insert_iterator<std::vector<int>> iter(v);
	iter = 1;
	*iter = 2;	// iter와 *iter 모두 동일하게 back_emplace_iterator의 참조를 반환한다. 가시적으로 *iter가 더 일반적이지만.
	std::back_inserter(v) = 3;

	// back_emplace_iterator가 존재하지 않는 이유
	// https://stackoverflow.com/questions/18724999/why-no-emplacement-iterators-in-c11-or-c14
	// 간단히 정리하자면, 단일 객체만 필요한 insert와 달리 emplace는 생성자 인자에 해당하는 가변 인자(튜플로 구현)가 필요하기 때문에 성능상의 이점이 없다. 

	NUtil::PrintElements(v);
}

void ClassName::Execute()
{
	NUtil::PrintDivider("Iterator::Execute()");

	//임시_이터레이터_연산();
	//생성삽입();
	삽입자();
}

