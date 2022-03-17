#include "stdafx.h"

#define SZ_MSG_MAX	512
char   szMsg[SZ_MSG_MAX];
#define DBG_TRACE(fmt, ...) _snprintf_s(szMsg, SZ_MSG_MAX, _TRUNCATE,fmt,  __VA_ARGS__);printf("%d: %s\n",__LINE__,szMsg);

#define my_print2(fmt,...)  printf(fmt,##__VA_ARGS__)  

/**
* @brief 主函数2文件
* @details 定义main入口函数
* @author E.Z.
* @date 2022-02-14
* @copyright Copyright (c) 2015-2022 北京北科麦思科自动化工程技术有限公司
*/
int testreturn()
{

	
	float r = atan(1.0);
	printf("%f\n", r);
	printf("%f\n", (r * 180 / acos(-1)));
	return 1;
}


