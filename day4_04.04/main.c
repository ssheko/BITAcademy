#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#pragma warning(disable:4996)	// 새문법을 쓰지 않겠다.

/* 2차원 배열을 1차원처럼 받기 */
//void array_1to2(char *p) {
//	puts(p);
//}
//
/* 2차원 배열을 2차원처럼 받기 */
//void array_2to2(char p[1000][10]) {	// 열의 크기 10개는 맞춰줘야 함
//	puts(p[2]);
//}
//
//main()
//{
//	char a[3][10] = { "abc", "defg", "zzzzzzz" };	// 10개짜리 요소 3개
//	array_1to2(a[2]);
//	array_2to2(a);
//}

/* 포인터, 배열 포인터, 포인터 배열, 배열 */
//void print_a(char *p[10])	// char **p	// char *p[]
//{
//	// 0번째인 abc에서 bc를 출력(포인터, 배열 포인터, 포인터 배열, 배열)
//	
//	printf("%s\n", &(*p)[1]);	// *p+1	// p[0]+1
//		//printf("%c%c\n", p[0][1], p[0][2]);
//	// 1번째인 home에서 h만 출력
//	printf("%c\n", 1[p][0]);	// *(p[1])	// *(*(p+1))	// (*(p+1))[0]	// 1[p][0]	// 0[1[p]]
//	// 2번째인 print에서 i만 출력하는 print문
//	printf("%c\n", p[2][2]);	// *(p[2]+2)	// *(*(p+2)+2)	// (*(p+2))[2]
//}
//
//main()
//{
//	char *a[3] = { "abc", "home", "print" };	// 10개짜리 요소 3개
//	print_a(a);
//}

/* argc, *argv[] 이용한 계산기 */
/* 속성-> 구성 속성 -> 디버깅 -> 명령 인수 */
//main(int argc, char *argv[]) {
//	// 강사님 코드
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

/* 함수 포인터 */
//// 함수도 주소니까 함수를 가리키는 포인터도 있을 것이다.
//int add(int a, int b) { return a + b; }
//int sub(int a, int b) { return a - b; }
//int mul(int a, int b) { return a * b; }
//int dvv(int a, int b) { return a / b; }
//
//main()
//{
//	int rlt;
//	//int *p(int, int);	// int형 포인터를 리턴하는 포인터
//	//int(*p)(int, int);	// 함수 포인터
//	////int(*p)[3];	// 배열 포인터
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
//	int(*p[4])(int, int) = { add, sub, mul, dvv };	// 4개짜리 함수 포인터 배열
//
//	for (size_t i = 0; i < 4; i++) {
//		printf("%d\n", p[i](10, 5));
//	}
////
////	rlt = add(10, 5);
////	printf("%d\n", rlt);
//}

/* 함수 포인터와 매개변수 */
//int add(int a, int b) { return a + b; }
//int sub(int a, int b) { return a - b; }
//
//int temp(int(*p_func)(int, int), int a, int b) {
//
//	return p_func(a, b);	// leaf function call	// 속도가 더 빨라진다.
//}
//
//void main()
//{
//	int a = 10, b = 5;
//
//	printf("%d", temp(add, a, b));
//}

/* 함수 포인터의 타입지정 */
//typedef unsigned int unit;
//
//typedef int(*myfp_t)(int, int);
//
//int add(int a, int b) { return a + b; }
//
//int temp(myfp_t p, int a, int b) {
//
//	return p(a, b);	// leaf function call	// 속도가 더 빨라진다.
//}
//
//void main()
//{
//	int a = 10, b = 5;
//
//	printf("%d", temp(add, a, b));
//}

/* 범용 포인터 */
//main()
//{
//	void *p;	// 범용 포인터	// 모든 형태의 주소
//
//	char ch = 'A';
//	p = &ch;	// 주소를 담고있지만 어떤 타입을 담고있는지 모른다.
//	printf("%d\n", *(char *)p);	// 값 (char형 주소로 바꿔서)p	// p가 가진 주소를 char형 주소로 바꿔서 값을 보겠다.
//
//	int i = 123;
//	p = &i;
//	printf("%d\n", *(int *)p);	// p가 가진 주소를 int형 주소로 바꿔서 값 보기
//
//	char arr[] = "abcde";
//	p = arr;
//	printf("%s\n", (char*)p);	// abcde를 출력하는 방법
//
//	printf("%c %c %c\n", *(char*)p, *((char*)p+1), *((char*)p+2));	// a b c를 출력하는 방법
//
//	printf("%c\n", *((char*)p)++);	// p++의 형태로 찍어보기 'a'
//	printf("%c\n", *(char*)p);	// 'b'
//}

