#include <windows.h>
#include <tchar.h>

#define MAX_LOADSTRING 100
TCHAR szTitle[MAX_LOADSTRING] = _TEXT("First Sample"); // ���� ǥ����
TCHAR szWindowClass[MAX_LOADSTRING] = _TEXT("BIT");    // �⺻ â Ŭ����

//  �Լ�: MyRegisterClass()
//  ����: ������ Ŭ���� ���� �� ���
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = DefWindowProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = 0;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = 0;
	return RegisterClassEx(&wcex);
}

//   �Լ�: InitInstance(HINSTANCE, int)
//   ����: ������ â�� ����� �ڵ��� ����
HWND InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
	if (!hWnd) {
		return 0;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}

BOOL fun_ModifyStylpe(HWND hwnd, LONG_PTR Add, LONG_PTR Remove, BOOL bRedraw)
{
	BOOL bFlag = FALSE;
	LONG_PTR style = GetWindowLongPtr(hwnd, GWL_STYLE);
	style |= Add;
	style &= ~Remove;
	bFlag = (BOOL)SetWindowLongPtr(hwnd, GWL_STYLE, style);
	if (bFlag  && bRedraw)
		SetWindowPos(hwnd, 0, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_DRAWFRAME);

	return bFlag;
}

int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrev, LPTSTR lpCmdLine, int nShowCmd)
{
	MyRegisterClass(hInst);
	HWND hwnd = InitInstance(hInst, nShowCmd);

	if (hwnd == 0)
		return FALSE;

	// �ǽð� ������ ��ü ���� ����
	HWND hWnd = FindWindow(0, _TEXT("���� ���� - �׸���"));

	fun_ModifyStylpe(hWnd, WS_SYSMENU, WS_THICKFRAME,TRUE);
	MessageBox(0, TEXT("����"), TEXT("����"), MB_OK);	// 0, ����, ����
	return 0;
}