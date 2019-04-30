#include "ExecuteInterface.h"
#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

DECLARE_INTERFACE(Iterator, 06);

void �ӽ�_���ͷ�����_����()
{
	NUtil::PrintDivider("�ӽ� ���ͷ����� ����");

	std::vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8 };
	std::random_shuffle(v.begin(), v.end());
	NUtil::PrintElements(v);
	std::sort(++v.begin(), v.end());			// ms�� c++ ���������� array, vector�� �ݺ��ڴ� Ŭ���� Ÿ���̹Ƿ� �ӽ� ������ ���Ͽ� ++ ������ ���� �����ϴ�.
	std::sort(std::next(v.begin()), v.end());	// ������ ���ͺ��ϰ� std::next() ��ƿ��Ƽ �Լ��� �����Ѵ�.
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
		std::cout << "�⺻ ������" << std::endl;
	}

	~CInsertTest()
	{
		std::cout << "�Ҹ���" << std::endl;
	}

	CInsertTest(const CInsertTest& c)
		: m_v(c.m_v)
	{
		std::cout << "���� ������" << std::endl;
	}

	CInsertTest(CInsertTest&& c)
		: m_v(std::move(c.m_v))
	{
		std::cout << "�̵� ������" << std::endl;
	}

	CInsertTest& operator=(const CInsertTest& c)
	{
		std::cout << "���� ���Կ�����" << std::endl;
		m_v = c.m_v;
		return *this;
	}

	CInsertTest& operator=(CInsertTest&& c)
	{
		std::cout << "�̵� ���Կ�����" << std::endl;
		m_v = std::move(c.m_v);
		return *this;
	}

private:
	std::vector<int> m_v;
};

void ��������()
{
	NUtil::PrintDivider("��������");

	CInsertTest c1(1);
	//CInsertTest c2(2);

	//c1 = c2;
	//c1 = std::move(c2);

	std::vector<CInsertTest> v;
	v.reserve(100);
	std::cout << "1" << std::endl;
	v.push_back(1);						// �ӽ� ��ü�� �����ȴ�. ����ȭ �������� �ӽ� ��ü ���� ������ �Ŷ� ����������, �ƴϴ�. �׷����� emplace�� ��������� �ʾҰ���.
	std::cout << "2" << std::endl;
	v.push_back(c1);					// �̵� ������ �ȴ�.
	std::cout << "3" << std::endl;
	v.emplace_back(1);					// �ٷ� �����Ѵ�. �ӽ� ��ü�� �������� �ʴ´�. c++11 ���Ŀ��� ������ �ַ� ����ϴ� ���� �����Ѵ�.
	std::cout << "end" << std::endl;
}

void ������()
{
	NUtil::PrintDivider("������");

	std::vector<int> v;
	std::back_insert_iterator<std::vector<int>> iter(v);
	iter = 1;
	*iter = 2;	// iter�� *iter ��� �����ϰ� back_emplace_iterator�� ������ ��ȯ�Ѵ�. ���������� *iter�� �� �Ϲ���������.
	std::back_inserter(v) = 3;

	// back_emplace_iterator�� �������� �ʴ� ����
	// https://stackoverflow.com/questions/18724999/why-no-emplacement-iterators-in-c11-or-c14
	// ������ �������ڸ�, ���� ��ü�� �ʿ��� insert�� �޸� emplace�� ������ ���ڿ� �ش��ϴ� ���� ����(Ʃ�÷� ����)�� �ʿ��ϱ� ������ ���ɻ��� ������ ����. 

	NUtil::PrintElements(v);
}

void ClassName::Execute()
{
	NUtil::PrintDivider("Iterator::Execute()");

	//�ӽ�_���ͷ�����_����();
	//��������();
	������();
}

