#include <windows.h>
#include <tchar.h>
#include "resource.h"

#define IDC_BUTTON 1
#define IDC_EDIT 2
#define IDC_LISTBOX 3

HWND hBtn, hEdit, hListBox;


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
		// ������� ����� ������ createwindow�� �����ؾ� ��.
		hEdit = CreateWindow(TEXT("Edit"), TEXT(""),	// Ŭ������, �������
			WS_CHILD | WS_VISIBLE | WS_BORDER,			// dwStyle
			10, 10, 90, 20, hwnd, (HMENU)IDC_EDIT, 0, 0);
		hBtn = CreateWindow(TEXT("button"), TEXT("Push"),
			WS_CHILD | WS_VISIBLE | WS_BORDER,
			10, 40, 90, 20, hwnd, (HMENU)IDC_BUTTON, 0, 0);
		hListBox = CreateWindow(TEXT("listbox"), TEXT(""),
			WS_CHILD | WS_VISIBLE | WS_BORDER,
			150, 10, 90, 90, hwnd, (HMENU)IDC_LISTBOX, 0, 0);	// ��ǥ(x, y, width, height)

		// Edit�� �Է� �޴� ���� ������ �����Ѵ�. - �޼����� ������.
		SendMessage(hEdit, EM_LIMITTEXT, 5, 0);

		// ListBox�� �׸��� �߰��Ѵ�.
		SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)TEXT("AAAA"));
		SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)TEXT("BBBB"));
	return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam))	// ID ����
		{
		case IDC_EDIT:	// EditBox�� ���� ���
			if (HIWORD(wParam) == EN_CHANGE)	// ���� �ڵ� ����
			{
				TCHAR s[256];
				GetWindowText(hEdit, s, 256);	// Edit���� ���� ��´�.
				SetWindowText(hwnd, s);	// �θ� �������� ĸ���� �����Ѵ�.
			}
			break;
		case IDC_BUTTON:
			if (HIWORD(wParam) == BN_CLICKED) // ��ư�� ���� �� ������ ���� �ڵ�
			{
				TCHAR s[256];
				GetWindowText(hEdit, s, sizeof(s));
				SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)s);
			}
			break;
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