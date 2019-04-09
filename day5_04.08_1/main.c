#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#pragma warning(disable:4996)	// 새문법을 쓰지 않겠다.

/*
 자료구조 (자료를 어떻게 저장할 것인가) 의 종류
	* 모든 자료구조는 반드시 초기화 함수가 있다.
	1. list (순서가 있는 구조)
		1-1. 정렬: select, bubble, insert, indirect-insert, shell, merge, quick Sort
		1-2. circular list, double linked list
		1-3. linux kernel (linked list)
	2. stack (last input first out : LIFO)
		2-1. 함수 콜 스택 내부 구조 (콜백 함수의 형태)
	3. queue (FIFO) - 기수정렬
	4. tree	(보통 이진트리, binary tree) - linux (Red-black T)
			- Tree sort
		4-1. 삼성폰: 공장초기화 (hash-Tree의 재구성)	// hash, tree 둘 다 빠름
	5. graph
*/

/* list: 배열, struct -> linked list
		배열: insert, delete할 때 제약이 따른다.
			  중간에 insert/delete할 경우 그만큼 뒷 배열을 shift해야 함
		linked list: 배열의 제약을 해결.
*/


/* structure: 서로 다른 타입을 묶은 집합 */
//typedef struct _list List;	// 사용자 정의 타입	// struct _list 대신 List로 사용
//	// 절차지향적인 C에선 typedef struct _list List가 아직 불완전한 구조로 만들어짐.
//	// 아래의 구조체 정의를 지나면 List가 완전한 구조체로 만들어진다.
//struct _list {
//	int key;
//	struct _list	*next;	// 자기 참조 구조체	// 자기 자신과 같은 메모리의 주소를 저장
//	// char* func() {} --> char형 주소를 반환하는 함수. * = 주소
//};
//// 좌우 기둥 만들기
//List *head, *tail;	// struct _list *head, *tail;
//
//void list_init(void) {	// 빨래를 널기 위한 초기화
//	head = (List *)malloc(sizeof(List));	// 좌측 기둥
//	tail = (List *)malloc(sizeof(List));	// 우측 기둥
//
//	head->next = tail;	// 빨래줄
//	tail->next = tail;	// 우측 빨래줄 매듭
//}
//
//// head 뒤에 계속 추가
//void list_add(int data) {
//	List *newNode;
//	newNode = (List *)malloc(sizeof(List));	// 새 노드	// 함수가 끝날 때 List는 사라지지만 heap 영역에 해당 데이터 값은 존재함.
//	newNode->key = data;
//
//	newNode->next = head->next;	// 좌측 기둥이 보고 있는 주소를 복사
//	head->next = newNode;	// 좌측기둥이 새 노드를 가리킨다.
//}
//
//void list_view(void) {
//	List *wk;	// 빨래 걷는 친구
//	wk = head->next;	// 첫 번째 빨래의 주소 (첫 노드)
//	if (wk == tail) {
//		printf("리스트가 비었습니다.\n");
//		return;
//	}
//
//	while (wk != tail) {
//		printf("%d ", wk->key);
//		wk = wk->next;
//	}
//}
//
//void list_delete(void) {
//	List *kill = head->next;	// 삭제할 노드의 주소를 kill에게
//	
//	head->next = kill->next;
//	free(kill);
//}
//
//void list_find(int data) {
//	List *find = head->next;
//
//	while (find->key != data && find != tail) {	// 못 찾고 끝이 아닐 때
//		find = find->next;
//	}
//
//	if (find->key == data)
//		printf("%d 찾음", data);
//*/
//	if (find == tail)	// 찾는 친구 (find) 가장 우측 기둥까지 가봤다.
//		printf("%d 없음", data);
//	else
//		printf("%d 찾음", data);
//}
//
//void list_find_del(int fd) {
//	List *wk;	// 빨래 걷는 친구
//	List *hold = NULL;
//	wk = head;
//
//	while (wk->next->key != fd && wk->next != tail)	// 찾으러 다닌다
//	{
//		wk = wk->next;
//	}	// 찾거나 끝까지 가서 못 찾았을 때
//	
//	if (wk->next != tail) {
//		hold = wk->next;	// 찾은 녀석을 홀딩.	// 지우거나 앞으로 던지거나		
//		wk->next = hold->next;
//		free(hold);
//	}
//}
//
//void list_add_sort(int data) {
//	List *nw;
//	List *prv;	// 앞쪽을 가리키는 포인터
//	List *cmp;	// 실제 data와 비교하는 노드
//	prv = head;
//	cmp = head->next;
//
//	while (cmp->key <= data && cmp != tail)	// 작으면 더 큰 것을 찾아야 한다.
//	{
//		prv = cmp;	// prv = prv->next;
//		cmp = cmp->next;
//	}
//
//	if (cmp == tail && cmp->key != data)
//		return;
//
//	nw = (List*)malloc(sizeof(List));
//	nw->key = data;
//	nw->next = cmp;
//	prv->next = nw;
//
//}
//
//// move to front
//// 찾은 노드를 제일 앞으로 옮김
//void list_moveToFront(int data) {
//	List *wk = head->next;
//	List *prev = head->next;
//
//	while (wk->key != data && wk != tail) {
//		prev = wk;
//		wk = wk->next;
//	}
//
//	if (wk != tail) {
//		prev->next = wk->next;
//		wk->next = head->next;
//		head->next = wk;
//	}
//}
//
//void list_all_del() {
//	List *del = head;
//	List *wk = head->next;
//
//	while (wk != tail) {
//		del->next = wk->next;
//		del = wk;
//		wk = wk->next;
//		free(del);
//	}
//
//	head->next = tail;
//}
//
//main()
//{
//	// 모든 자료구조는 반드시 초기화 함수가 있다.
//	list_init();
//
//	// 첫 번째 빨래 널기
//	list_add(7);
//	list_add(3);
//	list_add(2);
//	list_add(1);
//
//	list_view();	// 입력된 데이터들의 확인
//
//	puts("");
//	/*
//	list_moveToFront(7);
//	list_view();
//	puts("");
//*/
//	list_delete();
//	list_view();
//	puts("");
//
//	// 삽입, 보기, 삭제, 찾기
//	list_find(3);	// 3을 찾음		// head -> 2 -> 3 -> tail
//	puts("");
//	list_find(5);	// 5는 없습니다.
//	puts("");
//
//	list_find_del(1);
//	list_view();
//	puts("");
//
//	list_add_sort(5);
//	list_view(); 
//	puts("");
//
//	// 모든 리스트 삭제하는 함수
//	list_all_del();
//	list_view();
//	puts("");
//}	

