#include <stdio.h>
#pragma warning(disable:4996)	// 새문법을 쓰지 않겠다.

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
//	printf("%d\n", a);	// 7 출력
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

/* 배열, 포인터 */
//void check(int *p) {
//	// p를 이용해 a의 모든 값 출력
//	for (int i = 0; i < 5; i++)
//		printf("%d ", *p++);
//
//	printf("%d\n", sizeof(p) / sizeof(p[0]));	// 배열의 크기를 알 수 없으므로 크기를 매개변수로 함께 넘겨줘야 한다.
//	// 2로 출력됨
//
//
//	printf("\n ");
//	while(*p != NULL)
//		printf("%d ", *p++);*/
//}
//
//// check 수정버전
//void check(int *p, int size) {
//	// p를 이용해 a의 모든 값 출력
//	for (int i = 0; i < size; i++)
//		printf("%d ", p[i]);	// *(p+i) 가능
//
//}
//
//main()
//{
//	int a[5] = { 3,4,1,5,2 };
//	int size_a = sizeof(a) / sizeof(a[0]);
//	//printf("%d\n", sizeof(a) / sizeof(a[0]));	// 5로 출력
//	//check(a);
//	check(a, size_a);
//	
//	int *p;
//	p = a;	// a == &a[0] // 배열명은  선두요소의 주소
//}


/* 배열, 포인터 2 */
// 형식매개변수 *p를 사용하여 알파벳 k가 나오기 전까지 출력하는 함수
//void put_a(char *p) {
//	// 출력: abcdefghij
//	//for (int i = 0; i < 26; i++) {
//	//	if (p[i] == 'k')
//	//		break;
//	//	printf("%c ", p[i]);	// *(p+i) 가능
//	//}
//
//	for (int i = 0; p[i] != 'k'; i++) {
//		printf("%c ", p[i]);	// *(p+i) 가능
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
//	// 출력: abcdefghij
//
//	// 기준번지로부터 상대적 거리를 찾아가면서 출력
//	//for (int i = 0; p[i] != '\0'; i++) {
//	//	printf("%c", p[i]);	// *(p+i) 가능
//	//}
//	//printf("\n");	// putchar('\n');	// puts("");	// 개행문자 출력
//
//	// 기준번지를 이동시키면서 출력하기 때문에 for문보다 훨씬 빠르다.
//	while (*p)
//		putchar(*p++);
//	putchar('\n');
//}
//
//main()
//{
//	char a[] = "abcdefghijklmnopqrstuvwxyz";
//	puts(a);	// 마지막에 개행문자 존재
//	put_a(a);
//}

#include <string.h>

/* mystrcpy */
//void mystrcpy(char *dst, char *src) {
//	//while (*src)
//	////for (int i = 0; src[i] != '\0'; i++) 
//	//	*dst++ = *src++;
//	//// NULL값 전까지 while문이 돌기 때문에 마지막에 NULL값 추가
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
//	//while(*dst++);	// null을 만나 끝났지만 ++된 상태에서 추가됐기 때문에 abcde\0zzz 로 추가된 상태.
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

/* 더블 포인터 1 */
//main()
//{
//	int a;
//	int *p;
//	int **k;
//	p = &a;
//	k = &p;
//
//	scanf("%d", &a);	// a표현으로 a에 입력
//	printf("%d\n", a);
//
//	scanf("%d", p);	// p표현으로 a에 입력
//	printf("%d\n", *p);
//
//	scanf("%d", *k);	// k표현으로 a에 입력
//	printf("%d\n", **k);
//}

/* 더블 포인터 2 */
//void connect(int *a, int **p) {
//	*p = a;	// *(p의 주소) = (a의 값)
//}
//main()
//{
//	int a = 7;
//	int *p;
//	connect(&a, &p);
//	printf("%d\n", *p);	// 7출력
//}

