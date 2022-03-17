#include "stdafx.h"

#define SIZE 10

class cHanoiTower
{
public:
	stack<int>Tower_1;
	stack<int>Tower_2;
	stack<int>Tower_3;
	cHanoiTower();
	void move(int num, stack<int> *T1, stack<int> *T2, stack<int> *T3);
};

cHanoiTower::cHanoiTower()
{
	for (int i = SIZE; i >0; i--)
	{
		Tower_1.push(i);
	}
}
void cHanoiTower::move(int num, stack<int> *T1, stack<int> *T2, stack<int> *T3)
{
	if (num>=2)
	{
		this->move(num - 1, T1, T3, T2);
		this->move(1, T1, T2, T3);
		this->move(num - 1, T2, T1, T3);
	}
	else
	{
		T3->push(T1->top());
		T1->pop();
	}
}
void HanoiTower()
{
	cHanoiTower hanoi;
	hanoi.move(SIZE, &hanoi.Tower_1, &hanoi.Tower_2, &hanoi.Tower_3);
}