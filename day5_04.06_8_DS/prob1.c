/* 
	1~10까지 랜덤함수 받아와서 오름차순으로 저장
	맨 앞쪽으로 옮겨야하는 정보를 입력받고, 
	앞 노드와 바꿔야 하는 정보를 입력받음.
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <Windows.h>

#pragma warning(disable:4996)	// 새문법을 쓰지 않겠다.

typedef struct List {
	int data;
	struct List *next;
}List;

List *head, *tail;

void init() {
	head = (List*)malloc(sizeof(List));
	tail = (List*)malloc(sizeof(List));

	head->next = tail;
	tail->next = tail;
}
void print() {
	List* node = (List*)malloc(sizeof(List));
	node = head->next;
	printf("출력 : ");
	while (node != tail) {
		printf("%d ", node->data);
		node = node->next;
	}
	printf("\n");
}

void insert() {
	int randNum;
	int count = 0;
	List *check = (List*)malloc(sizeof(List));
	List *prev = (List*)malloc(sizeof(List));
	List *newNode;

	while (count < 10) {
		system("cls");
		check = head->next;
		prev = head;
		randNum = rand() % 10 + 1;
		// 처음 입력되는 값일 경우
		if (check == tail) {
			newNode = (List*)malloc(sizeof(List));
			newNode->data = randNum;
			newNode->next = tail;
			head->next = newNode;
			count++;
		}
		else {
			while (check->data <= randNum && check != tail) {
				prev = check;
				check = check->next;
			}			
			// 기준 노드(check)와 이전 노드(prev) 모두 randNum과 중복되지 않을 경우
			if (check->data != randNum && prev->data != randNum) {
				newNode = (List*)malloc(sizeof(List));
				newNode->data = randNum;
				newNode->next = check;

				prev->next = newNode;

				printf("%d\n", randNum);
				count++;
			}
			// 중복되는 값이 존재할 경우 
			else {
				printf("%d는 중복된 값입니다.\n", randNum);
				continue;
			}
		}

		// 노드 전체 출력
		print();
		Sleep(200);
	}
}

void moveToFront(int num) {
	List *check = (List*)malloc(sizeof(List));
	List *prev = (List*)malloc(sizeof(List));
	check = head->next;
	prev = head;

	while (check->data != num && check != tail) {
		prev = check;
		check = check->next;
	}

	// 원하는 정보를 찾지 못했을 경우
	if (check == tail)
		return;
	else {
		prev->next = check->next;
		check->next = head->next;
		head->next = check;
	}
}

void transpose(int num) {
	List *check = (List*)malloc(sizeof(List));
	List *prev = (List*)malloc(sizeof(List));
	List *pprev = (List*)malloc(sizeof(List));
	check = head->next;
	prev = head;

	while (check->data != num && check != tail) {
		pprev = prev;
		prev = check;
		check = check->next;
	}

	// 맨 앞의 노드이거나 원하는 정보를 찾지 못했을 경우
	if (prev == head || check == tail) {
		return;
	}
	else {
		pprev->next = check;
		prev->next = check->next;
		check->next = prev;
	}
}


main()
{
	int num;

	getchar();
	init();
	srand((unsigned)time(NULL));
		insert();
		printf("완성되었습니다.\n");
		getchar();

		while (1) {
		printf("맨 앞쪽으로 옮겨야하는 정보를 입력하시오: ");
		scanf("%d", &num);
		puts("");
		moveToFront(num);
		print();

		printf("앞 노드와 바꿔야 하는 정보를 입력하시오: ");
		scanf("%d", &num);
		puts("");
		transpose(num);
		print();
	}

}