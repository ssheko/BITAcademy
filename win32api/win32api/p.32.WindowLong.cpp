#include <windows.h>
#include <tchar.h>

#define MAX_LOADSTRING 100
TCHAR szTitle[MAX_LOADSTRING] = _TEXT("First Sample"); // 제목 표시줄
TCHAR szWindowClass[MAX_LOADSTRING] = _TEXT("BIT");    // 기본 창 클래스

//  함수: MyRegisterClass()
//  목적: 윈도우 클래스 생성 및 등록
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = DefWindowProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = 0;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = 0;
	return RegisterClassEx(&wcex);
}

//   함수: InitInstance(HINSTANCE, int)
//   목적: 윈도우 창을 만들고 핸들을 리턴
HWND InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
	if (!hWnd) {
		return 0;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}

BOOL fun_ModifyStylpe(HWND hwnd, LONG_PTR Add, LONG_PTR Remove, BOOL bRedraw)
{
	BOOL bFlag = FALSE;
	LONG_PTR style = GetWindowLongPtr(hwnd, GWL_STYLE);
	style |= Add;
	style &= ~Remove;
	bFlag = (BOOL)SetWindowLongPtr(hwnd, GWL_STYLE, style);
	if (bFlag  && bRedraw)
		SetWindowPos(hwnd, 0, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_DRAWFRAME);

	return bFlag;
}

int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrev, LPTSTR lpCmdLine, int nShowCmd)
{
	MyRegisterClass(hInst);
	HWND hwnd = InitInstance(hInst, nShowCmd);

	if (hwnd == 0)
		return FALSE;

	// 실시간 윈도우 객체 정보 수정
	HWND hWnd = FindWindow(0, _TEXT("제목 없음 - 그림판"));

	fun_ModifyStylpe(hWnd, WS_SYSMENU, WS_THICKFRAME,TRUE);
	MessageBox(0, TEXT("내용"), TEXT("제목"), MB_OK);	// 0, 내용, 제목
	return 0;
}