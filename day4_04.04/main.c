#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#pragma warning(disable:4996)	// �������� ���� �ʰڴ�.

/* 2���� �迭�� 1����ó�� �ޱ� */
//void array_1to2(char *p) {
//	puts(p);
//}
//
/* 2���� �迭�� 2����ó�� �ޱ� */
//void array_2to2(char p[1000][10]) {	// ���� ũ�� 10���� ������� ��
//	puts(p[2]);
//}
//
//main()
//{
//	char a[3][10] = { "abc", "defg", "zzzzzzz" };	// 10��¥�� ��� 3��
//	array_1to2(a[2]);
//	array_2to2(a);
//}

/* ������, �迭 ������, ������ �迭, �迭 */
//void print_a(char *p[10])	// char **p	// char *p[]
//{
//	// 0��°�� abc���� bc�� ���(������, �迭 ������, ������ �迭, �迭)
//	
//	printf("%s\n", &(*p)[1]);	// *p+1	// p[0]+1
//		//printf("%c%c\n", p[0][1], p[0][2]);
//	// 1��°�� home���� h�� ���
//	printf("%c\n", 1[p][0]);	// *(p[1])	// *(*(p+1))	// (*(p+1))[0]	// 1[p][0]	// 0[1[p]]
//	// 2��°�� print���� i�� ����ϴ� print��
//	printf("%c\n", p[2][2]);	// *(p[2]+2)	// *(*(p+2)+2)	// (*(p+2))[2]
//}
//
//main()
//{
//	char *a[3] = { "abc", "home", "print" };	// 10��¥�� ��� 3��
//	print_a(a);
//}

/* argc, *argv[] �̿��� ���� */
/* �Ӽ�-> ���� �Ӽ� -> ����� -> ��� �μ� */
//main(int argc, char *argv[]) {
//	// ����� �ڵ�
//	int fir = atoi(argv[1]);	// "123" -> 123
//	int sec = atoi(argv[3]);	// "10" -> 10
//
//	switch (argv[2][0])	// *(argv[2])
//	{
//	case '+':
//		printf("%d + %d = %d\n", fir, sec, fir + sec);
//		break;
//	case '-':
//		printf("%d - %d = %d\n", fir, sec, fir - sec);
//		break;
//	case '*':
//		printf("%d * %d = %d\n", fir, sec, fir * sec);
//		break;
//	case '/':
//		printf("%d / %d = %d\n", fir, sec, fir / sec);
//		break;
//	}
//
//	//int num = 0,  sum = 0, caseNum = 0;
//	//char op[2][5] = { '+',  '-' ,'*' ,'/' };
//	//while (*++argv) {
//	//	printf("%s ", *argv);
//	//	
//
//	//	if (strcmp(*argv, '+')) {
//	//		caseNum = 0;
//	//		continue;
//	//	}
//	//	else if (strcmp(*argv, '-')) {
//	//		caseNum = 1;
//	//		continue;
//	//	}
//	//	else if (strcmp(*argv, '*')) {
//	//		caseNum = 2;
//	//		continue;
//	//	}
//	//	else if (strcmp(*argv, '/')) {
//	//		caseNum = 3;
//	//		continue;
//	//	}
//	//	else
//	//		num = atoi(*argv);
//
//	//	switch(caseNum) {
//	//		case 0:
//	//			sum += num;
//	//			break;
//	//		case 1:
//	//			sum -= num;
//	//			break;
//	//		case 2:
//	//			sum *= num;
//	//			break;
//	//		case 3:
//	//			sum /= num;
//	//			break;
//	//		default:
//	//			break;
//	//	}
//
//	//}
//	//printf("= %d\n", sum);
//}

/* �Լ� ������ */
//// �Լ��� �ּҴϱ� �Լ��� ����Ű�� �����͵� ���� ���̴�.
//int add(int a, int b) { return a + b; }
//int sub(int a, int b) { return a - b; }
//int mul(int a, int b) { return a * b; }
//int dvv(int a, int b) { return a / b; }
//
//main()
//{
//	int rlt;
//	//int *p(int, int);	// int�� �����͸� �����ϴ� ������
//	//int(*p)(int, int);	// �Լ� ������
//	////int(*p)[3];	// �迭 ������
//	//p = add;
//	//
//	//rlt = p(10, 5);
//	//printf("%d\n", rlt);
//
//	//p = sub;
//
//	//rlt = p(10, 5);
//	//printf("%d\n", rlt);
//
//	//p = mul;
//
//	//rlt = p(10, 5);
//	//printf("%d\n", rlt);
//
//	//p = dvv;
//
//	//rlt = p(10, 5);
//	//printf("%d\n", rlt);
//
//
//	int(*p[4])(int, int) = { add, sub, mul, dvv };	// 4��¥�� �Լ� ������ �迭
//
//	for (size_t i = 0; i < 4; i++) {
//		printf("%d\n", p[i](10, 5));
//	}
////
////	rlt = add(10, 5);
////	printf("%d\n", rlt);
//}

