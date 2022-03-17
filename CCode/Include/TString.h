#ifndef TSTRING_H
#define TSTRING_H

#include <iostream>
#include <string>
#include <tchar.h>

#ifdef _UNICODE
#   define TString std::wstring
#else
#   define TString std::string
#endif

TString operator+(const TString& str, unsigned char uchr);
TString operator+(const TString& str, short sht);
TString operator+(const TString& str, unsigned short usht);
TString operator+(const TString& str, int i);
TString operator+(const TString& str, unsigned int ui);
TString operator+(const TString& str, long l);
TString operator+(const TString& str, unsigned long ul);
TString operator+(const TString& str, long long lld);
TString operator+(const TString& str, unsigned long long llu);
TString operator+(const TString& str, float f);
TString operator+(const TString& str, double d);
template <class T>
typename std::enable_if<std::is_same<T, float>::value || std::is_same<T, double>::value, TString>::type floatToString(T f, int i)
{
	TCHAR szBuff[64];
	_stprintf_s(szBuff, 64, _T("%.*f"), i, f);
	return szBuff;
}
#endif