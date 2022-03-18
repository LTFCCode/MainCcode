#include "stdafx.h"



void f1(int m, int n) { //转整数部分
	if (m) {
		f1(m / n, n);
		if (n<10) cout << m%n;
		else m%n >= 10 ? cout << char(m%n - 10 + 'A') : cout << m%n;
	}
}


void f2(double m, int n) { //转小数部分
	while (m) {
		if (n<10) cout << int(m*n);
		else m*n >= 10 ? cout << char(int(m*n) - 10 + 'A') : cout << int(m*n);
		m = m*n - int(m*n);
	}
}


void f(double m, int n) {
	f1(m, n);
	if (int(m) == m) return;
	cout << '.';
	m -= int(m);
	f2(m, n);
}


void f10(char c[], double m) {
	cout << ' ' << c << " 转换成" << 2 << "进制 = "; f(m, 2); cout << endl;
	cout << ' ' << c << " 转换成" << 8 << "进制 = "; f(m, 8); cout << endl;
	cout << ' ' << c << " 转换成" << 16 << "进制 = "; f(m, 16); cout << endl;
}


double fn_10(char c[], int n) {
	char z[100];
	int i = 0, j;
	double b = 0;
	cout << ' ' << c << " 转换成10进制 = ";
	while (*c != '.' && *c != '\0') z[i++] = *c++;
	i--;
	if (*c == '\0') c--;
	for (j = 0; j <= i; j++)
		if (z[j] < 65) b += (z[j] - 48) * pow(n, i - j);
		else          b += (z[j] - 55) * pow(n, i - j);
		for (c++, j = -1; *c != '\0'; c++, j--)
			if (*c < 65) b += (*c - 48) * pow(n, j);
			else        b += (*c - 55) * pow(n, j);
			cout << b << endl;
			return b;
}


void Demo_Test3() {
	cout << "   进制转换\n";
	char c[100];
	int n;
	cout << "\n 输入一数与它的进制: ";
	cin >> c >> n;
	cout << endl;
	f10(c, fn_10(c, n));
}
void Demo_Test2(){
	float a = 1.7408123456789f;
	printf("%.10f\n",a);

	unsigned char *hex = (unsigned char *)&a;

	for (int i = 0; i < 4; i++)
		printf("0x%x ", hex[i]);
	printf("\n");

	//unsigned char hex1[] = { 0x00, 0x00, 0x88, 0x46 };
	float f = *(float *)hex;

	printf("%g\n", f);
}
void Demo_Test1(){

	typedef struct{
		string a;
	}DemoStruct;
	char SlabNo[24] = "1234567890qwerty";
	char aim[16];
	int i = strlen(SlabNo) - 7;

	sprintf(aim, "aim:\t%s", SlabNo + i);
	printf("%s\n", aim);

	string demo = "1234567890";
	string test = demo.substr(2,7);
	printf("test:\t%s\n",test.c_str());
	int a = 0;
	demo.pop_back();
	demo.pop_back();
	cout << "删除后demo:"<<demo << endl;
	string b = "a";
	vector<DemoStruct> Demotest;
	for (auto iter = demo.begin(); iter < demo.end(); iter++){
		b.push_back(*iter);
	}
	for (auto iter = Demotest.begin(); iter < Demotest.end(); iter++){
		cout << iter->a.c_str()<< endl;

	}

}

void Demo_Test234(){
# include <iostream>
# include <vector>
using namespace std;
class Animal{public:    virtual void eat() const { cout << "I eat like a generic Animal." << endl; }    virtual ~Animal() {}}; 
class Wolf : public Animal{public:    void eat() const { cout << "I eat like a wolf!" << endl; }}; 
class Fish : public Animal{public:    void eat() const { cout << "I eat like a fish!" << endl; }}; 
class GoldFish : public Fish{public:    void eat() const { cout << "I eat like a goldfish!" << endl; }};  
class OtherAnimal : public Animal{}; 
std::vector<Animal*> animals;    
animals.push_back( new Animal() );    
animals.push_back( new Wolf() );    
animals.push_back( new Fish() );    
animals.push_back( new GoldFish() );    
animals.push_back( new OtherAnimal() );     
for( std::vector<Animal*>::const_iterator it = animals.begin();it != animals.end(); ++it)
{
	(*it)->eat();
	delete *it;
}    

}

struct test{
	test* next;
	test* prev;
	int data;
	char *name;
};
void Demo_Test123(){

	CString demo = "qwe";
	cout << (LPCTSTR)demo << endl;
	printf("%s", (LPCTSTR)demo.GetBuffer());

	
}

