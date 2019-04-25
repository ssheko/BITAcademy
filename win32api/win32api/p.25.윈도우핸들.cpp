#include <windows.h>
#include <tchar.h>
//
//int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrev, LPTSTR lpCmdLine, int nShowCmd)
//{
//	HWND hwnd = FindWindow(0, _TEXT("계산기"));
//	if (hwnd == 0) {
//		MessageBox(0, _TEXT("계산기 핸들을 얻을 수 없습니다."),
//			_TEXT("알림"), MB_OK | MB_ICONERROR);
//		return 0;
//	}
//	else {
//		TCHAR temp[20];
//		wsprintf(temp, _TEXT("계산기 핸들 : %d"), hwnd);
//		MessageBox(0, temp, _TEXT("알림"), MB_OK);
//	}
//	return 0;
//}

int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrev, LPTSTR lpCmdLine, int nShowCmd)
{
	HWND hwnd = FindWindow(0, _TEXT("계산기"));
	//계산기 클래스 이름 및 Rect 얻기
	TCHAR name[60];
	RECT rcCalc;
	GetClassName(hwnd, name, sizeof(name));
	GetWindowRect(hwnd, &rcCalc);	// 해당 윈도우의 영역을 가져옴

	//정보 출력	
	TCHAR info[256];
	wsprintf(info, _TEXT("클래스 명 : %s\n위치 : %d,%d ~ %d,%d"), name,
		rcCalc.left, rcCalc.top, rcCalc.right, rcCalc.bottom);
	MessageBox(0, info, TEXT("계산기 정보"), MB_OK);

	//계산기 이동하기
	MoveWindow(hwnd, 10, 10, rcCalc.right - rcCalc.left, rcCalc.bottom - rcCalc.top, TRUE);

	//계산기 숨기기
	MessageBox(0, _TEXT("계산기"), TEXT("계산기 숨기기"), MB_OK);
	ShowWindow(hwnd, SW_HIDE);
	
	//계산기 보이기
	MessageBox(0, _TEXT("계산기"), TEXT("계산기 보이기"), MB_OK);
	ShowWindow(hwnd, SW_SHOW);

	//계산기 종료하기
	MessageBox(0, _TEXT("계산기"), TEXT("계산기 종료하기"), MB_OK);
	SendMessage(hwnd, WM_CLOSE, 0, 0);

	return 0;
}
