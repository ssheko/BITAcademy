/* 
	1~10���� �����Լ� �޾ƿͼ� ������������ ����
	�� �������� �Űܾ��ϴ� ������ �Է¹ް�, 
	�� ���� �ٲ�� �ϴ� ������ �Է¹���.
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <Windows.h>

#pragma warning(disable:4996)	// �������� ���� �ʰڴ�.

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
	printf("��� : ");
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
		// ó�� �ԷµǴ� ���� ���
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
			// ���� ���(check)�� ���� ���(prev) ��� randNum�� �ߺ����� ���� ���
			if (check->data != randNum && prev->data != randNum) {
				newNode = (List*)malloc(sizeof(List));
				newNode->data = randNum;
				newNode->next = check;

				prev->next = newNode;

				printf("%d\n", randNum);
				count++;
			}
			// �ߺ��Ǵ� ���� ������ ��� 
			else {
				printf("%d�� �ߺ��� ���Դϴ�.\n", randNum);
				continue;
			}
		}

		// ��� ��ü ���
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

	// ���ϴ� ������ ã�� ������ ���
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

	// �� ���� ����̰ų� ���ϴ� ������ ã�� ������ ���
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
		printf("�ϼ��Ǿ����ϴ�.\n");
		getchar();

		while (1) {
		printf("�� �������� �Űܾ��ϴ� ������ �Է��Ͻÿ�: ");
		scanf("%d", &num);
		puts("");
		moveToFront(num);
		print();

		printf("�� ���� �ٲ�� �ϴ� ������ �Է��Ͻÿ�: ");
		scanf("%d", &num);
		puts("");
		transpose(num);
		print();
	}

}