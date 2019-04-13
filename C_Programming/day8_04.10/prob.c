#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#pragma warning(disable:4996)	// 새문법을 쓰지 않겠다.

#define QUEUE_SIZE 11
#define swap(a, b) do{int tmp = a; a=b; b=tmp;}while(0)

typedef struct Q {
	int data[QUEUE_SIZE];
	int front;
	int rear;
}Q;

void initQ(Q *q)
{
	for (int i = 0; i < QUEUE_SIZE; i++) {
		q[i].front = q[i].rear = 0;
	}
}

void put(Q *q, int *input)
{
	if (q->rear == QUEUE_SIZE) {
		printf("Overflow\n");
		return;
	}

	q->data[q->rear++] = input;
}

int* get(Q *q) {
	if (q->front == q->rear) {
		printf("Empty\n");
		return -1;
	}

	return q->data[q->front++];
}

main()
{
	int num[12];
	int count = 3;
	int retval = 0;
	int mod = 10, limit = 10;
	int inputData = 0;
	int first=1, second=0, curr=0;
	Q queue[2][QUEUE_SIZE];
	initQ(queue[0]);
	initQ(queue[1]);

	srand((unsigned)time(NULL));

	printf("자릿수를 입력하세요: ");
	scanf("%d", &count);

	for (int i = 1; i < count; i++) {
		limit *= 10;
	}
	
	for (int i = 0; i < sizeof(num) / sizeof(num[0]); i++) {
		num[i] = rand() % limit + 1;
	}
	
	for (int i = 0; i < sizeof(num)/sizeof(num[0]); i++) {
		put(&queue[0][num[i] % 10], num[i]);
	}

	for(int cn = 1; cn<count; cn++){
		mod *= 10;
		swap(first, second);
		for (int i = 0; i < QUEUE_SIZE; i++) {
			for (int j = queue[first][i].front; j < queue[first][i].rear; j++) {
				retval = get(&queue[first][i]);
				if (retval == -1)
					continue;
				inputData = queue[first][i].data[j] % mod;
				inputData /= (mod / 10);
				put(&queue[second][inputData], retval);	// queue[0][j].data/10
			}
		}
	}
	for (int i = 0; i < QUEUE_SIZE; i++) {
		for (int j = queue[second][i].front; j < queue[second][i].rear; j++) {
			printf("%d ", get(&queue[second][i]));	// queue[0][j].data/10
		}
		puts("");
	}

}