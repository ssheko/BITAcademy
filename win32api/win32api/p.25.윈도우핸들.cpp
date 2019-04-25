#include <windows.h>
#include <tchar.h>
//
//int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrev, LPTSTR lpCmdLine, int nShowCmd)
//{
//	HWND hwnd = FindWindow(0, _TEXT("����"));
//	if (hwnd == 0) {
//		MessageBox(0, _TEXT("���� �ڵ��� ���� �� �����ϴ�."),
//			_TEXT("�˸�"), MB_OK | MB_ICONERROR);
//		return 0;
//	}
//	else {
//		TCHAR temp[20];
//		wsprintf(temp, _TEXT("���� �ڵ� : %d"), hwnd);
//		MessageBox(0, temp, _TEXT("�˸�"), MB_OK);
//	}
//	return 0;
//}

int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrev, LPTSTR lpCmdLine, int nShowCmd)
{
	HWND hwnd = FindWindow(0, _TEXT("����"));
	//���� Ŭ���� �̸� �� Rect ���
	TCHAR name[60];
	RECT rcCalc;
	GetClassName(hwnd, name, sizeof(name));
	GetWindowRect(hwnd, &rcCalc);	// �ش� �������� ������ ������

	//���� ���	
	TCHAR info[256];
	wsprintf(info, _TEXT("Ŭ���� �� : %s\n��ġ : %d,%d ~ %d,%d"), name,
		rcCalc.left, rcCalc.top, rcCalc.right, rcCalc.bottom);
	MessageBox(0, info, TEXT("���� ����"), MB_OK);

	//���� �̵��ϱ�
	MoveWindow(hwnd, 10, 10, rcCalc.right - rcCalc.left, rcCalc.bottom - rcCalc.top, TRUE);

	//���� �����
	MessageBox(0, _TEXT("����"), TEXT("���� �����"), MB_OK);
	ShowWindow(hwnd, SW_HIDE);
	
	//���� ���̱�
	MessageBox(0, _TEXT("����"), TEXT("���� ���̱�"), MB_OK);
	ShowWindow(hwnd, SW_SHOW);

	//���� �����ϱ�
	MessageBox(0, _TEXT("����"), TEXT("���� �����ϱ�"), MB_OK);
	SendMessage(hwnd, WM_CLOSE, 0, 0);

	return 0;
}
