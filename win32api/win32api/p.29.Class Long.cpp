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


int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrev, LPTSTR lpCmdLine, int nShowCmd)
{
	MyRegisterClass(hInst);
	HWND hwnd = InitInstance(hInst, nShowCmd);
	if (hwnd == 0) { return FALSE; }

	//실시간 클래스 정보 수정
	MessageBox(0, TEXT("실시간 정보 수정"), TEXT("First"), MB_OK);
	SetClassLongPtr(hwnd, GCLP_HBRBACKGROUND, (LONG)GetStockObject(DKGRAY_BRUSH));	// GCLP_HBRBACKGROUND: 윈도우클래스에 있는 배경 정보 -> 다크그레이 색으로 변경
	InvalidateRect(hwnd, NULL, TRUE);	// 사각형 범위. NULL일 경우 윈도우의 전체 영역을 의미. 윈도우 전체 영역을 무효화시켜서 강제로 다시 그리게 한다
	MessageBox(0, TEXT("Hello,API"), TEXT("First"), MB_OK);

	//실시간 클래스 정보 획득
	TCHAR temp[126];
	DWORD flag = GetClassLongPtr(hwnd, GCLP_HBRBACKGROUND);
	// getRValue: 총 4개의 byte 중 맨 아래쪽 byte 가져옴. [alpha, B, G, R]
	wsprintf(temp, _TEXT("R : %d, G : %d : B : %d"), GetRValue(flag), GetGValue(flag), GetBValue(flag));	// sprintf의 윈도우 버전
	MessageBox(0, temp, TEXT("획득정보"), MB_OK);
	return 0;
}