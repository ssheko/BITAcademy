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
//
//int searchKey(char (*arr)[10], char *key, int size) {
//	//int index = 1;
//	int low = 0;
//	//int high = (sizeof(*arr) / sizeof(*arr[0]))-1;
//	int high = size;
//	int mid = (low + high) / 2;
//
//	while (1) {
//		if (strcmp(arr[mid], key) > 0) {	// key가 더 작은 경우
//			high = mid - 1;
//			mid = (low + high) / 2;
//		}
//		else if (strcmp(arr[mid], key) < 0) {	// key가 더 큰 경우
//
//			low = mid + 1;
//			mid = (low + high) / 2;
//		}
//		else
//			break;
//	}
//	/*while (strcmp(*arr++, key)) {
//		index++;
//	}*/
//	return mid;
//}
//
//int searchKey2(char (*arr)[10], char *key, int low, int high) {
//	int mid = (low + high) / 2;
//	if (strcmp(arr[mid], key) > 0) {
//		high = mid - 1;
//		mid = (low + high) / 2;
//		return searchKey2(arr, key, low, high);
//	}
//	else if (strcmp(arr[mid], key) < 0) {
//		low = mid + 1;
//		mid = (low + high) / 2;
//		return searchKey2(arr, key, low, high);
//	}
//	else
//		return mid;
//}
//
//int compare(const void *arr, const void *key) {
//	//if (strcmp((char*)arr, (char*)key) > 0)
//	//	return 1;
//	//else if (strcmp((char*)arr, (char*)key) < 0)
//	//	return -1;
//	//else
//	//	return 0;
//	return strcmp((char*)arr, (char*)key); // (strcmp((char*)arr, (char*)key) > 0);	// 작거나 같은 경우 1 리턴
//}
//
//main()
//{
//	char key[][10] = { "Alice", "Bill", "Carol", "David", "Elvis", "Fred", "Gabriel",
//	"Helen", "Isabel", "Jane", "Kuper", "Louic", "Mathilda", "Nadia", "Olive",
//	"Pablo", "Queen", "Rambo", "Scarlet", "Trisha", "Umberto", "Vincent",
//	"Wily", "Xxx", "Yuki", "Zorro" };
//	char *keyValue = "Pablo";
//	int retval = searchKey(key, keyValue, 25);
//	printf("%d\n", retval);
//	retval = searchKey2(key, keyValue, 0, 25);
//	printf("%d\n", retval);
//	
//	// 반드시 배열이 정렬이 되어 있어야 bsearch를 쓸 수 있다.
//	retval = bsearch(keyValue, key, 26, sizeof(key[0]), compare);	// sizeof(key) / sizeof(key[0])
//	printf("%d\n", retval);
//}

/* 
	이진탐색트리
		각 노드에 하나씩 데이터를 저장하는 탐색용 이진 트리
		모든 노드에 대하여 자신의 왼쪽 부트리에는 자신보다 작은 값이, 오른쪽에는 자신보다 큰 값이 위치한다.
		탐색해야 하는 영역이 계속적으로 추가되어 확장될 때 주로 사용

	이진탐색트리 삭제
		자식이 둘인 노드의 삭제
			왼쪽 부트리(자신보다 작은 값)에서 가장 큰 값
			혹은 오른쪽 부트리에서 가장 작은 값과 swap한 후 자기자신 삭제
*/

/* 
	균형 이진트리
		left_subtree = (n - 1)/2				// (전체 개수 - 루트) /2
		right_subtree = n - 1 - left_subtree;	// 전체 개수 - 루트 - 왼쪽 부트리 개수
*/

/* 
	힙 자료구조 
		1. 완전 이진트리 (모든 노드 꽉 차 있고, 우측 하단이 비어있는 경우)
		2. Max Heap의 경우 부모 노드의 값이 자식 노드의 값보다 크거나 같다.
			(따라서 Max heap의 경우 Root의 값이 가장 크다.) Min heap은 반대
		3. 완전 이진트리이므로 위에서부터 차례로 배열에 넣어 다음과 같이 표현할 수 있다.
			배열에 넣고 나면 다음의 성질을 만족시킨다.
				1. 중간에 빈 자리가 없다. (완전 이진트리)
				2. i번 노드의 왼쪽 자식 노드는 i*2번 노드
					오른쪽 자식 노드는 i*2+1번 노드
				3. i번 노드의 부모 노드는 [i/2]번 노드 (소수점은 버림)
		4. Insert: up-heap 알고리즘 (노드를 마지막에 넣고 값을 비교하면서 위로 올림)	// 값을 넣고 부모와 비교해서 부모보다 클 경우 부모와 swap
		   Delete: down-heap 알고리즘 (삭제할 노드를 마지막 노드와 바꾼 후 비교)
*/

/*
	Hash
		원소가 저장될 자리가 원소의 "값"에 의해 결정되는 자료구조
		평균 상수 시간에 삽입, 삭제, 검색
		매우 빠른 응답을 요하는 응용에 유용
		될 수 있으면 골고루 퍼트리게. 고른 분포를 갖도록
		1. 선형탐사법
			충돌이 일어날 경우 다음 버킷에 넣는 방법
		2. 이중해쉬법(선형탐사의 변형)
			키값을 변형시켜 이를 이용해 다른 버킷에 넣음
		3. 연결법 (chaining)
			같은 주소로 해싱되는 원소를 모두 하나의 연결 리스트로 관리 (Hash tree)
			추가적인 연결 리스트 필요			
*/