/* 범용 포인터를 사용한 계산기 */
//int add(int a, int b) { return a + b; }
//int sub(int a, int b) { return a - b; }
//int mul(int a, int b) { return a * b; }
//int dvv(int a, int b) { return a / b; }
//
//typedef int(*p_t)(int, int);	// 함수포인터 타입
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
//	printf("번호를 선택하세요: ");
//	scanf("%d", &num);
//
//	p = arr[num-1][0];	// *(arr[num-1])
//	
//	printf("결과는: %d\n", p(10, 5));	// ((p_t)p[num-1][0])(10,5)
//
//}
//
//main()
//{
//	void *arr[2][5] = { { add, sub, mul, dvv, 0}, {"ADDITION", "SUBTRACTION", "MULTIPLY", "DIVIDE", 0 } };
//
//	void **vp;	// a[0] = *a 이므로, a[1] = *(a+1) 이기때문에 더블포인터로 접근해야 한다.
//	int(*p)(int, int);
//
//	vp = (arr +1);
//
//	for (int i = 0; *((char**)vp); i++) {
//		printf("%d. %s\n", i, 
//			*((char**)vp)++);
//	}
//}

/* 힙 영역, 포인터 */
//main()
//{
//	//int size;
//	//scanf("%d", &size);
//
//	//int arr[size];	// 이렇게 해도 되지만 보통의 컴파일러는 이를 허용치 않음
//
//	int *p;	// 힙영역에 접근하는 거라서 반드시 포인터 써야 함. (힙 영역에 존재하는 것들은 이름이 없기 때문에 포인터를 이용해 간접적으로 접근할 수밖에 없다)
//
//	p = malloc(4);	// 4바이트 메모리를 만들고 주소를 리턴
//		// heap에 접근하는 4바이트 메모리
//
//	int a;	// stack에서 4byte 메모리를 가리키는 경우
//	int *p;
//	p = &a;
//
//	// heap, stack 둘 다 포인터로 접근하는 방법은 똑같다
//
//
//	int a[5];
//	int *p = a;
//
//	int *p;
//	p = (int*)malloc(5 * sizeof(int));	// 리턴타입이 범용포인터 타입. 따라서 int* 타입으로 캐스팅해야 한다.
//
//
//}

/*
	자신의 주소를 입력받아서 딱 맞는 주소의 크기만큼을 힙에 할당하고 넣은 뒤 출력
*/
//main()
//{
//	char *add_heap;
//	char add[100];
//	int i = 0;
//	
//	gets(add);
//
//	add_heap = (char*)malloc(strlen(add) * sizeof(char) + 1);	// null문자를 위한 공간 1 추가해야 함
//	//printf("%s %d %d\n", add_heap, strlen(add), strlen(add_heap));
//	strcpy(add_heap, add);	// copy될 때 null까지 저장시켜주지만, malloc할 때 사이즈를 +1을 해주지 않았으면 null이 저장되지 않는다.
//
//	puts(add_heap, add);
//
//	free(add_heap);	// free는 null문자가 나올때까지 소멸시키는데 null문자가 copy되지 않은 상태였다면 해제되는 과정에 머물러있게 된다.
//}

/* FILE stream (pipeline) */
//main()
//{
//	int num;
//	char ch;
//	char name[10];
//
//	FILE *fwp, *frp;	// 포인터 변수. a.txt 주소값만이 아닌 다른 주소값을 가질 수도 있다.
//	fwp = fopen("a.txt", "w");	// 출력스트림 fwp
//
//	fprintf(fwp, "%d %c ", 1, 'A');
//
//	fclose(fwp);
//
//	frp = fopen("a.txt", "r");		// 입력스트림 frp
//	fscanf(frp, "%d %c", &num, &ch);
//	fclose(frp);
//
//	fwp = fopen("a.txt", "a");	// "a": append ; 파일의 마지막에 문자 추가.
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

/* FILE 사진 */
//main()
//{
//	FILE *wp, *rp;
//	int count = 0;
//	char buf[100];
//	rp = fopen("1.jpg", "rb");	// binary 형태로 read
//	wp = fopen("2.jpg", "wb");
//	int totalSize = 0;
//	// 한 바이트 읽고 한 바이트 쓰기	
//	// 한 줄 읽고 한 줄 쓰기
//
//	// 원하는 만큼 읽고 쓰기
//	while (1) {
//
//		// 100개의 버퍼까지 다 집어넣으면 100이 리턴된다. 만약 10개만 들어왔으면 10이 리턴됨. 리턴값을 이용해 끝을 알아낼 수 있다. 100개씩 넣다가 남은 값은 100보다 작을 수 있음.
//		count = fread(buf, sizeof(char), 100, rp);
//		if (count < 100) {
//			// 두 가지의 경우 count가 100보다 작다.
//			if (feof(rp))	// eof = end of file	// 0	// 파일의 끝까지 도달
//			{
//				// 파일의 끝은 0이 아닌 값을 리턴. 파일을 읽는 경우 0. 파일이 깨져있어도 파일의 끝이 아니므로 0을 리턴한다.
//				// 읽은 만큼만 복사
//				totalSize += count;
//				fwrite(buf, sizeof(char), count, wp);
//				puts("복사 완료");
//			}
//			else
//				puts("복사 실패");
//			
//			break;
//		}
//		totalSize += count;
//		//printf("%dbyte 복사 완료\n", totalSize);
//		fwrite(buf, sizeof(char), 100, wp);
//	}
//
//	printf("%dbyte 복사 완료\n", totalSize);
//
//	fclose(rp);
//	fclose(wp);
//}