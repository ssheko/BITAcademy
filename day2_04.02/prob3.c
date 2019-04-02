#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#pragma warning(disable:4996)	// 새문법을 쓰지 않겠다.
/* 문제 3 */
main()
{
	int cash;
	printf("동전을 넣으시오(1000, 500, 100)만 가능: ");
	scanf("%d", &cash);
	int drink[6] = { 800, 1000, 1100, 1200, 1500, 2000 };

	char drinkN[6][20] = { "1. 물 800", "2. 콜라 1000", "3. 환타 1100", "4. 사이다 1200", "5. 비타민 1500", "6. 울트라 2000" };
	


	int total = cash;
	while (1) {
		printf("\n총 금액: %d\n", total);

		if (total < 800)
			printf("잔액 부족\n");
		// 총 금액에 따라 자동메뉴 출력
		for (int i = 0; i < 6; i++) {
			if (total >= drink[i])
				printf("%s\n", drinkN[i]);
		}

		printf("음료선택 또는 금액추가: ");
		scanf("%d", &cash);
		
		if (cash >= 1 && cash <= 6) {
			printf("%s 선택\n", drinkN[cash - 1]);
			if (total >= drink[cash - 1]) {
				total -= drink[cash - 1];
			}
		}
		else if(cash == 1000 || cash == 500 || cash == 100)
			total += cash;
		else
			printf("잘못 입력하셨습니다.\n");
	}

}