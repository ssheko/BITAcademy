#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#pragma warning(disable:4996)	// �������� ���� �ʰڴ�.
/* �ǽ� */
/* ���� 1 */
main()
{
	int rnum;
	srand(time(NULL));
	rnum = rand() % 100 + 1; // 1~100 ������ ���� ��������

	int input = 0, prev = 0;
	int count = 0;
	short isUp = 0, isDown = 0;
	while (input != rnum) {
		printf("���̸� �Է��ϼ��� : ");
		scanf("%d", &input);

		if (prev != 0 && input < prev && isUp) {
			printf("�� �� ���� ���� �����̽��ϱ�?\n");
			count++;
			continue;
		}
		else if (prev != 0 && input > prev && isDown) {
			printf("�� �� ū ���� �����̽��ϱ�?\n");
			count++;
			continue;
		}

		if (input > rnum) {
			printf("�׺��� ������\n");
			isDown = 1;
			isUp = 0;
		}
		else if (input < rnum) {
			printf("�׺��� ��ġ��\n");
			isDown = 0;
			isUp = 1;
		}
		else {
			printf("�½��ϴ�.\n%d�� ���� ���߼̽��ϴ�.\n", ++count);
			break;
		}
		count++;
		prev = input;
	}

}