#include "stdafx.h"

ZONE MZONE;//���ܶ�
ZONE VZONE;//�ֵ���
ZONE FBKZONE;//������

float DisLastStdToFmx = 0.0;//����ĩ���������ڸ��¼ƾ���
float DisFmxToFirstSpr = 0.0;//�������ڸ��¼����׷�����
float DisLastSprToCt = 0.0;//ĩ������ȡ��ڸ��¼ƾ���
float DisCtToPr = 0.0;//��ȡ��ڸ��¼������͹�����
float SprDis[30][15];//���30��̨�ܣ���̨��15����
float DisDemo;
void get(ZONE *MZONE, ZONE *VZONE, ZONE *FBKZONE){
	printf("��������ܶ�̨������\n");
	cin >> MZONE->TblNum;
	printf("����ļ��ܶ�̨����Ϊ��%d\n", MZONE->TblNum);

	printf("��������ܶ�ˮ������\n");
	cin >> MZONE->SprNum;
	printf("����ļ��ܶ�ˮ����Ϊ��%d\n", MZONE->SprNum);

	printf("��������ܶ�̨�ܼ�ࣺ\n");
	cin >> MZONE->DisTbl;
	printf("����ļ��ܶ�̨�ܼ��Ϊ��%f\n", MZONE->DisTbl);

	printf("��������ܶ�ˮ����ࣺ\n");
	cin >> MZONE->DisSpr;
	printf("����ļ��ܶ�ˮ����ࣺ%f\n", MZONE->DisSpr);

	printf("��������ܶ�ˮ�����2��\n");
	cin >> MZONE->DisSprDouble;
	printf("����ļ��ܶ�ˮ�����2��%f\n", MZONE->DisSprDouble);

	printf("������ֵ���̨������\n");
	cin >> VZONE->TblNum;
	printf("����Ĵֵ���̨����Ϊ��%d\n", VZONE->TblNum);

	printf("������ֵ���ˮ������\n");
	cin >> VZONE->SprNum;
	printf("����Ĵֵ���ˮ����Ϊ��%d\n", VZONE->SprNum);

	printf("������ֵ���̨�ܼ�ࣺ\n");
	cin >> VZONE->DisTbl;
	printf("����Ĵֵ���̨�ܼ��Ϊ��%f\n", VZONE->DisTbl);

	printf("������ֵ���ˮ����ࣺ\n");
	cin >> VZONE->DisSpr;
	printf("����Ĵֵ���ˮ�����Ϊ��%f\n", VZONE->DisSpr);

	printf("�����뾫����̨������\n");
	cin >> FBKZONE->TblNum;
	printf("����ľ�����̨����Ϊ��%d\n", FBKZONE->TblNum);

	printf("�����뾫����ˮ������\n");
	cin >> FBKZONE->SprNum;
	printf("����ľ�����ˮ����Ϊ��%d\n", FBKZONE->SprNum);

	printf("�����뾫����̨�ܼ�ࣺ\n");
	cin >> FBKZONE->DisTbl;
	printf("����ľ�����̨�ܼ��Ϊ��%f\n", FBKZONE->DisTbl);

	printf("�����뾫����ˮ����ࣺ\n");
	cin >> FBKZONE->DisSpr;
	printf("����ľ�����ˮ�����Ϊ��%f\n", FBKZONE->DisSpr);


}

void CalSpr(){
	printf("�����뾫��ĩ���������ڸ��¼ƾ��룺\n");
	cin >> DisLastStdToFmx;
	printf("����ľ���ĩ���������ڸ��¼ƾ���Ϊ��%f\n", DisLastStdToFmx);

	printf("�����뾫�����ڸ��¼����׷����룺\n");
	cin >> DisFmxToFirstSpr;
	printf("����ľ������ڸ��¼����׷�����Ϊ��%f\n", DisFmxToFirstSpr);

	printf("������ĩ������ȡ��ڸ��¼ƾ��룺\n");
	cin >> DisLastSprToCt;
	printf("�����ĩ������ȡ��ڸ��¼ƾ���Ϊ��%f\n", DisLastSprToCt);

	printf("�������ȡ��ڸ��¼������͹����룺\n");
	cin >> DisCtToPr;
	printf("����ľ�ȡ��ڸ��¼������͹�����Ϊ��%f\n", DisCtToPr);

}

float ShowSprDis(ZONE *MZONE, ZONE *VZONE, ZONE *FBKZONE){
	int TblNum = MZONE->TblNum + VZONE->TblNum + FBKZONE->TblNum;
	float DisNow = DisFmxToFirstSpr;
	int split = 1;
	//MZONE
	for (int i = 0; i < MZONE->TblNum; i++){
		split = 1;
		for (int n = 0; n < MZONE->SprNum; n++){
			SprDis[i][n] = DisNow;
			if (n<MZONE->SprNum - 1){
				if (MZONE->DisSprDouble == 0){
					DisNow += MZONE->DisSpr;
					printf("%0.2f,", SprDis[i][n]);
				}
				else{
					if (split % 2 == 1){
						DisNow += MZONE->DisSprDouble;
						printf("%0.2f,", SprDis[i][n]);
						split++;
					}
				}
			}
			else{
				printf("%0.2f\n", SprDis[i][n]);
			}
		}
		if (i<MZONE->TblNum - 1){
			DisNow += MZONE->DisTbl;
		}
		else
		{
			DisNow += VZONE->DisTbl;
		}

	}

	//VZONE
	for (int i = MZONE->TblNum; i < VZONE->TblNum + MZONE->TblNum; i++){
		for (int n = 0; n < VZONE->SprNum; n++){
			SprDis[i][n] = DisNow;
			if (n<VZONE->SprNum - 1){
				DisNow += VZONE->DisSpr;
				printf("%0.2f,", SprDis[i][n]);
			}
			else{
				printf("%0.2f\n", SprDis[i][n]);
			}
		}
		if (i<VZONE->TblNum - 1){
			DisNow += VZONE->DisTbl;
		}
		else
		{
			DisNow += FBKZONE->DisTbl;
		}
	}

	//FBKZONE
	for (int i = VZONE->TblNum + MZONE->TblNum; i < VZONE->TblNum + MZONE->TblNum + FBKZONE->TblNum; i++){
		for (int n = 0; n < FBKZONE->SprNum; n++){
			SprDis[i][n] = DisNow;
			if (n<FBKZONE->SprNum - 1){
				DisNow += FBKZONE->DisSpr;
				printf("%0.2f,", SprDis[i][n]);
			}
			else{
				printf("%0.2f\n", SprDis[i][n]);
			}
		}
		DisNow += FBKZONE->DisTbl;
	}
	DisNow += DisLastStdToFmx + DisFmxToFirstSpr + DisLastSprToCt + DisCtToPr;
	printf("�ܾ���Ϊ:%0.2f\n", DisNow);
	return(DisNow);
}
void DclInit_finally(){
	get(&MZONE, &VZONE, &FBKZONE);
	CalSpr();
	DisDemo = ShowSprDis(&MZONE, &VZONE, &FBKZONE);
	system("pause");
}