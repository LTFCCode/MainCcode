// delete.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

using namespace std;
class demo_ptr
{
public:
	int point;
	demo_ptr()
	{
		cout << "Strat" << endl;
	}
	~demo_ptr()
	{
		cout << "End,point:" <<point<< endl;
	}
};
int demo_safe_delete(){
	std::shared_ptr<demo_ptr>p;
	//reset只有一个指针参数时，使得p指向该指针
	p.reset(new demo_ptr);
	p->point = 123;
	//reset有两个参数时，p指向第一个指针参数并用第二个参数释放之前p指向的指针
	//若之前指向指针数组，则倒序释放运行析构函数
	//先运行参数1的构造函数,后结束之前指针的生命周期并运行之前指针的析构函数
	p.reset(new demo_ptr[3], std::default_delete<demo_ptr>());
	//p.get()返回p指向的指针
	//p.point指向该指针的索引0
	p.get()[0].point = 234;
	p.get()[1].point = 345;
	p.get()[2].point = 456;

	demo_ptr* q = new demo_ptr[3];
	q[0].point = 567;
	q[1].point = 678;
	q[2].point = 789;

	p.reset(q, std::default_delete<demo_ptr[]>());

	p.get()[0].point = 568;
	p.get()[1].point = 679;
	p.get()[2].point = 790;

	p.reset();
	system("pause");
	return 0;
}
void demo_sample_delete(){
	//通过new创建的指针，指向的内容在堆中,但指针本身在栈中
	//普通指针为栈内存
	cout << "new指针创建" << endl;
	demo_ptr* p = new demo_ptr;
	p->point = 111;
	delete p;
	demo_ptr *q = new demo_ptr[3];
	q[0].point = 222;
	q[1].point = 333;
	q[2].point = 444;
	delete[]q;
	system("pause");
}

void _stdcall demo_heap_stack(int param1,int param2,int param3,int param4,int param5){
		int var1 = param1;
		int var2 = param2;
		int var3 = param3;
		int var4 = param4;
		int var5 = param5;

		int *demo1 = new int(param1);
		int *demo2 = new int(param2);
		int *demo3 = new int(param3);
		int *demo4 = new int(param4);
		int *demo5 = new int(param5);

		static int sta1 = 0;
		static int sta2 = 1;
		static int sta3 = 2;
		static int sta4 = 3;
		static int sta5 = 4;

		printf("param1:0x%08x\n", &param1);//2
		printf("param2:0x%08x\n", &param2);//1
		printf("param3:0x%08x\n", &param3);//4
		printf("param4:0x%08x\n", &param4);//6
		printf("param5:0x%08x\n\n", &param5);//9

		printf("var1:0x%08x\n", &var1);//8
		printf("var2:0x%08x\n", &var2);//7
		printf("var3:0x%08x\n", &var3);//5
		printf("var4:0x%08x\n", &var4);//3
		printf("var5:0x%08x\n\n", &var5);//10

		printf("demo1:0x%08x\n", demo1);
		printf("demo2:0x%08x\n", demo2);
		printf("demo3:0x%08x\n", demo3);
		printf("demo4:0x%08x\n", demo4);
		printf("demo5:0x%08x\n\n", demo5);

		printf("sta1:0x%08x\n", &sta1);
		printf("sta2:0x%08x\n", &sta2);
		printf("sta3:0x%08x\n", &sta3);
		printf("sta4:0x%08x\n", &sta4);
		printf("sta5:0x%08x\n", &sta5);

		system("pause");
}
void demo(){
	string data = "Aasd";
	char base = 'Aasd';
	TCHAR	*tchar1 = NULL;
	tchar1 = new TCHAR[64];
	TCHAR a = base;
	tchar1[0] = base;
	tchar1[1] = base;
	tchar1[2] = base;

	cout << tchar1[0] << endl;
	delete[] tchar1;
	system("pause");
}

class base
{
public:
	base()
	{
		cout<< "调用默认构造函数" << endl;
	}
	~base()
	{
		cout<< "调用析构函数" << endl;
	}
};

void sample(){
	base* p = new base;
	delete[] p;
}
void delete_work(){
	demo_safe_delete();
	//demo_sample_delete();
	//demo_heap_stack(1, 2, 3, 4, 5);
	//demo();
	//sample();
}




