#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#pragma warning(disable:4996)	// �������� ���� �ʰڴ�.
//
//
//main()
//{
//	// heap ������ n���� �迭�� �������
//	// ���������� (����) -> �����͹迭(��) -> ���� �迭 (��)
//	// ���ÿ� ���۸� �ΰ� ���� �Է¹ް� ���� ���� ����
//	char **p;
//	int num;
//	char input[100];	// �����ͻ��
//
//	printf("���ϴ� ������ ������ �Է��ϼ���? ");
//	scanf("%d", &num);
//	getchar();
//
//	p = (char**)malloc((num+1) * sizeof(char*));	// ������ �迭
//	
//
//	for(int i=0; i<num; i++){
//		printf("%d��° ������?\n", i);
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