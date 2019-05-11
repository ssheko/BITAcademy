#pragma once
#include <Windows.h>
#include <stdio.h>
#include <time.h>

//#define PROFILE

#ifdef PROFILE
#define BEGIN(name)		ProFiler::getInstance().BeginProFile(#name)
#define END(name)		ProFiler::getInstance().EndProFile(#name)
#define PRINTPROFILE()	ProFiler::getInstance().FilePrint()
#endif // PROFILE
#ifndef PROFILE
#define BEGIN(name)  
#define END(name)  	
#define PRINTPROFILE()	
#endif // !PROFILE

template <class T>
class SingleTon
{
protected:
	SingleTon() {}
	~SingleTon() {}
public:
	SingleTon(const SingleTon&);

	SingleTon & operator = (const SingleTon &);
	static T  & getInstance()
	{
		static T instance;
		return instance;
	}
};
#define NONCOUNTSIZE 10
#define BLOCKCOUNT 10
#define MAXTHREAD 10

class ProFiler : public SingleTon <ProFiler>
{
	struct ProFileBlock
	{
		bool			_useFlag;
		char			_name[64];
		int				_callCount;
		LARGE_INTEGER	_startTime;
		LONGLONG		_minTime[NONCOUNTSIZE];
		LONGLONG		_maxTime[NONCOUNTSIZE];
		LONGLONG		_totalTime;
	};

	struct TLS_BLOCK
	{
		ProFileBlock proFileBlock[BLOCKCOUNT];
		DWORD threadID;
		TLS_BLOCK()
		{
			ZeroMemory(&proFileBlock, sizeof(ProFileBlock) * BLOCKCOUNT);
			threadID = NULL;
		}
	};


	FILE *			_file;							// ��¿� ����������
	LARGE_INTEGER	_frequency;						// CPU 1�ʴ� Ŭ��
	TLS_BLOCK *		_blockPointerArray[MAXTHREAD];	// �������� �������͸� ������ �迭
	int				_index;							// �� �迭 �ε���
	DWORD			_tlsIndex;						// TLS�ε���

	// name �̸��� �������Ϻ�� ������ �����͸� ��ġ��Ų��.
	bool MakeProFile(const char * name, ProFileBlock ** proFilePointer, TLS_BLOCK * blockPointer);
	// name�� ���� ���������� �̹� �ִ��� ã�Ƽ� �����͸� ��ġ��Ű�� ������ MakeProFile�� ȣ���Ѵ�.
	bool SearchProFile(const char * name, ProFileBlock ** proFilePointer, TLS_BLOCK * blockPointer);

public:
	ProFiler();
	~ProFiler();
	void BeginProFile(const char * name);
	void EndProFile(const char * name);
	void FilePrint();
	void Reset();
};