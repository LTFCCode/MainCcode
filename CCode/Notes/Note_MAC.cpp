#include "stdafx.h"


#include <winsock2.h>
#include <iphlpapi.h>
#pragma comment(lib, "IPHLPAPI.lib")
#pragma comment(lib,"ws2_32.lib")



int test()
{
	CString m_IP;              //IP地址临时变量
	CString m_LocalIP;
	char PCnameBuffer[128];    //获得本地计算机名
	CString m_PCname;

	WSAData data;              //初始化:如果不初始化，以下代码将无法执行
	if (WSAStartup(MAKEWORD(1, 1), &data) != 0)
	{
		cout << "初始化错误,无法获取主机信息..." << endl;
	}
	else
	{
		if (0 == gethostname(PCnameBuffer, 128))
		{
			m_PCname = PCnameBuffer;
			cout << m_PCname << endl;
			struct hostent* pHost;  //获得本地IP地址
			pHost = gethostbyname(PCnameBuffer);  //pHost返回的是指向主机的列表
			for (int i = 0; pHost != NULL && pHost->h_addr_list[i] != NULL; i++)
			{
				//得到指向ip的psz变量
				LPCSTR psz = inet_ntoa(*(struct in_addr *)pHost->h_addr_list[i]);
				m_IP += psz;
			}
			m_LocalIP = m_IP;
			cout << m_LocalIP << endl;
		}
		else
		{
			cout << "获取主机信息失败..." << endl;
		}
	}
	return 0;
}
bool  GetMacByGetAdaptersInfo(std::string& macOUT)
{
	test();
	bool ret = false;

	ULONG ulOutBufLen = sizeof(IP_ADAPTER_INFO);
	PIP_ADAPTER_INFO pAdapterInfo = (IP_ADAPTER_INFO*)malloc(sizeof(IP_ADAPTER_INFO));
	if (pAdapterInfo == NULL)
		return false;
	// Make an initial call to GetAdaptersInfo to get the necessary size into the ulOutBufLen variable
	if (GetAdaptersInfo(pAdapterInfo, &ulOutBufLen) == ERROR_BUFFER_OVERFLOW)
	{
		free(pAdapterInfo);
		pAdapterInfo = (IP_ADAPTER_INFO *)malloc(ulOutBufLen);
		if (pAdapterInfo == NULL)
			return false;
	}

	if (GetAdaptersInfo(pAdapterInfo, &ulOutBufLen) == NO_ERROR)
	{
		for (PIP_ADAPTER_INFO pAdapter = pAdapterInfo; pAdapter != NULL; pAdapter = pAdapter->Next)
		{
			// 确保是以太网
			if (pAdapter->Type != MIB_IF_TYPE_ETHERNET)
				continue;
			// 确保MAC地址的长度为 00-00-00-00-00-00
			if (pAdapter->AddressLength != 6)
				continue;
			char acMAC[32];
			sprintf(acMAC, "%02X-%02X-%02X-%02X-%02X-%02X",
				int(pAdapter->Address[0]),
				int(pAdapter->Address[1]),
				int(pAdapter->Address[2]),
				int(pAdapter->Address[3]),
				int(pAdapter->Address[4]),
				int(pAdapter->Address[5]));
			macOUT = acMAC;
			cout << macOUT << endl;
			ret = true;
			break;
		}
	}

	free(pAdapterInfo);
	return ret;
}
