#include "stdafx.h"
class Cvector{
public:
	string name;
	Cvector(string name){
		this->name = name;
		cout << "构造函数:" << this->name<<endl;
	}

	~Cvector(){
		cout << "析构函数:" << this->name << endl;
	}

	Cvector(const Cvector &Copy){
		this->name = Copy.name;
		cout << "拷贝构造函数:" << this->name << endl;
	}
};
void demo_vector(){
	vector<Cvector>test;

	Cvector test1("push_back");
	Cvector test2("emplace_back");

	test.push_back(test1);



	test.emplace_back(test2);
}