/* list_entry */
//#define list_entry(ptr, type, member) \
// ((type *)((char *)(ptr)-(unsigned long)(&((type *)0)->member)))
////list_entry를 이용하여 다음 구조체의 각멤버(a,b,c,d,x,y,z)를 이용해 
////구조체의 첫 주소를 출력하는 main함수를 완성하시오
//
//typedef struct engine {
//	char a[5];
//	double b;
//	int c[3];
//}engine;
//
//typedef struct car {
//	char x[10];
//	int y;
//	struct engine z;
//}car;
//
//
//void main()
//{
//	car bm;
//	//list_entry(&bm.y, int, car)
//	printf("&bm : [ %x ]\n", &bm);
//	printf("&bm : [ %x ]\n", list_entry(&bm.x, struct car, x));
//	printf("&bm : [ %x ]\n", list_entry(&bm.y, struct car, y));
//	printf("&bm : [ %x ]\n", list_entry(&bm.z.b, struct car, z.b));
//	printf("&bm : [ %x ]\n", list_entry(&bm.z.a, struct car, z.a));
//	printf("&bm : [ %x ]\n", list_entry(&bm.z.c, struct car, z.c));
//
//
//}


/* 리눅스 list.h 이용 예제 */
//#define __KERNEL__
//#include "list.h"
//
////-다음과 같이 출력되게 하시오
////
////************
////[Empty]
////* ***********
////[123]
////* ***********
////[789]
////[123]
////* ***********
////[123]
////계속하려면 아무 키나 누르십시오 . . .
////
////
////
////list.h(기존에 메일로 보낸 리눅스 커널 헤더)파일을 include 할 수 있도록 구현하시오
////inline이나 prefetch는 제공되지 않는 기능이다.
//
//typedef struct kernel_struct
//{
//	int key;
//	struct list_head list;
//
//}Node;
//#define ADRS(lt) &(lt)->list
//
//#define Node_SIZE (sizeof(Node))
//
//Node *head;
//
//
//void init_Node(void)
//{
//	//head를 메모리 할당시킨다 
//	head = malloc(Node_SIZE);
//
//	//head 구조체 멤버인 list내부의 멤버가 list를 가리키게 초기화시키자
//	INIT_LIST_HEAD(&head->list);
//}
//
//void print_all(void)
//{
//	struct list_head *temp;
//	printf("************\n");
//	list_for_each(temp, &head->list) {
//		Node *ps = list_entry(temp, Node, list);
//		printf("[%d]\n", ps->key);
//	}
//}
//
//void main()
//{
//	Node *a, *b;
//	if ((a = malloc(Node_SIZE)) == NULL)
//		printf("[ Error ]\n");
//	if ((b = malloc(Node_SIZE)) == NULL)
//		printf("[ Error ]\n");
//
//	init_Node();
//	a->key = 123; b->key = 789;
//	print_all();
//
//	if (list_empty(&head->list))
//		printf("[ Empty ]\n");
//
//
//
//
//
//	list_add();//list_add 함수를 이용하여 head뒤에 a를 삽입
//
//	print_all();
//	list_add();//list_add 함수를 이용하여 head뒤에 b를 삽입
//	print_all();
//	list_del(); // list_del함수를 이용하여 head뒤에 를 삭제
//
//
//		print_all();
//	free(a);
//	free(b);
//	free(head);
//}
//

/* 
	그래프 
		1. 인접 행렬 : 이차원 배열로 구현
		2. 인접 리스트: 정점 수만큼의 연결 리스트로 구성
	그래프 탐색
		1. 깊이우선: 스택 사용
		2. 너비우선: 큐 사용

	가중 그래프 + 방향 그래프 = 네트워크

	* 깊이우선탐색 (스택기반)
		중복이 발생할 수밖에 없기 때문에 중복 확인용 체크 배열이 꼭 있어야 한다.
			1. A를 스택에 넣고, 체크배열의[A]에 1
			2. A를 팝하고 A와 연결된 노드를 스택에 모두 넣고, 각각 체크 1
			3. 2번부터 다시 반복 (체크되어 있을 경우 무시)
		맹목적 탐색. 그래프를 중복 없이 탐색하겠다.
		깊이 파고 들어갔다 나옴
	* 너비우선탐색 (큐 기반)
		정점을 횡적으로 뺌
			1. 시작정점 넣고 체크배열에 1
			2. 큐를 get하고 get한 정점과 연결된 정점 put, 체크 1
			3. 2번부터 다시 반복. (체크되어 있을 경우 무시)
	* 신장나무 (Spanning tree)
		모든 정점의 방문 모든 간선을 방문치 않는다. (n, n-1)
		- 모든 정점 순회를 최소비용 (항공, 전자회로, 스케줄링)
			ex) 우선순위 탐색, Kruskal, Prim 알고리즘

		- 두 정점의 경로의 가중치 합이 가장 작게
			ex) dijkstra 알고리즘

		Kruskal 알고리즘
			같은 크기의 가중치의 간선끼리 집합을 만들고, 작은 값부터 추가
			차례로 확인하면서 cycle을 만들지 않는 간선만 추가하는 방식

		Prim 알고리즘
			간선을 확인하면서 정점끼리 연결해주는데
			연결 후 근처 정점 중 제일 가중치가 작은 간선을 선택해 연결.

*/
