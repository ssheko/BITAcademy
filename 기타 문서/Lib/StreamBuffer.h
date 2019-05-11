#pragma once
//#include <Windows.h>
#include "MemoryPool.h"

#define PacketAlloc(server)		StreamBuffer::Alloc(sizeof(server::PACKET_HEADER))
#define PacketFree(p)			StreamBuffer::Free(p)
#define PacketSIZE				512

//////////////////////////////////////////////////////////////
// StreamBuffer :
// ���� : ����ȭ ���� Ŭ����
//////////////////////////////////////////////////////////////
class StreamBuffer
{
	char * _buffer;
	int _front;
	int _rear;
	int _size;
	int _refCount;
	bool _headerFillFlag;
	bool _headerEnterFlag;
	bool _encodeFlag;
	static MemoryPoolTLS<StreamBuffer> _memoryPool;
public: 
	static int _allocCount;
	StreamBuffer(int size = PacketSIZE);
	~StreamBuffer();
	// _ref ����
	inline void AddRef();
	// _rear�� ������ �̵�
	inline void MoveEndIndex(int size = PacketSIZE);
	// ���� �ּ� ������ ����
	inline char * GetBuffer();
	// ������� �ּ� ����
	inline char * GetWritePtr();
	// ���� ũ�� ����
	inline int GetSize();
	// ���� ������� ũ�� ����
	inline int GetUseSize();
	// ���� ������ ���Ҵ�
	inline void ReSize(int size);
	// front�� headerSize��ŭ �̵�
	inline void BlankHeader(int headerSize);
	// ���� �����ּҺ��� size��ŭ ����
	inline void FillHeader(char * buffer, int size);
	// front rear 0���� ����
	inline void Clear();

	virtual inline void Encode(char * buffer, int size);
	virtual inline void Decode(char * buffer, int size);

	// ���ۿ� ������ ����
	inline int In(char * buffer, int size);
	inline int In(WCHAR * buffer, int size);

	template<typename T> inline bool In(T buffer);
	template<> inline bool In(char buffer);
	template<> inline bool In(unsigned char buffer);	
	template<> inline bool In(short buffer);
	template<> inline bool In(unsigned short buffer);
	template<> inline bool In(int buffer);
	template<> inline bool In(unsigned int buffer);
	template<> inline bool In(long buffer);
	template<> inline bool In(unsigned long buffer);
	template<> inline bool In(long long buffer);
	template<> inline bool In(unsigned long long buffer);
	//template<> inline bool In(BYTE buffer);
	//template<> inline bool In(WORD buffer);
	//template<> inline bool In(DWORD buffer);
	//template<> inline bool In(INT64 buffer);
	//template<> inline bool In(UINT64 buffer);

	// ���ۿ��� ������ ������
	inline int Out(char * buffer, int size);
	inline int Out(WCHAR * buffer, int size);

	template<typename T> inline void Out(T * buffer);
	template<> inline void Out(char * buffer);
	template<> inline void Out(unsigned char * buffer);
	template<> inline void Out(short * buffer);
	template<> inline void Out(unsigned short * buffer);
	template<> inline void Out(int * buffer);
	template<> inline void Out(unsigned int * buffer);
	template<> inline void Out(long * buffer);
	template<> inline void Out(unsigned long * buffer);
	template<> inline void Out(long long * buffer);
	template<> inline void Out(unsigned long long* buffer);
	//template<> inline void Out(BYTE * buffer);
	//template<> inline void Out(WORD * buffer);
	//template<> inline void Out(DWORD * buffer);
	//template<> inline void Out(INT64 * buffer);
	//template<> inline void Out(UINT64 *buffer);


	// ����, ������ ������ �����ε�
	template<typename T> inline StreamBuffer& operator <<(const T& inData);
	template<typename T> inline StreamBuffer& operator >>(const T& outData);
	// �Ҵ�
	static StreamBuffer * Alloc(int size);
	// ����
	static void Free(StreamBuffer * buffer);

	friend class LanServer;
	friend class NetServer;
	friend class ChatServer;
	friend class LanClient;
	friend class NetClient;
	friend class MMOServer;
	friend class MMOSession;
	friend class NovaEngine;
	friend class IOCPDummy;
};

template<typename T>
inline bool StreamBuffer::In(T buffer)
{
	int size = sizeof(T);
	if (_size < _rear + size)
		throw;
	memcpy_s(_buffer + _rear, size, &buffer, size);
	_rear += size;
	//return size;

	//if (_size < _rear + (int)sizeof(T))
	//	return false;
	//*(T*)(_buffer + _rear) = buffer;
	//_rear += sizeof(T);
	return true;
}

