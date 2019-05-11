#pragma once
#include <Windows.h>
#include "MemoryPool.h"

#define MAXLOOPCOUNT 200

template <typename T>
class LF_Queue
{
	struct LF_Queue_NODE
	{
		T data;
		LF_Queue_NODE * next;
	};

	struct LF_Queue_UNIQUE
	{
		LF_Queue_NODE * node;
		INT64			unique;
	};

	alignas(16) volatile LF_Queue_UNIQUE _head;
	alignas(16) volatile LF_Queue_UNIQUE _tail;
	MemoryPool<LF_Queue_NODE> _memoryPool;
	INT64 _useSize;
	
public:
	// ������
	LF_Queue()
	{
		// ���� ��� ����
		_head.node = _memoryPool.Alloc();
		_head.node->next = nullptr;
		_tail.node = _head.node;
		_head.unique = 0;
		_tail.unique = 0;
	}
	// �Ҹ���
	~LF_Queue()
	{

	}

	void EnQueue(T data)
	{
		LF_Queue_NODE * node = _memoryPool.Alloc();
		node->data = data;
		node->next = nullptr;

		alignas(16) LF_Queue_UNIQUE localTail;

		while (true)
		{
			localTail.unique = _tail.unique;
			localTail.node = _tail.node;

			LF_Queue_NODE * next = localTail.node->next;

			if (localTail.unique == _tail.unique)
			{
				// ���� tail�� �������ΰ� ����
				if (next == nullptr)
				{
					// ������ enqueue�Ѵ�
					if (InterlockedCompareExchange64((LONG64 *)&_tail.node->next, (LONG64)node, (LONG64)nullptr) == (LONG64)nullptr)
					{
						// tail�� �ű�� �غ���
						InterlockedCompareExchange128((LONG64 *)&_tail, localTail.unique + 1, (LONG64)localTail.node->next, (LONG64 *)&localTail);
						break;
					}
					// �׻��� ����tail�� tail�̶� �޶�����
					else
					{
						continue;
					}
				}
				// ���� tail�� �������̾ƴϾ���
				else
				{
					InterlockedCompareExchange128((LONG64 *)&_tail, localTail.unique + 1, (LONG64)next, (LONG64 *)&localTail);
				}
			}
		}
		InterlockedIncrement64((LONG64 *)&_useSize);
	}

	bool DeQueue(T * outData)
	{
		if (_useSize == 0)
			return false;
		//__declspec(align(16))
		//__declspec(align(16))
		alignas(16) LF_Queue_UNIQUE localHead;
		alignas(16) LF_Queue_UNIQUE localTail;
		LF_Queue_NODE * next;
		
		int loopCount = 1;
		//while (loopCount++)
		while(1)
		{
			// Head����
			localHead.unique = _head.unique;
			localHead.node = _head.node;
			// Tail����
			localTail.unique = _tail.unique;
			localTail.node = _tail.node;
			// head�� next����
			next = localHead.node->next;
			
			//// ���ο� ����
			//if (_useSize == 0)
			//{
			//	if(_head.node == _tail.node)
			//		return false;
			//}

			//// tail �ڿ� node�� ������ �б�
			//if (localTail.node->next != nullptr)
			//{
			//	InterlockedCompareExchange128((LONG64 *)&_tail, localTail.unique + 1, (LONG64)localTail.node->next, (LONG64 *)&localTail);
			//}
			//// 
			//else
			//{
			//	if (next != nullptr)
			//	{
			//		*outData = next->data;
			//		if (InterlockedCompareExchange128((LONG64 *)&_head, localHead.unique + 1, (LONG64)localHead.node->next, (LONG64 *)&localHead))
			//		{
			//			_memoryPool.Free(localHead.node);
			//			break;
			//		}
			//	}
			//}

			// head�� ���� �ٲ��� �ʾҴ�
			if (localHead.unique == _head.unique)
			{
				// head�� tail�� �پ��ִ�. ����ų� ���� tail�� �Ȱ��ų�
				if (localHead.node == localTail.node)
				{
					// ����head�� next�� ����
					// �� �� ť
					if (next == nullptr)
					{
						return false;
						//// �̸�ŭ �õ��ߴµ� �ȵǸ� ����ġ��
						//if (MAXLOOPCOUNT < loopCount++)
						//{
						//	return false;
						//}
						//// ��� �ٸ������� ���� �غ���
						//Sleep(0);
						//// ������������ �ٽ��� �غ���
						//continue;
					}
					// next�� ������ tail�� ���� �ȿ������� 
					// dequeue�� tail�� ť �����γ�����
					// tail�� next�� �������� ����
					//if (localTail.node->next != nullptr)
					else
					{
						InterlockedCompareExchange128((LONG64 *)&_tail, localTail.unique + 1, (LONG64)localTail.node->next, (LONG64 *)&localTail);
					}
				}
				// �ϴ� head�� tail�� �������ִ�
				else
				{
					// Ȥ�ø𸣴ϱ�
					if (next == nullptr)
						continue;
					if (localHead.unique != _head.unique)
						continue;
					// ������ dequeue�غ���
					*outData = next->data;
					if (InterlockedCompareExchange128((LONG64 *)&_head, localHead.unique + 1, (LONG64)next, (LONG64 *)&localHead))
					{
						_memoryPool.Free(localHead.node);
						break;
					}
					// �׻��� head�� �ٲ���� 
					else
					{
						// ó������ ��õ��� �� ���� �Ұž���
					}
				}
			}
		}
		InterlockedDecrement64((LONG64 *)&_useSize);
		return true;
	}

	bool Peek(T * data, int jumpCount)
	{
		if (jumpCount < 0)
			return false;
		if (GetUseCount() < jumpCount + 1)
			return false;

		LF_Queue_NODE * curNode = _head;

		for (int i = 0; i < jumpCount + 1; i++)
		{
			if (curNode->next == nullptr)
				return false;
			curNode = curNode->next;
		}
		*T = curNode->data;
		return true;
	}

	void EnQueue_UnSafe(T data)
	{
		LF_Queue_NODE * node = _memoryPool.Alloc();
		node->data = data;
		node->next = nullptr;

		_tail.node->next = node;
		_tail.node = node;
		_tail.unique++;
		InterlockedIncrement64((LONG64 *)&_useSize);
	}

	bool DeQueue_UnSafe(T * outData)
	{
		if (_useSize == 0)
			return false;

		LF_Queue_NODE * localHead = _head.node;

		_head.node = _head.node->next;
		*outData = _head.node->data;
		_head.unique++;
		_memoryPool.Free(localHead);
		InterlockedDecrement64((LONG64 *)&_useSize);
		return true;
	}

	INT64 GetUseCount()
	{
		return _useSize;
	}
};