#include <windows.h>
#include <tchar.h>
#include "resource.h"
// ������Ʈ�� ���� �ʿ��� ���
#include <CommCtrl.h>
#pragma comment(lib, "comctl32.lib")

typedef struct tagDATA {
	TCHAR str[20];
	int num;
}DATA;

BOOL CALLBACK DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static DATA *pData;
	switch (msg)
	{
		// Dialog�� ó�� ��Ÿ�� �� �߻�. �� ��Ʈ���� �ʱ�ȭ�Ѵ�.
	case WM_INITDIALOG:
	{
		pData = (DATA*)lParam;
		SetDlgItemText(hDlg, IDC_EDIT1, pData->str);
		SetDlgItemInt(hDlg, IDC_EDIT2, pData->num, 0);		
	}
	break;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDOK:
			GetDlgItemText(hDlg, IDC_EDIT1, pData->str, sizeof(pData->str));
			pData->num = GetDlgItemInt(hDlg, IDC_EDIT2, 0, 0);
			EndDialog(hDlg, IDOK);
			return TRUE;
		case IDCANCEL:
			EndDialog(hDlg, IDCANCEL);
			return TRUE;
		}
	}
	return FALSE;	// �޼��� ó���� ���� ���
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_LBUTTONDOWN:
	{
		DATA data = { TEXT("ȫ�浿"), 20 };
		UINT ret = DialogBoxParam(GetModuleHandle(0),	// hinstance
			MAKEINTRESOURCE(IDD_DIALOG1),
			hwnd, // �θ�
			DlgProc,	// �޼��� �Լ�
			(LPARAM)&data);	// WM_INITDIALOG�� lParam���� ���޵ȴ�.
		if (ret == IDOK)
		{
			// ���� Dialog�� �Է��� ���� data�� �ִ�.
			TCHAR buf[128];
			wsprintf(buf, TEXT("%s / %d"), data.str, data.num);
			SetWindowText(hwnd, buf);
		 }
			
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