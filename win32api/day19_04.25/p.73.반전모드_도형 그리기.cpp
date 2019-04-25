#include <windows.h>
#include <tchar.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static POINTS start, end;
	switch (msg)
	{
	case WM_LBUTTONDOWN:
		start = end = MAKEPOINTS(lParam);
		SetCapture(hwnd);
		return 0;

	case WM_LBUTTONUP:
		if (GetCapture() == hwnd)
		{
			ReleaseCapture();	// ĸ�� �Ҵ� ����. ��ȭ���� ���´�.
			// �������� R2_COPYPEN���� �׷��� �Ѵ�.
			// Ȯ���ϰ� �׷��ֱ� ����. MOVE���� �׷��� �� ���� �� �����ϱ�.
			// end = pt�� �������ϱ� ������ ���� �κ�����\
			move���� �׸� �簢������ ��� �����鼭 ������ �簢���� ���������� �׸�.
			HDC hdc = GetDC(hwnd);	// ����Ʈ �׸��� ��尡 R2_COPYPEN
			SelectObject(hdc, GetStockObject(NULL_BRUSH));	// NULL_BRUSH: ���� �귯��. NULL_BRUSH�� �׸��� �ƹ��͵� �׷����� ����.
			Rectangle(hdc, start.x, start.y, end.x, end.y);
			ReleaseDC(hwnd, hdc);
		}
		return 0;
	case WM_MOUSEMOVE:
		if (GetCapture() == hwnd)	// ĸ�����϶���
		{
			POINTS pt = MAKEPOINTS(lParam);
			HDC hdc = GetDC(hwnd);
			SetROP2(hdc, R2_NOTXORPEN);	// �׸��� ��� ����	//R2_NOTXORPEN
			SelectObject(hdc, GetStockObject(NULL_BRUSH));
			Rectangle(hdc, start.x, start.y, end.x, end.y);
			Rectangle(hdc, start.x, start.y, pt.x, pt.y);	// �����ٰ� ���� �׸��� ������
			end = pt;	// ���� ���� Old�� ����
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