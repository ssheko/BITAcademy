#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#pragma warning(disable:4996)	// 새문법을 쓰지 않겠다.

main()
{
	char *d[2][3];	// [2][3] 배열. 한 요소에 포인터 값이 있는 배열 d
	char *(*pd)[3] = d;	// d의 [3]짜리 배열을 읽는 포인터 pd. 요소 안의 값이 *값이므로 char *를 반환해야 함
	char *(*ppd)[2][3] = &d;	// pd = d이므로, ppd는 d 전체를 포인터. [2][3] 배열을 읽어야 하고, 한 요소의 값이 *값이므로 char *

	char **dd[2][3];	// [2][3] 배열 dd. 한 요소에 더블포인터 값이 있는 배열 dd
	char **(*pdd)[3] = dd;	// dd의 [3]짜리 배열을 읽는 포인터 pdd. 요소 안의 값이 **값이므로 char **
	char **(*ppdd)[2][3] = &dd;	// pdd = dd. ppdd는 dd 전체를 읽는 포인터. [2][3] 배열을 읽어야 하고, 한 요소의 값이 **이므로 char**

	char a[7][3], b[2][3];

	char(*pab[2])[3];	// = {a, b}	// 2개짜리 포인터 배열을 만들어서 각각 a의 주소값, b의 주소값을 읽어야 함. [3]짜리 배열을 읽어야함.
	pab[0] = a;
	pab[1] = b;

	
}