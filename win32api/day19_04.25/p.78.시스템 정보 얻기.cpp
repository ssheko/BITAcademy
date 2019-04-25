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
		// strcat(d, s)	// s���� d�� ����� �� ��� ����. d�� �迭 �ڿ� s�� ��.
		// strcat_s(d, c, s) // ����� �־��ֹǷ� s�� �ƹ��� ��� ���͵� count������ŭ�� ����.
		wcscat(info, temp);
		MessageBox(NULL, info, TEXT(""), MB_OK);

	}
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrev, LPTSTR lpCmdLine, int nShowCmd)
{
	// 1. ������ Ŭ���� �����
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

	// 2. ��� (������Ʈ����)
	RegisterClass(&wc);

	// 3. ������ â �����
	HWND hwnd = CreateWindowEx(0,	// WS_EX_TOPMOST
		TEXT("first"),				// Ŭ���� ��
		TEXT("Hello"),				// ĸ�ǹ� ����
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,	// �ʱ� ��ġ
		0, 0,						// �θ� ������ �ڵ�, �޴� �ڵ�
		hInst,						// WinMain�� 1��° �Ķ���� (exe �ּ�)
		0);							// ���� ����

	// 4. ������ �����ֱ�
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