/**************************************************************
 *  Filename:    @OutputName.cpp
 *  Copyright:   @Company Co., Ltd.
 *
 *  Description: 多线程安全型.
 *
 *  @author:     @WenboZou
 *  @version     @MM/@dd/@yyyy  @Reviser  Initial Version
 **************************************************************/

#pragma once
#include <string>
#include <fstream>
#include <mutex>

namespace CommonUtilitySDK {

	class CLogHelper
	{
	protected:
		CLogHelper();

	public:
		~CLogHelper();

		void WriteLog(const std::string &strLocal, const std::string &strEventMsg);
		void WriteLog(const std::wstring &wstrLocal, const std::wstring &wstrEventMsg);

		static CLogHelper* Instance();
		static void UnInstance();
	private:
		void InitLogsFile();
		void GetCurTime(std::string& strTime);

	private:
		static CLogHelper *m_pLogHelpInstance;	//日志对象实例

		std::ofstream m_of;	//输出文件流
		std::wstring m_strLogFile;	//日志文件名及其路径

		/*
		class CGarbo
		{
		public:
			~CGarbo()
			{
				if (CLogHelper::m_pLogHelpInstance)
				{
					delete CLogHelper::m_pLogHelpInstance;
					CLogHelper::m_pLogHelpInstance = NULL;
				}
			}
		};

		static CGarbo m_sGarbo;
		//*/
	};

}