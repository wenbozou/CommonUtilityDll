#pragma once
#include <string>
#include <windows.h>
using std::string;
using std::wstring;

namespace CommonUtilitySDK
{
	class CStringConversion
	{
	public:
		CStringConversion();
		~CStringConversion();

		static string  UnicodeToAnsi(LPCWSTR pString);
		static wstring AnsiToUnicode(LPCSTR pString);
		static string UTF8ToAnsi(LPCSTR pString);
		static string AnsiToUTF8(LPCSTR lpszAnsi);
		static wstring UTF8ToUnicode(LPCSTR pString);
	};
}




