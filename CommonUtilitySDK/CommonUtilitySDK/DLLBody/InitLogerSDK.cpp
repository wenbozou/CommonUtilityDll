#include "pch.h"

#ifndef INIT_LOG_SDK
#define INIT_LOG_SDK extern "C" __declspec(dllexport)
#endif

#include "InitLogerSDK.h"
#include "LogHelper.h"

using namespace CommonUtilitySDK;

void InitLoger()
{
}

void WriteLogA(const std::string &strLocal, const std::string &strEventMsg)
{
	CLogHelper::Instance()->WriteLog(strLocal, strEventMsg);
}

void WriteLogW(const std::wstring &wstrLocal, const std::wstring &wstrEventMsg)
{
	CLogHelper::Instance()->WriteLog(wstrLocal, wstrEventMsg);
}

void ReleaseLoger()
{
	CLogHelper::UnInstance();
}