#include "stdafx.h"

ZONE MZONE;//加密段
ZONE VZONE;//粗调段
ZONE FBKZONE;//精调段

float DisLastStdToFmx = 0.0;//精轧末机架至出口高温计距离
float DisFmxToFirstSpr = 0.0;//精轧出口高温计至首阀距离
float DisLastSprToCt = 0.0;//末阀至卷取入口高温计距离
float DisCtToPr = 0.0;//卷取入口高温计至夹送辊距离
float SprDis[30][15];//最多30个台架，各台架15个阀
float DisDemo;
void get(ZONE *MZONE, ZONE *VZONE, ZONE *FBKZONE){
	printf("请输入加密段台架数：\n");
	cin >> MZONE->TblNum;
	printf("输入的加密段台架数为：%d\n", MZONE->TblNum);

	printf("请输入加密段水阀数：\n");
	cin >> MZONE->SprNum;
	printf("输入的加密段水阀数为：%d\n", MZONE->SprNum);

	printf("请输入加密段台架间距：\n");
	cin >> MZONE->DisTbl;
	printf("输入的加密段台架间距为：%f\n", MZONE->DisTbl);

	printf("请输入加密段水阀间距：\n");
	cin >> MZONE->DisSpr;
	printf("输入的加密段水阀间距：%f\n", MZONE->DisSpr);

	printf("请输入加密段水阀间距2：\n");
	cin >> MZONE->DisSprDouble;
	printf("输入的加密段水阀间距2：%f\n", MZONE->DisSprDouble);

	printf("请输入粗调段台架数：\n");
	cin >> VZONE->TblNum;
	printf("输入的粗调段台架数为：%d\n", VZONE->TblNum);

	printf("请输入粗调段水阀数：\n");
	cin >> VZONE->SprNum;
	printf("输入的粗调段水阀数为：%d\n", VZONE->SprNum);

	printf("请输入粗调段台架间距：\n");
	cin >> VZONE->DisTbl;
	printf("输入的粗调段台架间距为：%f\n", VZONE->DisTbl);

	printf("请输入粗调段水阀间距：\n");
	cin >> VZONE->DisSpr;
	printf("输入的粗调段水阀间距为：%f\n", VZONE->DisSpr);

	printf("请输入精调段台架数：\n");
	cin >> FBKZONE->TblNum;
	printf("输入的精调段台架数为：%d\n", FBKZONE->TblNum);

	printf("请输入精调段水阀数：\n");
	cin >> FBKZONE->SprNum;
	printf("输入的精调段水阀数为：%d\n", FBKZONE->SprNum);

	printf("请输入精调段台架间距：\n");
	cin >> FBKZONE->DisTbl;
	printf("输入的精调段台架间距为：%f\n", FBKZONE->DisTbl);

	printf("请输入精调段水阀间距：\n");
	cin >> FBKZONE->DisSpr;
	printf("输入的精调段水阀间距为：%f\n", FBKZONE->DisSpr);


}

void CalSpr(){
	printf("请输入精轧末机架至出口高温计距离：\n");
	cin >> DisLastStdToFmx;
	printf("输入的精轧末机架至出口高温计距离为：%f\n", DisLastStdToFmx);

	printf("请输入精轧出口高温计至首阀距离：\n");
	cin >> DisFmxToFirstSpr;
	printf("输入的精轧出口高温计至首阀距离为：%f\n", DisFmxToFirstSpr);

	printf("请输入末阀至卷取入口高温计距离：\n");
	cin >> DisLastSprToCt;
	printf("输入的末阀至卷取入口高温计距离为：%f\n", DisLastSprToCt);

	printf("请输入卷取入口高温计至夹送辊距离：\n");
	cin >> DisCtToPr;
	printf("输入的卷取入口高温计至夹送辊距离为：%f\n", DisCtToPr);

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
	printf("总距离为:%0.2f\n", DisNow);
	return(DisNow);
}
void DclInit_finally(){
	get(&MZONE, &VZONE, &FBKZONE);
	CalSpr();
	DisDemo = ShowSprDis(&MZONE, &VZONE, &FBKZONE);
	system("pause");
}