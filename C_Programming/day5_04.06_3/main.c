#include <stdio.h>

#pragma warning(disable:4996)	// �������� ���� �ʰڴ�.

int get_bank();	// extern int get_bank();	// extern�� ������ ����

void set_bank();	// extern void set_bank();	// extern�� ������ ����

int main()
{
	int withdraw;

	set_bank();

	withdraw = get_bank();

	printf("%d\n", withdraw);
}