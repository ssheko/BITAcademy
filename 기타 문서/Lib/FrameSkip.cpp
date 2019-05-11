#pragma once
//#include "stdafx.h"
//#include "pch.h"
#include "FrameSkip.h"

//////////////////////////////////////////////////////////////
// class : public class
//////////////////////////////////////////////////////////////

/*----------------------------------------------------------*/
// FrameSkip::FrameSkip (public)
// ���� : �����ӽ�ŵ ������
//  ��  : timeBeginPeriod(1)�� ȣ���Ѵ�.
// ���� : (int) �ʴ� ������ ��
// ���� :
/*----------------*////////////////////////*----------------*/
FrameSkip::FrameSkip(int FPS)
{
	timeBeginPeriod(1);
	_systemTick = timeGetTime();
	_maxFrame = FPS;
	_oneFrameTick = 1000 / FPS;
	_tick = 0;
}

/*----------------------------------------------------------*/
// FrameSkip::~FrameSkip (public)
// ���� : �����ӽ�ŵ �Ҹ���
//  ��  : timeEndPeriod(1)�� ȣ���Ѵ�.
// ���� : 
// ���� :
/*----------------*////////////////////////*----------------*/
FrameSkip::~FrameSkip()
{
	timeEndPeriod(1);
}

/*----------------------------------------------------------*/
// FrameSkip::Skip (public)
// ���� : ������ ��ŵ���� ����
// ���� : 
// ���� : (bool) ������ ��ŵ����
/*----------------*////////////////////////*----------------*/
bool FrameSkip::Skip()
{
	DWORD curTime = timeGetTime();
	_tick += (curTime - _systemTick) - _oneFrameTick;
	_systemTick = curTime;
	if (_oneFrameTick <= _tick)
	{
		_tick -= _oneFrameTick;
		return true;
	}

	else if (_tick < 0)
	{
		Sleep((-1) * _tick);
		_tick = 0;
		_systemTick = timeGetTime();
	}
	return false;
}

FrameSkipServer::FrameSkipServer(int FPS) : FrameSkip(FPS)
{
}

FrameSkipServer::~FrameSkipServer()
{
}

bool FrameSkipServer::Skip()
{
	DWORD curTime = timeGetTime();
	_tick += (curTime - _systemTick) - _oneFrameTick;
	_systemTick = curTime;
	// ���� �ð� ���󰡱�
	if (_oneFrameTick <= _tick)
	{
		_tick -= _oneFrameTick;
		return true;
	}
	// �ʹ� ���� ȣ������� false��ȯ
	return false;
}

int FrameSkipServer::GetTick()
{
	return _tick;
}

void FrameSkipServer::ChangeTick(int tick)
{
	_tick = tick;
}
