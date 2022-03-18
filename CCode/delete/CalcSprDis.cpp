#include "stdafx.h"

float Demo_CalSpr1(float demo){
	printf("%0.2f, ", demo);
	demo = demo + 0.81;
	printf("%0.2f, ", demo);
	demo = demo + 1.35;
	printf("%0.2f, ", demo);
	demo = demo + 0.81;
	printf("%0.2f\n", demo);
	demo = demo + 1.08;
	return demo;
}

float Demo_CalSpr2(float demo){
	printf("%0.2f, ", demo);
	demo = demo + 0.3;
	printf("%0.2f, ", demo);
	demo = demo + 0.8;
	printf("%0.2f, ", demo);
	demo = demo + 0.3;
	printf("%0.2f", demo);
	demo = demo + 1.08;
	printf("%0.2f, ", demo);
	demo = demo + 0.3;
	printf("%0.2f, ", demo);
	demo = demo + 0.8;
	printf("%0.2f, ", demo);
	demo = demo + 0.3;
	printf("%0.2f\n", demo);
	demo = demo + 0.72;
	return demo;
}
void Demo_calculate(){
	float demo;
	printf("ÇëÊäÈë³õÊ¼¾àÀë\n");
	cin >> demo;
	for (int i = 1; i <= 12; i++){
		demo = Demo_CalSpr1(demo);
	}
	for (int i = 1; i <= 3; i++){
		demo = Demo_CalSpr2(demo);
	}
	system("pause");

}