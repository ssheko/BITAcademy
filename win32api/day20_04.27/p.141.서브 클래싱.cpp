#include <windows.h>
#include <tchar.h>
#include "resource.h"

WNDPROC old;	// 원래의 EditBox의 메세지 처리함수의 주소를 담을 변수
/* 서브 클래싱
	윈도우 프로시저로 보내지는 메세지 가로채기
	*/
LRESULT CALLBACK foo(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg)
	{
	case WM_CHAR:
		if ((wParam >= '0' && wParam <= '9') || wParam == 8)	// 8은 backspace
			return CallWindowProc(old, hwnd, msg, wParam, lParam);
		return 0;	// 숫자 이외의 경우는 무시
	}
	// 나머지 모든 메세지는 원래의 함수로 전달
	return CallWindowProc(old, hwnd, msg, wParam, lParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static HWND hEdit;
	switch (msg)
	{
	case WM_CREATE:
		hEdit = CreateWindow(TEXT("edit"), TEXT(""), WS_CHILD | WS_VISIBLE | WS_BORDER,
			10, 10, 200, 200, hwnd, (HMENU)1, 0, 0);

		old = (WNDPROC)SetWindowLong(hEdit, GWL_WNDPROC, (LONG)foo);
		SetFocus(hEdit);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}
int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrev, LPTSTR lpCmdLine, int nShowCmd)
{
	WNDCLASS wc;
	wc.cbWndExtra = 0;
	wc.cbClsExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hInstance = hInst;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = TEXT("First");
	//wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);	// 1번째 방법
	wc.lpszMenuName = 0;	// 2번째 방법
	wc.style = 0;

	// 2.등록 (레지스트리)
	RegisterClass(&wc);

	// 3. 윈도우 창 만들기
	//HWND hwnd = CreateWindowEx(0,	// WS_EX_TOPMOST
	//	TEXT("first"),				// 클래스 명
	//	TEXT("Hello"),				// 캡션바 내용
	//	WS_OVERLAPPEDWINDOW,
	//	CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,	// 초기 위치
	//	0, 0,						// 부모 윈도우 핸들, 메뉴 핸들
	//	hInst,						// WinMain의 1번째 파라미터 (exe 주소)
	//	0);							// 생성 인자


		// 2번째 방법
	HMENU hMenu = LoadMenu(hInst, MAKEINTRESOURCE(IDR_MENU1));
	HWND hwnd = CreateWindowEx(0, TEXT("first"), TEXT("Hello"),
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,
		0, hMenu,
		hInst, 0);
	SetMenu(hwnd, hMenu);

	// 4. 윈도우 보여주기
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);

	// 5. Message
	MSG msg;
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}