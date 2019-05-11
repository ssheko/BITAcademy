#pragma once
//��Ʈ���� ť Ŭ���� �ʿ� �Լ�

class StreamQueue
{
	char *_bufferPointer;	// ���� ���� �ּ� ������
	int _front;				// �б� ������
	int _rear;				// ���� ������
	int _size;				// ���� ũ��
	int _availableSize;		// ���� ������ ���� ũ��
	int _useSize;			// ����� ������ ũ��
protected: 
	void Initial(int iBufferSize);
public:
	StreamQueue(int iBufferSize = 10000);
	~StreamQueue();
	// ���� ������ size��ŭ ���Ҵ�
	inline void Resize(int size);
	// ���� ������ ���� ũ�� ����
	inline int	GetBufferSize();
	// �������� ������ ũ�� ����
	inline int	GetUseSize();
	// �� ���尡���� ������ ũ�� ����
	inline int	GetFreeSize();
	// �ѹ��� ������ �ִ� ������ ũ�� ����
	inline int	GetNotBrokenGetSize();
	// �ѹ��� ���� ������ ������ ũ�� ����
	inline int	GetNotBrokenPutSize();
	// ������ ����
	int	Enqueue(char *chpData, int iSize);
	// ������ ����
	int	Dequeue(char *chpDest, int iSize);
	// ������ �����ʰ� �б�
	int	Peek(char *chpDest, int iSize, int jumpSize = 0);
	// ������ �պκ� ����
	inline void RemoveData(int iSize);
	// ������ �޺κ� �߰�
	inline void MoveWritePos(int iSize);
	// ������ ��� ����
	inline void ClearBuffer();
	// ���� ���� �ּ� ������ ����
	inline char * GetBufferPtr();
	// �б� ���� �ּ� ������ ����
	inline char * GetReadBufferPtr();
	// ���� ���� �ּ� ������ ����
	inline char * GetWriteBufferPtr();
	// ����
	inline void Clear();
};
/////////////////////////////////////////////////////////////////////////
// ũ�� ����.
// Parameters: (int)���ο� ũ��.
// Return:
/////////////////////////////////////////////////////////////////////////
inline void StreamQueue::Resize(int size)
{
	delete[] _bufferPointer;
	_bufferPointer = new char[size];
}
/////////////////////////////////////////////////////////////////////////
// ������ ũ�� ���
// Parameters:
// Return: (int)������ ũ��.
/////////////////////////////////////////////////////////////////////////
inline int StreamQueue::GetBufferSize()
{
	return _availableSize;
}
/////////////////////////////////////////////////////////////////////////
// ���� ������� �뷮 ���.
// Parameters: ����.
// Return: (int)������� �뷮.
/////////////////////////////////////////////////////////////////////////
inline int StreamQueue::GetUseSize()
{
	//return _useSize;
	// �����忡 �����ϵ��� ���������� ����
	int front = _front;
	int rear = _rear;
	if (front < rear)
		return rear - front;
	else if (rear < front)
		return rear + (_size - front);
	// front = rear 
	else
		return 0;
}
/////////////////////////////////////////////////////////////////////////
// ���� ���ۿ� ���� �뷮 ���.
// Parameters: ����.
// Return: (int)�����뷮.
/////////////////////////////////////////////////////////////////////////
inline int StreamQueue::GetFreeSize()
{
	//return _availableSize - _useSize;
	// �����忡 �����ϵ��� ���������� ����
	int front = _front;
	int rear = _rear;
	if (front < rear)
		return _availableSize - (rear - front);
	else if (rear < front)
		return front - rear - 1;
	// front = rear 
	else
		return _availableSize;
	//return _availableSize - _useSize;
}
/////////////////////////////////////////////////////////////////////////
// ���� �����ͷ� �ܺο��� �ѹ濡 �а�, �� �� �ִ� ����.
// (������ ���� ����)
// Parameters: ����.
// Return: (int)��밡�� �뷮.
////////////////////////////////////////////////////////////////////////
inline int StreamQueue::GetNotBrokenGetSize()
{
	// Enqueue Dequeue�� ���ÿ� �����ϰ� �ϱ����� ��Ȯ���� ������
	//if (_front == _availableSize)
	//	return _availableSize;
	//else
	//	return _availableSize - _front;

	// �� ��Ȯ������ ��Ƽ�����忡 ������������
	// �����忡 �����ϵ��� ���������� ����
	int front = _front;
	int rear = _rear;
	if (front < rear)
		return rear - front;
	else if (rear < front)
	{
		if (front == _availableSize)
			return rear + 1;
		else
			return _availableSize - front;
	}
	else
		return 0;
}

