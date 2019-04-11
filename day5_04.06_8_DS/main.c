#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#pragma warning(disable:4996)	// 새문법을 쓰지 않겠다.

/* 구조체 */
//struct car {
//	int engine;
//	int wheel;
//	int body;
//};
//
//main()
//{
//	struct car bm;	// 구조체 변수
//	bm.engine = 300;
//	scnaf("%d", &bm.engine);
//
//	struct car *p;	// 구조체 포인터 변수
//	p = &bm;
//
//	p->body = 500;
//	scanf("%d", p->body);
//}

/* 중첩 구조체 */
//struct bonnet {
//	int engine;
//	int pipe;
//	int piston;
//};
//struct car {
//	struct bonnet bn; //int engine;
//	int wheel;
//	int body;
//};
//
//main()
//{
//	struct car bm;	// 구조체 변수
//	bm.bn.engine = 300;
//	scnaf("%d", &bm.bn.engine);
//
//	struct car *p;	// 구조체 포인터 변수
//	p = &bm;
//
//	p->body = 500;
//	scanf("%d", p->body);
//}

/* 구조체 예제 */
//struct num {
//	int fir;
//	int sec;
//};
//
//void func1(int a, int b) { printf("%d\n", a + b); }
//void func2(struct num *a) { printf("%d\n",a->fir + a->sec); }	// *a = a[] = a[100]	// 구조체 싱글 포인터
//void func3(struct num *a) { 
//	printf("%d\n", a[0].fir + a[0].sec + a[1].fir + a[1].sec);
//	printf("%d\n", a->fir + a->sec + (a + 1)->fir + (a + 2)->sec);	// 연산자 우선순위 (+) < (->) 이므로 반드시 (a+1)->fir
//	printf("%d\n", (*a).fir + (*a).sec + (*(a+1)).fir + (*(a + 1)).sec);
//}
//
//main()
//{
//	struct num a = { 1, 2 }, b = { 3,4 }, c[2] = { 5, 6,7,8 };
//
//	func1(a.fir, a.sec);	// 함수 내부에서 1 + 2 출력
//	func2(&b); // b의 주소를 던져서 3 + 4 출력
//	func3(c);	// c의 주소를 던져서 5+6+7+8 출력	// 배열은 이름이 첫 번째 요소의 주소가 된다.
//}

/* 구조체 문제 */
// 국어점수, 영어점수, 수학점수, 총점, 랭킹(순위)를 매기고 출력
struct subject {
	int subname[5];	// 국어, 영어, 수학, 총점, 랭킹
};

struct sung {
	char name[10];
	float avg; // 평균
	struct subject sub;
};

char *su[] = { "국어", "영어", "수학" };


void print(struct sung *p) {
	printf("성명\t%s\t%s\t%s\t총점\t순위\t평균\n", su[0], su[1], su[2]);
	printf("-------------------------------------------------\n");
	for (int i = 0; i < 3; i++) {
		printf("%s\t", (p + i)->name);	//  p[i].name
		for (int j = 0; j < 5; j++)
			printf("%d\t", (p + i)->sub.subname[j]);	// p[i].sub.subname[j]
		printf("%.1f\n", (p + i)->avg);	// p[i].avg)
	}
}
//
//
//main()
//{
//	struct sung man[3];
//	//int rank[2][3];
//
//	for (int i = 0; i < 3; i++) {
//		printf("%d번째 사람 이름: ", i);
//		scanf("%s", &man[i].name);
//
//		man[i].sub.subname[3] = 0;	// 총점의 초기화
//		man[i].sub.subname[4] = 1;	// 랭킹 초기화
//		for (int j = 0; j < 3; j++) {
//			printf("%s점수: ", su[j]);
//			scanf("%d", &man[i].sub.subname[j]);
//			man[i].sub.subname[3] += man[i].sub.subname[j];	// 총점
//		}
//		
//		/*printf("국어점수 : ");
//		scanf("%d", &man[i].sub.subname[0]);
//		printf("영어점수 : ");
//		scanf("%d", &man[i].sub.subname[1]);
//		printf("수학점수 : ");
//		scanf("%d", &man[i].sub.subname[2]);
//
//		man[i].sub.subname[3] = (man[i].sub.subname[0] + man[i].sub.subname[1] + man[i].sub.subname[2]);
//		*/
//		man[i].avg = man[i].sub.subname[3] / (float)3;
//		/*
//				rank[0][i] = i+1;
//				rank[1][i] = man[i].sub.subname[3];*/
//	}
//
//	for (int i = 0; i < 3; i++) {
//		for (int j = 0; j < 3; j++) {
//			if (man[i].sub.subname[3] < man[j].sub.subname[3])	// 본인보다 큰 점수를 만날때마다 등수 +1씩
//				man[i].sub.subname[4]++;
//		}
//	}
//	/*
//	for (int i = 0; i < 2; i++) {
//		for (int j = 1; j < 3; j++) {
//			if (rank[1][i] == rank[1][j]) {
//				int tmp = (rank[0][i] > rank[0][j]) ? rank[0][j] : rank[0][i];
//				rank[0][i] = rank[0][j] = tmp;
//			}
//			else if (rank[1][i] < rank[1][j]) {
//				int tmp = rank[0][i];
//				rank[0][i] = rank[0][j];
//				rank[0][j] = tmp;
//			}
//		}
//	}
//
//	for (int i = 0; i < 3; i++)
//		man[i].sub.subname[4] = rank[0][i];
//*/
//
//	print(man);	// 구조체 배열의 이름을 던짐 : 배열명은 선두 요소의 주소
//}