/* 선택 정렬 */
void Selectionsort(int A[], int n)
{
	int dx, k, min;
	int t;
	for (dx = 0; dx < n - 1; dx++) {
		min = dx;
		for (k = dx + 1; k < n; k++)
			if (A[k] < A[min])	min = k;
		t = A[min];
		A[min] = A[dx];
		A[dx] = t;
	}
}

/* 개선된 선택 정렬 */
void Selectionsort2(int A[], int n)
{
	int min, minindex;
	int dx, k;
	for (dx = 0; dx < n - 1; dx++) {
		minindex = dx;
		min = A[dx];
		for (k = dx + 1; k < n; k++) {
			// 조건을 간단하게 하는 게 속도 튜닝의 한 방법 (체인 제거)
			if (min > A[k]) {	// 속도차원에서 중요한 것은 비교 연산	// 고정된 값 하나, 상대적 거리 계산하는 값 하나
				min = A[k];
				minindex = k;
			}
		}
		k = A[min];
		A[min] = A[dx];
		A[dx] = k;
	}
}

/* 구조체 문제 */
//struct engine {
//	int piston;
//	int fan;
//	int pipe;
//};
//
//struct car {
//	struct engine *sedan, *sports;
//};
//
//void hyundai(struct car *man) {
//	// main에서 메모리 할당한 후 주소값을 넘겨줬으므로 여기서 또 할당하면 안됨.
//	//struct engine *en = (struct engine*)malloc(sizeof(struct engine));
//	//en = &man->sedan;
//	struct engine *en = man->sedan;
//	
//	en->piston = 50;
//	en->fan = 30;
//	en->pipe = 20;
//}
//
//void main()
//{
//	struct car hi;
//	hi.sedan = (struct engine*)malloc(sizeof(struct engine));
//	hyundai(&hi);
//	printf("%d %d %d\n", hi.sedan->piston, hi.sedan->fan, hi.sedan->pipe);
//}