template<typename T>
inline void StreamBuffer::Out(T * buffer)
{
	int size = sizeof(T);
	if (_size < _front + size)
		throw;
	memcpy_s(buffer, size, _buffer + _front, size);
	_front += size;
	//return size;
	//*buffer = *(T*)(_buffer + _front);
	//_front += sizeof(T);
}

template<>
inline bool StreamBuffer::In(char buffer)
{
	if (_size < _rear + 1)
		return false;
	*(char*)(_buffer + _rear) = buffer;
	_rear += 1;
	return true;
}

template<>
inline bool StreamBuffer::In(unsigned char buffer)
{
	if (_size < _rear + 1)
		return false;
	*(unsigned char*)(_buffer + _rear) = buffer;
	_rear += 1;
	return true;
}

template<>
inline bool StreamBuffer::In(short buffer)
{
	if (_size < _rear + 2)
		return false;
	*(short*)(_buffer + _rear) = buffer;
	_rear += 2;
	return true;
}

template<>
inline bool StreamBuffer::In(unsigned short buffer)
{
	if (_size < _rear + 2)
		return false;
	*(unsigned short*)(_buffer + _rear) = buffer;
	_rear += 2;
	return true;
}

template<>
inline bool StreamBuffer::In(int buffer)
{
	if (_size < _rear + 4)
		return false;
	*(int*)(_buffer + _rear) = buffer;
	_rear += 4;
	return true;
}

template<>
inline bool StreamBuffer::In(unsigned int buffer)
{
	if (_size < _rear + 4)
		return false;
	*(unsigned int*)(_buffer + _rear) = buffer;
	_rear += 4;
	return true;
}

template<>
inline bool StreamBuffer::In(long buffer)
{
	if (_size < _rear + 4)
		return false;
	*(long*)(_buffer + _rear) = buffer;
	_rear += 4;
	return true;
}

template<>
inline bool StreamBuffer::In(unsigned long buffer)
{
	if (_size < _rear + 4)
		return false;
	*(unsigned long*)(_buffer + _rear) = buffer;
	_rear += 4;
	return true;
}

template<>
inline bool StreamBuffer::In(long long buffer)
{
	if (_size < _rear + 8)
		return false;
	*(long long*)(_buffer + _rear) = buffer;
	_rear += 8;
	return true;
}

template<>
inline bool StreamBuffer::In(unsigned long long buffer)
{
	if (_size < _rear + 8)
		return false;
	*(unsigned long long*)(_buffer + _rear) = buffer;
	_rear += 8;
	return true;
}

/*----------------------------------------------------------*/
// StreamBuffer::In (public)
// ���� : in
// ���� : (BYTE)
// ���� :
/*----------------*////////////////////////*----------------*/
//template<>
//inline bool StreamBuffer::In(BYTE buffer)
//{
//	if (_size < _rear + 1)
//		return false;
//	*(BYTE*)(_buffer + _rear) = buffer;
//	_rear += 1;
//	return true;
//}
//
///*----------------------------------------------------------*/
//// StreamBuffer::In (public)
//// ���� : 
//// ���� : (WORD)
//// ���� :
///*----------------*////////////////////////*----------------*/
//template<>
//inline bool StreamBuffer::In(WORD buffer)
//{
//	if (_size < _rear + 2)
//		return false;
//	*(WORD*)(_buffer + _rear) = buffer;
//	_rear += 2;
//	return true;
//}
//
///*----------------------------------------------------------*/
//// StreamBuffer::In (public)
//// ���� : 
//// ���� : (DWORD)
//// ���� :
///*----------------*////////////////////////*----------------*/
//template<>
//inline bool StreamBuffer::In(DWORD buffer)
//{
//	if (_size < _rear + 4)
//		return false;
//	*(DWORD*)(_buffer + _rear) = buffer;
//	_rear += 4;
//	return true;
//}
//
//template<>
//inline bool StreamBuffer::In(INT64 buffer)
//{
//	if (_size < _rear + 8)
//		return false;
//	*(DWORD*)(_buffer + _rear) = buffer;
//	_rear += 8;
//	return true;
//}
//
//template<>
//inline bool StreamBuffer::In(UINT64 buffer)
//{
//	if (_size < _rear + 8)
//		return false;
//	*(DWORD*)(_buffer + _rear) = buffer;
//	_rear += 8;
//	return true;
//}

