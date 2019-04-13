/* Linked List로 삽입, 삭제, 수정, 정렬 */
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int data;
	struct Node* next;
} Node;

struct Node* head, *tail;

void init();
void addEnd(int data);
void add(int data, int newData);
void deleteNode(int data);
void modify(int data, int newData);
void sort();
void printAll();

int main() {

	init();
	addEnd(1);
	addEnd(2);
	addEnd(4);
	//add(2, 3);	// 2 노드 뒤에 3 노드 추가

	printAll();

	deleteNode(2);
	printAll();

	deleteNode(4);
	printAll();

	deleteNode(1);
	printAll();

	return 0;
}

void init() {
	Node *headNode = (Node*)malloc(sizeof(struct Node));
	Node *tailNode = (Node*)malloc(sizeof(struct Node));
	headNode->next = NULL;
	headNode->data = NULL;
	head = headNode;

	tailNode->next = NULL;
	tailNode->data = NULL;
	tail = tailNode;
}

void addEnd(int data) {
	// 리스트 가장 마지막에 새 노드 추가
	Node *newNode = (Node*)malloc(sizeof(struct Node));
	newNode->data = data;

	if (head->data == NULL) {
		head = newNode;
		newNode->next = NULL;
		tail = newNode;
	}
	else {
	/*	tail = head;
		while (tail->next != NULL) {
			tail = tail->next;
		}*/
		tail->next = newNode;
		tail = newNode;
	}
}
void add(int data, int newData) {	// 추가할 위치, 추가할 데이터
	Node *checkNode = (Node*)malloc(sizeof(struct Node));
	Node *newNode = (Node*)malloc(sizeof(struct Node));
	newNode->data = data;
	checkNode = head;

	while (checkNode->data != data && checkNode != tail) {
		checkNode = checkNode->next;
	}
	newNode->next = checkNode->next;
	checkNode->next = newNode;
}


void deleteNode(int data) {
	Node *checkNode = (Node*)malloc(sizeof(struct Node));
	Node *prevNode = (Node*)malloc(sizeof(struct Node));
	checkNode = head;
	prevNode = head;
	
	while (checkNode->data != data && checkNode != tail) {
		prevNode = checkNode;
		checkNode = checkNode->next;
	}

	if (checkNode == head) {
		checkNode->next = NULL;
		head = NULL;
		free(checkNode);
	}
	else if (checkNode == tail) {
		prevNode->next = NULL;
		tail = prevNode;
		free(checkNode);
	}
	else {
		prevNode->next = checkNode->next;
		free(checkNode);
	}		
}

void modify(int data, int newData) {
	Node *checkNode = (Node*)malloc(sizeof(struct Node));
	checkNode = head;

	while (checkNode->data != data && checkNode != tail) {
		checkNode = checkNode->next;
	}
	
	checkNode->data = newData;
}

void printAll() {
	Node *checkNode = (Node*)malloc(sizeof(struct Node));
	checkNode = head;

	while (checkNode != NULL && checkNode != tail) {
		printf("%d  ", checkNode->data);
		checkNode = checkNode->next;
	}

	// tail 출력
	if(checkNode != NULL)
		printf("%d  ", checkNode->data);
	else
		printf("빈 노드입니다.");

	printf("\n");
}

void sort() {

}