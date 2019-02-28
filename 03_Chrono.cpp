#include "ExecuteInterface.h"
#include <iostream>
#include <chrono>

DECLARE_INTERFACE(Chrono, 03);

template <typename V, typename R>
std::ostream& operator<<(std::ostream& s, const std::chrono::duration<V,R>& d)
{
	s << "[" << d.count() << " of " << R::num << "/" << R::den << "]";
	return s;
}

void PrintDivider(const std::string& title)
{
	std::cout << "\n###################################################################################\n";
	std::cout << title;
	std::cout << "\n###################################################################################\n\n";
}

void 기본동작확인()
{
	PrintDivider("chrono 기본 동작 확인");

	std::chrono::seconds sec;
	std::chrono::hours hours(1);

	sec = hours;

	std::cout << "hours: " << hours.count() << ", sec: " << sec.count() << std::endl;
	// error: 암묵적인 데이터형 변환이 가능하다면 한 시간 기간을 다른 단위의 시간 기간으로 바꿀 수 있다. 작은 단위에서 큰 단위로의 변환은 정보를 잃을 수 있으므로 변환할 수 없다.
	// 이 경우 duration_cast를 사용하여 명시적 변환이 가능하다.
	// hours = sec;

	sec = sec * 2 + sec / 2; // 2시간 30분
	hours = std::chrono::duration_cast<std::chrono::hours>(sec);	// 하지만 값 손실이 발생하여 2시간.

	std::cout << sec << std::endl;
	std::cout << hours << std::endl;
}


template <typename C>
void printClockData()
{
	using namespace std;
	cout << "- precision: ";
	using P = typename C::period;
	// 만약 시간이 1 밀리초보다 작거나 같으면
	if (ratio_less_equal<P, milli>::value)
	{
		using TT = typename ratio_multiply<P, kilo>::type;
		// 밀리초로 바꿔 출력한다.
		cout << fixed << double(TT::num) / TT::den << " milliseconds" << endl;
	}
	else
	{
		cout << fixed << double(P::num) / P::den << " seconds" << endl;
	}

	cout << "- is_steady: " << boolalpha << C::is_steady << endl;
}

void 클럭테스트()
{
	PrintDivider("클럭테스트");

	// 다양한 클럭에 대한 속성 출력
	std::cout << "system_clock: " << std::endl;
	printClockData<std::chrono::system_clock>();
	std::cout << std::endl << "high_resolution_clock: " << std::endl;
	printClockData<std::chrono::high_resolution_clock>();
	std::cout << std::endl << "steady_clock: " << std::endl;
	printClockData<std::chrono::steady_clock>();

	// 시간 측정 테스트
	auto start = std::chrono::system_clock::now();
	system("pause");
	auto diff = std::chrono::system_clock::now() - start;
	auto millisec = std::chrono::duration_cast<std::chrono::milliseconds>(diff);
	auto sec = std::chrono::duration_cast<std::chrono::seconds>(diff);
	std::cout << "millisec: " << millisec.count() << ", sec: " << sec.count() << std::endl;
}

void Chrono03::Execute()
{
	std::cout << "Chrono03::Execute()" << std::endl;

	//std::chrono::duration<int> secondes(20);
	//std::common_type<long, int>::type t;


	//using seconds = duration<long long>;
	//using minutes = duration<int, ratio<60>>;
	//using hours = duration<int, ratio<3600>>;

	기본동작확인();
	클럭테스트();
}
