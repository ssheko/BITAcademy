#include <Windows.h>
#include <tchar.h>

/* 윈도우 프로그램의 기본 구조 */
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("First");	// const char*

/*
	UNICODE: wWinMain	// UNICODE 외 다른 환경: WinMain
	lpszCmdparam: 매개인자 받는 변수.  -> UNICODE: wchar_t *	//// window: char*. 환경에 따라 알아서 컴파일
	WINAPI: C는 함수 호출 규악이 있음. WINAPI가 없을 경우 cdecl방식으로 함수 호출. WINAPI를 붙이면 stdcall 방식.
	WINAPI는 함수 호출 방식을 의미.
	nCmdShow: 윈도우를 생성할 때 normal하게 생성할 것인지, hide방식으로 할 것인지

	MSDN에서 함수호출 문서 확인. 그 뒤에 사용 예제 찾아볼 것
*/
int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpszCmdPara, int nCmdShow)	
{
	HWND hWnd;
	MSG Message;
	WNDCLASSEX WndClass;	// Window Class 구조체
	g_hInst = hInstance;

	// 윈도우 클래스 구조체에 속성 정의 시작
	WndClass.cbClsExtra = 0;	// future use 용. 현재 사용 x	// cb = count of bytes
	WndClass.cbWndExtra = 0;	// future use 용. 현재 사용 x
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	// 배경용 brush handle. 시스템에서 기본적으로 가져오는 옵션: GetStockObject. 모든 타입을 다 가져오는 거라서 HBRUSH타입으로 캐스팅
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);	// 커서 핸들. 시스템에서 기본적으로 제공하는 LoadCursor. IDC_ARROW: ID cursor의 arrow
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;		// lp: pointer, fn: function. 함수포인터. 모든 개발자가 관례적으로 윈도우 프로세서 WndProc을 사용.
	WndClass.lpszClassName = lpszClass;	// lp: pointer, sz: 문자열	// 윈도우 클래스 명
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;	// 가로, 세로가 사이즈가 변경될 때마다 다시 그리기. 윈도우의 기본 타입. OR연산 -> CS_HREDRAW, CS_VREDRAW가 비트연산으로 되어 있음.
	WndClass.hIconSm = 0;	// small Icon. 없으면 기본 아이콘 줄여서 씀
	WndClass.cbSize = sizeof(WNDCLASSEX);	// 내부적으로 구버전의 윈도우 클래스인지, 신버전인지 확인하려고. 사이즈를 비교하면 알 수 있음.
	// 여기까지가 윈도우 클래스 정보 담기 (속성 정의)

	RegisterClassEx(&WndClass);	// 윈도우 클래스를 Register함수로 등록
	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, (HMENU)NULL, hInstance, NULL);	// 등록된 window 만듬
	ShowWindow(hWnd, nCmdShow);	// 윈도우 생성
	//UpdateWindow(hWnd);	// 이젠 할 필요 없음.

	// 윈도우는 기본적으로 message driven 방식. 외부에서 이벤트 메세지가 들어오면 메세지에 따라 동작.
	// OS 자체 내에서 System Queue가 존재. OS 입장에서 받아들이는 모든 이벤트가 들어옴.
	// 각 애플리케이션마다 하나의 스레드가 존재. 스레드마다 thread Queue가 존재.
	// message Queue에서 메세지를 하나씩 꺼내옴
	while (GetMessage(&Message, NULL, 0, 0)) {	// WM_QUIT을 만나면 0을 리턴해줘서 while문을 나가게 됨
		TranslateMessage(&Message);
		DispatchMessage(&Message);	// LRESULT CALLBACK WndProc에 Message 호출. 메세지별로 알아서 처리하도록
	}

	return (int)Message.wParam;	// main이므로 의미 없는 리턴
}

/* 
	ATOM CreateWindow(lpszClassName, lpsWindowName, dwStyle, x, y, nWidth, nHeight, hwndParent, hmenu, hInst, lpvParam)
	ATOM: 절대 중복되지 않는 고유의 값을 넘겨줌.

	lpszClassName: 윈도우 클래스명
	lpsWindowName: 타이틀바 표시명
	dwStyle: 윈도우 스타일
	x, y, nWidth, nHeight: 윈도우 위치, 크기
	hwndParent: 부모 윈도우 핸들, NULL일 경우 데스크탑을 부모로 가짐. 바탕화면 어디든지 위치 가능
	hmenu: 윈도우에서 사용할 메뉴 핸들(윈도우 클래스에서 지정한 메뉴 사용시 NULL)
	hInst: 윈도우를 생성하는 주체
	lpvParam: CREATESTRUCT 구조체의 번지, 여러 개의 윈도우를 만들 때 각 윈도우에 고유의 패러미터를 전달하는 특수한 목적에 사용.
*/

/* 
	stdcall방식. CALLBACK 규약
	내부에서 호출해주는 함수라서 CALLBACK 방식.
	임의로 WndProc를 호출하는 게 아닌 내부에서 호출하는 것을 의미.

	hWnd: 윈도우 핸들	
	wParam: 핸들 또는 정수를 받을 때 주로 사용 (unsigned int) (4byte, 32bit를 모두 사용)
	lparam: 포인터 값 전달 (long) (총 32bit)
*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage) {
	case WM_DESTROY:	// WM: Window Message
		PostQuitMessage(0);	// message queue로 WM_QUIT메세지를 보냄.
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));	// 우리가 처리하지 않을 메세지를 default window procedure로 보냄
}