template<>
inline void StreamBuffer::Out(char * buffer)
{
	*buffer = *(char*)(_buffer + _front);
	_front += 1;
}

template<>
inline void StreamBuffer::Out(unsigned char * buffer)
{
	*buffer = *(unsigned char*)(_buffer + _front);
	_front += 1;
}

template<>
inline void StreamBuffer::Out(short * buffer)
{
	*buffer = *(short*)(_buffer + _front);
	_front += 2;
}

template<>
inline void StreamBuffer::Out(unsigned short * buffer)
{
	*buffer = *(unsigned short*)(_buffer + _front);
	_front += 2;
}

template<>
inline void StreamBuffer::Out(int * buffer)
{
	*buffer = *(int*)(_buffer + _front);
	_front += 4;
}

template<>
inline void StreamBuffer::Out(unsigned int * buffer)
{
	*buffer = *(unsigned int*)(_buffer + _front);
	_front += 4;
}

template<>
inline void StreamBuffer::Out(long * buffer)
{
	*buffer = *(long*)(_buffer + _front);
	_front += 4;
}

template<>
inline void StreamBuffer::Out(unsigned long * buffer)
{
	*buffer = *(unsigned long*)(_buffer + _front);
	_front += 4;
}

template<>
inline void StreamBuffer::Out(long long * buffer)
{
	*buffer = *(long long*)(_buffer + _front);
	_front += 8;
}

template<>
inline void StreamBuffer::Out(unsigned long long * buffer)
{
	*buffer = *(unsigned long long*)(_buffer + _front);
	_front += 8;
}

/*----------------------------------------------------------*/
// StreamBuffer::Out (public)
// ���� : 
// ���� : (BYTE)
// ���� :
/*----------------*////////////////////////*----------------*/
//template<>
//inline void StreamBuffer::Out(BYTE * buffer)
//{
//	*buffer = *(BYTE*)(_buffer + _front);
//	_front += 1;
//}
//
///*----------------------------------------------------------*/
//// StreamBuffer::Out (public)
//// ���� : 
//// ���� : (WORD)
//// ���� :
///*----------------*////////////////////////*----------------*/
//template<>
//inline void StreamBuffer::Out(WORD * buffer)
//{
//	*buffer = *(WORD*)(_buffer + _front);
//	_front += 2;
//}
//
///*----------------------------------------------------------*/
//// StreamBuffer::Out (public)
//// ���� : 
//// ���� : (DWORD)
//// ���� :
///*----------------*////////////////////////*----------------*/
//template<>
//inline void StreamBuffer::Out(DWORD * buffer)
//{
//	*buffer = *(DWORD*)(_buffer + _front);
//	_front += 4;
//}
//
//template<>
//inline void StreamBuffer::Out(INT64 * buffer)
//{
//	*buffer = *(INT64*)(_buffer + _front);
//	_front += 8;
//}
//
//template<>
//inline void StreamBuffer::Out(UINT64 * buffer)
//{
//	*buffer = *(UINT64*)(_buffer + _front);
//	_front += 8;
//}
/*----------------------------------------------------------*/
// StreamBuffer::Method (public)
// ���� : 
// ���� : 
// ���� :
/*----------------*////////////////////////*----------------*/
template<typename T>
inline StreamBuffer& StreamBuffer::operator<<(const T & inData)
{
	//static_assert(std::is_aritmetic<T>::value || std::is_enum<T>::value , "Wrong Type")
	//In((char*)&inData, sizeof(inData));
	Encode((char*)&inData, sizeof(T));
	In(inData);
	return (*this);
}

/*----------------------------------------------------------*/
// StreamBuffer::Method (public)
// ���� : 
// ���� : 
// ���� :
/*----------------*////////////////////////*----------------*/
template<typename T>
inline StreamBuffer& StreamBuffer::operator>>(const T & outData)
{
	//static_assert(std::is_aritmetic<T>::value || std::is_enum<T>::value, "Wrong Type")
	//Out((char*)&outData, sizeof(outData));
	Out((T*)&outData);
	Decode((char*)&outData, sizeof(T));
	return (*this);
}

/*----------------------------------------------------------*/
// StreamBuffer::Method (public)
// ���� : 
// ���� : 
// ���� :
/*----------------*////////////////////////*----------------*/
inline void StreamBuffer::AddRef()
{
	InterlockedIncrement((LONG *)&_refCount);
}

