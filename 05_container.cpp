#include "ExecuteInterface.h"
#include <iostream>
#include <array>
#include <string>
#include <vector>
#include <deque>

DECLARE_INTERFACE(Container, 05);

class CArrTest
{
public:
	CArrTest() {}
	CArrTest(int) { m_arr[0] = "a"; m_arr[1] = "b"; }

private:
	std::string m_arr[2];
};

void 배열()
{
	NUtil::PrintDivider("배열");
	std::array<std::string, 2> a1 = { "a", "b" };	// 초기화자 목록을 사용하여 생성하는 부분 확인 필요.
	decltype(a1) a2;
	// 이동 문맥을 암묵적으로 제공한다.
	a2 = std::move(a1);
	NUtil::PrintElements(a2);

	// 기본 배열은 이동문맥이 제공되지 않지만, 클래스의 멤버로 있을 경우 암묵적으로 이동이 가능하다? <- 확인 필요
	CArrTest a(0);
	CArrTest b;
	b = std::move(a);
}

void 백터()
{
	NUtil::PrintDivider("백터");

	std::vector<int> v;
	for (int i = 0; i < 10; ++i)
	{
		v.push_back(i);
	}
	std::cout << "cap: " << v.capacity() << std::endl;	// cap: 13
	// capacity를 size에 맞추도록 요청. 강제력이 없다. 하지만 소스를 봤을 때 항상 동작할 것으로 예상됨.
	v.shrink_to_fit();
	// c++11 이전에서 사용했던 테크닉. 임시 값에서도 상수가 아닌 멤버 함수를 호출할 수 있다.
	//std::vector<int>(v).swap(v);
	std::cout << "cap: " << v.capacity() << std::endl;	// cap: 10

	// assign은 주어진 요소로 기존 요소를 대체하고 나머지는 모두 삭제한다.
	//v.assign(3, 777);
	NUtil::PrintElements(v);

	// push_back(Class(arg...));에서 불필요한 임시객체의 생성/삭제가 발생하는데, emplace_back(arg...));에서는 벡터의 요소를 바로 생성하여 임시 객체를 생략한다.
	// 하지만 이런 임시객체는 최적화 과정에서 제거될 수 있으므로 emplace_back이 push_back 대비 무조건 효율적인 것은 아니다.
	//v.emplace_back(0);
}

void 데크()
{
	NUtil::PrintDivider("데크");


	std::vector<int> v;
	std::deque<int> d;

	// 내부 구조상 데크가 벡터 보다 더 큰 max_size()를 갖을 수도 있지만, 현재 시스템에서는 동일하다.
	std::cout << "max_size(): vector: " << v.max_size() << ", deque: " << d.max_size() << std::endl;
}

void ClassName::Execute()
{
	NUtil::PrintDivider("Container05::Execute()");
	배열();
	백터();
	데크();
}


