#include <windows.h>
#include <tchar.h>
#include "resource.h"
// 공용컨트롤 사용시 필요한 헤더
//#include <CommCtrl.h>
//#pragma comment(lib, "comctl32.lib")

BOOL CALLBACK DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		// Dialog가 처음 나타날 때 발생. 각 컨트롤을 초기화한다.
	case WM_INITDIALOG:
	{
	}
	return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDCANCEL:
			EndDialog(hDlg, IDCANCEL);
			return 0;
		}
		return TRUE;
	}
	return FALSE;	// 메세지 처리를 안한 경우
}

int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrev, LPTSTR lpCmdLine, int nShowCmd)
{
	UINT ret = DialogBox(hInst,	// instance
		MAKEINTRESOURCE(IDD_DIALOG1),	// 다이얼로그 선택
		0,	// 부모 윈도우
		DlgProc);	// Proc
	return 0;
}