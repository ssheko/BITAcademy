#include <Windows.h>
#include <tchar.h>

/* ������ ���α׷��� �⺻ ���� */
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("First");	// const char*

/*
	UNICODE: wWinMain	// UNICODE �� �ٸ� ȯ��: WinMain
	lpszCmdparam: �Ű����� �޴� ����.  -> UNICODE: wchar_t *	//// window: char*. ȯ�濡 ���� �˾Ƽ� ������
	WINAPI: C�� �Լ� ȣ�� �Ծ��� ����. WINAPI�� ���� ��� cdecl������� �Լ� ȣ��. WINAPI�� ���̸� stdcall ���.
	WINAPI�� �Լ� ȣ�� ����� �ǹ�.
	nCmdShow: �����츦 ������ �� normal�ϰ� ������ ������, hide������� �� ������

	MSDN���� �Լ�ȣ�� ���� Ȯ��. �� �ڿ� ��� ���� ã�ƺ� ��
*/
int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpszCmdPara, int nCmdShow)	
{
	HWND hWnd;
	MSG Message;
	WNDCLASSEX WndClass;	// Window Class ����ü
	g_hInst = hInstance;

	// ������ Ŭ���� ����ü�� �Ӽ� ���� ����
	WndClass.cbClsExtra = 0;	// future use ��. ���� ��� x	// cb = count of bytes
	WndClass.cbWndExtra = 0;	// future use ��. ���� ��� x
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	// ���� brush handle. �ý��ۿ��� �⺻������ �������� �ɼ�: GetStockObject. ��� Ÿ���� �� �������� �Ŷ� HBRUSHŸ������ ĳ����
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);	// Ŀ�� �ڵ�. �ý��ۿ��� �⺻������ �����ϴ� LoadCursor. IDC_ARROW: ID cursor�� arrow
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;		// lp: pointer, fn: function. �Լ�������. ��� �����ڰ� ���������� ������ ���μ��� WndProc�� ���.
	WndClass.lpszClassName = lpszClass;	// lp: pointer, sz: ���ڿ�	// ������ Ŭ���� ��
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;	// ����, ���ΰ� ����� ����� ������ �ٽ� �׸���. �������� �⺻ Ÿ��. OR���� -> CS_HREDRAW, CS_VREDRAW�� ��Ʈ�������� �Ǿ� ����.
	WndClass.hIconSm = 0;	// small Icon. ������ �⺻ ������ �ٿ��� ��
	WndClass.cbSize = sizeof(WNDCLASSEX);	// ���������� �������� ������ Ŭ��������, �Ź������� Ȯ���Ϸ���. ����� ���ϸ� �� �� ����.
	// ��������� ������ Ŭ���� ���� ��� (�Ӽ� ����)

	RegisterClassEx(&WndClass);	// ������ Ŭ������ Register�Լ��� ���
	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, (HMENU)NULL, hInstance, NULL);	// ��ϵ� window ����
	ShowWindow(hWnd, nCmdShow);	// ������ ����
	//UpdateWindow(hWnd);	// ���� �� �ʿ� ����.

	// ������� �⺻������ message driven ���. �ܺο��� �̺�Ʈ �޼����� ������ �޼����� ���� ����.
	// OS ��ü ������ System Queue�� ����. OS ���忡�� �޾Ƶ��̴� ��� �̺�Ʈ�� ����.
	// �� ���ø����̼Ǹ��� �ϳ��� �����尡 ����. �����帶�� thread Queue�� ����.
	// message Queue���� �޼����� �ϳ��� ������
	while (GetMessage(&Message, NULL, 0, 0)) {	// WM_QUIT�� ������ 0�� �������༭ while���� ������ ��
		TranslateMessage(&Message);
		DispatchMessage(&Message);	// LRESULT CALLBACK WndProc�� Message ȣ��. �޼������� �˾Ƽ� ó���ϵ���
	}

	return (int)Message.wParam;	// main�̹Ƿ� �ǹ� ���� ����
}

/* 
	ATOM CreateWindow(lpszClassName, lpsWindowName, dwStyle, x, y, nWidth, nHeight, hwndParent, hmenu, hInst, lpvParam)
	ATOM: ���� �ߺ����� �ʴ� ������ ���� �Ѱ���.

	lpszClassName: ������ Ŭ������
	lpsWindowName: Ÿ��Ʋ�� ǥ�ø�
	dwStyle: ������ ��Ÿ��
	x, y, nWidth, nHeight: ������ ��ġ, ũ��
	hwndParent: �θ� ������ �ڵ�, NULL�� ��� ����ũž�� �θ�� ����. ����ȭ�� ������ ��ġ ����
	hmenu: �����쿡�� ����� �޴� �ڵ�(������ Ŭ�������� ������ �޴� ���� NULL)
	hInst: �����츦 �����ϴ� ��ü
	lpvParam: CREATESTRUCT ����ü�� ����, ���� ���� �����츦 ���� �� �� �����쿡 ������ �з����͸� �����ϴ� Ư���� ������ ���.
*/

/* 
	stdcall���. CALLBACK �Ծ�
	���ο��� ȣ�����ִ� �Լ��� CALLBACK ���.
	���Ƿ� WndProc�� ȣ���ϴ� �� �ƴ� ���ο��� ȣ���ϴ� ���� �ǹ�.

	hWnd: ������ �ڵ�	
	wParam: �ڵ� �Ǵ� ������ ���� �� �ַ� ��� (unsigned int) (4byte, 32bit�� ��� ���)
	lparam: ������ �� ���� (long) (�� 32bit)
*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage) {
	case WM_DESTROY:	// WM: Window Message
		PostQuitMessage(0);	// message queue�� WM_QUIT�޼����� ����.
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));	// �츮�� ó������ ���� �޼����� default window procedure�� ����
}