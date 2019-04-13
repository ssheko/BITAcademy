#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#pragma warning(disable:4996)	// �������� ���� �ʰڴ�.

#define STACK_SIZE 5
char STACK[STACK_SIZE][20];
int top, curr;

void initStack(void) {
	top = -1;
	curr = -1;
}

void push(char *data) {
	if (top >= STACK_SIZE - 1) {
		printf("STACK OVERFLOW\n");
		return;
	}
	curr++;
	//STACK[++top] = (char*)malloc(strlen(data) * sizeof(char) +1);
	strcpy(STACK[++top], data);
}

char *pop(void) {
	if (top <= -1) {
		printf("abot: blank\n");
		return NULL;
	}		

	return STACK[top--];
}

void pushURL(void) {
	char newUrl[20];
	int count = top - curr;
	printf("������ URL: ");
	scanf("%s", &newUrl);

	// �ڷ� �̵��� �� ���� �������� ��� �� ���� ���� pop�� �� ���� push
	if (top != curr) {
		
		for (int i = 0; i <= count; i++) {
			pop();
		}
		curr = top;
	}
	push(newUrl);
}

void printStack(void) {

	int count = 1;
	printf("2. �湮��� ���⸦ ���� �ϼ̽��ϴ�.\n�ڷ� �̵��� �� �ִ� ���\n");
	printf("============================\n");

	for (int i = 0; i < curr; i++) {
		printf("%d. %s\n", i + 1, STACK[i]);
	}

	if (curr == top)
		return;

	printf("\n������ �̵��� �� �ִ� ���\n");
	printf("============================\n");

	for (int i = curr+1; i <= top; i++) {
		printf("%d. %s\n", count++, STACK[i]);
	}
}

void goback(void) {
	if (curr == 0) {
		printf("ù ��° �������Դϴ�.\n");
		return;
	}
	curr--;
}

int goforward(void) {
	if (curr == top) {
		printf("�� �̻� �̵��� �� �����ϴ�.\n");
		return -1;
	}
	curr++;
	return 0;
}

main()
{
	int input;
	int forwardRetval = 0;
	initStack();

	while (1) {
		printf("====================\n");
		printf("1. URL ����\n");
		printf("2. �湮 ��� ����\n");
		printf("3. �ڷ�\n");
		printf("4. ������\n");
		printf("0. ����\n");
		printf("====================\n");
		printf("�޴��� �Է��ϼ���: \n");
		scanf("%d", &input);
		if (input == 0)
			break;

		switch (input) {
		case 1:
			pushURL();
			break;
		case 2:
			printStack();
			break;
		case 3:
			goback();
			break;
		case 4:
			goforward();
			break;
		default:
			break;
		}
/*
		if (forwardRetval == -1) {
			printf("�� �̻� �̵��� �� �����ϴ�.\n");
			forwardRetval = 0;
		}*/
			if (curr == -1)
				printf("���� �������� �� ������: about: balnk\n");
			else
				printf("���� �������� �� ������: %s\n", STACK[curr]);

			puts("");
	}
}