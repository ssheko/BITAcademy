#include <stdio.h>
#pragma warning(disable:4996)	// �������� ���� �ʰڴ�.

/* call by value */
//void change(int a)
//{
//	a = 100;
//}
//
//main()
//{
//	int a = 7;
//	change(a);	// call by value
//	printf("%d\n", a);	// 7 ���
//}

/* call by reference */
//void change(int *a)
//{
//	*a = 100;
//}
//
//main()
//{
//	int a = 7;
//	//int *p;
//	//p = &a;
//
//	change(&a);
//	printf("%d\n", a);
//
//}

/* pointer */
//void swap(int *a, int *b)
//{
//	int tmp = *a;
//	*a = *b;
//	*b = tmp;
//}
//
//main()
//{
//	int a = 10, b = 5;
//
//	swap(&a, &b);
//	printf("%d %d\n", a, b);
//}

/* �迭, ������ */
//void check(int *p) {
//	// p�� �̿��� a�� ��� �� ���
//	for (int i = 0; i < 5; i++)
//		printf("%d ", *p++);
//
//	printf("%d\n", sizeof(p) / sizeof(p[0]));	// �迭�� ũ�⸦ �� �� �����Ƿ� ũ�⸦ �Ű������� �Բ� �Ѱ���� �Ѵ�.
//	// 2�� ��µ�
//
//
//	printf("\n ");
//	while(*p != NULL)
//		printf("%d ", *p++);*/
//}
//
//// check ��������
//void check(int *p, int size) {
//	// p�� �̿��� a�� ��� �� ���
//	for (int i = 0; i < size; i++)
//		printf("%d ", p[i]);	// *(p+i) ����
//
//}
//
//main()
//{
//	int a[5] = { 3,4,1,5,2 };
//	int size_a = sizeof(a) / sizeof(a[0]);
//	//printf("%d\n", sizeof(a) / sizeof(a[0]));	// 5�� ���
//	//check(a);
//	check(a, size_a);
//	
//	int *p;
//	p = a;	// a == &a[0] // �迭����  ���ο���� �ּ�
//}


/* �迭, ������ 2 */
// ���ĸŰ����� *p�� ����Ͽ� ���ĺ� k�� ������ ������ ����ϴ� �Լ�
//void put_a(char *p) {
//	// ���: abcdefghij
//	//for (int i = 0; i < 26; i++) {
//	//	if (p[i] == 'k')
//	//		break;
//	//	printf("%c ", p[i]);	// *(p+i) ����
//	//}
//
//	for (int i = 0; p[i] != 'k'; i++) {
//		printf("%c ", p[i]);	// *(p+i) ����
//	}
//}
//
//main()
//{
//	char a[] = "abcdefghijklmnopqrstuvwxyz";
//
//	put_a(a);
//}
//
//void put_a(char *p) {
//	// ���: abcdefghij
//
//	// ���ع����κ��� ����� �Ÿ��� ã�ư��鼭 ���
//	//for (int i = 0; p[i] != '\0'; i++) {
//	//	printf("%c", p[i]);	// *(p+i) ����
//	//}
//	//printf("\n");	// putchar('\n');	// puts("");	// ���๮�� ���
//
//	// ���ع����� �̵���Ű�鼭 ����ϱ� ������ for������ �ξ� ������.
//	while (*p)
//		putchar(*p++);
//	putchar('\n');
//}
//
//main()
//{
//	char a[] = "abcdefghijklmnopqrstuvwxyz";
//	puts(a);	// �������� ���๮�� ����
//	put_a(a);
//}

#include <string.h>

/* mystrcpy */
//void mystrcpy(char *dst, char *src) {
//	//while (*src)
//	////for (int i = 0; src[i] != '\0'; i++) 
//	//	*dst++ = *src++;
//	//// NULL�� ������ while���� ���� ������ �������� NULL�� �߰�
//	//*dst = '\0';
//
//	while (*dst++ = *src++);
//}
//
//main()
//{
//	char dst[100];
//	char src[] = "abcde";
//
//	mystrcpy(dst, src);
//	//strcpy(dst, src);
//
//	puts(dst);	// abcde
//}


