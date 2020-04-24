/**************************************************************
 *  Filename:    @OutputName.cpp
 *  Copyright:   @Company Co., Ltd.
 *
 *  Description: 多线程安全型.
 *
 *  @author:     @WenboZou
 *  @version     10/03/2019  @Reviser  Initial Version
 **************************************************************/

#include "pch.h"
#include "LogHelperMT.h"
#include <ctime>
using namespace CommonUtilitySDK;

CLogHelperMT* CLogHelperMT::m_pLogHelperMTInstance = NULL;

CLogHelperMT::CLogHelperMT() : m_hConsumeLogMsgThread(NULL), m_uConsumeLogMsgThreadId(0), m_bIsQuitThread(false)
{
	InitLogsFile();

	m_hConsumeLogMsgThread = (HANDLE)_beginthreadex(NULL, 0, &CLogHelperMT::ConsumeLogMsgThreadFun,
		this, 0, &m_uConsumeLogMsgThreadId);

	InitializeCriticalSection(&m_criSecLogMsg);
}

CLogHelperMT::~CLogHelperMT()
{
	m_bIsQuitThread = true;

	bool bIsEmpty = IsEmptyLogMsgQueue();
	while (!bIsEmpty)
	{
		Sleep(500);
		bIsEmpty = IsEmptyLogMsgQueue();
	}

	DeleteCriticalSection(&m_criSecLogMsg);

	if (NULL != m_pLogHelperMTInstance)
	{
		delete m_pLogHelperMTInstance;
		m_pLogHelperMTInstance = NULL;
	}
}

CLogHelperMT* CLogHelperMT::Instance()
{
	if (m_pLogHelperMTInstance == NULL)
	{
		m_pLogHelperMTInstance = new CLogHelperMT();
	}

	return m_pLogHelperMTInstance;
}

void CLogHelperMT::WriteLoger(const std::string &strLocal, const std::string &strEventMsg)
{
	if (strLocal.empty() && strEventMsg.empty())
		return;

	std::string current_time;
	GetCurTime(current_time);
	std::string strCurLogMsg = current_time + " " + strLocal + " " + strEventMsg + "\n";

	PushBackLogMsg(strCurLogMsg);
}

string CLogHelperMT::PopFrontLogMsg()
{
	string strLogMsg;

	EnterCriticalSection(&m_criSecLogMsg);
	if (!m_quLogMsg.empty())
	{
		strLogMsg = m_quLogMsg.front();
		m_quLogMsg.pop();
	}
	LeaveCriticalSection(&m_criSecLogMsg);

	return strLogMsg;
}

void CLogHelperMT::PushBackLogMsg(const string& strLogMsg)
{
	EnterCriticalSection(&m_criSecLogMsg);
	m_quLogMsg.push(strLogMsg);
	LeaveCriticalSection(&m_criSecLogMsg);
}

bool CLogHelperMT::IsEmptyLogMsgQueue()
{
	bool bResult = true;
	EnterCriticalSection(&m_criSecLogMsg);
	bResult = m_quLogMsg.empty();
	LeaveCriticalSection(&m_criSecLogMsg);

	return bResult;
}

void CLogHelperMT::InitLogsFile()
{
	TCHAR exeFullPath[MAX_PATH];
	memset(exeFullPath, 0, MAX_PATH);

	GetModuleFileName(NULL, exeFullPath, MAX_PATH);
	wchar_t *pszPos = wcsrchr(exeFullPath, '\\');
	memset(pszPos, 0, MAX_PATH - (pszPos - exeFullPath) * sizeof(TCHAR));

	std::wstring logFilePath = exeFullPath;
	m_wstrLogFile = logFilePath.append(L"\\logs.txt");
}

void CLogHelperMT::WriteLoger(const std::string &strLogMsg)
{
	if (m_of.is_open())
	{

	}
	else
	{
		m_of.open(m_wstrLogFile, std::ios::app | std::ios::out);
	}
	m_of.write(strLogMsg.c_str(), strLogMsg.length());
	m_of.close();
}

void CLogHelperMT::GetCurTime(std::string& strTime)
{
	char cBuff[20] = { 0 };
	time_t ttNow = time(nullptr);
	tm tmTime;
	memset(&tmTime, 0, sizeof(tmTime));
	localtime_s(&tmTime, &ttNow);
	strftime(cBuff, sizeof(cBuff), "%Y-%m-%d %H:%M:%S", &tmTime);
	strTime = cBuff;
}

unsigned CLogHelperMT::ConsumeLogMsgThreadFun(void *pParam)
{
	CLogHelperMT *pLogHelperMT = (CLogHelperMT*)pParam;

	do 
	{
		if (pLogHelperMT == NULL)
		{
			_endthreadex(-1);
			break;
		}

		while (true)
		{
			if (pLogHelperMT->IsEmptyLogMsgQueue())
			{
				if (pLogHelperMT->m_bIsQuitThread)
					break;

				Sleep(500);
			}
			else
			{
				string strLogMsg = pLogHelperMT->PopFrontLogMsg();
				pLogHelperMT->WriteLoger(strLogMsg);
			}
		}

		_endthreadex(0);
	} while (false);

	return 0;
}

