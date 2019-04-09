#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#pragma warning(disable:4996)	// �������� ���� �ʰڴ�.

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
//	if (wk == tail) {
//		printf("����Ʈ�� ������ϴ�.\n");
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
//
//	if (find->key == data)
//		printf("%d ã��", data);
//*/
//	if (find == tail)	// ã�� ģ�� (find) ���� ���� ��ձ��� ���ô�.
//		printf("%d ����", data);
//	else
//		printf("%d ã��", data);
//}
//
//void list_find_del(int fd) {
//	List *wk;	// ���� �ȴ� ģ��
//	List *hold = NULL;
//	wk = head;
//
//	while (wk->next->key != fd && wk->next != tail)	// ã���� �ٴѴ�
//	{
//		wk = wk->next;
//	}	// ã�ų� ������ ���� �� ã���� ��
//	
//	if (wk->next != tail) {
//		hold = wk->next;	// ã�� �༮�� Ȧ��.	// ����ų� ������ �����ų�		
//		wk->next = hold->next;
//		free(hold);
//	}
//}
//
//void list_add_sort(int data) {
//	List *nw;
//	List *prv;	// ������ ����Ű�� ������
//	List *cmp;	// ���� data�� ���ϴ� ���
//	prv = head;
//	cmp = head->next;
//
//	while (cmp->key <= data && cmp != tail)	// ������ �� ū ���� ã�ƾ� �Ѵ�.
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
//	/*
//	list_moveToFront(7);
//	list_view();
//	puts("");
//*/
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
//	list_find_del(1);
//	list_view();
//	puts("");
//
//	list_add_sort(5);
//	list_view(); 
//	puts("");
//
//	// ��� ����Ʈ �����ϴ� �Լ�
//	list_all_del();
//	list_view();
//	puts("");
//}	

/* ���� ���� */
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

/* ������ ���� ���� */
void Selectionsort2(int A[], int n)
{
	int min, minindex;
	int dx, k;
	for (dx = 0; dx < n - 1; dx++) {
		minindex = dx;
		min = A[dx];
		for (k = dx + 1; k < n; k++) {
			// ������ �����ϰ� �ϴ� �� �ӵ� Ʃ���� �� ��� (ü�� ����)
			if (min > A[k]) {	// �ӵ��������� �߿��� ���� �� ����	// ������ �� �ϳ�, ����� �Ÿ� ����ϴ� �� �ϳ�
				min = A[k];
				minindex = k;
			}
		}
		k = A[min];
		A[min] = A[dx];
		A[dx] = k;
	}
}

/* ����ü ���� */
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
//	// main���� �޸� �Ҵ��� �� �ּҰ��� �Ѱ������Ƿ� ���⼭ �� �Ҵ��ϸ� �ȵ�.
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

//#define swap(a, b) do{int t; t=a; a=b; b=t;}while(0)	// �� ���� �ݺ��ǰ�
#define swap(a, b) {int t; t=a; a=b; b=t;}	// �� ���� �ݺ��ǰ�
/* ���� ���� */
//#define swap(a, b) do{int t; t=a; a=b; b=t;}while(0)
//
//int partition(int arr[], int s, int e)
//{
//	int i, j, pivot;
//	i = s;	// big
//	j = e + 1;	// small
//	pivot = arr[i];
//	while (i < j) {
//		//pivot���� ū���� ã�� ����
//		while (i <= e && pivot >= arr[++i]);
//		//pivot ���� �۰ų� ���� ���� ã�� ����
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
////����  �迭�� ���� �Ͻÿ�
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

/* ��Ʈ�� ���� (��������) */
//////���� �̸��� 2���� �迭�� �ְ� ���� ������ �̿��Ͽ� ���� �Ͻÿ�
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
//void isort(char (*a)[7], int n)	// *a[] �ƴ�
//{
//	int i, j; // , t;
// char t[7];
// for (i = 1; i < n; i++)
// {
//  //t = a[i];
//	 strcpy(t, a[i]);
//  j = i;
//  while (j > 0 && strcmp(a[j - 1], t) > 0)	// strcmp(a, b): ������ 0	 a > b => 1		 a < b => -1 ����	(�ҹ��� > �빮��)
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
//	char arr[][7] = { "����", "���ؿ�", "�պ���", "�����", "���α�", "����", "�����", "�ڼ���", "�ڼ���", "�ŵ���", "�̰��", "������", "Ȳ����", "������", "��ȣ��", "���϶�", "�̽¿�", "������", "������", "������" };
//
//	isort(arr, 20);
//	for(int i=0; i<20; i++)
//		printf("%s ", arr[i]);
//}

