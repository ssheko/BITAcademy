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

main()
{
	struct sung man[3];
	int rank[2][3];
	
	for (int i = 0; i < 3; i++) {
		printf("%d번째 사람 이름: ", i);
		scanf("%s", &man[i].name);
		printf("국어점수 : ");
		scanf("%d", &man[i].sub.subname[0]);
		printf("영어점수 : ");
		scanf("%d", &man[i].sub.subname[1]);
		printf("수학점수 : ");
		scanf("%d", &man[i].sub.subname[2]);

		man[i].sub.subname[3] = (man[i].sub.subname[0] + man[i].sub.subname[1] + man[i].sub.subname[2]);
		man[i].avg = man[i].sub.subname[3]/3;

		rank[0][i] = i+1;
		rank[1][i] = man[i].sub.subname[3];
	}
	
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

	printf("성명\t국어\t영어\t수학\t총점\t순위\t평균\n");
	printf("-------------------------------------------------\n");
	for (int i = 0; i < 3; i++) {
		printf("%s\t", man[i].name);
		printf("%d\t", man[i].sub.subname[0]);
		printf("%d\t", man[i].sub.subname[1]);
		printf("%d\t", man[i].sub.subname[2]);
		printf("%d\t", man[i].sub.subname[3]);
		printf("%d\t", man[i].sub.subname[4]);
		printf("%.1f\n", man[i].avg);
	}
}

/* 
 자료구조 (자료를 어떻게 저장할 것인가) 의 종류
	* 모든 자료구조는 반드시 초기화 함수가 있다.
	1. list (순서가 있는 구조)
		1-1. 정렬: select, bubble, insert, indirect-insert, shell, merge, quick Sort
		1-2. circuler list, double linked list
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
//void list_init(void) {
//	head = (List *)malloc(sizeof(List));
//	tail = (List *)malloc(sizeof(List));
//
//	head->next = tail;
//}
//
//main()
//{
//	// 모든 자료구조는 반드시 초기화 함수가 있다.
//	list_init();
//}
