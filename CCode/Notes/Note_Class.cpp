#include "stdafx.h"

class Base1{
public:
	int data;	
	virtual void fun_Base1_1() = 0;
	virtual void fun_Base1_2(){ cout << "Base1::fun_Base1_2:"<<this->data << endl; };
};
class Base2{
public:
	int data;
	virtual void fun_Base2_1(){ cout << "Base2::fun_Base2_1:"<<this->data << endl; };
	virtual void fun_Base2_2(){ cout << "Base2::fun_Base2_2:"<<this->data << endl; };
};
class Derive1 : public Base1 ,public Base2{
public:
	int data;
	virtual void fun_Base1_1(){ cout << "Derive1::fun_Base1_1:"<<this->data << endl; };
	virtual void fun_Base1_2(){ cout << "Derive1::fun_Base1_2:"<<this->data << endl; };
	virtual void fun_Base2_1(){ cout << "Derive1::fun_Base2_1:"<<this->data << endl; };
	virtual void fun_Base2_2(){ cout << "Derive1::fun_Base2_2:"<<this->data << endl; };
};
class Derive2 : public Base1, public Base2{
public:
	int data;
	virtual void fun_Base1_1(){ cout << "Derive2::fun_Base1_1:" <<this->data << endl; };
	virtual void fun_Base1_2(){ cout << "Derive2::fun_Base1_2:" << this->data << endl; };
	virtual void fun_Base2_1(){ cout << "Derive2::fun_Base2_1:" << this->data << endl; };
	virtual void fun_Base2_2(){ cout << "Derive2::fun_Base2_2:" << this->data << endl; };
};
int Demo_Class(){
	Base1 *pBase1 ;
	Base2 *pBase2 = new Base2;
	Derive1 *p1 = new Derive1;
	Derive2 *p2 = new Derive2;
	int a = 123;
	int *pi = &a;
	a = 234;
	cout << *pi << endl;
	cout << sizeof(p1) << "\t" << sizeof(p2) << "\t" << sizeof(pBase1) << "\t" << sizeof(pBase2) << "\t" << endl; 
	cout << offsetof(Base1, data)<<endl;
	p1->data = 1;
	p2->data = 2;
	
	pBase2->data = 4;
	p1->fun_Base1_1();
	p1->fun_Base1_2();
	p1->fun_Base2_1();
	p1->fun_Base2_2();
	cout << endl;

	p2->fun_Base1_1();
	p2->fun_Base1_2();
	p2->fun_Base2_1();
	p2->fun_Base2_2();
	cout << endl;

	pBase1 = (Base1*)p1;
	pBase1->fun_Base1_1();
	pBase1->fun_Base1_2();
	cout << endl;

	pBase2->fun_Base2_1();
	pBase2->fun_Base2_2();
	cout << endl;

	Base1 **ppDemo = &pBase1;
	Base1 *pDemo = pBase1;

	(*ppDemo)->fun_Base1_1();
	pDemo->fun_Base1_1();

	pBase1 = (Base1*)p1;

	(*ppDemo)->fun_Base1_1();
	pDemo->fun_Base1_1();

	pDemo = pBase1;
	(*ppDemo)->fun_Base1_1();
	pDemo->fun_Base1_1();


	pBase1->fun_Base1_1();
	pBase1->fun_Base1_2();
	cout << endl;

	pBase1 = (Base1*)p2;
	pBase1->fun_Base1_1();
	pBase1->fun_Base1_2();
	cout << endl;

	pBase2 = (Base2*)p1;
	pBase2->fun_Base2_1();
	pBase2->fun_Base2_2();
	cout << endl;

	pBase2 = (Base2*)p2;
	pBase2->fun_Base2_1();
	pBase2->fun_Base2_2();
	cout << endl;

	cout << p1->data <<
	p2->data <<
	pBase1->data <<
	pBase2->data  << endl;
	return 1;
}