/* mystrcat */
//void mystrcpy(char *dst, char *src) {
//	while (*dst++ = *src++);
//}
//void mystrcat(char *dst, char *src) {
//	//while (*dst != '\0')
//	//while (*dst)
//	//	*dst++;
//
//	//while(*dst++);	// null�� ���� �������� ++�� ���¿��� �߰��Ʊ� ������ abcde\0zzz �� �߰��� ����.
//	while (*++dst);
//	while (*dst++ = *src++);
//}
//
//main()
//{
//	char dst[100];
//	char src[] = "abcde";
//
//	mystrcpy(dst, src);
//	mystrcat(dst, "zzz");
//
//	puts(dst);	// abcde
//}

/* ���� ������ 1 */
//main()
//{
//	int a;
//	int *p;
//	int **k;
//	p = &a;
//	k = &p;
//
//	scanf("%d", &a);	// aǥ������ a�� �Է�
//	printf("%d\n", a);
//
//	scanf("%d", p);	// pǥ������ a�� �Է�
//	printf("%d\n", *p);
//
//	scanf("%d", *k);	// kǥ������ a�� �Է�
//	printf("%d\n", **k);
//}

/* ���� ������ 2 */
//void connect(int *a, int **p) {
//	*p = a;	// *(p�� �ּ�) = (a�� ��)
//}
//main()
//{
//	int a = 7;
//	int *p;
//	connect(&a, &p);
//	printf("%d\n", *p);	// 7���
//}

/* ���� ������ (swap) */
//#define A 6
//// main�� ��ġ�� a, b������ �ּҸ� ���޹޾� a, b���� ��ȯ�ϴ� �Լ�
//#if A == 1
//void swap(int *a, int *b) {
//	int temp = *a;
//	*a = *b;
//	*b = temp;
//}
//#elif A == 2
//// ap,bp ������ �ּҸ� ���޹޾� a, b���� ��ȯ�ϴ� �Լ�
//void swap(int **ap, int **bp) {
//	int temp = **ap;	// a
//	**ap = **bp;
//	**bp = temp;
//}
//#elif A == 3
//// app,bpp ������ �ּҸ� ���޹޾� a, b���� ��ȯ�ϴ� �Լ�
//void swap(int ***app, int ***bpp) {
//	int temp = ***app;	// 1,2,3 ���̽��� ��� a, b��
//	***app = ***bpp;
//	***bpp = temp;
//
//}
//#elif A == 4
//// ap,bp ������ �ּҸ� ���޹޾� ap, bp���� ��ȯ�ϴ� �Լ�
//void swap(int **ap, int **bp) {
//	int *temp = *ap;
//	*ap = *bp;
//	*bp = temp;
//}
//#elif A == 5
//// app,bpp ������ �ּҸ� ���޹޾� ap, bp���� ��ȯ�ϴ� �Լ�
//void swap(int ***app, int ***bpp) {
//	int *temp = **app;
//	**app = **bpp;
//	**bpp = temp;
//}
//#elif A == 6
//// app,bpp ������ �ּҸ� ���޹޾� app, bpp���� ��ȯ�ϴ� �Լ�
//void swap(int ***app, int ***bpp) {
//	int **temp = *app;
//	*app = *bpp;
//	*bpp = temp;
//}
//#endif
//
//main()
//{
//	int a = 10, b = 20;
//	int *ap = &a, *bp = &b;
//	int **app = &ap;
//	int **bpp = &bp;
//	printf("a: %d b: %d\n", a, b);
//	printf("ap: %p bp: %p\n", ap, bp);
//	printf("app: %p bpp: %p\n", app, bpp);
//	printf("\n");
//#if A == 1
//	swap(&ap, &bp);
//#elif A == 2
//	swap(&ap, &bp);
//#elif A == 3
//	swap(&app, &bpp);
//#elif A == 4
//	swap(&ap, &bp);
//#elif A == 5
//	swap(&app, &bpp);
//#elif A == 6
//	swap(&app, &bpp);
//#endif
//	printf("a: %d b: %d\n", a, b);
//	printf("ap: %p bp: %p\n", ap, bp);
//	printf("app: %p bpp: %p\n", app, bpp);
//}

