#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>

#pragma warning(disable:4996)	// 새문법을 쓰지 않겠다.

/* 빙고 게임 */
//void putRandom(int (*board)[5], int maxRow, int maxCol) {
//	int curr = 0;
//	short isIn = 0;
//	int randNum;
//
//
//	randNum = rand() % 25 + 1;
//	board[curr / 5][curr % 5] = randNum;
//	curr++;
//
//	while (curr < maxCol * maxRow) {
//		int x = 0, y = 0;
//		isIn = 0;
//		randNum = rand() % 25 + 1;
//
//		while (board[x][y] != 0) {	// player 번호판이 비어있지 않고,
//			if (board[x][y] == randNum) {	// randNum과 같을 경우
//				isIn = 1;
//			}
//			y++;
//			if (y == maxCol) {
//				x++;
//				y = 0;
//			}
//		}
//
//		if (!isIn) {	// 중복된 값이 없을 경우
//			board[curr / 5][curr % 5] = randNum;	// randNum을 넣어줌
//			curr++;
//		}
//	}
//}

void putRandom(int(*board)[5], int maxRow, int maxCol) {
	int shuffleCount = 50;
	int randNum1, randNum2;
	int randArr[25] = { 0 };

	for (int i = 0; i < 25; i++)
		randArr[i] = i + 1;

	while (shuffleCount--) {
		randNum1 = rand() % 25;
		randNum2 = rand() % 25;

		int tmp = randArr[randNum1];
		randArr[randNum1] = randArr[randNum2];
		randArr[randNum2] = tmp;
	}

	for(int i=0; i<25; i++)
		board[i / 5][i % 5] = randArr[i];
}

// 0: x  1: win
int isBingo(int (*board)[5], int maxRow) {
	int count = 12;
	int bingoCount = 0;

	int i = 0, j = 0;


for (int i = 0; i < maxRow; i++) {
		bingoCount = 0; j = 0;
		while (j < maxRow &&board[i][j++] == 0)	bingoCount++;
		if (bingoCount == 5) {
			return 1;
		}
	}

	i = 0; j = 0;
	for (int j = 0; j < maxRow; j++) {
		bingoCount = 0;
		i = 0;
		while (i < maxRow && board[i++][j] == 0)	bingoCount++;
		if (bingoCount == 5)
			return 1;
	}

	i = 0; j = 0;
	while (i < maxRow && j < maxRow && board[i++][j++] == 0)	bingoCount++;
	if (bingoCount == 5)
		return 1;

	i = 0; j = 0;
	bingoCount = 0;
	while (i < maxRow && board[i++][(maxRow - i - 1)] == 0)	bingoCount++;
	if (bingoCount == 5)
		return 1;

	return 0;
}

main()
{
	int win = 0;
	int player[5][5] = { 0 }, computer[5][5] = { 0 };

	int curr = 0;
	short isIn = 0;
	short isPlayerTurn = 1;
	int randNum;
	int input;
	int count = 25;
	int bingoCount = 1;
	int i = 0, j = 0;

	int shuffleCount = 50;
	int randNum1, randNum2;
	int randArr[25] = { 0 };

	for (int i = 0; i < 25; i++)
		randArr[i] = i + 1;

	srand((unsigned)time(NULL));

	putRandom(&player, 5, 5);
	putRandom(&computer, 5, 5);

	for (int i = 0; i < 25; i++)
		randArr[i] = i + 1;


	while (!win) {
		puts("\tUSER\t\t\tCOM");
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if(player[i][j] != 0)
					printf("%3d ", player[i][j]);
				else
					printf("  X ");
			}
			printf("\t");
			for (int j = 0; j < 5; j++) {
				if (computer[i][j] != 0)
					printf("%3d ", computer[i][j]);
				else
					printf("  X ");
			}
			printf("\n");
		}

		if (isBingo(&player, 5)) {
			printf("player win\n");
			return 0;
		}

		if (isBingo(&computer, 5)) {
			printf("computer win\n");
			return 0;
		}



		if (isPlayerTurn) {
			do {
				printf("\n수를 입력하세요: ");
				scanf("%d", &input);

			} while (randArr[input-1] == 0);

			randArr[input-1] = 0;
			isPlayerTurn = 0;
		}
		else {
			do{
				randNum = rand() % 25;
			} while (randArr[randNum] == 0);

			randArr[randNum] = 0;
			isPlayerTurn = 1;
			input = randNum + 1;
		}
		count = 25;
		while (count--) {
			if (input == player[count / 5][count % 5])
				player[count / 5][count % 5] = 0;
			if (input == computer[count / 5][count % 5])
				computer[count / 5][count % 5] = 0;
		}

		
		system("cls");
	}
}