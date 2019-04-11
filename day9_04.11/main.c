#ifndef HEADER
#define HEADER
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>

#pragma warning(disable:4996)	// 새문법을 쓰지 않겠다.

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
 expression은 변수나 임의의 수식
 expression이 false일 경우 assert()가 stderr에 오류메세지
 NDEBUG의 정의 유무에 따라 되고 안되고를 구별한다.
*/

/* assert 무력화 */
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

/* 순차 탐색 */
//int Seqsearch(int A[], int key, int n)
//{
//	int k = n;
//	A[0] = key; // 찾고자 하는 배열을 맨 앞이나 맨 뒤에 둠
//	while (A[k] != key)
//		k--;	// down counting을 할 경우 어셈블러 내부 구조에서 4줄->3줄로 줄어듬	for(i=10;i>=10; i--)	
//				// (같은 down counting이어도 조건문에 따라 속도가 달라짐) i>=0, i !=0 : 3줄, i>0 : 4줄
//	return k;
//}

/* algo header
	1. qsort()	 // 정렬
	2. bsearch() // 이미 정렬된 배열에서 원하는 값을 찾음
*/
/* 예제
char key[][] = {"Alice", "Bill", "Carol", "David", "Elvis", "Fred", "Gabriel",
    "Helen", "Isabel", "Jane", "Kuper", "Louic", "Mathilda", "Nadia", "Olive",
    "Pablo", "Queen", "Rambo", "Scarlet", "Trisha", "Umberto", "Vincent", 
    "Wily", "Xxx", "Yuki", "Zorro"};


1. 일반함수로 만들어 찾기 
2. 재귀함수로 만들어 찾기
3. bsearch() - 라이브러리 함수로 찾기

 

위 1,2,3번 함수로 Pablo가 몇번째 위치하는 지를 출력하시오
*/

int searchKey(char (*arr)[10], char *key, int size) {
	//int index = 1;
	int low = 0;
	//int high = (sizeof(*arr) / sizeof(*arr[0]))-1;
	int high = size;
	int mid = (low + high) / 2;

	while (1) {
		if (strcmp(arr[mid], key) > 0) {	// key가 더 작은 경우
			high = mid - 1;
			mid = (low + high) / 2;
		}
		else if (strcmp(arr[mid], key) < 0) {	// key가 더 큰 경우

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
	return (strcmp((char*)arr, (char*)key) > 0);	// 작거나 같은 경우 1 리턴
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
	
	// 반드시 배열이 정렬이 되어 있어야 bsearch를 쓸 수 있다.
	retval = bsearch(keyValue, key, 26, sizeof(key[0]), compare);	// sizeof(key) / sizeof(key[0])
	printf("%d\n", retval);
}

/* 
	이진탐색트리
		각 노드에 하나씩 데이터를 저장하는 탐색용 이진 트리
		모든 노드에 대하여 자신의 왼쪽 부트리에는 자신보다 작은 값이, 오른쪽에는 자신보다 큰 값이 위치한다.
		탐색해야 하는 영역이 계속적으로 추가되어 확장될 때 주로 사용
*/
