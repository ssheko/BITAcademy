#include <Windows.h>
#include <tchar.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_LBUTTONDOWN:
	{
		BOOL bPresent = GetSystemMetrics(SM_MOUSEPRESENT);
		BOOL bWheel = GetSystemMetrics(SM_MOUSEPRESENT);
		int nBtn = GetSystemMetrics(SM_CMOUSEBUTTONS);
		int scx = GetSystemMetrics(SM_CXSCREEN);
		int scy = GetSystemMetrics(SM_CYSCREEN);
		TCHAR info[128];

		wsprintf(info, _TEXT("%s %s is installed. (%d Buttons)\n"),
			(bWheel ? _TEXT("Wheel") : _TEXT("")), (bPresent ? _TEXT("Mouse") : _TEXT("No Mouse")), nBtn);


		TCHAR temp[64];
		wsprintf(temp, _TEXT("\NnScreen Resolution : %d * %d"), scx, scy);
		// strcat(d, s)	// s보다 d의 사이즈가 더 적어도 복사. d늬 배열 뒤에 s가 들어감.
		// strcat_s(d, c, s) // 사이즈를 넣어주므로 s가 아무리 긴게 들어와도 count개수만큼만 복사.
		wcscat(info, temp);
		MessageBox(NULL, info, TEXT(""), MB_OK);

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