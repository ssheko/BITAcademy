#include <Windows.h>
#include <tchar.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static POINTS start, end;
	static BOOL bNowDraw = FALSE;
	switch (msg)
	{
	case WM_LBUTTONDOWN:
	{
		start = MAKEPOINTS(lParam);
		end = start;
		bNowDraw = TRUE;
	}

	return 0;

	case WM_MOUSEMOVE:
	{
		if (bNowDraw)
		{
			HDC hdc = GetDC(hwnd);
			SetROP2(hdc, R2_NOT);	// R2_NOT: 원래의 그림을 반전시킨다	// 이전의 선들을 지우면서 이동
			// 그릴 영역, 시작 지점 x, y, 이전 포지션을 받는 POINT struct의 포인터 (NULL일 경우 이전 포지션이 리턴되지 않음)
			MoveToEx(hdc, start.x, start.y, NULL);
			LineTo(hdc, end.x, end.y);

			end = MAKEPOINTS(lParam);
			MoveToEx(hdc, start.x, start.y, NULL);
			LineTo(hdc, end.x, end.y);
			ReleaseDC(hwnd, hdc);
		}
	}
	return 0;
	case WM_LBUTTONUP:
	{
		bNowDraw = FALSE;
		HDC hdc = GetDC(hwnd);
		MoveToEx(hdc, start.x, start.y, NULL);
		LineTo(hdc, end.x, end.y);
		ReleaseDC(hwnd, hdc);
	}
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}



int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrev, LPTSTR lpCmdLine, int nShowCmd)
{
	// 1. 윈도우 클래스 만들기
	WNDCLASS wc;
	wc.cbWndExtra = 0;
	wc.cbClsExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hInstance = hInst;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = TEXT("First");
	wc.lpszMenuName = 0;
	wc.style = 0;

	// 2. 등록 (레지스트리에)
	RegisterClass(&wc);

	// 3. 윈도우 창 만들기
	HWND hwnd = CreateWindowEx(0,	// WS_EX_TOPMOST
		TEXT("first"),				// 클래스 명
		TEXT("Hello"),				// 캡션바 내용
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,	// 초기 위치
		0, 0,						// 부모 윈도우 핸들, 메뉴 핸들
		hInst,						// WinMain의 1번째 파라미터 (exe 주소)
		0);							// 생성 인자

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