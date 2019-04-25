#include <Windows.h>
#include <stdio.h>

#define WM_MYMESSAGE WM_USER+100
//
//void main()
//{
//	HWND hwnd = FindWindow(0, TEXT("Hello"));
//	int value = SendMessage(hwnd, WM_MYMESSAGE, 10, 20);
//	printf("%d\n", value);
//}
void main()
{
	HWND hwnd = FindWindow(0, TEXT("Hello"));
	BOOL b = PostMessage(hwnd, WM_MYMESSAGE, 10, 20);
	if (b)
	{
		printf("전송 되었습니다.\n");
	}

	printf("프로그램을 종료합니다.\n");

}