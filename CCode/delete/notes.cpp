#include "stdafx.h"

//fstream write(path, ios::app)  ios::in ��  ios::out����д�� ios::app׷��д��

double fuc(double x, double y)                        //���庯��
{
	if (y == 0)
	{
		throw y; //����Ϊ0���׳��쳣
		throw 1;
	}
	return x / y;                                    //���򷵻�����������
}

void demo_try()
{
	double res;
	try                                            //�����쳣
	{
		res = fuc(2, 3);
		cout << "The result of x/y is : " << res << endl;
		res = fuc(4, 0);                                //�����쳣
	}
	catch (double a)                                    //���񲢴����쳣
	{
		cerr << "error of dividing zero.\n";
		printf("����ֵΪ:%f\n",a);
		//exit(1);                                    //�쳣�˳�����
	}
	catch (int b ){
		cerr << "error:" << b << endl;
	}
	
}
int demo_PointArray(){
	//����ָ����ָ������
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

		printf("�ļ�·��:%s\n", __FILE__);
		printf("��������������:%d\n", __LINE__);
		#line 200  //ָ����һ�е�__LINE__Ϊ200
		printf("��������������:%d\n", __LINE__);
		printf("��������������:%d\n", __LINE__);

		printf("����:%s\n", __DATE__);
		printf("ʱ��:%s\n", __TIME__);
		printf("������:%s\n", __FUNCTION__);
		return 1;
}
