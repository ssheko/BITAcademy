#include <stdio.h>

#pragma warning(disable:4996)	// �������� ���� �ʰڴ�.

int passbook = 100;

int get_bank()
{
	return passbook;	// withdraw
}

void set_bank()
{
	passbook++;	// deposit
}

int main()
{
	int withdraw;

	set_bank();

	withdraw = get_bank();

	printf("%d\n", withdraw);
}