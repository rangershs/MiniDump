#include "MiniDump.h"

MiniDump::MiniDump()
{
}


MiniDump::~MiniDump()
{
}

void MiniDump::EnableAutoDump(bool bEnable)
{
	if (bEnable)
	{
		SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER) ApplicationCrashHandler);
		DisableSetUnhandledExceptionFilter();
	}
}

LONG MiniDump::ApplicationCrashHandler(EXCEPTION_POINTERS *pException)
{
	/*if (IsDebuggerPresent())
	{
		return EXCEPTION_CONTINUE_SEARCH;
	}*/

	TCHAR szDumpDir[MAX_PATH] = { 0 };
	TCHAR szDumpFile[MAX_PATH] = { 0 };
	TCHAR szMsg[MAX_PATH] = { 0 };
	SYSTEMTIME	stTime = { 0 };
	// 构建dump文件路径，在当前路径下创建Dump目录保存dump文件
	GetLocalTime(&stTime);
	::GetCurrentDirectory(MAX_PATH, szDumpDir);
	lstrcat(szDumpDir, TEXT("\\Dump\\"));
	::CreateDirectory(szDumpDir, NULL);
	TSprintf(szDumpFile, _T("%s%04d%02d%02d_%02d%02d%02d.dmp"), szDumpDir,
		stTime.wYear, stTime.wMonth, stTime.wDay,
		stTime.wHour, stTime.wMinute, stTime.wSecond);
	// 创建dump文件;
	CreateDumpFile(szDumpFile, pException);

	// 弹出一个错误对话框或者提示上传， 并退出程序;
	TSprintf(szMsg, _T("I'm so sorry, but the program crashed.\r\ndump file : %s"), szDumpFile);
	FatalAppExit(-1, szMsg);

	return EXCEPTION_EXECUTE_HANDLER;
}

void MiniDump::CreateDumpFile(LPCWSTR strPath, EXCEPTION_POINTERS *pException)
{
	// 创建Dump文件;
	HANDLE hDumpFile = CreateFile(strPath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hDumpFile != INVALID_HANDLE_VALUE)
	{ 
		// Dump信息;
		MINIDUMP_EXCEPTION_INFORMATION dumpInfo;
		dumpInfo.ExceptionPointers = pException;
		dumpInfo.ThreadId = GetCurrentThreadId();
		dumpInfo.ClientPointers = TRUE;

		// 写入Dump文件内容;
		MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hDumpFile, MiniDumpNormal, &dumpInfo, NULL, NULL);
		CloseHandle(hDumpFile);
	}
}

void MiniDump::DisableSetUnhandledExceptionFilter()
{
	void* addr = (void*)GetProcAddress(LoadLibrary(L"kernel32.dll"),
		"SetUnhandledExceptionFilter");

	if (addr)
	{
		unsigned char code[16];
		int size = 0;

		code[size++] = 0x33;
		code[size++] = 0xC0;
		code[size++] = 0xC2;
		code[size++] = 0x04;
		code[size++] = 0x00;

		DWORD dwOldFlag, dwTempFlag;
		VirtualProtect(addr, size, PAGE_READWRITE, &dwOldFlag);
		WriteProcessMemory(GetCurrentProcess(), addr, code, size, NULL);
		VirtualProtect(addr, size, dwOldFlag, &dwTempFlag);
	}
}