//#define swap(a, b) do{int t; t=a; a=b; b=t;}while(0)	// 한 번만 반복되게
#define swap(a, b) {int t; t=a; a=b; b=t;}	// 한 번만 반복되게
/* 정렬 문제 */
//#define swap(a, b) do{int t; t=a; a=b; b=t;}while(0)
//
//int partition(int arr[], int s, int e)
//{
//	int i, j, pivot;
//	i = s;	// big
//	j = e + 1;	// small
//	pivot = arr[i];
//	while (i < j) {
//		//pivot보다 큰값을 찾는 구문
//		while (i <= e && pivot >= arr[++i]);
//		//pivot 보다 작거나 같은 값을 찾는 구문
//		while (j >= 0 && pivot < arr[--j]);
//
//		if (i < j) {
//			swap(arr[i], arr[j]);
//		}
//	}
//	swap(arr[s], arr[j]);
//	return j;
//}
//void myqsort(int arr[], int s, int e)
//{
//	int mid;
//	if (s < e) {
//		mid = partition(arr, s, e);
//		myqsort(arr, s, mid - 1);
//		myqsort(arr, mid + 1, e);
//	}
//}
//
////다음  배열을 정렬 하시오
//
//main()
//{
//	int arri[] = { 3,4,1,5,2,8,9,6,10,7 };
//
//	myqsort(arri, 0, 9);
//	for (int i = 0; i < 10; i++)
//		printf("%d ", arri[i]);
//
//}

/* 스트링 정렬 (오류있음) */
//////다음 이름을 2차원 배열에 넣고 다음 정렬을 이용하여 정렬 하시오
////void isort(int a[], int n)
////{
//// int i, j, t;
//// for (i = 1; i < n; i++)
//// {
////  t = a[i];
////  j = i;
////  while (a[j-1] > t && j > 0)
////  {
////   a[j] = a[j-1];
////   j--;
////  }
////  a[j] = t;
//// }
////}
//void isort(char (*a)[7], int n)	// *a[] 아님
//{
//	int i, j; // , t;
// char t[7];
// for (i = 1; i < n; i++)
// {
//  //t = a[i];
//	 strcpy(t, a[i]);
//  j = i;
//  while (j > 0 && strcmp(a[j - 1], t) > 0)	// strcmp(a, b): 같으면 0	 a > b => 1		 a < b => -1 리턴	(소문자 > 대문자)
//  {
//	  strcpy(a[j], a[j-1]);
//   j--;
//  }
//  strcpy(a[j], t);
//
// }
//}
//
//void main()
//{
//	char arr[][7] = { "배상우", "소준영", "손병국", "고승희", "구민교", "김기백", "김다희", "박선애", "박성경", "신동열", "이경수", "조희은", "황상진", "강상헌", "이호세", "전하람", "이승연", "정낙현", "조민희", "이인찬" };
//
//	isort(arr, 20);
//	for(int i=0; i<20; i++)
//		printf("%s ", arr[i]);
//}

/* 서버, 클라이언트 call, call back */
//void cold(void) { puts("cold"); }	// 클라이언트
//void hot(void) { puts("hot"); }	// 클라이언트
//
//void aircon(void(*p) (void))	// 서버코드
//{
//	p();	// call back
//}
//
//main()	// 클라이언트 코드 
//{
//	aircon(cold);	// call
//	
//	aircon(hot);
//}

