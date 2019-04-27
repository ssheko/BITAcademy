#include <windows.h>
#include <tchar.h>
#include "resource.h"
// 공용컨트롤 사용시 필요한 헤더
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
		// Dialog가 처음 나타날 때 발생. 각 컨트롤을 초기화한다.
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
	return FALSE;	// 메세지 처리를 안한 경우
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_LBUTTONDOWN:
	{
		DATA data = { TEXT("홍길동"), 20 };
		UINT ret = DialogBoxParam(GetModuleHandle(0),	// hinstance
			MAKEINTRESOURCE(IDD_DIALOG1),
			hwnd, // 부모
			DlgProc,	// 메세지 함수
			(LPARAM)&data);	// WM_INITDIALOG의 lParam으로 전달된다.
		if (ret == IDOK)
		{
			// 이제 Dialog에 입력한 값은 data에 있다.
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
	//wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);	// 1번째 방법
	wc.lpszMenuName = 0;	// 2번째 방법
	wc.style = 0;

	// 2.등록 (레지스트리)
	RegisterClass(&wc);

	// 3. 윈도우 창 만들기
	HWND hwnd = CreateWindowEx(0,	// WS_EX_TOPMOST
		TEXT("first"),				// 클래스 명
		TEXT("Hello"),				// 캡션바 내용
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,	// 초기 위치
		0, 0,						// 부모 윈도우 핸들, 메뉴 핸들
		hInst,						// WinMain의 1번째 파라미터 (exe 주소)
		0);							// 생성 인자



	// 4. 윈도우 보여주기
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