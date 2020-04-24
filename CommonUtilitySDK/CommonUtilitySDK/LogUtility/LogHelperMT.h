/**************************************************************
 *  Filename:    @LogHelperMT.cpp
 *  Copyright:   @Company Co., Ltd.
 *
 *  Description: 多线程安全型.
 *
 *  @author:     @WenboZou
 *  @version     10/03/2019  @Reviser  Initial Version
 **************************************************************/
#pragma once
#include <string>
#include <fstream>
#include <mutex>
#include <queue>
#include <windows.h>
#include <process.h>

using std::string;
using std::wstring;
using std::ofstream;
using std::queue;

namespace CommonUtilitySDK {

	class CLogHelperMT
	{
	protected:
		CLogHelperMT();

	public:
		~CLogHelperMT();

		static CLogHelperMT* Instance();
		
		void WriteLoger(const std::string &strLocal, const std::string &strEventMsg);

	private:
		string PopFrontLogMsg();
		void PushBackLogMsg(const string& strLogMsg);
		bool IsEmptyLogMsgQueue();
		void WriteLoger(const std::string &strLogMsg);

		void InitLogsFile();
		void GetCurTime(std::string& strTime);

		static unsigned int __stdcall ConsumeLogMsgThreadFun(void *pParam);

	private:
		static CLogHelperMT* m_pLogHelperMTInstance;	//日志对象实例

		wstring m_wstrLogFile;	//日志文件名及其路径
		ofstream m_of;	//输出文件流

		HANDLE m_hConsumeLogMsgThread;
		unsigned int m_uConsumeLogMsgThreadId;
		CRITICAL_SECTION m_criSecLogMsg;
		bool m_bIsQuitThread;

		queue<string> m_quLogMsg;	//	日志信息缓存队列
	};

}

