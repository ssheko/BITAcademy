#include <stdio.h>

#include "common.h"
#include "dup.h"

int main()
{
	TAG rlt;

	rlt = put(10, 5);

	printf("%d %d\n", rlt.fir, rlt.sec);
}