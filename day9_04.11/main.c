#ifndef HEADER
#define HEADER
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>

#pragma warning(disable:4996)	// �������� ���� �ʰڴ�.

#endif
/* #define DEBUG */
//#define NDEBUG
//#define DEBUG
//
//void main()
//{
//#ifdef NDEBUG
//	printf("a a a\n");
//#endif
//}
//
//#ifdef DEBUG
//#define _(exp) exp
//#define _(exp) exp
//#else
//#define _(exp) (void*)0
//#endif

/*
	void assert(int expression);
 expression�� ������ ������ ����
 expression�� false�� ��� assert()�� stderr�� �����޼���
 NDEBUG�� ���� ������ ���� �ǰ� �ȵǰ� �����Ѵ�.
*/

/* assert ����ȭ */
//#define NDEBUG
//#ifdef NDEBUG
//#include <assert.h>
//#endif
//
//main()
//{
//	int x;
//	printf("\nEnter an integer value: ");
//	scanf("%d", &x);
//	assert(x >= 0);
//	printf("You entered %d.", x);
//	return(0);
//}

/* ���� Ž�� */
//int Seqsearch(int A[], int key, int n)
//{
//	int k = n;
//	A[0] = key; // ã���� �ϴ� �迭�� �� ���̳� �� �ڿ� ��
//	while (A[k] != key)
//		k--;	// down counting�� �� ��� ����� ���� �������� 4��->3�ٷ� �پ��	for(i=10;i>=10; i--)	
//				// (���� down counting�̾ ���ǹ��� ���� �ӵ��� �޶���) i>=0, i !=0 : 3��, i>0 : 4��
//	return k;
//}

/* algo header
	1. qsort()	 // ����
	2. bsearch() // �̹� ���ĵ� �迭���� ���ϴ� ���� ã��
*/
/* ����
char key[][] = {"Alice", "Bill", "Carol", "David", "Elvis", "Fred", "Gabriel",
    "Helen", "Isabel", "Jane", "Kuper", "Louic", "Mathilda", "Nadia", "Olive",
    "Pablo", "Queen", "Rambo", "Scarlet", "Trisha", "Umberto", "Vincent", 
    "Wily", "Xxx", "Yuki", "Zorro"};


1. �Ϲ��Լ��� ����� ã�� 
2. ����Լ��� ����� ã��
3. bsearch() - ���̺귯�� �Լ��� ã��

 

�� 1,2,3�� �Լ��� Pablo�� ���° ��ġ�ϴ� ���� ����Ͻÿ�
*/

int searchKey(char (*arr)[10], char *key, int size) {
	//int index = 1;
	int low = 0;
	//int high = (sizeof(*arr) / sizeof(*arr[0]))-1;
	int high = size;
	int mid = (low + high) / 2;

	while (1) {
		if (strcmp(arr[mid], key) > 0) {	// key�� �� ���� ���
			high = mid - 1;
			mid = (low + high) / 2;
		}
		else if (strcmp(arr[mid], key) < 0) {	// key�� �� ū ���

			low = mid + 1;
			mid = (low + high) / 2;
		}
		else
			break;
	}
	/*while (strcmp(*arr++, key)) {
		index++;
	}*/
	return mid;
}

int searchKey2(char (*arr)[10], char *key, int low, int high) {
	int mid = (low + high) / 2;
	if (strcmp(arr[mid], key) > 0) {
		high = mid - 1;
		mid = (low + high) / 2;
		return searchKey2(arr, key, low, high);
	}
	else if (strcmp(arr[mid], key) < 0) {
		low = mid + 1;
		mid = (low + high) / 2;
		return searchKey2(arr, key, low, high);
	}
	else
		return mid;
}

int compare(const void *arr, const void *key) {
	//if (strcmp((char*)arr, (char*)key) > 0)
	//	return 1;
	//else if (strcmp((char*)arr, (char*)key) < 0)
	//	return -1;
	//else
	//	return 0;
	return (strcmp((char*)arr, (char*)key) > 0);	// �۰ų� ���� ��� 1 ����
}

main()
{
	char key[][10] = { "Alice", "Bill", "Carol", "David", "Elvis", "Fred", "Gabriel",
	"Helen", "Isabel", "Jane", "Kuper", "Louic", "Mathilda", "Nadia", "Olive",
	"Pablo", "Queen", "Rambo", "Scarlet", "Trisha", "Umberto", "Vincent",
	"Wily", "Xxx", "Yuki", "Zorro" };
	char *keyValue = "Pablo";
	int retval = searchKey(key, keyValue, 25);
	printf("%d\n", retval);
	retval = searchKey2(key, keyValue, 0, 25);
	printf("%d\n", retval);
	
	// �ݵ�� �迭�� ������ �Ǿ� �־�� bsearch�� �� �� �ִ�.
	retval = bsearch(keyValue, key, 26, sizeof(key[0]), compare);	// sizeof(key) / sizeof(key[0])
	printf("%d\n", retval);
}

/* 
	����Ž��Ʈ��
		�� ��忡 �ϳ��� �����͸� �����ϴ� Ž���� ���� Ʈ��
		��� ��忡 ���Ͽ� �ڽ��� ���� ��Ʈ������ �ڽź��� ���� ����, �����ʿ��� �ڽź��� ū ���� ��ġ�Ѵ�.
		Ž���ؾ� �ϴ� ������ ��������� �߰��Ǿ� Ȯ��� �� �ַ� ���
*/
