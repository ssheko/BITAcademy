#include <stdio.h>
#include "left.h"
#include "right.h"

#pragma warning(disable:4996)	// �������� ���� �ʰڴ�.

int main()
{
	int withdraw;

	set_bank();

	withdraw = get_bank();

	printf("%d\n", withdraw);
}