/* ����, Ŭ���̾�Ʈ call, call back */
//void cold(void) { puts("cold"); }	// Ŭ���̾�Ʈ
//void hot(void) { puts("hot"); }	// Ŭ���̾�Ʈ
//
//void aircon(void(*p) (void))	// �����ڵ�
//{
//	p();	// call back
//}
//
//main()	// Ŭ���̾�Ʈ �ڵ� 
//{
//	aircon(cold);	// call
//	
//	aircon(hot);
//}

/* ���� Ÿ�� ���� */
//void printInt(int *arr, int size);
//void printDbl(double *arr, int size);
//void printstr(double(*arr)[10], int size);
//
//int comp_i(const void* a, const void* b) {	// ���� �ּҸ� �޾ƿ�.
//	return (*(int*)a - *(int*)b);	// *(int*)a -> a�� �ּҷ� �ٲ㼭 �� ���� ���� �޾ƿ�.
//}
//
////���̺귯�� �����ϴ� qsort�� ���� comp_d �Լ� �ϼ�
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
////���̺귯�� �����ϴ� qsort�� ���� comp_s �Լ� �ϼ�
//int comp_s(const void* a, const void* b) {
//	return strcmp((char*)a, (char*)b);
//}
//
//int main(void) {
//	int arri[] = { 3,4,1,5,2,8,9,6,10,7 };
//	double arrd[] = { 3.2, 5.6, 4.3, 8.7, 2.3, 4.5, 2.1, 2.3, 4.6, 4.5 };
//	char arrs[][7] = { "����", "���ؿ�", "�պ���", "�����", "���α�",
//		"����", "�����", "�ڼ���", "�ڼ���", "�ŵ���",
//		"�̰��", "������", "Ȳ����", "������", "��ȣ��",
//		"���϶�", "�̽¿�", "������", "������", "������",
//		"������" };	// �ѱ� �� ���ڴ� char 2byte��
//	qsort(arri, sizeof(arri) / sizeof(arri[0]), sizeof(int), comp_i);
//	//    ���� ���, ����� ����,				1�� ������ ũ��, ���ı���
//	printInt(arri, sizeof(arri) / sizeof(arri[0]));
//
//	qsort(arrd, sizeof(arrd) / sizeof(arrd[0]), sizeof(double), comp_d);
//	printDbl(arrd, sizeof(arrd) / sizeof(arrd[0]));
//
//	//���̺귯�� qsort�� �̿��Ͽ� 2�����迭�� �ִ� ���ڿ��� �����սô�.
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

/* ����ü �迭 ���� */
//���� ����ü�� ���̺귯�� qsort�� ����Ͽ� itemname�� ������������ �����Ͻÿ�
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

/* ����ü ������ �迭 ���� */
//���� ����ü������ �迭�� ���̺귯�� qsort�� ����Ͽ� name�� ������������ �����Ͻÿ�
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

/* qsort ���� ���� ���� */
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
//	//���������� cmp_i�� cmp_s�� ȣ���Ѵ� //����� -1(����), 0, 1(���)�� �����Ѵ�.
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
	���� �� �޸𸮿� ���� �����͸� �����
	���Խ� warning�� �߻����� �ʵ��� �Ͻÿ�

	��) char **a;
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
//	char **a;	// ����������
//	char *b[2];	// char�� ������ 2��¥�� b
//	char c[2][3];	// char�� 3��¥�� �� 2��
//	char *d[2][3] = { "aa","bb","cc","dd","ee","ff" };	// char�� ������ 3��¥���� �� 2��	// �� ���ڿ��� �ּҰ� �迭 �ȿ� �� �ִ� ��.
//	char(*e)[2][3];	// 3���� �迭�� ���� ������	(���ӿ��� ��Ե��� ����)	// �迭�� ���� �̱� ������
//	char(*f[2])[3];	// char�� 3��¥�� �迭�� ����Ű�� �����Ͱ� 2���� f	// �迭 �����͸� ���� �迭
//
//	// b, c, d�� �迭�̹Ƿ� �̸� ��ü�� �ּҸ� �ǹ�.
//	// a: ����������, e: �̱�������
//	char ***ap = &a;
//	char **bp = b;	// ���� ������
//	char (*cp)[3] = c;	//  char�� 3��¥���� ���� ������
//	char *(*dp)[3] = d;	// char�� ������ 3���� ������	// char�� ������ 3��¥���� ����Ű�� ������
//	char (**ep)[2][3] = &e;	// 
//	char(**fp)[3] = f;
//
//	printf("%s ", *dp[1]);
//}

