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

char *su[] = { "����", "����", "����" };


void print(struct sung *p) {
	printf("����\t%s\t%s\t%s\t����\t����\t���\n", su[0], su[1], su[2]);
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
//		printf("%d��° ��� �̸�: ", i);
//		scanf("%s", &man[i].name);
//
//		man[i].sub.subname[3] = 0;	// ������ �ʱ�ȭ
//		man[i].sub.subname[4] = 1;	// ��ŷ �ʱ�ȭ
//		for (int j = 0; j < 3; j++) {
//			printf("%s����: ", su[j]);
//			scanf("%d", &man[i].sub.subname[j]);
//			man[i].sub.subname[3] += man[i].sub.subname[j];	// ����
//		}
//		
//		/*printf("�������� : ");
//		scanf("%d", &man[i].sub.subname[0]);
//		printf("�������� : ");
//		scanf("%d", &man[i].sub.subname[1]);
//		printf("�������� : ");
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
//			if (man[i].sub.subname[3] < man[j].sub.subname[3])	// ���κ��� ū ������ ���������� ��� +1��
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
//	print(man);	// ����ü �迭�� �̸��� ���� : �迭���� ���� ����� �ּ�
//}


main()
{
	struct sung man[3];
	//int rank[2][3];
	struct sung *pman = (struct sung*)malloc(sizeof(struct sung));
	pman = &man[0];

	for (int i = 0; i < 3; i++) {
		printf("%d��° ��� �̸�: ", i);
		//scanf("%s", &man[i].name);
		scanf("%s", pman->name);

		//man[i].sub.subname[3] = 0;	// ������ �ʱ�ȭ
		//man[i].sub.subname[4] = 1;	// ��ŷ �ʱ�ȭ
		pman->sub.subname[3] = 0;
		pman->sub.subname[4] = 1;
		for (int j = 0; j < 3; j++) {
			printf("%s����: ", su[j]);
			//scanf("%d", &man[i].sub.subname[j]);
			scanf("%d", &pman->sub.subname[j]);
			//man[i].sub.subname[3] += man[i].sub.subname[j];	// ����
			pman->sub.subname[3] += pman->sub.subname[j];	// ����
		}
		
		/*printf("�������� : ");
		scanf("%d", &man[i].sub.subname[0]);
		printf("�������� : ");
		scanf("%d", &man[i].sub.subname[1]);
		printf("�������� : ");
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
			if (man[i].sub.subname[3] < man[j].sub.subname[3])	// ���κ��� ū ������ ���������� ��� +1��
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

	print(man);	// ����ü �迭�� �̸��� ���� : �迭���� ���� ����� �ּ�
}

/* 
 �ڷᱸ�� (�ڷḦ ��� ������ ���ΰ�) �� ����
	* ��� �ڷᱸ���� �ݵ�� �ʱ�ȭ �Լ��� �ִ�.
	1. list (������ �ִ� ����)
		1-1. ����: select, bubble, insert, indirect-insert, shell, merge, quick Sort
		1-2. circular list, double linked list
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
//void list_init(void) {	// ������ �α� ���� �ʱ�ȭ
//	head = (List *)malloc(sizeof(List));	// ���� ���
//	tail = (List *)malloc(sizeof(List));	// ���� ���
//
//	head->next = tail;	// ������
//	tail->next = tail;	// ���� ������ �ŵ�
//}
//
//// head �ڿ� ��� �߰�
//void list_add(int data) {
//	List *newNode;
//	newNode = (List *)malloc(sizeof(List));	// �� ���	// �Լ��� ���� �� List�� ��������� heap ������ �ش� ������ ���� ������.
//	newNode->key = data;
//
//	newNode->next = head->next;	// ���� ����� ���� �ִ� �ּҸ� ����
//	head->next = newNode;	// ��������� �� ��带 ����Ų��.
//}
//
//void list_view(void) {
//	List *wk;	// ���� �ȴ� ģ��
//	wk = head->next;	// ù ��° ������ �ּ� (ù ���)
//	while (wk != tail) {
//		printf("%d ", wk->key);
//		wk = wk->next;
//	}
//}
//
//void list_delete(void) {
//	List *kill = head->next;	// ������ ����� �ּҸ� kill����
//	
//	head->next = kill->next;
//	free(kill);
//}
//
//void list_find(int data) {
//	List *find = head->next;
//
//	while (find->key != data && find != tail) {	// �� ã�� ���� �ƴ� ��
//		find = find->next;
//	}
///*
//	if (find->key == data)
//		printf("%d ã��", data);
//*/
//	if (find == tail)	// ã�� ģ�� (find) ���� ���� ��ձ��� ���ô�.
//		printf("%d ����", data);
//	else
//		printf("%d ã��", data);
//}
//
//// move to front
//// ã�� ��带 ���� ������ �ű�
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
//	// ��� �ڷᱸ���� �ݵ�� �ʱ�ȭ �Լ��� �ִ�.
//	list_init();
//
//	// ù ��° ���� �α�
//	list_add(7);
//	list_add(3);
//	list_add(2);
//	list_add(1);
//
//	list_view();	// �Էµ� �����͵��� Ȯ��
//
//	puts("");
//	list_delete();
//	list_view();
//	puts("");
//
//	// ����, ����, ����, ã��
//	list_find(3);	// 3�� ã��		// head -> 2 -> 3 -> tail
//	puts("");
//	list_find(5);	// 5�� �����ϴ�.
//	puts("");
//
//	list_moveToFront(7);
//	list_view();
//}
