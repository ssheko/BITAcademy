#include <windows.h>
#include <tchar.h>
#include "resource.h"
// ������Ʈ�� ���� �ʿ��� ���
//#include <CommCtrl.h>
//#pragma comment(lib, "comctl32.lib")

BOOL CALLBACK DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		// Dialog�� ó�� ��Ÿ�� �� �߻�. �� ��Ʈ���� �ʱ�ȭ�Ѵ�.
	case WM_INITDIALOG:
	{
	}
	return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDCANCEL:
			EndDialog(hDlg, IDCANCEL);
			return 0;
		}
		return TRUE;
	}
	return FALSE;	// �޼��� ó���� ���� ���
}

int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrev, LPTSTR lpCmdLine, int nShowCmd)
{
	UINT ret = DialogBox(hInst,	// instance
		MAKEINTRESOURCE(IDD_DIALOG1),	// ���̾�α� ����
		0,	// �θ� ������
		DlgProc);	// Proc
	return 0;
}