/* 다중 포인터 (swap) */
//#define A 6
//// main에 위치한 a, b변수의 주소를 전달받아 a, b값을 교환하는 함수
//#if A == 1
//void swap(int *a, int *b) {
//	int temp = *a;
//	*a = *b;
//	*b = temp;
//}
//#elif A == 2
//// ap,bp 변수의 주소를 전달받아 a, b값을 교환하는 함수
//void swap(int **ap, int **bp) {
//	int temp = **ap;	// a
//	**ap = **bp;
//	**bp = temp;
//}
//#elif A == 3
//// app,bpp 변수의 주소를 전달받아 a, b값을 교환하는 함수
//void swap(int ***app, int ***bpp) {
//	int temp = ***app;	// 1,2,3 케이스는 모두 a, b값
//	***app = ***bpp;
//	***bpp = temp;
//
//}
//#elif A == 4
//// ap,bp 변수의 주소를 전달받아 ap, bp값을 교환하는 함수
//void swap(int **ap, int **bp) {
//	int *temp = *ap;
//	*ap = *bp;
//	*bp = temp;
//}
//#elif A == 5
//// app,bpp 변수의 주소를 전달받아 ap, bp값을 교환하는 함수
//void swap(int ***app, int ***bpp) {
//	int *temp = **app;
//	**app = **bpp;
//	**bpp = temp;
//}
//#elif A == 6
//// app,bpp 변수의 주소를 전달받아 app, bpp값을 교환하는 함수
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

/* 포인터/다중 포인터로 값 변경 */
//void last(int *ka) {
//	*ka = 300;	// ka도 a의 주소를 포인트
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
//// 둘 다 같은 결과값
//
//void last(int **ka) {
//	**ka = 300;	// **(pa 주소) = * (a 주소) = a = 300
//}
//
//void middle(int *pa)
//{
//	*pa = 200;
//	last(&pa);	// pa주소를 ka에게 줌
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
//	char *p[3] = { "abc", "bbb", "ccc" };	// 포인터배열
//
//	print(p);	// 배열명 p
//}


/* 포인터와 문자열 */
//main()
//{
//	char a[] = "abc";	// a: 4byte
//	char b[3] = "abc";	// error. 3byte짜리에 4byte를 넣으려 함
//	char c[10];
//	c = "abc";	// error. c는 c의 0번째 요소의 주소. 주소에 값을 넣을 수 없음.
//	// "abc" = 문자열. --> 1. c 뒤에 널문자가 있음. 2. 문자열은 주소다.
//	strcpy(c, "abc");	// 바로 위 에러를 해결하는 방법
//	c[0] = 'z';	// zbc로 바뀜
//
//	char *p = "abc";	// 문자열은 주소이므로 *p는 값.
//	char *k;
//	k = "abc";	// 위와 똑같은 이유로 가능.
//	strcpy(k, "abc");	// error. 포인터가 쳐다보고 있는 문자열은 global 영역에 있는 존재. 특히 Read Only인 SA(String Address) 영역에 존재하는 변수에 접근해 수정하는 것은 불가능.
//	k[0] = 'z';	// error.
//}

/* 포인터와 문자열 2 */
//char *g = "abc";
//main() {
//	char *a = "abc";
//	char *b[3] = { "abc", "abc", "abc" };
//
//	printf("%x %x %x\n", g, a, b[0]);	// g, a, b 포인터 모두 같은 값을 가리키고 있음. 문자열이 같으면 같은 주소값을 가짐.
//	// 위 포인터 변수는 모두 R/O 영역에 있는 변수를 가리킴.
//
//	char buf[100];
//	a = buf;
//	strcpy(a, "xyz");	// R/W 가능 변수이므로 가능.
//	// strcpy(buff, "xyz"); 와 똑같음.
//
//}


/* 포인터와 문자열 2 */
//void get_num(int(*p)[3])
//{
//	int rx, cx;
//	for (rx = 0; rx < 2; rx++) {
//		for (cx = 0; cx < 3; cx++) {
//			scanf("%d", &p[rx][cx]);	// (p[rx]+cx)	// (*(p+rx)+cx)	// &(*(p+rx))[cx]	// 모두 같은 표현
//		}
//	}
//}
//void put_num(int(*p)[3])
//{
//	int rx, cx;
//	for (rx = 0; rx < 2; rx++) {
//		for (cx = 0; cx < 3; cx++) {
//			printf("%d", p[rx][cx]);	// *(p[rx]+cx)	// *(*(p+rx)+cx)	// (*(p+rx))[cx]	// 모두 같은 표현
//		}
//	}
//}
//main()
//{
//	int a[2][3];
//	get_num(a);
//	put_num(a);
//}