void Demo_Testasd(){
	int demo[10] = {1,2,3,4,5,6,7,8,9,10};
	int* p;
	p = demo;
	printf("值:%d\n", *p);
	printf("值:%d\n", *demo);
	printf("地址:%d\n", p);
	printf("地址:%d\n", demo);
	//printf("%d\n", *(p++));
	//printf("%d\n", *p);

	////printf("p地址:%d\n", p);
	//printf("%d\n", *(++p));
	////printf("p地址:%d\n", p);
	//printf("%d\n", *(p++));
	////printf("p地址:%d\n", p);
	//printf("%d\n", *p);
	//demo[3] = 100;
	//printf("%d\n", p[2]);
}
class Father{
public:
	int data;
	void function(){
		cout << "Father Work" << endl;
	}
};
class Son :public Father{
public:
	int data;
	void function(){
		cout << "Son Work" << endl;
	}
};
void Demo_Class(Son* pcSon,Father* pcFather){
	Son* new_pcFather = (Son*)pcFather;
	cout << "Son-data:\t" << pcSon->data << endl;
	cout << "Father-data:\t" << pcFather->data << endl;
	cout << "Father-right:\t" << new_pcFather->data << endl;

	pcSon->function();
	pcFather->function();
	new_pcFather->function();

}
//形参为父类指针，实参可为子类指针
//形参为子类指针，实参可将父类指针强制转换为子类指针
void Demo_Testujm(){
	Son* pcSon = new Son;
	Father* pcfather = new Father;
	pcSon->data = 234;
	pcfather->data = 456;
	Demo_Class(pcSon, pcfather);

	Demo_Class((Son*)pcfather, pcSon);
}

void Demo_Testedc(){
	char data[256] = "";
	float demo = 3.00;
	sprintf(data, "%d", (int)demo);
	sprintf(data, "update DCRCOF set F_DC2APTBLLEADRATIO = %d where I_GRTIDX = %d and I_GRDFAMILY = %d and i_wrtidx = %d",
		8, 1, 10, 5);//(int)(demo * 100)
	printf(data);
}

void Demo_Testthm(){
	class TestF{
	};
	class Tests1 :public TestF{
	public:
		int a;
		int c;
		int b;
		void function(){
			cout <<this->a<<  "\t" << a << endl;
			cout <<this->b<<  "\t" << b << endl;
			cout <<this->c<<  "\t" << c << endl;
		}
	};
	class Tests2 :public TestF{
	public:
		int a;
		int b;
		int c;
		void function(){
			cout << this->a << "\t" << a << endl;
			cout << this->b << "\t" << b << endl;
			cout << this->c << "\t" << c << endl;
		}
	};
	Tests1 *p1 = new Tests1;
	Tests2 *p2 = new Tests2;
	vector<int> test;
	test.front() = 1;
	test.back() = 1;
	//test.emplace_back
	p1->a = 11;
	p1->b = 12;
	p1->c = 13;
	p2->a = 21;
	p2->b = 22;
	p2->c = 23;
	p1->function();
	p2->function();
	p1 = (Tests1*)p2;
	p1->function();
	p2->function();

}
void Demo_Testegn(){

	int a = 432;
	int b = 234;
	a = a^b;
	b = a^b;
	a = a^b;
	cout << a << endl << b << endl;
}
void Demo_Test(){
	//822b4a352f53d0a8a040edb46b36cfe5
	int demo[4] = { 0x822b4a35, 0x2f53d0a8, 0xa040edb4, 0x6b36cfe5 };
	char test = (char)demo[0];
	printf("%s\n",test);
}
void test123(string test){
	string strsql;
	strsql.clear();
	strsql = strsql + "select * from MDB_UPD where table_name = '" + test + "'";
	printf("%s\n", strsql.c_str());
	printf("%s----\n",test.c_str());
	printf("%d,%d",sizeof(test),strlen(test.c_str()));
}
void Demo_Test_char(){
	char slab[5] = "ress";
	printf("%d\n", sizeof(slab));

	for (int i = 0; i < sizeof(slab) - 1; i++){
		printf("%s\n", &slab[i]);
	}
	char test[24];
	memcpy(test, slab, sizeof(slab));
	test123(test);
}

typedef struct{
	int *p1;//指向int的指针
	const int *p2;//指向int的常指针
	int* const p3;//指向常量int的指针
	const int * const p4;//指向常量int的常指针
	int a;
}TestA;

typedef struct{
	int *pb;
	int b;
	TestA a;
	TestA *pa;
}TestB;

//void Demo_Test_point(){
//	TestA testa;
//	TestB testb;
//	const TestA *ptesta = &testa ;
//	const TestB *ptestb = &testb;
//	int *p;
//	const int a = 1;
//
//	ptesta->a = 1;
//	ptesta->pa = p;
//	*ptesta->pa = 1;
//
//	ptestb->b = 1;
//	ptestb->pb = p;
//	ptestb->a = testa;
//	ptestb->a.a = 1;
//	ptestb->a.pa = 1;
//	*ptestb->a.pa = 1;
//	ptestb->pa = &testa;
//	*ptestb->pa = testa;
//	ptestb->pa->a = 1;
//	ptestb->pa->pa = p;
//	
//
//}