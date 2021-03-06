// case1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <memory>
#include <chrono>


using namespace std;
using namespace chrono;
using namespace chrono_literals;

volatile int g_moo = 10;
const int TotalWorkCount = 100000000;

// #TODO const shared_ptr& 대신에 쌩 ptr로 바꿔서 실행해보자.

void Func2(const shared_ptr<int64_t>& a, const shared_ptr<int64_t>& b);

class X
{
public:
	shared_ptr<int64_t> m_value1;
};


void Func1(const shared_ptr<int64_t>& a, const shared_ptr<int64_t>& b)
{
	(*a)++;
	(*b)++;

	// 여기를 주목!
	X x;
	x.m_value1 = b;

	Func2(a, b);
}

void Func2(const shared_ptr<int64_t>& a, const shared_ptr<int64_t>& b)
{
	(*a) += g_moo;
	(*b) += g_moo;
}

int main()
{
	auto t0 = high_resolution_clock::now();

	shared_ptr<int64_t> a = make_shared<int64_t>(0);
	shared_ptr<int64_t> b = make_shared<int64_t>(100);

	for (int i = 0; i < TotalWorkCount; i++)
	{
		Func1(a, b);
	}
	auto t1 = high_resolution_clock::now();

	auto elapsedMs = duration_cast<milliseconds>(t1 - t0).count();

	std::cout << "Work took " << elapsedMs << " ms.\n";
	std::cout << "a=" << *a << ", b=" << *b << endl;

}