/* �Լ� �����Ϳ� �Ű����� */
//int add(int a, int b) { return a + b; }
//int sub(int a, int b) { return a - b; }
//
//int temp(int(*p_func)(int, int), int a, int b) {
//
//	return p_func(a, b);	// leaf function call	// �ӵ��� �� ��������.
//}
//
//void main()
//{
//	int a = 10, b = 5;
//
//	printf("%d", temp(add, a, b));
//}

/* �Լ� �������� Ÿ������ */
//typedef unsigned int unit;
//
//typedef int(*myfp_t)(int, int);
//
//int add(int a, int b) { return a + b; }
//
//int temp(myfp_t p, int a, int b) {
//
//	return p(a, b);	// leaf function call	// �ӵ��� �� ��������.
//}
//
//void main()
//{
//	int a = 10, b = 5;
//
//	printf("%d", temp(add, a, b));
//}

/* ���� ������ */
//main()
//{
//	void *p;	// ���� ������	// ��� ������ �ּ�
//
//	char ch = 'A';
//	p = &ch;	// �ּҸ� ��������� � Ÿ���� ����ִ��� �𸥴�.
//	printf("%d\n", *(char *)p);	// �� (char�� �ּҷ� �ٲ㼭)p	// p�� ���� �ּҸ� char�� �ּҷ� �ٲ㼭 ���� ���ڴ�.
//
//	int i = 123;
//	p = &i;
//	printf("%d\n", *(int *)p);	// p�� ���� �ּҸ� int�� �ּҷ� �ٲ㼭 �� ����
//
//	char arr[] = "abcde";
//	p = arr;
//	printf("%s\n", (char*)p);	// abcde�� ����ϴ� ���
//
//	printf("%c %c %c\n", *(char*)p, *((char*)p+1), *((char*)p+2));	// a b c�� ����ϴ� ���
//
//	printf("%c\n", *((char*)p)++);	// p++�� ���·� ���� 'a'
//	printf("%c\n", *(char*)p);	// 'b'
//}

/* ���� �����͸� ����� ���� */
//int add(int a, int b) { return a + b; }
//int sub(int a, int b) { return a - b; }
//int mul(int a, int b) { return a * b; }
//int dvv(int a, int b) { return a / b; }
//
//typedef int(*p_t)(int, int);	// �Լ������� Ÿ��
//main()
//{
//	void *arr[5][2] = { {add, "ADDITION"},{sub, "SUBTRACTION"},{mul, "MULTIPLY"},{dvv, "DIVIDE"}, {0,0} };
//
//	void **vp;
//	int(*p)(int, int);
//
//	int num = 0;
//	
//	vp = arr;
//	
//	for (int i = 0; i<4; i++) {
//		printf("%d. %s\n", i, (char*)arr[i][1]);
//		//printf(" %s", *((char*)vp)++);
//	}
//	
//	printf("��ȣ�� �����ϼ���: ");
//	scanf("%d", &num);
//
//	p = arr[num-1][0];	// *(arr[num-1])
//	
//	printf("�����: %d\n", p(10, 5));	// ((p_t)p[num-1][0])(10,5)
//
//}
//
//main()
//{
//	void *arr[2][5] = { { add, sub, mul, dvv, 0}, {"ADDITION", "SUBTRACTION", "MULTIPLY", "DIVIDE", 0 } };
//
//	void **vp;	// a[0] = *a �̹Ƿ�, a[1] = *(a+1) �̱⶧���� ���������ͷ� �����ؾ� �Ѵ�.
//	int(*p)(int, int);
//
//	vp = (arr +1);
//
//	for (int i = 0; *((char**)vp); i++) {
//		printf("%d. %s\n", i, 
//			*((char**)vp)++);
//	}
//}

