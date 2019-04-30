// CalcDLL.cpp : DLL의 초기화 루틴을 정의합니다.
//

#include "stdafx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// __declspec: def 파일을 안 건들이고 외부에서 이 함수를 부를 수 있음.
int WINAPI Calculate(int fir, int sec, CString &op)	//
{
	int result = 0;
	switch (*op)
	{
	case '+':
		result = fir + sec;
		break;
	case '-':
		result = fir - sec;
		break;
	case '*':
		result = fir * sec;
		break;
	case '/':
		result = fir / sec;
		break;
	default:
		result = 0;
		break;
	}
	return result;
}