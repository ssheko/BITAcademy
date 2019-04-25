#include <Windows.h>
#include <tchar.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static HCURSOR h1 = LoadCursorFromFile(TEXT("C:\\windows\\cursors\\size1_i.cur"));
	static HCURSOR h2 = LoadCursorFromFile(TEXT("C:\\windows\\cursors\\size1_il.cur"));
	static RECT rc = { 100, 100, 300, 300 };	// Ŭ���̾�Ʈ ��ǥ

	switch (msg)
	{
	case WM_SETCURSOR:
	{
		int code = LOWORD(lParam); // hit test code�� ��� �ִ�.
		POINT pt;
		GetCursorPos(&pt);	// ���� Ŀ���� ��ġ (��ũ�� ��ǥ)
		ScreenToClient(hwnd, &pt);	// ��ũ�� ��ǥ�� Ŭ���̾�Ʈ ��ǥ��
		//Ŭ���̾�Ʈ �ȿ����� Ư�� ��ġ������ �ٸ� Ŀ���� ����ϴ� ���
		if (code == HTCLIENT && PtInRect(&rc, pt))
		{
			SetCursor(LoadCursor(0, IDC_ARROW));
			return TRUE;
		}

		// �� ���� client������ DefWindowProc�� ������ �� ��.
		if (code == HTLEFT || code == HTRIGHT)
		{
			SetCursor(h2);
			return TRUE;	// Ŀ���� ������ ��� TRUE ����
		}
		else if (code == HTTOP || code == HTBOTTOM)
		{
			SetCursor(h1);
			return TRUE;
		}

	}
	// ���� �������� ���� �ٸ� �κ��� �����ϱ� ���� �Ʒ� �Լ���
	// �ݵ�� ������ �Ѵ�.
	return DefWindowProc(hwnd, msg, wParam, lParam);
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