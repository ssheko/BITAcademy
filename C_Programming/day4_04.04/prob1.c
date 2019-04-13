#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#pragma warning(disable:4996)	// 새문법을 쓰지 않겠다.
//
//
//main()
//{
//	// heap 공간에 n개의 배열이 만들어짐
//	// 더블포인터 (스택) -> 포인터배열(힙) -> 문장 배열 (힙)
//	// 스택에 버퍼를 두고 문장 입력받고 힙에 문장 저장
//	char **p;
//	int num;
//	char input[100];	// 포인터상수
//
//	printf("원하는 문장의 갯수를 입력하세요? ");
//	scanf("%d", &num);
//	getchar();
//
//	p = (char**)malloc((num+1) * sizeof(char*));	// 포인터 배열
//	
//
//	for(int i=0; i<num; i++){
//		printf("%d번째 문장은?\n", i);
//		gets(input);
//
//		p[i] = (char*)malloc(strlen(input) + 1);
//		strcpy(p[i], input);
//	}
//	//p[num] = (char*)malloc(strlen(input) + 1);
//	//p[num] = NULL;
//
//	for (int i = 0; i <= num; i++)
//		printf("%s\n", p[i]);
//
//	//while (*p) {
//	//	printf("%s\n", *p++);
//	//}
//
//	for (int i = 0; i < num; i++)
//		free(p[i]);
//
//	free(p);
//}