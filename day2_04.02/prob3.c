#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#pragma warning(disable:4996)	// �������� ���� �ʰڴ�.
/* ���� 3 */
main()
{
	int cash;
	printf("������ �����ÿ�(1000, 500, 100)�� ����: ");
	scanf("%d", &cash);
	int drink[6] = { 800, 1000, 1100, 1200, 1500, 2000 };

	char drinkN[6][20] = { "1. �� 800", "2. �ݶ� 1000", "3. ȯŸ 1100", "4. ���̴� 1200", "5. ��Ÿ�� 1500", "6. ��Ʈ�� 2000" };
	


	int total = cash;
	while (1) {
		printf("\n�� �ݾ�: %d\n", total);

		if (total < 800)
			printf("�ܾ� ����\n");
		// �� �ݾ׿� ���� �ڵ��޴� ���
		for (int i = 0; i < 6; i++) {
			if (total >= drink[i])
				printf("%s\n", drinkN[i]);
		}

		printf("���ἱ�� �Ǵ� �ݾ��߰�: ");
		scanf("%d", &cash);
		
		if (cash >= 1 && cash <= 6) {
			printf("%s ����\n", drinkN[cash - 1]);
			if (total >= drink[cash - 1]) {
				total -= drink[cash - 1];
			}
		}
		else if(cash == 1000 || cash == 500 || cash == 100)
			total += cash;
		else
			printf("�߸� �Է��ϼ̽��ϴ�.\n");
	}

}