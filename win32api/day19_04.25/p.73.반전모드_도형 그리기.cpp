#include <windows.h>
#include <tchar.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static POINTS start, end;
	switch (msg)
	{
	case WM_LBUTTONDOWN:
		start = end = MAKEPOINTS(lParam);
		SetCapture(hwnd);
		return 0;

	case WM_LBUTTONUP:
		if (GetCapture() == hwnd)
		{
			ReleaseCapture();	// 캡쳐 할당 해제. 도화지를 찢는다.
			// 최종선은 R2_COPYPEN으로 그려야 한다.
			// 확실하게 그려주기 위해. MOVE에서 그려진 게 남을 수 있으니까.
			// end = pt를 해줬으니까 마지막 끝난 부분으로\
			move에서 그린 사각형들을 모두 덮으면서 마지막 사각형을 최종적으로 그림.
			HDC hdc = GetDC(hwnd);	// 디폴트 그리기 모드가 R2_COPYPEN
			SelectObject(hdc, GetStockObject(NULL_BRUSH));	// NULL_BRUSH: 투명 브러쉬. NULL_BRUSH로 그리면 아무것도 그려지지 않음.
			Rectangle(hdc, start.x, start.y, end.x, end.y);
			ReleaseDC(hwnd, hdc);
		}
		return 0;
	case WM_MOUSEMOVE:
		if (GetCapture() == hwnd)	// 캡쳐중일때만
		{
			POINTS pt = MAKEPOINTS(lParam);
			HDC hdc = GetDC(hwnd);
			SetROP2(hdc, R2_NOTXORPEN);	// 그리기 모드 변경	//R2_NOTXORPEN
			SelectObject(hdc, GetStockObject(NULL_BRUSH));
			Rectangle(hdc, start.x, start.y, end.x, end.y);
			Rectangle(hdc, start.x, start.y, pt.x, pt.y);	// 지웠다가 새로 그리기 때문에
			end = pt;	// 현재 점을 Old에 보관
			ReleaseDC(hwnd, hdc);
		}
		return 0;
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