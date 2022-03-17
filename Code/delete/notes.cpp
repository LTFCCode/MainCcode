#include "stdafx.h"

//fstream write(path, ios::app)  ios::in 读  ios::out覆盖写入 ios::app追加写入

double fuc(double x, double y)                        //定义函数
{
	if (y == 0)
	{
		throw y; //除数为0，抛出异常
		throw 1;
	}
	return x / y;                                    //否则返回两个数的商
}

void demo_try()
{
	double res;
	try                                            //定义异常
	{
		res = fuc(2, 3);
		cout << "The result of x/y is : " << res << endl;
		res = fuc(4, 0);                                //出现异常
	}
	catch (double a)                                    //捕获并处理异常
	{
		cerr << "error of dividing zero.\n";
		printf("错误值为:%f\n",a);
		//exit(1);                                    //异常退出程序
	}
	catch (int b ){
		cerr << "error:" << b << endl;
	}
	
}
int demo_PointArray(){
	//数组指针与指针数组
	int a = 10;
	int z = 5;
	int *b = &a;
	int *c = &z;
	int *demo[10];
	cout << a << endl;
	demo[1] = b;
	cout << demo[1] << endl;
	demo[2] = c;
	cout << demo[2] << endl;
	return TRUE;
}
int demo_define(){

		printf("文件路径:%s\n", __FILE__);
		printf("这句代码所在行数:%d\n", __LINE__);
		#line 200  //指定下一行的__LINE__为200
		printf("这句代码所在行数:%d\n", __LINE__);
		printf("这句代码所在行数:%d\n", __LINE__);

		printf("日期:%s\n", __DATE__);
		printf("时间:%s\n", __TIME__);
		printf("函数名:%s\n", __FUNCTION__);
		return 1;
}
