#include <windows.h>
#include <tchar.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static HMENU hMenu = 0;
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_LBUTTONDOWN:
		if (hMenu == 0)
		{
			HMENU h = GetMenu(hwnd);

			// 1. 메뉴 추가, 기존 메뉴 아래에 서브메뉴 추가
			// 메뉴 추가. 어디에 추가되는가?	
			//AppendMenu(h, MF_POPUP, 5000, TEXT("추가메뉴"));	// 5000 = ID값
			//HMENU h1 = GetSubMenu(h, 2);
			//AppendMenu(h1, MF_STRING, 5001, TEXT("BBB"));
			//AppendMenu(h1, MF_SEPARATOR, 5002, TEXT(""));

			// 2. 메뉴 및 서브 메뉴 추가 (인터넷 검색)
			//HMENU addMenu = CreateMenu();
			//AppendMenu(h, MF_POPUP, (UINT_PTR)addMenu, TEXT("추가메뉴"));	// 5000 = ID값
			////HMENU h1 = GetSubMenu(h, 2);
			//AppendMenu(addMenu, MF_STRING, 5001, TEXT("BBB"));
			//AppendMenu(addMenu, MF_SEPARATOR, 5002, TEXT(""));

			// 2. 메뉴 및 서브 메뉴 추가 (강사님 코드)
			HMENU hPopup = CreateMenu();
			//HMENU h1 = GetSubMenu(h, 2);
			AppendMenu(hPopup, MF_STRING, 5001, TEXT("BBB"));
			AppendMenu(hPopup, MF_SEPARATOR, 5002, TEXT(""));
			AppendMenu(h, MF_STRING | MF_POPUP, (UINT)hPopup, TEXT("추가메뉴"));	// 5000 = ID값


			// 메뉴바에 직접 추가한 경우에는 반드시 메뉴바를 다시 그려야 한다.
			DrawMenuBar(hwnd);

		}
		return 0;
	case WM_RBUTTONDOWN:
	{
		HMENU h = GetMenu(hwnd);
		HMENU hSub = GetSubMenu(h, 0);
		RemoveMenu(hSub, ID_MENU1_TEST2, MF_BYCOMMAND);
	}
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