#include "stdafx.h"
using namespace std;
void pass_by_value(int a ,int b){

	cout << "传值函数接收的第一个参数a：" << a << endl;
	cout << "传值函数接收的第二个参数b：" << b << endl;
	a++;
	b++;
}
void pass_by_reference(int &a,int &b){

	cout << "传址函数接收的第一个参数a：" << a << endl;
	cout << "传址函数接收的第二个参数b：" << b << endl;
	a++;
	b++;
}

int base_work(){
	int num1 = 5;
	int num2 = 2;

	pass_by_value(num1,num2);
	printf("传值函数结束后的num1:%d\n", num1);
	printf("传值函数结束后的num2:%d\n\n", num2);

	pass_by_reference(num1,num2);
	printf("传址函数结束后的num1:%d\n", num1);
	printf("传址函数结束后的num2:%d\n\n", num2);

	system("pause");
	return 0;
}


template<typename Typedemo>
void function_template(Typedemo demo){
	cout << "传入的参数类型为：" << typeid(demo).name() << endl;
}
template<typename Typedemo1,typename Typedemo2>
void function_template(Typedemo1 demo1, Typedemo2 demo2){
	cout << "传入的第一个参数类型为：" << typeid(demo1).name() << endl;
	cout << "传入的第二个参数类型为：" << typeid(demo2).name() << endl;
}
int function_template_work(){
	int a = 0;
	char b = 'abc';
	bool c = TRUE;
	string d = "LTT加油！";
	//函数模板
	function_template(a);
	function_template(b);
	function_template(c);

	function_template(a,b);
	function_template(c,d);
	system("pause");
	return 0;
}