/* �� ����, ������ */
//main()
//{
//	//int size;
//	//scanf("%d", &size);
//
//	//int arr[size];	// �̷��� �ص� ������ ������ �����Ϸ��� �̸� ���ġ ����
//
//	int *p;	// �������� �����ϴ� �Ŷ� �ݵ�� ������ ��� ��. (�� ������ �����ϴ� �͵��� �̸��� ���� ������ �����͸� �̿��� ���������� ������ ���ۿ� ����)
//
//	p = malloc(4);	// 4����Ʈ �޸𸮸� ����� �ּҸ� ����
//		// heap�� �����ϴ� 4����Ʈ �޸�
//
//	int a;	// stack���� 4byte �޸𸮸� ����Ű�� ���
//	int *p;
//	p = &a;
//
//	// heap, stack �� �� �����ͷ� �����ϴ� ����� �Ȱ���
//
//
//	int a[5];
//	int *p = a;
//
//	int *p;
//	p = (int*)malloc(5 * sizeof(int));	// ����Ÿ���� ���������� Ÿ��. ���� int* Ÿ������ ĳ�����ؾ� �Ѵ�.
//
//
//}

/*
	�ڽ��� �ּҸ� �Է¹޾Ƽ� �� �´� �ּ��� ũ�⸸ŭ�� ���� �Ҵ��ϰ� ���� �� ���
*/
//main()
//{
//	char *add_heap;
//	char add[100];
//	int i = 0;
//	
//	gets(add);
//
//	add_heap = (char*)malloc(strlen(add) * sizeof(char) + 1);	// null���ڸ� ���� ���� 1 �߰��ؾ� ��
//	//printf("%s %d %d\n", add_heap, strlen(add), strlen(add_heap));
//	strcpy(add_heap, add);	// copy�� �� null���� �������������, malloc�� �� ����� +1�� ������ �ʾ����� null�� ������� �ʴ´�.
//
//	puts(add_heap, add);
//
//	free(add_heap);	// free�� null���ڰ� ���ö����� �Ҹ��Ű�µ� null���ڰ� copy���� ���� ���¿��ٸ� �����Ǵ� ������ �ӹ����ְ� �ȴ�.
//}

/* FILE stream (pipeline) */
//main()
//{
//	int num;
//	char ch;
//	char name[10];
//
//	FILE *fwp, *frp;	// ������ ����. a.txt �ּҰ����� �ƴ� �ٸ� �ּҰ��� ���� ���� �ִ�.
//	fwp = fopen("a.txt", "w");	// ��½�Ʈ�� fwp
//
//	fprintf(fwp, "%d %c ", 1, 'A');
//
//	fclose(fwp);
//
//	frp = fopen("a.txt", "r");		// �Է½�Ʈ�� frp
//	fscanf(frp, "%d %c", &num, &ch);
//	fclose(frp);
//
//	fwp = fopen("a.txt", "a");	// "a": append ; ������ �������� ���� �߰�.
//	scanf("%s", &name);
//	fprintf(fwp, "%s\n", name);
//	fclose(fwp);
//
//	frp = fopen("a.txt", "r");
//	fscanf(frp, "%d %c", &num, &ch);
//	fscanf(frp, "%s", &name);
//	fclose(frp);
//
//	printf("%s\n", name);
//}

/* FILE ���� */
//main()
//{
//	FILE *wp, *rp;
//	int count = 0;
//	char buf[100];
//	rp = fopen("1.jpg", "rb");	// binary ���·� read
//	wp = fopen("2.jpg", "wb");
//	int totalSize = 0;
//	// �� ����Ʈ �а� �� ����Ʈ ����	
//	// �� �� �а� �� �� ����
//
//	// ���ϴ� ��ŭ �а� ����
//	while (1) {
//
//		// 100���� ���۱��� �� ��������� 100�� ���ϵȴ�. ���� 10���� �������� 10�� ���ϵ�. ���ϰ��� �̿��� ���� �˾Ƴ� �� �ִ�. 100���� �ִٰ� ���� ���� 100���� ���� �� ����.
//		count = fread(buf, sizeof(char), 100, rp);
//		if (count < 100) {
//			// �� ������ ��� count�� 100���� �۴�.
//			if (feof(rp))	// eof = end of file	// 0	// ������ ������ ����
//			{
//				// ������ ���� 0�� �ƴ� ���� ����. ������ �д� ��� 0. ������ �����־ ������ ���� �ƴϹǷ� 0�� �����Ѵ�.
//				// ���� ��ŭ�� ����
//				totalSize += count;
//				fwrite(buf, sizeof(char), count, wp);
//				puts("���� �Ϸ�");
//			}
//			else
//				puts("���� ����");
//			
//			break;
//		}
//		totalSize += count;
//		//printf("%dbyte ���� �Ϸ�\n", totalSize);
//		fwrite(buf, sizeof(char), 100, wp);
//	}
//
//	printf("%dbyte ���� �Ϸ�\n", totalSize);
//
//	fclose(rp);
//	fclose(wp);
//}