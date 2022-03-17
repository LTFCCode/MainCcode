#include "stdafx.h"

#define LenGet (12)
#define LenByte (6)
#define LenDemo (2)
#define ReadByByte 1
#define ReadByWord 2
#define ReadByBit 3
char *readpath = "F:\\ForTest\\TestRead.txt";
char *writepath = "F:\\ForTest\\TestWrite.txt";
char *demopath = "F:\\ForTest\\TestDemo.txt";
char *testpath = "F:\\ForTest\\test.txt";
fstream read(readpath, ios::in);
fstream write(writepath, ios::out);
void split(string& data, vector<string>&container, string& delema1){
	string::size_type start = data.find_first_not_of(delema1, 0);//�ҵ���һ����Ϊ���ŵ��±�
	string::size_type pose = data.find_first_of(delema1, start);//�ҵ���һ�����ŵ��±�
	while (string::npos != start || string::npos != pose){//����û�ж���Ҳû���ַ���ʱ�����
		try{
			container.push_back(data.substr(start, pose - start));
		}
		catch (out_of_range){
			printf("�����ַ���ʱ��ʼλ�ó���\n");
		}
		start = data.find_first_not_of(delema1, pose);//����start ��pose��ʼ
		pose = data.find_first_of(delema1, start);//����pos,��start��ʼ
	}
}
int Clean(string &data){
	int pointPass1, pointPass2,pointPass3;
	data.erase(0, data.find_first_not_of(" "));
	data.erase(0, data.find_first_not_of("\t"));
	pointPass1 = data.find("//");
	pointPass3 = data.find("unsigned");
	if (pointPass3 >= 0){
		return FALSE;
	}
	if (pointPass1 == 0){
		cout << "//ע�͵�����:" << endl;
		cout << "\t"<<data << endl;
		return FALSE;
	}
	pointPass2 = data.find("/*");
	if (pointPass2 >= 0){
		pointPass2 = data.find("*/");
		cout << "/**/ע�͵�����:" << endl;
		cout << "\t" << data << endl;
		while (pointPass2<0)
		{
			getline(read, data);
			cout << "\t" << data << endl;
			pointPass2 = data.find("*/");
		}
		return FALSE;
	}
	return TRUE;
}

int Select(string &data, int &pointGet, int &pointTest, int &pointByte){

	pointGet = data.find("GetVariable");
	pointTest = data.find("TestBit");
	pointByte = data.find("Byte");
	if (pointGet >= 0 && pointByte >= 0){
		return ReadByByte;
	}
	if (pointGet >= 0){
		return ReadByWord;
	}
	if (pointByte >= 0){
		return ReadByBit;
	}
	return ReadByByte;
}
void MakeWriteTxt(){
	//  //��/**/ע�������ѽ��
	//  ����forѭ��д������
	string Delema1 = "(";
	string Delema2 = "/>";
	string Delema3 = ",";
	string data;
	string OldAddress;
	vector<string> container;
	int  pointIO, pointAnd, pointWword;
	int pointGet, pointTest, pointByte;
	int status;
	while (getline(read,data)){

		status=Clean(data);

		if (status == FALSE){
			continue;
		}

		status = Select(data, pointGet, pointTest, pointByte);
		switch (status)
		{
		case ReadByByte:
		{
			int demo_aim = pointGet + LenGet;
			int pointDemo = data.find(",");
			write << "Byte\t";
			for (int n = demo_aim; n < pointDemo; n++){
				write << data[n];
				if (n == pointDemo - 1){
					write << "\n";
				}
			}
			break;
		}
		case ReadByWord:
		{
			int demo_aim = pointGet + LenGet;
			int pointDemo = data.find(",");
			write << "Word\t";
			for (int n = demo_aim; n < pointDemo; n++){
				write << data[n];
				if (n == pointDemo - 1){
					write << "\t";
				}
			}
			pointWword = data.find("wWord");
			if (pointWword == -1){
				pointIO = data.find("pIO");
				pointAnd = data.find(")");
				for (int n = pointIO; n < pointAnd; n++){
					write << data[n];
					if (n == pointAnd - 1){
						write << "\n";
					}
				}
				break;
			}
			getline(read, data);
			pointIO = data.find("pIO");
			pointAnd = data.find("=");
			for (int n = pointIO; n < pointAnd; n++){
				write << data[n];
				if (n == pointAnd - 1){
					write << "\n";
				}
			}
			break;
		}
		case ReadByBit:{
			write << "\t";
			int pointDemo = data.find(",") + LenDemo;
			int pointkuohao = data.find(")");
			for (int n = pointDemo; n < pointkuohao; n++){
				write << data[n];
				if (n == pointkuohao - 1){
					write << "\t";
				}
			}
			pointIO = data.find("pIO");
			pointAnd = data.find("=");
			for (int n = pointIO; n < pointAnd; n++){
				write << data[n];
				if (n == pointAnd - 1){
					write << "\n";
				}
			}
			continue;
		}
		default:
			break;
		}
	}
	write.close();
	read.close();
}
int Test(){
	int StartPoint = 0;
	int iSpr = 0;
	unsigned char Byte = 0;
	int demo = 12;
	int iBnkNum = 12;
	int iZoneNum = 4;
	for (int i = 0; i < iZoneNum; i++)
		{
			for (int iBnk = 0; iBnk < iBnkNum; iBnk++)
			{
				if (demo<= 8)
				{
					for (int test = 0; test < demo; test++)
					{
						iSpr++;
					}
					cout << StartPoint + iBnk * 2<<"\tSpr:"<<iSpr<<"\tiZone:"<<i<<"\tiBnk:"<<iBnk << endl;
				}
				else
				{
					for (int test = 0; test < 8; test++)
					{
						iSpr++;
					}
					cout << StartPoint + iBnk * 2 << "\tSpr:" << iSpr << "\tiZone:" << i << "\tiBnk:" << iBnk << endl;

					for (int test = 0; test < demo - 8; test++)
					{
						
						iSpr++;
					}
					cout << StartPoint + iBnk * 2+1 << "\tSpr:" << iSpr << "\tiZone:" << i << "\tiBnk:" << iBnk << endl;
				}
			}
			StartPoint = StartPoint + iBnkNum * 2;
	}

	return StartPoint;
}

void demo_test(){
	float x = 2.0;
	float result = exp(x);
	cout << x <<"\t"<<result<< endl;
	result = log(x);
	cout << result << endl;
	
}
void ComVariableScale(){
	//MakeWriteTxt();
	demo_test();
}
