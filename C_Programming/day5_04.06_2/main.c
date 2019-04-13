#include <stdio.h>

#pragma warning(disable:4996)	// 새문법을 쓰지 않겠다.

int get_bank();	// extern int get_bank();	// extern이 생략된 형태

void set_bank();	// extern void set_bank();	// extern이 생략된 형태

int main()
{
	int withdraw;

	set_bank();

	withdraw = get_bank();

	printf("%d\n", withdraw);
}