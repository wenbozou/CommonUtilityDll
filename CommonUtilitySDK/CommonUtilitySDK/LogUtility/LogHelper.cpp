/**************************************************************
 *  Filename:    @OutputName.cpp
 *  Copyright:   @Company Co., Ltd.
 *
 *  Description: 多线程安全型.
 *
 *  @author:     @WenboZou
 *  @version     @MM/@dd/@yyyy  @Reviser  Initial Version
 **************************************************************/

#include "pch.h"
#include "LogHelper.h"
#include "StringConversion.h"

#include <windows.h>
#include <iostream>
#include <ctime>

using namespace CommonUtilitySDK;

#pragma warning (disable:4996)

CLogHelper * CLogHelper::m_pLogHelpInstance = nullptr;

CLogHelper::CLogHelper()
{
	InitLogsFile();
}

CLogHelper::~CLogHelper()
{
}

void CLogHelper::WriteLog(const std::string &strLocal, const std::string &strEventMsg)
{
	std::string current_time;
	GetCurTime(current_time);
	std::string strCurLogMsg= current_time + " " + strLocal + " " + strEventMsg + "\n";

	if (m_of.is_open())
	{

	}
	else
	{
		m_of.open(m_strLogFile, std::ios::app | std::ios::out);
	}	
	m_of.write(strCurLogMsg.c_str(), strCurLogMsg.length());
	m_of.close();
}

void CLogHelper::WriteLog(const std::wstring &wstrLocal, const std::wstring &wstrEventMsg)
{
	WriteLog(CStringConversion::UnicodeToAnsi(wstrLocal.c_str()), CStringConversion::UnicodeToAnsi(wstrEventMsg.c_str()));
}

CLogHelper* CLogHelper::Instance()
{
	if (nullptr == m_pLogHelpInstance)
	{
		m_pLogHelpInstance = new CLogHelper();
	}

	return m_pLogHelpInstance;
}

void CLogHelper::UnInstance()
{
	if (nullptr != m_pLogHelpInstance)
	{
		delete m_pLogHelpInstance, m_pLogHelpInstance = nullptr;
	}
}

void CLogHelper::InitLogsFile()
{
	TCHAR exeFullPath[MAX_PATH];
	memset(exeFullPath, 0, MAX_PATH);

	GetModuleFileName(NULL, exeFullPath, MAX_PATH);
	wchar_t *pszPos = wcsrchr(exeFullPath, '\\');
	memset(pszPos, 0, MAX_PATH - (pszPos - exeFullPath) * sizeof(TCHAR));

	std::wstring logFilePath = exeFullPath;
	m_strLogFile = logFilePath.append(L"\\logs.txt");
}

void CLogHelper::GetCurTime(std::string& strTime)
{
	char cBuff[20] = { 0 };
	time_t ttNow = time(nullptr);
	tm tmTime;
	memset(&tmTime, 0, sizeof(tmTime));
	localtime_s(&tmTime, &ttNow);
	strftime(cBuff, sizeof(cBuff), "%Y-%m-%d %H:%M:%S", &tmTime);
	strTime = cBuff;
}