/*----------------------------------------------------------*/
// StreamBuffer::Method (public)
// ���� : 
// ���� : 
// ���� :
/*----------------*////////////////////////*----------------*/
inline void StreamBuffer::MoveEndIndex(int size)
{
	if (size == 0)
		_rear = _size - 1;
	else
		_rear = size;
}

/*----------------------------------------------------------*/
// StreamBuffer::Method (public)
// ���� : 
// ���� : 
// ���� :
/*----------------*////////////////////////*----------------*/
inline char * StreamBuffer::GetBuffer()
{
	return _buffer;
}

inline char * StreamBuffer::GetWritePtr()
{
	return _buffer + _rear;
}

/*----------------------------------------------------------*/
// StreamBuffer::Method (public)
// ���� : 
// ���� : 
// ���� :
/*----------------*////////////////////////*----------------*/
inline int StreamBuffer::GetSize()
{
	return _size;
}

/*----------------------------------------------------------*/
// StreamBuffer::Method (public)
// ���� : 
// ���� : 
// ���� :
/*----------------*////////////////////////*----------------*/
inline int StreamBuffer::GetUseSize()
{
	return _rear - _front;
}

/*----------------------------------------------------------*/
// StreamBuffer::Method (public)
// ���� : 
// ���� : 
// ���� :
/*----------------*////////////////////////*----------------*/
inline void StreamBuffer::ReSize(int size)
{
	delete[] _buffer;
	_buffer = new char[size];
}

/*----------------------------------------------------------*/
// StreamBuffer::Method (public)
// ���� : 
// ���� : 
// ���� :
/*----------------*////////////////////////*----------------*/
inline void StreamBuffer::BlankHeader(int headerSize)
{
	if (_size < headerSize)
		throw;
	_rear += headerSize;
}

/*----------------------------------------------------------*/
// StreamBuffer::Method (public)
// ���� : 
// ���� : 
// ���� :
/*----------------*////////////////////////*----------------*/
inline void StreamBuffer::FillHeader(char * buffer, int size)
{
	if (_size < size)
		throw;
	if (_headerFillFlag)
		return;
	memcpy_s(_buffer, size, buffer, size);
	_headerFillFlag = true;
}

/*----------------------------------------------------------*/
// StreamBuffer::Method (public)
// ���� : 
// ���� : 
// ���� :
/*----------------*////////////////////////*----------------*/
inline void StreamBuffer::Clear()
{
	_front = 0;
	_rear = 0;
	//InterlockedAdd((LONG *)&_refCount, 1 - _refCount);
	_refCount = 1;
	_headerEnterFlag = false;
	_headerFillFlag = false;
	_encodeFlag = false;
}

inline void StreamBuffer::Encode(char * buffer, int size)
{
}

inline void StreamBuffer::Decode(char * buffer, int size)
{
}

/*----------------------------------------------------------*/
// StreamBuffer::In (public)
// ���� : ����ȭ ���۷� buffer�� ������ size��ŭ ����
// ���� : (char *) ������ ���� ������, (int) ������ ũ��
// ���� : (int) ����� ũ��
/*----------------*////////////////////////*----------------*/
inline int StreamBuffer::In(char * buffer, int size)
{
	if (_size < _rear + size)
		throw;
	memcpy_s(_buffer + _rear, size, buffer, size);
	_rear += size;
	return size;
}

inline int StreamBuffer::In(WCHAR * buffer, int size)
{
	if (_size < _rear + (size * 2))
		throw;
	memcpy_s(_buffer + _rear, size * 2, buffer, size * 2);
	_rear += size * 2;
	return size * 2;
}

/*----------------------------------------------------------*/
// StreamBuffer::Out (public)
// ���� : ����ȭ ���ۿ��� buffer�� size��ŭ ����
// ���� : (char *) ������ ���� ������, (int) ������ ũ��
// ���� : (int) ����� ũ��
/*----------------*////////////////////////*----------------*/
inline int StreamBuffer::Out(char * buffer, int size)
{
	if (_size < _front + size)
		throw;
	memcpy_s(buffer, size, _buffer + _front, size);
	_front += size;
	return size;
}

inline int StreamBuffer::Out(WCHAR * buffer, int size)
{
	if (_size < _front + (size * 2))
		throw;
	memcpy_s(buffer, size * 2, _buffer + _front, size * 2);
	_front += size * 2;
	return size * 2;
}

typedef StreamBuffer Packet;