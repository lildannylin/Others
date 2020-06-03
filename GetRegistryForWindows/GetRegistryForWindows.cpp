
#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>
#include <iomanip>
#include <stdio.h>
#include <typeinfo>
#include <Windows.h>
#include <sqlite3.h>
#include <atlbase.h>

using namespace std;



LONG GetDWORDRegKey(HKEY hKey, const std::wstring &strValueName, DWORD &nValue, DWORD nDefaultValue)
{
	nValue = nDefaultValue;
	DWORD dwBufferSize(sizeof(DWORD));
	DWORD nResult(0);
	LONG nError = ::RegQueryValueExW(hKey,
		strValueName.c_str(),
		0,
		NULL,
		reinterpret_cast<LPBYTE>(&nResult),
		&dwBufferSize);
	if (ERROR_SUCCESS == nError)
	{
		nValue = nResult;
	}
	return nError;
}

LONG GetBoolRegKey(HKEY hKey, const std::wstring &strValueName, bool &bValue, bool bDefaultValue)
{
	DWORD nDefValue((bDefaultValue) ? 1 : 0);
	DWORD nResult(nDefValue);
	LONG nError = GetDWORDRegKey(hKey, strValueName.c_str(), nResult, nDefValue);
	if (ERROR_SUCCESS == nError)
	{
		bValue = (nResult != 0) ? true : false;
	}
	return nError;
}

LONG GetStringRegKey(HKEY hKey, const std::wstring &strValueName, std::wstring &strValue, const std::wstring &strDefaultValue)
{
	strValue = strDefaultValue;
	WCHAR szBuffer[512];
	DWORD dwBufferSize = sizeof(szBuffer);
	ULONG nError;
	nError = RegQueryValueExW(hKey, strValueName.c_str(), 0, NULL, (LPBYTE)szBuffer, &dwBufferSize);
	if (ERROR_SUCCESS == nError)
	{
		strValue = szBuffer;
	}
	return nError;
	
}
int main()
{
	HKEY hKey;
	LONG lRes = RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\App Paths\\BroadWinExe", 0, KEY_READ, &hKey);
	bool bExistsAndSuccess(lRes == ERROR_SUCCESS);
	bool bDoesNotExistsSpecifically(lRes == ERROR_FILE_NOT_FOUND);
	std::wstring strValueOfBinDir;
	std::wstring strKeyDefaultValue;

	cout << bExistsAndSuccess << endl;
	GetStringRegKey(hKey, L"Path", strValueOfBinDir, L"bad");
	wcout << strValueOfBinDir;
	
	
}





