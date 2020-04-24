/**************************************************************
 *  Filename:    @PCInfo.cpp
 *  Copyright:   @Company Co., Ltd.
 *
 *  Description: 获取PC的基本信息(eg: 系统版本、用户名、).
 *
 *  @author:     @WenboZou
 *  @version     @10/@12/@2019  @Reviser  Initial Version
 **************************************************************/
 
#pragma once

#include <string>
using namespace std;

namespace CommonCodeLibrary {

	class CPCInfo
	{
	protected:
		CPCInfo();

	public:
		~CPCInfo();

		static CPCInfo* Instance();
		const string& GetOSVersion();

	private:
		string GetSysName();

	private:
		static CPCInfo* m_pPCInfoInstance;

		string m_strOSVersion;
	};
}

