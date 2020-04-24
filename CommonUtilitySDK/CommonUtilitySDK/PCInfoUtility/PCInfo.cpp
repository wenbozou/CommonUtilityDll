/**************************************************************
 *  Filename:    @PCInfo.cpp
 *  Copyright:   @Company Co., Ltd.
 *
 *  Description: 模板测试源文件.
 *
 *  @author:     @WenboZou
 *  @version     @10/@12/@2019  @Reviser  Initial Version
 **************************************************************/
#include "PCInfo.h"
#include <windows.h>

using namespace CommonCodeLibrary;

CPCInfo* CPCInfo::m_pPCInfoInstance = NULL;

CPCInfo::CPCInfo()
{
}

CPCInfo::~CPCInfo()
{
	if (NULL != m_pPCInfoInstance)
	{
		delete m_pPCInfoInstance;
		m_pPCInfoInstance = NULL;
	}
}

CPCInfo* CPCInfo::Instance()
{
	if (NULL == m_pPCInfoInstance)
	{
		m_pPCInfoInstance = new CPCInfo();
	}

	return m_pPCInfoInstance;
}

const string& CPCInfo::GetOSVersion()
{
	if (m_strOSVersion.empty())
	{
		m_strOSVersion = GetSysName();
	}

	return m_strOSVersion;
}

string CPCInfo::GetSysName()
{
	string strSysName;

	SYSTEM_INFO sys_info;
	RtlZeroMemory(&sys_info, sizeof(sys_info));
	GetSystemInfo(&sys_info);

	OSVERSIONINFOEX os_ver_info;



	return strSysName;
}