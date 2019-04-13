#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//#pragma warning(disable:4996)	// 새문법을 쓰지 않겠다.

/*
 자료구조 (자료를 어떻게 저장할 것인가) 의 종류
	* 모든 자료구조는 반드시 초기화 함수가 있다.
	1. list (순서가 있는 구조)
		1-1. 정렬: select, bubble, insert, indirect-insert, shell, merge, quick Sort
		1-2. circular list, double linked list
		1-3. linux kernel (linked list)
	2. stack (last input first out : LIFO)
		2-1. 함수 콜 스택 내부 구조 (콜백 함수의 형태)
	3. queue (FIFO) - 기수정렬
	4. tree	(보통 이진트리, binary tree) - linux (Red-black T)
			- Tree sort
		4-1. 삼성폰: 공장초기화 (hash-Tree의 재구성)	// hash, tree 둘 다 빠름
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
///*  노드 추가 */
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
//	/*  노드 5개 추가 */
//	for (i = 0; i < 5; i++) //이 반복문이 3번 도는 경우까지의 메모리 모양 그리기
//	{
//		NewNode = CreateNode(i);
//		AppendNode(&List, NewNode);
//		
//	}
//}

/*
	STACK	후입선출 LIFO
	3가지 동작
		push() 데이터 삽입
		pop() 데이터 삭제
		peek() 상단 데이터 보기
	1가지 속성
		stack의 위치를 가리키는 top포인터가 존재한다

	리스트로 구현 (배열, 싱글 혹은 더블로 구현 가능)
*/
//
//#define STACK_SIZE 5
//
//int STACK[STACK_SIZE];
//int top;
//
//void init_stack(void) {
//	top = -1;	// 0일 수도 있음. -1이면 증가시키고 삽입, 0이면 삽입시킨 후 증가시켜야 함.
//}
//
//void push(int data) {
//	if (top >= STACK_SIZE-1)
//	{
//		printf("Stack Overflow\n");
//		return;
//	}
//	STACK[++top] = data;
//	printf("%d %d in\n", top, data );
//}
//
//int pop() {
//	if (top <= -1) {
//		printf("Stack Empty\n");
//		return -1;
//	}
//	return STACK[top--];
//}
//
//main()
//{
//	init_stack();
//	printf("%d\n", pop());
//	push(8);
//	push(5);
//	push(1);
//	push(2);
//	push(3);
//	push(4);
//	push(6);
//	printf("%d\n", pop());
//	printf("%d\n", pop());
//	printf("%d\n", pop());
//	printf("%d\n", pop());
//	printf("%d\n", pop());
//	printf("%d\n", pop());
//	printf("%d\n", pop());
//	printf("%d\n", pop());
//}

/* 함수 콜스택 내부 */
////#include <stdarg.h>
#include <stdio.h>
typedef char *  myva_list;	// x86, x64
#define _INTSIZEOF(n)   ( (sizeof(n) + sizeof(int) - 1) & ~(sizeof(int) - 1) )
#define va_start(ap,v)  ( ap = (myva_list)&v + _INTSIZEOF(v) )
#define va_arg(ap,t)    ( *(t *)((ap += _INTSIZEOF(t)) - _INTSIZEOF(t)) )
#define va_end(ap)      ( ap = (myva_list)0 )


float average(int num, ...)
{
	myva_list arg_ptr;
	int cnt, total = 0;

	va_start(arg_ptr, num);

	for (cnt = 0; cnt < num; cnt++)
		total += va_arg(arg_ptr, int);

	va_end(arg_ptr);

	return ((float)total / num);
}

main()
{
	float x;

	x = average(10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
	printf("first avg is %f\n", x);
}
