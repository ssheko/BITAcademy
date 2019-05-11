#pragma once
//#include "pch.h"
//#include "stdafx.h"
#include "StreamBuffer.h"

/*----------------------------------------------------------*/
// StreamBuffer::StreamBuffer (public)
// ���� : ������
// ���� : (int) ���� ������
// ���� :
/*----------------*////////////////////////*----------------*/
StreamBuffer::StreamBuffer(int size)
{
	_buffer = new char[size];
	_front = 0;
	_rear = 0;
	_size = size;
	_refCount = 1;
	_headerFillFlag = false;
}

/*----------------------------------------------------------*/
// StreamBuffer::~StreamBuffer (public)
// ���� : �Ҹ���, ���۸� �����Ѵ�
// ���� : 
// ���� :
/*----------------*////////////////////////*----------------*/
StreamBuffer::~StreamBuffer()
{
	delete[] _buffer;
}





/*----------------------------------------------------------*/
// StreamBuffer::Alloc (public)
// ���� : ����ȭ ���۸� �޸� Ǯ���� �Ҵ�
// ���� : (int) size <�̻��>
// ���� : (StreamBuffer *) ����ȭ ���� ������
/*----------------*////////////////////////*----------------*/
StreamBuffer * StreamBuffer::Alloc(int headerSize)
{
	StreamBuffer * newBuffer = _memoryPool.Alloc();
	newBuffer->Clear();
	newBuffer->_rear += headerSize;
	InterlockedIncrement((LONG *)&_allocCount);
	return newBuffer;
}

/*----------------------------------------------------------*/
// StreamBuffer::Free (public)
// ���� : ����ȭ ���۸� �޸� Ǯ�� ��ȯ
// ���� : (StreamBuffer *) ����ȭ ���� ������
// ���� :
/*----------------*////////////////////////*----------------*/
void StreamBuffer::Free(StreamBuffer * buffer)
{
	int count = InterlockedDecrement((LONG *)&buffer->_refCount);
	if (count == 0)
	{
		InterlockedDecrement((LONG *)&_allocCount);
		_memoryPool.Free(buffer);
	}
}

int StreamBuffer::_allocCount = 0;
MemoryPoolTLS<StreamBuffer> StreamBuffer::_memoryPool;