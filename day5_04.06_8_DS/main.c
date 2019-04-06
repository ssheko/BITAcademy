#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#pragma warning(disable:4996)	// �������� ���� �ʰڴ�.

/* ����ü */
//struct car {
//	int engine;
//	int wheel;
//	int body;
//};
//
//main()
//{
//	struct car bm;	// ����ü ����
//	bm.engine = 300;
//	scnaf("%d", &bm.engine);
//
//	struct car *p;	// ����ü ������ ����
//	p = &bm;
//
//	p->body = 500;
//	scanf("%d", p->body);
//}

/* ��ø ����ü */
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
//	struct car bm;	// ����ü ����
//	bm.bn.engine = 300;
//	scnaf("%d", &bm.bn.engine);
//
//	struct car *p;	// ����ü ������ ����
//	p = &bm;
//
//	p->body = 500;
//	scanf("%d", p->body);
//}

/* ����ü ���� */
//struct num {
//	int fir;
//	int sec;
//};
//
//void func1(int a, int b) { printf("%d\n", a + b); }
//void func2(struct num *a) { printf("%d\n",a->fir + a->sec); }	// *a = a[] = a[100]	// ����ü �̱� ������
//void func3(struct num *a) { 
//	printf("%d\n", a[0].fir + a[0].sec + a[1].fir + a[1].sec);
//	printf("%d\n", a->fir + a->sec + (a + 1)->fir + (a + 2)->sec);	// ������ �켱���� (+) < (->) �̹Ƿ� �ݵ�� (a+1)->fir
//	printf("%d\n", (*a).fir + (*a).sec + (*(a+1)).fir + (*(a + 1)).sec);
//}
//
//main()
//{
//	struct num a = { 1, 2 }, b = { 3,4 }, c[2] = { 5, 6,7,8 };
//
//	func1(a.fir, a.sec);	// �Լ� ���ο��� 1 + 2 ���
//	func2(&b); // b�� �ּҸ� ������ 3 + 4 ���
//	func3(c);	// c�� �ּҸ� ������ 5+6+7+8 ���	// �迭�� �̸��� ù ��° ����� �ּҰ� �ȴ�.
//}

/* ����ü ���� */
// ��������, ��������, ��������, ����, ��ŷ(����)�� �ű�� ���
struct subject {
	int subname[5];	// ����, ����, ����, ����, ��ŷ
};

struct sung {
	char name[10];
	float avg; // ���
	struct subject sub;
};

main()
{
	struct sung man[3];
	int rank[2][3];
	
	for (int i = 0; i < 3; i++) {
		printf("%d��° ��� �̸�: ", i);
		scanf("%s", &man[i].name);
		printf("�������� : ");
		scanf("%d", &man[i].sub.subname[0]);
		printf("�������� : ");
		scanf("%d", &man[i].sub.subname[1]);
		printf("�������� : ");
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

	printf("����\t����\t����\t����\t����\t����\t���\n");
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
 �ڷᱸ�� (�ڷḦ ��� ������ ���ΰ�) �� ����
	* ��� �ڷᱸ���� �ݵ�� �ʱ�ȭ �Լ��� �ִ�.
	1. list (������ �ִ� ����)
		1-1. ����: select, bubble, insert, indirect-insert, shell, merge, quick Sort
		1-2. circuler list, double linked list
		1-3. linux kernel (linked list)
	2. stack (last input first out : LIFO)
		2-1. �Լ� �� ���� ���� ���� (�ݹ� �Լ��� ����)
	3. queue (FIFO) - �������
	4. tree	(���� ����Ʈ��, binary tree) - linux (Red-black T)
			- Tree sort
		4-1. �Ｚ��: �����ʱ�ȭ (hash-Tree�� �籸��)	// hash, tree �� �� ����
	5. graph
*/

/* list: �迭, struct -> linked list 
		�迭: insert, delete�� �� ������ ������.
			  �߰��� insert/delete�� ��� �׸�ŭ �� �迭�� shift�ؾ� ��
		linked list: �迭�� ������ �ذ�.
*/


/* structure: ���� �ٸ� Ÿ���� ���� ���� */
//typedef struct _list List;	// ����� ���� Ÿ��	// struct _list ��� List�� ���
//	// ������������ C���� typedef struct _list List�� ���� �ҿ����� ������ �������.
//	// �Ʒ��� ����ü ���Ǹ� ������ List�� ������ ����ü�� ���������.
//struct _list {
//	int key;
//	struct _list	*next;	// �ڱ� ���� ����ü	// �ڱ� �ڽŰ� ���� �޸��� �ּҸ� ����
//	// char* func() {} --> char�� �ּҸ� ��ȯ�ϴ� �Լ�. * = �ּ�
//};
//// �¿� ��� �����
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
//	// ��� �ڷᱸ���� �ݵ�� �ʱ�ȭ �Լ��� �ִ�.
//	list_init();
//}