/* ������/���� �����ͷ� �� ���� */
//void last(int *ka) {
//	*ka = 300;	// ka�� a�� �ּҸ� ����Ʈ
//}
//
//void middle(int *pa)
//{
//	*pa = 200;
//	last(pa);
//}
//
//main()
//{
//	int a = 100;
//	middle(&a);
//	printf("%d\n", a);	// 300
//}
//
//// �� �� ���� �����
//
//void last(int **ka) {
//	**ka = 300;	// **(pa �ּ�) = * (a �ּ�) = a = 300
//}
//
//void middle(int *pa)
//{
//	*pa = 200;
//	last(&pa);	// pa�ּҸ� ka���� ��
//}
//
//main()
//{
//	int a = 100;
//	middle(&a);
//	printf("%d\n", a);
//}

/* array of pointer, pointer to array */
//void print(char **pp) {
//	for (size_t i = 0; i < 3; i++) {
//		printf("%s\n", pp[i]);
//	}
//}
//
//main()
//{
//	char *p[3] = { "abc", "bbb", "ccc" };	// �����͹迭
//
//	print(p);	// �迭�� p
//}


/* �����Ϳ� ���ڿ� */
//main()
//{
//	char a[] = "abc";	// a: 4byte
//	char b[3] = "abc";	// error. 3byte¥���� 4byte�� ������ ��
//	char c[10];
//	c = "abc";	// error. c�� c�� 0��° ����� �ּ�. �ּҿ� ���� ���� �� ����.
//	// "abc" = ���ڿ�. --> 1. c �ڿ� �ι��ڰ� ����. 2. ���ڿ��� �ּҴ�.
//	strcpy(c, "abc");	// �ٷ� �� ������ �ذ��ϴ� ���
//	c[0] = 'z';	// zbc�� �ٲ�
//
//	char *p = "abc";	// ���ڿ��� �ּ��̹Ƿ� *p�� ��.
//	char *k;
//	k = "abc";	// ���� �Ȱ��� ������ ����.
//	strcpy(k, "abc");	// error. �����Ͱ� �Ĵٺ��� �ִ� ���ڿ��� global ������ �ִ� ����. Ư�� Read Only�� SA(String Address) ������ �����ϴ� ������ ������ �����ϴ� ���� �Ұ���.
//	k[0] = 'z';	// error.
//}

/* �����Ϳ� ���ڿ� 2 */
//char *g = "abc";
//main() {
//	char *a = "abc";
//	char *b[3] = { "abc", "abc", "abc" };
//
//	printf("%x %x %x\n", g, a, b[0]);	// g, a, b ������ ��� ���� ���� ����Ű�� ����. ���ڿ��� ������ ���� �ּҰ��� ����.
//	// �� ������ ������ ��� R/O ������ �ִ� ������ ����Ŵ.
//
//	char buf[100];
//	a = buf;
//	strcpy(a, "xyz");	// R/W ���� �����̹Ƿ� ����.
//	// strcpy(buff, "xyz"); �� �Ȱ���.
//
//}


/* �����Ϳ� ���ڿ� 2 */
//void get_num(int(*p)[3])
//{
//	int rx, cx;
//	for (rx = 0; rx < 2; rx++) {
//		for (cx = 0; cx < 3; cx++) {
//			scanf("%d", &p[rx][cx]);	// (p[rx]+cx)	// (*(p+rx)+cx)	// &(*(p+rx))[cx]	// ��� ���� ǥ��
//		}
//	}
//}
//void put_num(int(*p)[3])
//{
//	int rx, cx;
//	for (rx = 0; rx < 2; rx++) {
//		for (cx = 0; cx < 3; cx++) {
//			printf("%d", p[rx][cx]);	// *(p[rx]+cx)	// *(*(p+rx)+cx)	// (*(p+rx))[cx]	// ��� ���� ǥ��
//		}
//	}
//}
//main()
//{
//	int a[2][3];
//	get_num(a);
//	put_num(a);
//}