#include "pch.h"
#include "StringConversion.h"
using namespace CommonUtilitySDK;

CStringConversion::CStringConversion()
{
}


CStringConversion::~CStringConversion()
{
}

string  CStringConversion::UnicodeToAnsi(LPCWSTR pString)
{
	char *pANSI = NULL;
	int nByte = 0;
	nByte = WideCharToMultiByte(CP_ACP, 0, pString, -1, NULL, 0, NULL, NULL);
	pANSI = (char*)malloc(nByte + 1);
	memset(pANSI, 0, nByte + 1);
	WideCharToMultiByte(CP_ACP, 0, pString, -1, pANSI, nByte, NULL, NULL);
	string str = pANSI;
	free(pANSI);
	return str;
}

wstring CStringConversion::AnsiToUnicode(LPCSTR pString)
{
	wchar_t *pUnicode = NULL;
	int nWideCharLen = 0;
	nWideCharLen = MultiByteToWideChar(CP_ACP, 0, pString, -1, NULL, 0);
	pUnicode = (wchar_t*)malloc((nWideCharLen + 1) * sizeof(wchar_t));
	memset(pUnicode, 0, (nWideCharLen + 1) * sizeof(wchar_t));
	MultiByteToWideChar(CP_ACP, 0, pString, -1, pUnicode, nWideCharLen);
	std::wstring str = pUnicode;
	free(pUnicode);
	return str;
}

string CStringConversion::UTF8ToAnsi(LPCSTR pString)
{
	int nwLen = MultiByteToWideChar(CP_UTF8, 0, pString, -1, NULL, 0);
	wchar_t *pwBuf = new wchar_t[nwLen + 1];
	memset(pwBuf, 0, (nwLen = 1) * sizeof(wchar_t));
	MultiByteToWideChar(CP_UTF8, 0, pString, strlen(pString), pwBuf, nwLen);
	int nLen = WideCharToMultiByte(CP_ACP, 0, pwBuf, -1, NULL, NULL, NULL, NULL);
	char *pBuf = new char[nLen + 1];
	memset(pBuf, 0, nLen + 1);
	WideCharToMultiByte(CP_ACP, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);
	string retStr = pBuf;
	delete[] pBuf;
	delete[] pwBuf;
	pBuf = NULL;
	pwBuf = NULL;
	return retStr;
}

string CStringConversion::AnsiToUTF8(LPCSTR lpszAnsi)
{
	int wlen = MultiByteToWideChar(CP_ACP, 0, lpszAnsi, -1, NULL, 0);
	wchar_t *pwBuf = (wchar_t*)malloc(sizeof(wchar_t)*(wlen + 1));
	memset(pwBuf, 0, (wlen + 1) * sizeof(wchar_t));
	MultiByteToWideChar(CP_ACP, 0, lpszAnsi, strlen(lpszAnsi), pwBuf, wlen);
	int len = WideCharToMultiByte(CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL);
	char* pBuf = (char*)malloc(len + 1);
	memset(pBuf, 0, len + 1);
	WideCharToMultiByte(CP_UTF8, 0, pwBuf, wlen, pBuf, len, NULL, NULL);
	string str = pBuf;
	free(pBuf);
	free(pwBuf);
	return str;
}

wstring CStringConversion::UTF8ToUnicode(LPCSTR pString)
{
	int nwLen = MultiByteToWideChar(CP_UTF8, 0, pString, -1, NULL, 0);
	wchar_t* pwBuf = new wchar_t[nwLen + 1];
	memset(pwBuf, 0, (nwLen + 1) * sizeof(wchar_t));
	MultiByteToWideChar(CP_UTF8, 0, pString, strlen(pString), pwBuf, nwLen);
	wstring retStr = pwBuf;
	delete[] pwBuf;
	pwBuf = NULL;
	return retStr;
}