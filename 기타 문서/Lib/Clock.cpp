//#include "pch.h"
#include "Clock.h"

void Clock::GetTimeString(wstring * timeStr)
{
	tm * now = new tm;
	time(&_tick);
	localtime_s(now, &_tick);
	WCHAR buffer[34];
	swprintf_s(buffer, 34, L"%04d-%02d-%02d %02d:%02d:%02d :: ",
		now->tm_year + 1900,   // tm_year�� 1900�� ���ؾ� ���� ������ ��
		now->tm_mon + 1, // tm_mon�� 1���� 0, 2���� 1... ������ �Ǿ� ���� 
		now->tm_mday,
		now->tm_hour,
		now->tm_min,
		now->tm_sec);
	*timeStr += buffer;
	delete now;
}
Clock * Clock::_instance = nullptr;
