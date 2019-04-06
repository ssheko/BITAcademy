#include <stdio.h>

typedef struct tag {
	int fir;
	int sec;
}TAG;

TAG put(int a, int b);

int main()
{
	TAG rlt;

	rlt = put(10, 5);

	printf("%d %d\n", rlt.fir, rlt.sec);
}