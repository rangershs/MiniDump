#ifndef MINI_DUMP_H
#define MINI_DUMP_H

#include <Windows.h>
#include <tchar.h>
#include <DbgHelp.h>
#pragma comment(lib, "dbghelp.lib")

#ifdef UNICODE
#define TSprintf	wsprintf
#else
#define TSprintf	sprintf
#endif

//	Similar to namespace
class MiniDump
{
private:
	MiniDump();
	~MiniDump();

public:
	// 程序崩溃时是否启动自动生成dump文件;
	// 只需要在main函数开始处调用该函数即可;
	static void EnableAutoDump(bool bEnable = true);

private:

	static LONG ApplicationCrashHandler(EXCEPTION_POINTERS *pException);

	static void CreateDumpFile(LPCWSTR lpstrDumpFilePathName, EXCEPTION_POINTERS *pException);
	//	防止编译器自动添加SetUnhandledExceptionFilter(nullptr)，从而阻止生成dump文件
	static void DisableSetUnhandledExceptionFilter();
};

#endif