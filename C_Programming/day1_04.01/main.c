#include <stdio.h>
// char short int long // 정수형데이터
// float double

// 1byte == 8bit (0000 0000)
// 4byte == 32bit

// F10 디버깅진입
// shift+F5 디버깅 정지

main()
{
	char c; // 1byte  short
	int i = 0x12345678;	// 4byte   long	i = 10 (decimal), i = 010(octal), i=0x10 (hexa decimal)
	float f = 12.5f;	// 4byte
	float g = 6.0f;	// bit열? 6.0 -> 0110 -> 1.10 * 2^2 -> 0100 0000 1100 0000... -> 00 00 c0 40
	double d = 12.5;	// 8byte
}

//12.5	1100.1