inline int StreamQueue::GetNotBrokenPutSize()
{
	// Enqueue Dequeue�� ���ÿ� �����ϰ� �ϱ����� ��Ȯ���� ������
	//if (_rear == _availableSize)
	//	return _availableSize;
	//else
	//	return _availableSize - _rear;

	// �� ��Ȯ������ ��Ƽ�����忡 ������������
	// �����忡 �����ϵ��� ���������� ����
	int front = _front;
	int rear = _rear;
	if (front < rear)
	{
		if (rear == _availableSize)
			return  front;
		else
			return _availableSize - rear;
	}
	else if (rear < front)
		return front - rear - 1;
	else
	{
		if (rear == _availableSize)
			return _availableSize;
		else
			return _availableSize - rear;
	}
}
/////////////////////////////////////////////////////////////////////////
// ���ϴ� ���̸�ŭ �б���ġ ���� ���� / ���� ��ġ �̵�
// Parameters: (int)ũ��.
// Return: ����.
/////////////////////////////////////////////////////////////////////////
inline void StreamQueue::RemoveData(int iSize)
{
	int front = _front;
	front += iSize;
	if (_availableSize < front)
		front %= _size;
	_front = front;
	//InterlockedAdd((LONG *)&_useSize, -iSize);
	//_useSize -= iSize;
}
inline void StreamQueue::MoveWritePos(int iSize)
{
	int rear = _rear;
	rear += iSize;
	if (_availableSize < rear)
		rear %= _size;
	_rear = rear;
	//InterlockedAdd((LONG *)&_useSize, iSize);
	//_useSize += iSize;
}
/////////////////////////////////////////////////////////////////////////
// ������ ��� ����Ÿ ����.
// Parameters: ����.
// Return: ����.
/////////////////////////////////////////////////////////////////////////
inline void StreamQueue::ClearBuffer()
{
	_rear = _front;
}
/////////////////////////////////////////////////////////////////////////
// ������ ������ ����.
// Parameters: ����.
// Return: (char *) ���� ������.
/////////////////////////////////////////////////////////////////////////
inline char * StreamQueue::GetBufferPtr()
{
	return _bufferPointer;
}
/////////////////////////////////////////////////////////////////////////
// ������ ReadPos ������ ����.
// Parameters: ����.
// Return: (char *) ���� ������.
/////////////////////////////////////////////////////////////////////////
inline char * StreamQueue::GetReadBufferPtr()
{
	//char * readPointer = _bufferPointer + _front;
	//return readPointer;
	if (_front == _availableSize)
		return _bufferPointer;
	else
		return _bufferPointer + _front + 1;
}
/////////////////////////////////////////////////////////////////////////
// ������ WritePos ������ ����.
// Parameters: ����.
// Return: (char *) ���� ������.
/////////////////////////////////////////////////////////////////////////
inline char * StreamQueue::GetWriteBufferPtr()
{
	//char * writePointer = _bufferPointer + _rear;
	//return writePointer;
	if (_rear == _availableSize)
		return _bufferPointer;
	else
		return _bufferPointer + _rear + 1;
}

inline void StreamQueue::Clear()
{
	_front = 0;
	_rear = 0;
}
