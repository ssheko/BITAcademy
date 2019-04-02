#include <stdio.h>

//int main()
//{
//	int a = 10;
//	int b = 6;
//
//	// 속도 빠르게, 메모리 하나 더 사용
//	int t;
//	t = a;
//	a = b;
//	b = t;
//
//	// 속도 느리지만 메모리 덜 소모
//	printf("%d %d\n", a, b);
//	a = a ^ b;	// a ^= b;
//	b = a ^ b;
//	a = a ^ b;
//	printf("%d %d\n", a, b);
//	getchar();
//}

main()
{
	int a = 0xA;	// 1010

	// bit shift
	//a = a | 4;		// 1110 E
	// 더 많이 사용
	//a = a | (1 << 2);

	//a = a | (1 << 16);

	//a |= (1 << 16) + (1 << 2);



	//// bit check
	//if (a & 8)	// check는 if와 &가 결합되어 사용됨.
	//	puts("true");
	//else
	//	puts("false");

	//// 16번째 비트가 1인지 아닌지 검사
	//if (a & (1<<16))
	//	puts("true");
	//else
	//	puts("false");


	//// bit mask
	//a = 0x12345678;
	//// a가 가진 45부분을 mask해서 출력
	//a &= 0x45000;



	//// bit clear &~
	//a = 0x12345678;	// 0111 1000

	////a = a & ~16;
	////a &= ~(1 << 21);
	//a &= ~((1 << 21) + (1 << 3));

	//printf("%x\n", a);


	//// 문제
	///** int a = 0xA5
	//	int *p를 이용해 a의 내용들을 변경하고 출력하시오
	//	(비트는 우측에서 0부터 시작한다)
	//	1. 6번 비트가 0인지 1이면 ture 0이면 false
	//	2. 3번 비트와 1번 비트를 1로 set하고 출력
	//	3. 1번 비트와 2번 비트를 0으로 clear하고 출력
	//	4. 5,6,7번 비트를 추출하여 값을 출력
	//**/
	//a = 0xA5;
	//int *p = &a;
	//if (a & (1 << 6))	// false
	//	puts("true");
	//else
	//	puts("false");	

	//*p |= (1 << 3) + (1 << 1);
	//printf("%x\n", a);	// AF

	//*p &= ~((1 << 1) + (1 << 2));
	//printf("%x\n", a);	// A9

	//*p &= 0xE0;		// A0
	//printf("%x\n", a);

	//a = 0x12345678;
	// 78563412 출력
	/*int b = a & 0x12345600;
	printf("%x %x\n", a, b);
	a = a << 24;
	b = b >> 8;
	a |= b;
	printf("%x %x\n", a, b);*/
//	a = (a & 0xff) << 24 | (a & 0xff00) << 8 |
//		(a>>8)&0xff00 | (a>>24)&0xff; 	// (a&0xff000000) >> 24 | (a&0xff0000) >> 8
//
//
//
//	// 문제
//	/*
//	어떤 값이 입력되든지
//	4의 배수 형태로 출력되게
//	--> 3을 더하고 3을 지워라
//	*/
////	int x = 7;
////	//scanf("%d", &x);
////	if (x % 4 == 0)
////		return;
/////*
////	if (x / 4 > 0)
////		x &= (1 << ((x / 4)+2));
////	else*/
////
////	x |= (1 << ((x / 4) + 2));
////	if (x & 0x10 || x & 0x1)
////		x &= ~((1<<1) + (1<<0));
//	int x = 7;
//	x += 3;
//	x &= ~0x11;
//
//
//
//
//	// 문제
//	/*
//	10진수 num의 우측 n비트에서 w번째 비트까지 값을 추출하여 10진수로
//
//	십진수 입력: 684
//	n수 입력: 4
//	w수 입력: 3
//
//	0010 1010 1100
//	0010 1010 1100
//	결과 출력: 5
//	*/
//	int num = 684, n = 4, w = 3;
///*
//	num = num >> n;
//	int mask = 0xff << w;
//	mask = ~mask;
//	num &= mask;*/
//	printf("%x\n", num >> (n-1) & ~((~0) << w));
//	// ((~0)): 1111 1111
//	// << w : 1111 1000
//	
//	
//	// 반복문의 3가지 필수 조건: 초기값, 조건, 증감
//
//	int sum = 0, num = 1;	// 초기값
//	// goto문을 사용하여 1 ~ 10까지의 합을 출력
//RED:
//		sum += num;
//		num++;	// 증감
//	
//
//	if (num <= 10)	// 조건
//		goto RED;
//
//	printf("%d\n", sum);
//
//
//
	/*
	1. 1~10사이의 수가 입력되면 '통과', 아니면 '불통'
	2. 입력문자가 A~Z면 '대문자' 출력, a~z면 '소문자' 출력
	3. 대문자가 입력되면 소문자로 소문자면 대문자로 출력	// a 97 A 65
	*/
	int input = 0;
	scanf_s("%d", &input);
	getchar();

	if (input >= 1 && input <= 10)
		printf("통과\n");
	else
		printf("불통\n");


	char inputchar;
	scanf_s("%c", &inputchar);
	getchar();
	if (inputchar >= 'a' && inputchar <= 'z')
		printf("소문자\n");
	if (inputchar >= 'A' && inputchar <= 'Z')
		printf("대문자\n");

	if (inputchar >= 'a' && inputchar <= 'z')
		printf("%c\n", inputchar & ~32);
	if (inputchar >= 'A' && inputchar <= 'Z')
		printf("%c\n", inputchar | 32);
}