#include <Windows.h>
#include <tchar.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_LBUTTONDOWN:
	{
		HDC hdc = GetDC(hwnd);

		// ȭ�� DC�� ȣȯ(���ϻ���)�Ǵ� �޸� DC�� ����
		HDC memDC = CreateCompatibleDC(hdc);
		HBITMAP hBitmap = LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDB_BITMAP1));
		BITMAP bm;

		GetObject(hBitmap, sizeof(bm), &bm);

		// �޸� DC�� ��Ʈ�� ����
		SelectObject(memDC, hBitmap);

		// ��Ʈ������ ���
		TextOut(memDC, 5, 5, TEXT("LoadBitmap���� ���"), 15);

		// �޸� DC -> ȭ�� DC//
		POINTS pt = MAKEPOINTS(lParam);
		BitBlt(hdc, pt.x, pt.y, bm.bmWidth, bm.bmHeight, memDC, 0, 0, SRCCOPY);
		
		// �޸� ����
		DeleteDC(memDC);
		ReleaseDC(hwnd, hdc);
		DeleteObject(hBitmap);
	}
	return 0;
	case WM_RBUTTONDOWN:
	{
		HDC hdc = GetDC(hwnd);

		// ȭ�� DC�� ȣȯ(���ϻ���)�Ǵ� �޸� DC�� ����
		HDC memDC = CreateCompatibleDC(hdc);
		HBITMAP hBitmap = (HBITMAP)LoadImage(0,	// ���ҽ����� �ε��� ���� ���
			TEXT("bit24.bmp"), IMAGE_BITMAP,
			0, 0,	// Ŀ��, Icon, load�ø� ���
			LR_LOADFROMFILE);
		BITMAP bm;
		GetObject(hBitmap, sizeof(bm), &bm);

		// �޸� DC�� ��Ʈ�� ����
		SelectObject(memDC, hBitmap);

		// ��Ʈ������ ���
		TextOut(memDC, 5, 5, TEXT("LoadImage�� ���"), 13);

		// �޸� DC -> ȭ�� DC//
		POINTS pt = MAKEPOINTS(lParam);
		BitBlt(hdc, pt.x, pt.y, bm.bmWidth, bm.bmHeight, memDC, 0, 0, SRCCOPY);

		// �޸� ����
		DeleteDC(memDC);
		ReleaseDC(hwnd, hdc);
		DeleteObject(hBitmap);
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