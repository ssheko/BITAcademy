#pragma once
#pragma comment(lib, "Dbghelp.lib")
#include <signal.h>
#include <Windows.h>
#include <crtdbg.h>
#include <DbgHelp.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////
// CrashDump 
// ���� : ���ܸ� �ڵ鸵�Ͽ� �������� ���鵵�� �����ϴ� Ŭ����
//////////////////////////////////////////////////////////////
class CrashDump
{
public:
	// ������
	// ���� �ڵ鸵
	CrashDump()				
	{
		_dumpCount = 0;

		_invalid_parameter_handler oldHandler, newHandler;
		newHandler = myInvalidParameterHandler;

		oldHandler = _set_invalid_parameter_handler(newHandler);
		_CrtSetReportMode(_CRT_WARN, 0);
		_CrtSetReportMode(_CRT_ASSERT, 0);
		_CrtSetReportMode(_CRT_ERROR, 0);

		_CrtSetReportHook(_custom_Report_hook);

		_set_purecall_handler(myPurecallHandler);

		_set_abort_behavior(0, _WRITE_ABORT_MSG | _CALL_REPORTFAULT);
		signal(SIGABRT, signalHandler);
		signal(SIGINT, signalHandler);
		signal(SIGILL, signalHandler);
		signal(SIGFPE, signalHandler);
		signal(SIGSEGV, signalHandler);
		signal(SIGTERM, signalHandler);

		SetHandlerDump();
	}

	static void Crash()
	{
		int *p = nullptr;
		*p = 0;
	}

	static LONG WINAPI MyExceptionFilter(__in PEXCEPTION_POINTERS pExceptionPointer)
	{
		long dumpCount = InterlockedIncrement(&_dumpCount);

		WCHAR filename[MAX_PATH];
		SYSTEMTIME nowTime;
		GetLocalTime(&nowTime);

		wsprintf(filename, L"Dump_%d%02d%02d_%02d.%02d.%02d_%d.dmp",
			nowTime.wYear, nowTime.wMonth, nowTime.wDay, nowTime.wHour, nowTime.wMinute, nowTime.wSecond, dumpCount);

		HANDLE dumpFile = ::CreateFile(filename,
			GENERIC_WRITE,
			FILE_SHARE_WRITE,
			NULL,
			CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL, NULL);

		if (dumpFile != INVALID_HANDLE_VALUE)
		{
			_MINIDUMP_EXCEPTION_INFORMATION minidumpExceptionInformation;

			minidumpExceptionInformation.ThreadId = ::GetCurrentThreadId();
			minidumpExceptionInformation.ExceptionPointers = pExceptionPointer;
			minidumpExceptionInformation.ClientPointers = TRUE;

			MiniDumpWriteDump(GetCurrentProcess(),
				GetCurrentProcessId(),
				dumpFile,
				MiniDumpWithFullMemory,
				&minidumpExceptionInformation,
				NULL,
				NULL);

			CloseHandle(dumpFile);
		}
		return EXCEPTION_EXECUTE_HANDLER;
	}

	static LONG WINAPI RedirectedSetUnhandledExceptionFilter(EXCEPTION_POINTERS * exceptionInfo)
	{
		MyExceptionFilter(exceptionInfo);
		return EXCEPTION_EXECUTE_HANDLER;
	}

	static void SetHandlerDump()
	{
		SetUnhandledExceptionFilter(MyExceptionFilter);
	}

	static void myInvalidParameterHandler(const wchar_t * expression, const wchar_t * function, const wchar_t * filfile, unsigned int line, uintptr_t pReserved)
	{
		Crash();
	}

	static int _custom_Report_hook(int ireposttype, char * message, int * returnvalue)
	{
		Crash();
		return 0;
	}

	static void myPurecallHandler()
	{
		Crash();
	}

	static void signalHandler(int Error)
	{
		Crash();
	}
	static long _dumpCount;
};