/* 여러 타입 정렬 */
//void printInt(int *arr, int size);
//void printDbl(double *arr, int size);
//void printstr(double(*arr)[10], int size);
//
//int comp_i(const void* a, const void* b) {	// 각각 주소를 받아옴.
//	return (*(int*)a - *(int*)b);	// *(int*)a -> a를 주소로 바꿔서 그 안의 값을 받아옴.
//}
//
////라이브러리 제공하는 qsort를 위한 comp_d 함수 완성
//int comp_d(const void* a, const void* b) {
//	if ((*(double*)a > *(double*)b))
//		return 1;
//	else if ((*(double*)a < *(double*)b))
//		return -1;
//	else
//		return 0;
//	//return ((*(double*)a - *(double*)b) > 0) ? 1 : (*(double*)a - *(double*)b);
//}
//
////라이브러리 제공하는 qsort를 위한 comp_s 함수 완성
//int comp_s(const void* a, const void* b) {
//	return strcmp((char*)a, (char*)b);
//}
//
//int main(void) {
//	int arri[] = { 3,4,1,5,2,8,9,6,10,7 };
//	double arrd[] = { 3.2, 5.6, 4.3, 8.7, 2.3, 4.5, 2.1, 2.3, 4.6, 4.5 };
//	char arrs[][7] = { "배상우", "소준영", "손병국", "고승희", "구민교",
//		"김기백", "김다희", "박선애", "박성경", "신동열",
//		"이경수", "조희은", "황상진", "강상헌", "이호세",
//		"전하람", "이승연", "정낙현", "조민희", "이인찬",
//		"지도현" };	// 한글 한 글자당 char 2byte씩
//	qsort(arri, sizeof(arri) / sizeof(arri[0]), sizeof(int), comp_i);
//	//    소팅 대상, 대상의 개수,				1개 개수의 크기, 정렬기준
//	printInt(arri, sizeof(arri) / sizeof(arri[0]));
//
//	qsort(arrd, sizeof(arrd) / sizeof(arrd[0]), sizeof(double), comp_d);
//	printDbl(arrd, sizeof(arrd) / sizeof(arrd[0]));
//
//	//라이브러리 qsort를 이용하여 2차원배열에 있는 문자열을 정렬합시다.
//	qsort(arrs, sizeof(arrs) / sizeof(arrs[0]), sizeof(arrs[0]), comp_s);
//	printstr(arrs, sizeof(arrs) / sizeof(arrs[0]));
//
//	return 0;
//}
//void printInt(int *arr, int size) {
//	int dx = 0;
//	for (dx = 0; dx < size; ++dx) {
//		printf("%d ", arr[dx]);
//	}
//	printf("\n");
//}
//
//void printDbl(double *arr, int size) {
//	int dx = 0;
//	for (dx = 0; dx < size; ++dx) {
//		printf("%.1f  ", arr[dx]);
//	}
//	printf("\n");
//}
//
//void printstr(char(*arr)[10], int size) {
//	int dx = 0;
//	for (dx = 0; dx < size; ++dx) {
//		printf("%s ", arr[dx]);
//	}
//	printf("\n");
//}
//

/* 구조체 배열 정렬 */
//다음 구조체를 라이브러리 qsort를 상용하여 itemname의 오름차순으로 정렬하시오
//typedef struct _sales
//{
//	char itemname[20];
//	int unitprice;
//	int count;
//	int amount;
//}Sales;
//
//int prd_item(const void *a, const void *b)
//{
//	return strcmp((*(Sales*)a).itemname, (*(Sales*)b).itemname);	// (Sales*)a->itemname
//}
//
//main()
//{
//	Sales prd[5] = {
//	 { "ccc", 10,90,900 },
//	{ "aaa", 20,80,1600 },
//	{ "ddd", 30,70,2100 },
//	{ "eee", 40,60,2400 },
//	{ "bbb", 50,50,2500 }
//	};
//	int dx;
//
//	qsort(prd, 5, sizeof(prd[0]), prd_item);
//
//
//	for (dx = 0; dx < 5; dx++)
//		printf("%s %d %d %d\n", prd[dx].itemname,
//			prd[dx].unitprice, prd[dx].count, prd[dx].amount);
//
//
//}

