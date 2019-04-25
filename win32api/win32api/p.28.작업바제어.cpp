#include <windows.h>
#include <tchar.h>

int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrev, LPTSTR lpCmdLine, int nShowCmd)
{
	HWND hWnd = FindWindow(TEXT("Shell_TrayWnd"), 0);
	if (IsWindowVisible(hWnd))
		ShowWindow(hWnd, SW_HIDE);
	else
		ShowWindow(hWnd, SW_SHOW);
	return 0;
}
