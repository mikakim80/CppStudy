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

void �⺻����Ȯ��()
{
	PrintDivider("chrono �⺻ ���� Ȯ��");

	std::chrono::seconds sec;
	std::chrono::hours hours(1);

	sec = hours;

	std::cout << "hours: " << hours.count() << ", sec: " << sec.count() << std::endl;
	// error: �Ϲ����� �������� ��ȯ�� �����ϴٸ� �� �ð� �Ⱓ�� �ٸ� ������ �ð� �Ⱓ���� �ٲ� �� �ִ�. ���� �������� ū �������� ��ȯ�� ������ ���� �� �����Ƿ� ��ȯ�� �� ����.
	// �� ��� duration_cast�� ����Ͽ� ����� ��ȯ�� �����ϴ�.
	// hours = sec;

	sec = sec * 2 + sec / 2; // 2�ð� 30��
	hours = std::chrono::duration_cast<std::chrono::hours>(sec);	// ������ �� �ս��� �߻��Ͽ� 2�ð�.

	std::cout << sec << std::endl;
	std::cout << hours << std::endl;
}


template <typename C>
void printClockData()
{
	using namespace std;
	cout << "- precision: ";
	using P = typename C::period;
	// ���� �ð��� 1 �и��ʺ��� �۰ų� ������
	if (ratio_less_equal<P, milli>::value)
	{
		using TT = typename ratio_multiply<P, kilo>::type;
		// �и��ʷ� �ٲ� ����Ѵ�.
		cout << fixed << double(TT::num) / TT::den << " milliseconds" << endl;
	}
	else
	{
		cout << fixed << double(P::num) / P::den << " seconds" << endl;
	}

	cout << "- is_steady: " << boolalpha << C::is_steady << endl;
}

void Ŭ���׽�Ʈ()
{
	PrintDivider("Ŭ���׽�Ʈ");

	// �پ��� Ŭ���� ���� �Ӽ� ���
	std::cout << "system_clock: " << std::endl;
	printClockData<std::chrono::system_clock>();
	std::cout << std::endl << "high_resolution_clock: " << std::endl;
	printClockData<std::chrono::high_resolution_clock>();
	std::cout << std::endl << "steady_clock: " << std::endl;
	printClockData<std::chrono::steady_clock>();

	// �ð� ���� �׽�Ʈ
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

	�⺻����Ȯ��();
	Ŭ���׽�Ʈ();
}
