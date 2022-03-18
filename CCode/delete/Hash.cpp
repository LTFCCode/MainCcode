#include "stdafx.h"

#include <ctime>

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <malloc.h>
using namespace std;

#define CALCULATETIME 99999 //计算次数
#define ARRAYSIZE 99999 //数据大小
#define INEXISTENCE -1 //find未找到返回值




template <typename K, typename V>
class HashNode
{
public:
	HashNode(const K& key = K(), const V& value = V())
	{
		key_ = key;
		value_ = value;
	}

	K key_;
	V value_;
	bool initialized_ = false;
};

template <typename K, typename V>
class HashTable
{
public:
	HashTable(int size)
	{
		node_num_ = 0;
		nodes_.resize(size*2);
	}

	int hashFunction(const K& key)
	{
		return hash(key);
		//return hash_index_ % hash(key);
	}

	V find(const K& key)
	{
		int index;
		try{
			index = hashFunction(key);
			if (index >= ARRAYSIZE){
				throw index;
			}
		}
		catch (int error){
			cout << "index超限:" << error << endl;
		}
		while (nodes_[index].initialized_)
		{
			if (nodes_[index].key_ == key)
			{
				return nodes_[index].value_;
			}
			index++;
			if (index == node_num_)
			{
				index = 0;
			}
		}
		return INEXISTENCE;
	}


	void insert(const K& key, const V& value)
	{	
		int index = hashFunction(key);
		while (nodes_[index].initialized_)
		{
			index++;
			if (index == node_num_)
			{
				index = 0;
			}
		}

		nodes_[index].key_ = key;
		nodes_[index].value_ = value;
		nodes_[index].initialized_ = true;
	}

	int hash(const K& key)
	{
		return key*2-1;
	}

private:
	std::vector<HashNode<K, V> > nodes_;
	int node_num_;
	int hash_index_;
};


void Demo_Hash(){

	int Demo_Array[ARRAYSIZE];
	int RandArray[CALCULATETIME];
	SYSTEMTIME ArrayStart, ArrayEnd, HashStart, HashEnd;
	ULONGLONG	ft_start_point, ft_end_point;

	srand(time(0));

	for (int i = 0; i < CALCULATETIME; i++){

		RandArray[i] = rand() % (ARRAYSIZE-10)+1;//产生[0，ARRAYSIZE-10]随机数
	}
	cout << "RandArray初始化成功" << endl;

	for (int i = 0; i < ARRAYSIZE; i++){

		Demo_Array[i] = i;
	}
	cout << "Array初始化成功" << endl;

	HashTable<int, int> table(ARRAYSIZE);
	for (int i = 0; i < ARRAYSIZE; i++){

		table.insert(i,i);
	}
	cout << "Hash初始化成功" << endl;

	cout << "Array查找中..." << endl;
	GetLocalTime(&ArrayStart);
	for (int t = 0; t < CALCULATETIME; t++)
	{
		for (int i = 0; i < ARRAYSIZE; i++)
		{
			if (Demo_Array[i] == RandArray[t])
			{
				break;
			}
		}
	}
	GetLocalTime(&ArrayEnd);

	SystemTimeToFileTime(&ArrayStart, (LPFILETIME)&ft_start_point);
	SystemTimeToFileTime(&ArrayEnd, (LPFILETIME)&ft_end_point);	
	printf("Array时间差:%f\n", elapsedTime(ft_start_point, ft_end_point));

	cout << "Hash查找中..." << endl;

	GetLocalTime(&HashStart);

	for (int t = 0; t < CALCULATETIME; t++)
	{
		table.find(RandArray[t]);
		
	}
	GetLocalTime(&HashEnd);

	SystemTimeToFileTime(&HashStart, (LPFILETIME)&ft_start_point);
	SystemTimeToFileTime(&HashEnd, (LPFILETIME)&ft_end_point);

	printf("Hash时间差:%f\n", elapsedTime(ft_start_point, ft_end_point));

}


