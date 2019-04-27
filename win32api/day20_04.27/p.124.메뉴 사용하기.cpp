#include <windows.h>
#include <tchar.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static int submenu1 = ID_MENU1_TEST1;
	static int submenu2 = ID_MENU2_TEST4;
	switch (msg)
	{
		// POPUP �޴��� �������� ����
	case WM_INITMENUPOPUP: {
		HMENU hMenu = (HMENU)wParam;
		// CheckMenuItem(HMENU hMenu, UINT uIDcheckItem, UINT uCheck)
		CheckMenuItem(hMenu, ID_MENU1_TEST1,
			submenu1 == ID_MENU1_TEST1 ? MF_CHECKED : MF_UNCHECKED);
		
		CheckMenuItem(hMenu, ID_MENU1_TEST2,
			submenu1 == ID_MENU1_TEST2 ? MF_CHECKED : MF_UNCHECKED);
		CheckMenuItem(hMenu, ID_MENU1_TEST3,
			submenu1 == ID_MENU1_TEST3 ? MF_CHECKED : MF_UNCHECKED);

		// EnableMenuItem(HMENU hMenu, UINT uIDEnableItem, UINT uEnable)
		EnableMenuItem(hMenu, ID_MENU2_TEST4,
			submenu2 == ID_MENU2_TEST4 ? MF_GRAYED : MF_ENABLED);
		EnableMenuItem(hMenu, ID_MENU2_TEST5,
			submenu2 == ID_MENU2_TEST5 ? MF_GRAYED : MF_ENABLED);
		EnableMenuItem(hMenu, ID_MENU2_TEST6,
			submenu2 == ID_MENU2_TEST6 ? MF_GRAYED : MF_ENABLED);

	}
	return 0;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))	// ID ����
		{
		case ID_MENU1_TEST1:
			SetWindowText(hwnd, TEXT("ID_MENU1_TEST1"));
			submenu1 = ID_MENU1_TEST1;
			break;
		case ID_MENU1_TEST2:
			SetWindowText(hwnd, TEXT("ID_MENU1_TEST2"));
			submenu1 = ID_MENU1_TEST2;
			break;
		case ID_MENU1_TEST3:
			SetWindowText(hwnd, TEXT("ID_MENU1_TEST3"));
			submenu1 = ID_MENU1_TEST3;
			break;
		case ID_MENU2_TEST4:
			SetWindowText(hwnd, TEXT("ID_MENU2_TEST4"));
			submenu2 = ID_MENU2_TEST4;
			break;
		case ID_MENU2_TEST5:
			SetWindowText(hwnd, TEXT("ID_MENU2_TEST5"));
			submenu2 = ID_MENU2_TEST5;
			break;
		case ID_MENU2_TEST6:
			SetWindowText(hwnd, TEXT("ID_MENU2_TEST6"));
			submenu2 = ID_MENU2_TEST6;
			break;
		}
		return 0;
	}
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