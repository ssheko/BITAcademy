#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#pragma warning(disable:4996)	// 새문법을 쓰지 않겠다.

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
	printf("접속할 URL: ");
	scanf("%s", &newUrl);

	// 뒤로 이동한 후 새로 접속했을 경우 위 스택 전부 pop한 후 새로 push
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
	printf("2. 방문기록 보기를 선택 하셨습니다.\n뒤로 이동할 수 있는 목록\n");
	printf("============================\n");

	for (int i = 0; i < curr; i++) {
		printf("%d. %s\n", i + 1, STACK[i]);
	}

	if (curr == top)
		return;

	printf("\n앞으로 이동할 수 있는 목록\n");
	printf("============================\n");

	for (int i = curr+1; i <= top; i++) {
		printf("%d. %s\n", count++, STACK[i]);
	}
}

void goback(void) {
	if (curr == 0) {
		printf("첫 번째 페이지입니다.\n");
		return;
	}
	curr--;
}

int goforward(void) {
	if (curr == top) {
		printf("더 이상 이동할 수 없습니다.\n");
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
		printf("1. URL 접속\n");
		printf("2. 방문 기록 보기\n");
		printf("3. 뒤로\n");
		printf("4. 앞으로\n");
		printf("0. 종료\n");
		printf("====================\n");
		printf("메뉴를 입력하세요: \n");
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
			printf("더 이상 이동할 수 없습니다.\n");
			forwardRetval = 0;
		}*/
			if (curr == -1)
				printf("현재 접속중인 웹 페이지: about: balnk\n");
			else
				printf("현재 접속중인 웹 페이지: %s\n", STACK[curr]);

			puts("");
	}
}