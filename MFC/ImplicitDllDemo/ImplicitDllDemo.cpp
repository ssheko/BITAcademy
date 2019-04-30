// ImplicitDllDemo.cpp : DLL의 초기화 루틴을 정의합니다.
//

#include "stdafx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// __declspec: def 파일을 안 건들이고 외부에서 이 함수를 부를 수 있음.
 BOOL WINAPI GetModulePath(CString& strPath)	//__declspec(dllexport)
{
	TCHAR szBuffer[MAX_PATH];
	::ZeroMemory(szBuffer, sizeof(szBuffer));
	::GetModuleFileName(NULL, szBuffer, MAX_PATH);

	for (int i = lstrlen(szBuffer) - 1; i >= 0; --i)
	{
		if (szBuffer[i] == '\\')
		{
			int j = lstrlen(szBuffer) - 1;
			for (; j >= i; --j)
			{
				szBuffer[j] = NULL;
			}

			if (szBuffer[i] == ':')
				szBuffer[j + 1] = '\\';

			strPath = szBuffer;
			return TRUE;
		}
	}
	return FALSE;
}