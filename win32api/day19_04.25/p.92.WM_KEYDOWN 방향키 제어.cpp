#include <Windows.h>
#include <tchar.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static POINTS pt = { 100, 100 };

	switch (msg)
	{
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_LEFT: pt.x -= 10; break;
		case VK_RIGHT: pt.x += 10; break;
		case VK_UP:		pt.y -= 10; break;
		case VK_DOWN:   pt.y += 10; break;
		}
		HDC hdc = GetDC(hwnd);
		TextOut(hdc, pt.x, pt.y, TEXT("#"), 1);
		ReleaseDC(hwnd, hdc);
	}
	return 0;
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