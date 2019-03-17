#include "ExecuteInterface.h"
#include <iostream>
#include <array>
#include <string>

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


void ClassName::Execute()
{
	NUtil::PrintDivider("Container05::Execute()");
	배열();
}


