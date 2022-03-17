#include "stdafx.h"

#define MAX_SIZE 20

#define invalid(x) ((x)>=0 && (x)<MAX_SIZE)
class cNineQueen
{
public:
	
	cNineQueen();
	bool insert(int x_in, int y_in);
	void withdraw();
	void showresult(map<int, int> data);
	void showstatus();
	void showanwser();
	bool auto_insert(int hang);
	void empty();
private:
	vector<map<int,int>>Queens;//各解的集合
	map<int, int>now;//当前各皇后的坐标
	int result_num;//解的数量
	int QueenNum;//皇后的数量
	int status[MAX_SIZE][MAX_SIZE];//当前棋盘的状态
};

cNineQueen::cNineQueen()
{
	this->empty();
}
void cNineQueen::showresult(map<int,int> data)
{
	printf("+");
	for (int i = 0; i < MAX_SIZE; i++)
	{
		printf("---+");
	}
	printf("\n");
	for (int x = 0; x < MAX_SIZE; x++)
	{
		printf("+");
		for (int y = 0; y < MAX_SIZE; y++)
		{
			if (data[x] == y)
			{
				printf(" X +");
			}
			else
			{
				printf("   +");
			}
		}
		printf("\n");
		printf("+");
		for (int i = 0; i < MAX_SIZE; i++)
		{
			printf("---+");
		}
		printf("\n");
	}
}
void cNineQueen::withdraw()
{
	for (int x = 0; invalid(x); x++)
	{
		for (int y = 0; invalid(y); y++)
		{
			if (this->status[x][y] == this->QueenNum)
			{
				this->status[x][y] = 0;
			}
		}
	}
	this->QueenNum--;
}
bool cNineQueen::auto_insert(int hang)
{
	if (hang ==MAX_SIZE)
	{
		return false;
	}
	for (int i = 0; invalid(i); i++)
	{
		if (this->insert(hang, i))
		{
			if (hang == MAX_SIZE - 1)
			{
				this->Queens.emplace_back(now);
				printf("解法%d:\n", ++this->result_num);
				this->showresult(now);
			}
			else
			{
				this->auto_insert(hang + 1);
			}
			this->withdraw();
		}
	}
	return true;
}
void cNineQueen::showanwser()
{
	this->empty();
	this->auto_insert(0);
}
void cNineQueen::empty()
{
	for (int x = 0; x < MAX_SIZE; x++)
	{
		for (int y = 0; y < MAX_SIZE; y++)
		{
			status[x][y] = 0;
		}
	}
	QueenNum = 0;
	this->result_num = 0;
}
bool cNineQueen::insert(int x_in, int y_in){

	if (status[x_in][y_in] != 0)
	{
		//printf("插入(%d,%d)冲突\n",x_in,y_in);
		return false;
	}	
	int left_slash,right_slash;
	QueenNum++;
	for (int x = 0; x < MAX_SIZE; x++)
	{
		for (int y = 0; y < MAX_SIZE; y++)
		{
			left_slash = y - (x_in - x);
			right_slash = y + (x_in - x);
			if (x == x_in || y == y_in)
			{
				if (status[x][y] == 0)
				{
					status[x][y] = QueenNum;
				}
				if (invalid(left_slash))
				{
					if (status[x][left_slash] == 0)
					{
						status[x][left_slash] = QueenNum;
					}
				}
				if (invalid(right_slash))
				{
					if (status[x][right_slash] == 0)
					{
						status[x][right_slash] = QueenNum;
					}
				}
				if (status[x_in][y] == 0)
				{
					status[x_in][y] = QueenNum;
				}
				if (status[x][y_in] == 0)
				{
					status[x][y_in] = QueenNum;
				}
			}
		}
	}
	now[x_in] = y_in;
	return true;
}
void NineQueenQues()
{
	cNineQueen NineQueen;
	NineQueen.showanwser();
}