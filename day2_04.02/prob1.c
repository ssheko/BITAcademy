#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#pragma warning(disable:4996)	// 새문법을 쓰지 않겠다.
/* 실습 */
/* 문제 1 */
main()
{
	int rnum;
	srand(time(NULL));
	rnum = rand() % 100 + 1; // 1~100 사이의 값이 나오도록

	int input = 0, prev = 0;
	int count = 0;
	short isUp = 0, isDown = 0;
	while (input != rnum) {
		printf("나이를 입력하세요 : ");
		scanf("%d", &input);

		if (prev != 0 && input < prev && isUp) {
			printf("왜 더 작은 값을 넣으셨습니까?\n");
			count++;
			continue;
		}
		else if (prev != 0 && input > prev && isDown) {
			printf("왜 더 큰 값을 넣으셨습니까?\n");
			count++;
			continue;
		}

		if (input > rnum) {
			printf("그보단 적지요\n");
			isDown = 1;
			isUp = 0;
		}
		else if (input < rnum) {
			printf("그보단 만치요\n");
			isDown = 0;
			isUp = 1;
		}
		else {
			printf("맞습니다.\n%d번 만에 맞추셨습니다.\n", ++count);
			break;
		}
		count++;
		prev = input;
	}

}