/* 구조체 포인터 배열 정렬 */
//다음 구조체포인터 배열을 라이브러리 qsort를 상용하여 name의 오름차순으로 정렬하시오
//typedef struct _node node;
//struct _node {
//	char name[10];
//	struct _node *next;
//};
////int gg = 0;
//int cmp_node(const void *a, const void *b)
//{	
//	return strcmp((*(node**)a)->name, (*(node**)b)->name);
//}
//node *p, *q;
//main()
//{
//	node *k[4];
//
//	p = (node*)malloc(sizeof(node));
//	strcpy(p->name, "ccc");
//	p->next = NULL;
//	q = (node*)malloc(sizeof(node));
//	strcpy(q->name, "aaa");
//	q->next = NULL;
//
//
//	k[0] = q;
//	k[1] = p;
//	k[2] = (node*)malloc(sizeof(node));
//	strcpy(k[2]->name, "bbb");
//	qsort(k, 3, sizeof(node*), cmp_node);
//
//	puts("\n-----");
//	printf("%s\n", k[0]->name);
//	printf("%s\n", k[1]->name);
//	printf("%s\n", k[2]->name);
//
//}

/* qsort 내부 구조 문제 */
//typedef int FCMP(const void* p, const void *k);
//
//int cmp_i(const void *p, const void*k)
//{
//	return *(int*)p - *(int*)k;
//}
//
//int cmp_s(const void *p, const void*k)
//{
//	return strcmp((char*)p, (char*)k);
//}
//
//// quicksort
//void *func(void *base, size_t num, size_t width, FCMP fcmp)	//  int (*fcmp)()
//{
//	//내부적으로 cmp_i나 cmp_s를 호출한다 //결과는 -1(음수), 0, 1(양수)을 리턴한다.
//	//if (fcmp == cmp_i)
//	//	printf("%d\n", fcmp((int*)base, ((int*)base + width)));
//	//else if (fcmp == cmp_s)
//	//	printf("%d\n", fcmp((char*)base, ((char*)base + width)));
//
//	printf("%d\n", fcmp(base, ((char*)base + width)));
//	//printf("%d\n", fcmp((void*)base, (&((void*)base) + width)));	// (&(void*)base)+1)
//
//}
//main()
//{
//	int a[5] = { 10000000,3,1,5,2 };
//	char b[10][10] = { "aaaa","aaaa" };
//
//	func(a, 5, sizeof(int), cmp_i);
//	func(b, 2, sizeof(b[0]), cmp_s);
//}

/*	
	다음 각 메모리에 대한 포인터를 만들고
	대입시 warning이 발생하지 않도록 하시오

	예) char **a;
	char ***pa = &a;
*/

// char **a;
// char *b[2];
// char c[2][3];
// char *d[2][3]={"aa","bb","cc","dd","ee","ff"};
// char (*e)[2][3];
// char (*f[2])[3];
//
//main()
//{
//	char **a;	// 더블포인터
//	char *b[2];	// char형 포인터 2개짜리 b
//	char c[2][3];	// char형 3개짜리 총 2개
//	char *d[2][3] = { "aa","bb","cc","dd","ee","ff" };	// char형 포인터 3개짜리가 총 2개	// 각 문자열의 주소가 배열 안에 들어가 있는 것.
//	char(*e)[2][3];	// 3차원 배열을 위한 포인터	(게임에서 밥먹듯이 쓰임)	// 배열을 보는 싱글 포인터
//	char(*f[2])[3];	// char형 3개짜리 배열을 가리키는 포인터가 2개인 f	// 배열 포인터를 위한 배열
//
//	// b, c, d는 배열이므로 이름 자체가 주소를 의미.
//	// a: 더블포인터, e: 싱글포인터
//	char ***ap = &a;
//	char **bp = b;	// 더블 포인터
//	char (*cp)[3] = c;	//  char형 3개짜리를 보는 포인터
//	char *(*dp)[3] = d;	// char형 포인터 3개를 봐야함	// char형 포인터 3개짜리를 가리키는 포인터
//	char (**ep)[2][3] = &e;	// 
//	char(**fp)[3] = f;
//
//	printf("%s ", *dp[1]);
//}

