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
			// ������ �޴��� �ڵ� ���
			hMenu = GetMenu(hwnd);

			// �������� �޴� ����. 0�̹Ƿ� �޴��� �Ҹ��.
			SetMenu(hwnd, 0);
		}
		return 0;
	case WM_RBUTTONDOWN:
		if (hMenu != 0)
		{
			// �������� �޴� ����. hMenu
			SetMenu(hwnd, hMenu);
			hMenu = 0;
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
	//wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);	// 1��° ���
	wc.lpszMenuName = 0;	// 2��° ���
	wc.style = 0;

	// 2.��� (������Ʈ��)
	RegisterClass(&wc);

	// 3. ������ â �����
	//HWND hwnd = CreateWindowEx(0,	// WS_EX_TOPMOST
	//	TEXT("first"),				// Ŭ���� ��
	//	TEXT("Hello"),				// ĸ�ǹ� ����
	//	WS_OVERLAPPEDWINDOW,
	//	CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,	// �ʱ� ��ġ
	//	0, 0,						// �θ� ������ �ڵ�, �޴� �ڵ�
	//	hInst,						// WinMain�� 1��° �Ķ���� (exe �ּ�)
	//	0);							// ���� ����


		// 2��° ���
	HMENU hMenu = LoadMenu(hInst, MAKEINTRESOURCE(IDR_MENU1));
	HWND hwnd = CreateWindowEx(0, TEXT("first"), TEXT("Hello"),
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,
		0, hMenu,
		hInst, 0);
	SetMenu(hwnd, hMenu);

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