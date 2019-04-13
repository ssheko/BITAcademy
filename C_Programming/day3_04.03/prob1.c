#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#pragma warning(disable:4996)	// �������� ���� �ʰڴ�.

/* ���ڿ��� ������ ���ڷ� �ٲٰ� ����. �̸� ��� �ݺ�. */

int myatoi(char *str) {
	int result = 0;
	
	while (*str) {
		result *= 10;
		result += (*str - '0');
		*str++;
	}
	return result;
}

void myitoa(int num, char* str, int std) {
	int count = std, remain = num;

	while ((num = num / std) >= std)
		count *= std;
	num = remain;
	while (count > 0) {
		remain = num / count;
		num %= count;
		count /= std;
		*str++ = remain + '0';
	}
	*str = '\0';
}

// ���ڿ��� ������ �Լ�
void mystrrev(char *str) {
	char revBuff[20];
	int count = 0;
	int i = 0;
	for (int i = 0; str[i] != '\0'; i++) {
		count++;
	}
	/*while (*str++)
		count++;*/

	for (int i = 0; i < count; i++) {
		revBuff[i] = str[count - i-1];
	}

	revBuff[count] = '\0';
	
	while ((i <= count) && (*str++ = revBuff[i++]));
}


main()
{
	char buff[10] = "127";
	int num, totalCount, revNum;
	//int num=127, totalCount=3, revNum;
	char revBuff[10];

	scanf("%d %d", &num, &totalCount);

	while (totalCount-- > 0) {
		myitoa(num, buff, 10);

		printf("%6d\n", num);
		mystrrev(&buff);
		printf("+%5s\n", buff);
		printf("-------\n");
		revNum = myatoi(&buff);
		printf("%6d\n\n", num + revNum);

		num += revNum;
	}

	/*strcpy(revBuff, buff);

	mystrrev(&revBuff);
	puts(revBuff);

	num = myatoi(&buff);
	printf("%d\n", num);*/



	//strrev(buff);	// ���ڿ��� ������ �Լ�
	//puts(buff);

	//num = atoi("123");	// ���ڿ��� ���ڷ� ��ȯ
	//printf("%d\n", num);

	//itoa(456, buff, 10);	// 10���� ���ڸ� ���ڿ��� ��ȯ
	//puts(buff);
}