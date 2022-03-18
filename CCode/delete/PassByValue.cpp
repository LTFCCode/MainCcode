#include "stdafx.h"
using namespace std;
void pass_by_value(int a ,int b){

	cout << "��ֵ�������յĵ�һ������a��" << a << endl;
	cout << "��ֵ�������յĵڶ�������b��" << b << endl;
	a++;
	b++;
}
void pass_by_reference(int &a,int &b){

	cout << "��ַ�������յĵ�һ������a��" << a << endl;
	cout << "��ַ�������յĵڶ�������b��" << b << endl;
	a++;
	b++;
}

int base_work(){
	int num1 = 5;
	int num2 = 2;

	pass_by_value(num1,num2);
	printf("��ֵ�����������num1:%d\n", num1);
	printf("��ֵ�����������num2:%d\n\n", num2);

	pass_by_reference(num1,num2);
	printf("��ַ�����������num1:%d\n", num1);
	printf("��ַ�����������num2:%d\n\n", num2);

	system("pause");
	return 0;
}


template<typename Typedemo>
void function_template(Typedemo demo){
	cout << "����Ĳ�������Ϊ��" << typeid(demo).name() << endl;
}
template<typename Typedemo1,typename Typedemo2>
void function_template(Typedemo1 demo1, Typedemo2 demo2){
	cout << "����ĵ�һ����������Ϊ��" << typeid(demo1).name() << endl;
	cout << "����ĵڶ�����������Ϊ��" << typeid(demo2).name() << endl;
}
int function_template_work(){
	int a = 0;
	char b = 'abc';
	bool c = TRUE;
	string d = "LTT���ͣ�";
	//����ģ��
	function_template(a);
	function_template(b);
	function_template(c);

	function_template(a,b);
	function_template(c,d);
	system("pause");
	return 0;
}