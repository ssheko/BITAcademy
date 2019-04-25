#include <windows.h>
#include <tchar.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_PAINT:
	{
		TCHAR str[] = TEXT("�� ��° �μ��� ����� ������ ��� �ִ� ����ü �������̴�.�ټ���° �μ��� DrawText �Լ��� ���ڿ��� ����� ����������ϴ� �÷����̸� ������ ���� ���� ���� �÷����� ������ �����Ѵ�.");
		RECT rt = { 100, 100, 400, 300 };
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		// DrawText(HDC hdc, LPCSTR lpString, int nCount, LPRECT lpRect, UINT uFormat);
		// 3��° �μ�: ����� ���ڿ��� ����. -1�� �����ϸ� �� ���� ���ڿ��� ����. ���ڿ� ��� ��ٷ� ��� ����
		// 4��° �μ�: ����� ������ ��� �ִ� ����ü ������.
		// 5��° �μ�: ���ڿ��� ����� ����� �����ϴ� �÷���
		DrawText(hdc, str, -1, &rt, DT_CENTER | DT_WORDBREAK);
		EndPaint(hwnd, &ps);
	}
	return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
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