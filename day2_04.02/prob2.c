#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#pragma warning(disable:4996)	// �������� ���� �ʰڴ�.
/* ���� 2 */
main()
{
	int arr[45] = { 0 };
	int standard = 0;
	int rnum, max = 44;
	srand((unsigned)time(NULL));
	rnum = rand() % max + 1; // 0~max ������ ���� ��������

	standard = rnum;

	for (int i = 0; i < 45; i++)
		arr[i] = i + 1;
	printf("���� ��: %d\n", standard);

	printf("%d ", arr[standard]);
	arr[standard] = arr[max--];
	while (1) {
		if (max < standard)
			break;
		rnum = rand() % max + 1; // 0~max ������ ���� ��������
		if (rnum != standard)
			continue;

		printf("%d ", arr[standard]);
		arr[standard] = arr[max--];

		for(int i=0; i<max; i++)
			printf("%d ", arr[i]);
		printf("\n");
	}
}