main()
{
	struct sung man[3];
	//int rank[2][3];
	struct sung *pman = (struct sung*)malloc(sizeof(struct sung));
	pman = &man[0];

	for (int i = 0; i < 3; i++) {
		printf("%d번째 사람 이름: ", i);
		//scanf("%s", &man[i].name);
		scanf("%s", pman->name);

		//man[i].sub.subname[3] = 0;	// 총점의 초기화
		//man[i].sub.subname[4] = 1;	// 랭킹 초기화
		pman->sub.subname[3] = 0;
		pman->sub.subname[4] = 1;
		for (int j = 0; j < 3; j++) {
			printf("%s점수: ", su[j]);
			//scanf("%d", &man[i].sub.subname[j]);
			scanf("%d", &pman->sub.subname[j]);
			//man[i].sub.subname[3] += man[i].sub.subname[j];	// 총점
			pman->sub.subname[3] += pman->sub.subname[j];	// 총점
		}
		
		/*printf("국어점수 : ");
		scanf("%d", &man[i].sub.subname[0]);
		printf("영어점수 : ");
		scanf("%d", &man[i].sub.subname[1]);
		printf("수학점수 : ");
		scanf("%d", &man[i].sub.subname[2]);

		man[i].sub.subname[3] = (man[i].sub.subname[0] + man[i].sub.subname[1] + man[i].sub.subname[2]);
		*/
		pman->avg = pman->sub.subname[3] / (float)3;
		/*
				rank[0][i] = i+1;
				rank[1][i] = man[i].sub.subname[3];*/
		pman = &man[i + 1];
	}

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (man[i].sub.subname[3] < man[j].sub.subname[3])	// 본인보다 큰 점수를 만날때마다 등수 +1씩
				man[i].sub.subname[4]++;
		}
	}
	/*
	for (int i = 0; i < 2; i++) {
		for (int j = 1; j < 3; j++) {
			if (rank[1][i] == rank[1][j]) {
				int tmp = (rank[0][i] > rank[0][j]) ? rank[0][j] : rank[0][i];
				rank[0][i] = rank[0][j] = tmp;
			}
			else if (rank[1][i] < rank[1][j]) {
				int tmp = rank[0][i];
				rank[0][i] = rank[0][j];
				rank[0][j] = tmp;
			}
		}
	}

	for (int i = 0; i < 3; i++)
		man[i].sub.subname[4] = rank[0][i];
*/

	print(man);	// 구조체 배열의 이름을 던짐 : 배열명은 선두 요소의 주소
}

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
///*
//	if (find->key == data)
//		printf("%d 찾음", data);
//*/
//	if (find == tail)	// 찾는 친구 (find) 가장 우측 기둥까지 가봤다.
//		printf("%d 없음", data);
//	else
//		printf("%d 찾음", data);
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
//	list_moveToFront(7);
//	list_view();
//}
