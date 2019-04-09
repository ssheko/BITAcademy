#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#pragma warning(disable:4996)	// �������� ���� �ʰڴ�.

/*
 �ڷᱸ�� (�ڷḦ ��� ������ ���ΰ�) �� ����
	* ��� �ڷᱸ���� �ݵ�� �ʱ�ȭ �Լ��� �ִ�.
	1. list (������ �ִ� ����)
		1-1. ����: select, bubble, insert, indirect-insert, shell, merge, quick Sort
		1-2. circular list, double linked list
		1-3. linux kernel (linked list)
	2. stack (last input first out : LIFO)
		2-1. �Լ� �� ���� ���� ���� (�ݹ� �Լ��� ����)
	3. queue (FIFO) - �������
	4. tree	(���� ����Ʈ��, binary tree) - linux (Red-black T)
			- Tree sort
		4-1. �Ｚ��: �����ʱ�ȭ (hash-Tree�� �籸��)	// hash, tree �� �� ����
	5. graph
*/

/* 
	circular linked list
		1-1. queue (deque: double ended queue)
*/
//typedef int ElementType;
//
//typedef struct tagNode
//{
//	ElementType Data;
//	struct tagNode* PrevNode;
//	struct tagNode* NextNode;
//} Node;
//Node* CreateNode(ElementType NewData)
//{
//	Node* NewNode = (Node*)malloc(sizeof(Node));
//
//	NewNode->Data = NewData;
//	NewNode->PrevNode = NULL;
//	NewNode->NextNode = NULL;
//
//	return NewNode;
//}
//
//
///*  ��� �߰� */
//void AppendNode(Node** Head, Node* NewNode)
//{
//
//	if ((*Head) == NULL)
//	{
//		*Head = NewNode;
//		(*Head)->NextNode = *Head;
//		(*Head)->PrevNode = *Head;
//	}
//	else
//	{
//
//		Node* Tail = (*Head)->PrevNode;
//
//		Tail->NextNode->PrevNode = NewNode;
//		Tail->NextNode = NewNode;
//
//		NewNode->NextNode = (*Head);
//		NewNode->PrevNode = Tail;
//
//	}
//}
//int main(void)
//{
//	int   i = 0;
//	int   Count = 0;
//	Node* List = NULL;
//	Node* NewNode = NULL;
//	Node* Current = NULL;
//
//	/*  ��� 5�� �߰� */
//	for (i = 0; i < 5; i++) //�� �ݺ����� 3�� ���� �������� �޸� ��� �׸���
//	{
//		NewNode = CreateNode(i);
//		AppendNode(&List, NewNode);
//		
//	}
//}

/*
	STACK	���Լ��� LIFO
	3���� ����
		push() ������ ����
		pop() ������ ����
		peek() ��� ������ ����
	1���� �Ӽ�
		stack�� ��ġ�� ����Ű�� top�����Ͱ� �����Ѵ�

	����Ʈ�� ���� (�迭, �̱� Ȥ�� ����� ���� ����)
*/

#define STACK_SIZE 5

int STACK[STACK_SIZE];
int top;

void init_stack(void) {
	top = -1;	// 0�� ���� ����. -1�̸� ������Ű�� ����, 0�̸� ���Խ�Ų �� �������Ѿ� ��.
}

void push(int data) {
	if (top >= STACK_SIZE-1)
	{
		printf("Stack Overflow\n");
		return;
	}
	STACK[++top] = data;
	printf("%d %d in\n", top, data );
}

int pop() {
	if (top <= -1) {
		printf("Stack Empty\n");
		return -1;
	}
	return STACK[top--];
}

main()
{
	init_stack();
	printf("%d\n", pop());
	push(8);
	push(5);
	push(1);
	push(2);
	push(3);
	push(4);
	push(6);
	printf("%d\n", pop());
	printf("%d\n", pop());
	printf("%d\n", pop());
	printf("%d\n", pop());
	printf("%d\n", pop());
	printf("%d\n", pop());
	printf("%d\n", pop());
	printf("%d\n", pop());
}