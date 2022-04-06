#include "stdafx.h"
#define ZoneNum 2
#define BankNum1 6
#define BankNum2 2
#define SprNum 8
#define SprDis1 0.52
#define SprDis2 0.78
#define BankDis 0.78
#define FmxToFirSpr 15.10

template <class T>
class FIFOQueue 
{
public:
	FIFOQueue(LPVOID TEST){ size = 0; };
	void insert(T data)
	{
		if (last.size() == 0)
		{
			last.push(data);
		}
		else
		{
			LastToFirst();
			last.push(data);
			FirstToLast();
		}
		size++;
	}
	void clear(){ first.clear();  last.clear(); };
	int getsize(){ return size; };
	T gettop()
	{
		LastToFirst();
		T result = first.top();
		FirstToLast();
		return result;
	}
	T pop()
	{
		LastToFirst();
		T result = first.pop();
		FirstToLast();
		size--;
		return result;
	}
	T getbottom()
	{
		return last.top();
	}
	void movebottom()
	{
		last.pop();
		size--;
	}
private:
	int size;
	stack<T>first;
	stack<T>last;
	void LastToFirst()
	{
		while (last.size() != 0)
		{
			first.push(last.top());
			last.pop();
		}
	}
	void FirstToLast()
	{
		while (first.size() != 0)
		{
			last.push(first.top());
			first.pop();
		}
	}
};


void CalCtcDis()
{
	double dis[ZoneNum][SprNum] = { { 0.52, 0.52, 0.52, 0.78, 0.52, 0.52, 0.52 }, 
								   { 0.52, 0.52, 0.52, 0.78, 0.52, 0.52, 0.52 } };

	double result = FmxToFirSpr;
	INT * TEST;
	FIFOQueue<double> queue(TEST);
	for (int i = 0; i < BankNum1;i++)
	{
		for (int j = 0; j < SprNum; j++)
		{
			queue.insert(result);
			result += dis[0][j];
		}
		result += BankDis;
	}
	result += BankDis;
	for (int i = 0; i < BankNum2; i++)
	{
		for (int j = 0; j < SprNum; j++)
		{
			queue.insert(result);
			result += dis[1][j];
		}
		result += BankDis;
	}
	string folder = "E:\\CCodeSSH\\Log\\CTCDis.txt";
	fstream out(folder, ios::out);
	char data[24] = "";
	for (int i = 0; i < BankNum1; i++)
	{
		out << "I ";
		for (int j = 0; j < SprNum; j++)
		{
			sprintf_s(data, "%0.2f", queue.getbottom());
			queue.movebottom();
			out << data;
			if (j !=SprNum-1)
			{
				out << ", ";
			}
		}
		out << endl;
	}
	for (int i = 0; i < BankNum2; i++)
	{
		out << "I ";
		for (int j = 0; j < SprNum; j++)
		{
			sprintf_s(data, "%0.2f", queue.getbottom());
			queue.movebottom();
			out << data;
			if (j != SprNum - 1)
			{
				out << ", ";
			}
		}
		out << endl;
	}
	out.close();
}