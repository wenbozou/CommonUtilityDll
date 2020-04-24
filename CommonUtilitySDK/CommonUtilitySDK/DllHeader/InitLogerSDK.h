#pragma once
#include <string>

#ifdef  INIT_LOG_SDK
#else
#define INIT_LOG_SDK extern "C" __declspec(dllimport)
#endif!INIT_LOG_SDK


INIT_LOG_SDK void InitLoger();

INIT_LOG_SDK void WriteLogA(const std::string &strLocal, const std::string &strEventMsg);

INIT_LOG_SDK void WriteLogW(const std::wstring &wstrLocal, const std::wstring &wstrEventMsg);

INIT_LOG_SDK void ReleaseLoger();


