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
	// �������ʱ�Ƿ������Զ�����dump�ļ�;
	// ֻ��Ҫ��main������ʼ�����øú�������;
	static void EnableAutoDump(bool bEnable = true);

private:

	static LONG ApplicationCrashHandler(EXCEPTION_POINTERS *pException);

	static void CreateDumpFile(LPCWSTR lpstrDumpFilePathName, EXCEPTION_POINTERS *pException);
	//	��ֹ�������Զ����SetUnhandledExceptionFilter(nullptr)���Ӷ���ֹ����dump�ļ�
	static void DisableSetUnhandledExceptionFilter();
};

#endif