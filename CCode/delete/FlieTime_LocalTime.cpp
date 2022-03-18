#include "stdafx.h"

int absoluteTime(long long *PnewTime, float offset)
{
	ULONGLONG ftCurrentTime;
	SYSTEMTIME st;

	::GetLocalTime(&st);
	::SystemTimeToFileTime(&st, (LPFILETIME)&ftCurrentTime);
	*PnewTime = ftCurrentTime + (ULONGLONG)(offset*1000.0f*1000.0f*10.0f);

	return TRUE;
}

double elapsedTime(long long time1, long long time2)
{
	return ((double)(time2 - time1)) / 10.0 / 1000.0 / 1000.0;
}

void demo_time(){

	SYSTEMTIME		stLocal, stUTC, stUTC2;
	FILETIME		ftLocal, ftUTC;
	ULARGE_INTEGER	time1,time2;//大整数
	long long		time3, time4;
	double a;
	GetLocalTime(&stLocal);
	GetSystemTime(&stUTC);
	printf("Local System Time(YYYY-MM-DD HH:MM:SS): %d-%d-%d %d:%d:%d\n", stLocal.wYear, stLocal.wMonth,
		stLocal.wDay, stLocal.wHour, stLocal.wMinute, stLocal.wSecond);
	printf("UTC System Time  (YYYY-MM-DD HH:MM:SS): %d-%d-%d %d:%d:%d\n", stUTC.wYear, stUTC.wMonth,
		stUTC.wDay, stUTC.wHour, stUTC.wMinute, stUTC.wSecond);

	SystemTimeToFileTime(&stLocal, &ftLocal);

	time1.LowPart = ftLocal.dwLowDateTime;
	time1.HighPart = ftLocal.dwHighDateTime;
	printf("Local File Time: %llu\n", time1.QuadPart);

	LocalFileTimeToFileTime(&ftLocal, &ftUTC);

	time2.LowPart = ftUTC.dwLowDateTime;
	time2.HighPart = ftUTC.dwHighDateTime;
	printf("UTC File Time: %llu\n", time2.QuadPart);

	absoluteTime(&time3, 0);
	printf("------------统计等待任意键输入的时间-----------\n");
	system("pause");
	absoluteTime(&time4, 0);
	printf("起始时间：%d\n", time3);
	printf("结束时间：%d\n", time4);
	a=elapsedTime(time3, time4);
	printf("时间差值：%f秒\n",a);


	FileTimeToSystemTime(&ftUTC, &stUTC2);
	printf("UTC System Time2 (YYYY-MM-DD HH:MM:SS): %d-%d-%d %d:%d:%d\n", stUTC2.wYear, stUTC2.wMonth,
		stUTC2.wDay, stUTC2.wHour, stUTC2.wMinute, stUTC2.wSecond);
	system("pause");

}
void time_play(){
	SYSTEMTIME start_point, end_point;
	ULONGLONG	ft_start_point,ft_end_point;
	float time_difference;
	char test_input ='5';
	while (test_input=='5')
	{
		printf("比较两次按键间隔时间\n");
		printf("测试开始\n");
		printf("------------按任意键开始计时-------------\n");
		system("pause");
		GetLocalTime(&start_point);
		printf("------------按任意键结束计时-------------\n");
		system("pause");
		GetLocalTime(&end_point);

		printf("开始时刻: %d:%d:%d\n", start_point.wHour, start_point.wMinute, start_point.wSecond);
		printf("结束时刻: %d:%d:%d\n", end_point.wHour, end_point.wMinute, end_point.wSecond);

		printf("粗略时间差:%d:%d:%d\n", end_point.wHour - start_point.wHour, end_point.wMinute - start_point.wMinute, end_point.wSecond-start_point.wSecond );


		SystemTimeToFileTime(&start_point, (LPFILETIME)&ft_start_point);
		SystemTimeToFileTime(&end_point, (LPFILETIME)&ft_end_point);
		time_difference=elapsedTime(ft_start_point,ft_end_point);
		printf("精确时间差:%f\n",time_difference);
		cout << "输入数字5继续，其余键退出\n" << endl;
		cin  >> test_input;
		printf("输入的值为:%c\n",test_input);
	}
}

void demo_time_test(){
	
	char test_input[10] = "123456";
	int a = test_input[0] - ANSI0;
	printf("%d\n", a);
	a = test_input[1] - ANSI0;
	printf("%d\n", a);
	a = test_input[2] - ANSI0;
	printf("%d\n", a);
	a = test_input[3] - ANSI0;
	printf("%d\n", a);
	a = test_input[4] - ANSI0;
	printf("%d\n", a);
	a = test_input[5] - ANSI0;
	printf("%d\n", a);
	a=test_input[0];
	printf("%d\n",test_input);
	system("pause"); 
}
void time_ms(){
	double start_time_ms = GetTickCount();
	double now_time_ms = 0.0;
	double start_time_s = time(NULL);
	double now_time_s = 0.0;
	while (true){
		now_time_ms = GetTickCount();
		now_time_s = time(NULL);
		printf("%fms\n", now_time_ms - start_time_ms);
		printf("%fs\n", now_time_s - start_time_s);
		printf("%fs\n", (now_time_ms - start_time_ms)/1000.0);
		system("pause");
	}
}
void time_work(){
	//demo_time();
	time_play();
	//demo_time_test();
	//time_ms();
}