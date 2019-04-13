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
//
//int searchKey(char (*arr)[10], char *key, int size) {
//	//int index = 1;
//	int low = 0;
//	//int high = (sizeof(*arr) / sizeof(*arr[0]))-1;
//	int high = size;
//	int mid = (low + high) / 2;
//
//	while (1) {
//		if (strcmp(arr[mid], key) > 0) {	// key�� �� ���� ���
//			high = mid - 1;
//			mid = (low + high) / 2;
//		}
//		else if (strcmp(arr[mid], key) < 0) {	// key�� �� ū ���
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
//	return strcmp((char*)arr, (char*)key); // (strcmp((char*)arr, (char*)key) > 0);	// �۰ų� ���� ��� 1 ����
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
//	// �ݵ�� �迭�� ������ �Ǿ� �־�� bsearch�� �� �� �ִ�.
//	retval = bsearch(keyValue, key, 26, sizeof(key[0]), compare);	// sizeof(key) / sizeof(key[0])
//	printf("%d\n", retval);
//}

/* 
	����Ž��Ʈ��
		�� ��忡 �ϳ��� �����͸� �����ϴ� Ž���� ���� Ʈ��
		��� ��忡 ���Ͽ� �ڽ��� ���� ��Ʈ������ �ڽź��� ���� ����, �����ʿ��� �ڽź��� ū ���� ��ġ�Ѵ�.
		Ž���ؾ� �ϴ� ������ ��������� �߰��Ǿ� Ȯ��� �� �ַ� ���

	����Ž��Ʈ�� ����
		�ڽ��� ���� ����� ����
			���� ��Ʈ��(�ڽź��� ���� ��)���� ���� ū ��
			Ȥ�� ������ ��Ʈ������ ���� ���� ���� swap�� �� �ڱ��ڽ� ����
*/

/* 
	���� ����Ʈ��
		left_subtree = (n - 1)/2				// (��ü ���� - ��Ʈ) /2
		right_subtree = n - 1 - left_subtree;	// ��ü ���� - ��Ʈ - ���� ��Ʈ�� ����
*/

/* 
	�� �ڷᱸ�� 
		1. ���� ����Ʈ�� (��� ��� �� �� �ְ�, ���� �ϴ��� ����ִ� ���)
		2. Max Heap�� ��� �θ� ����� ���� �ڽ� ����� ������ ũ�ų� ����.
			(���� Max heap�� ��� Root�� ���� ���� ũ��.) Min heap�� �ݴ�
		3. ���� ����Ʈ���̹Ƿ� ���������� ���ʷ� �迭�� �־� ������ ���� ǥ���� �� �ִ�.
			�迭�� �ְ� ���� ������ ������ ������Ų��.
				1. �߰��� �� �ڸ��� ����. (���� ����Ʈ��)
				2. i�� ����� ���� �ڽ� ���� i*2�� ���
					������ �ڽ� ���� i*2+1�� ���
				3. i�� ����� �θ� ���� [i/2]�� ��� (�Ҽ����� ����)
		4. Insert: up-heap �˰��� (��带 �������� �ְ� ���� ���ϸ鼭 ���� �ø�)	// ���� �ְ� �θ�� ���ؼ� �θ𺸴� Ŭ ��� �θ�� swap
		   Delete: down-heap �˰��� (������ ��带 ������ ���� �ٲ� �� ��)
*/

/*
	Hash
		���Ұ� ����� �ڸ��� ������ "��"�� ���� �����Ǵ� �ڷᱸ��
		��� ��� �ð��� ����, ����, �˻�
		�ſ� ���� ������ ���ϴ� ���뿡 ����
		�� �� ������ ���� ��Ʈ����. �� ������ ������
		1. ����Ž���
			�浹�� �Ͼ ��� ���� ��Ŷ�� �ִ� ���
		2. �����ؽ���(����Ž���� ����)
			Ű���� �������� �̸� �̿��� �ٸ� ��Ŷ�� ����
		3. ����� (chaining)
			���� �ּҷ� �ؽ̵Ǵ� ���Ҹ� ��� �ϳ��� ���� ����Ʈ�� ���� (Hash tree)
			�߰����� ���� ����Ʈ �ʿ�			
*/


/* list_entry */
//#define list_entry(ptr, type, member) \
// ((type *)((char *)(ptr)-(unsigned long)(&((type *)0)->member)))
////list_entry�� �̿��Ͽ� ���� ����ü�� �����(a,b,c,d,x,y,z)�� �̿��� 
////����ü�� ù �ּҸ� ����ϴ� main�Լ��� �ϼ��Ͻÿ�
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


/* ������ list.h �̿� ���� */
//#define __KERNEL__
//#include "list.h"
//
////-������ ���� ��µǰ� �Ͻÿ�
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
////����Ϸ��� �ƹ� Ű�� �����ʽÿ� . . .
////
////
////
////list.h(������ ���Ϸ� ���� ������ Ŀ�� ���)������ include �� �� �ֵ��� �����Ͻÿ�
////inline�̳� prefetch�� �������� �ʴ� ����̴�.
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
//	//head�� �޸� �Ҵ��Ų�� 
//	head = malloc(Node_SIZE);
//
//	//head ����ü ����� list������ ����� list�� ����Ű�� �ʱ�ȭ��Ű��
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
//	list_add();//list_add �Լ��� �̿��Ͽ� head�ڿ� a�� ����
//
//	print_all();
//	list_add();//list_add �Լ��� �̿��Ͽ� head�ڿ� b�� ����
//	print_all();
//	list_del(); // list_del�Լ��� �̿��Ͽ� head�ڿ� �� ����
//
//
//		print_all();
//	free(a);
//	free(b);
//	free(head);
//}
//

/* 
	�׷��� 
		1. ���� ��� : ������ �迭�� ����
		2. ���� ����Ʈ: ���� ����ŭ�� ���� ����Ʈ�� ����
	�׷��� Ž��
		1. ���̿켱: ���� ���
		2. �ʺ�켱: ť ���

	���� �׷��� + ���� �׷��� = ��Ʈ��ũ

	* ���̿켱Ž�� (���ñ��)
		�ߺ��� �߻��� ���ۿ� ���� ������ �ߺ� Ȯ�ο� üũ �迭�� �� �־�� �Ѵ�.
			1. A�� ���ÿ� �ְ�, üũ�迭��[A]�� 1
			2. A�� ���ϰ� A�� ����� ��带 ���ÿ� ��� �ְ�, ���� üũ 1
			3. 2������ �ٽ� �ݺ� (üũ�Ǿ� ���� ��� ����)
		�͸��� Ž��. �׷����� �ߺ� ���� Ž���ϰڴ�.
		���� �İ� ���� ����
	* �ʺ�켱Ž�� (ť ���)
		������ Ⱦ������ ��
			1. �������� �ְ� üũ�迭�� 1
			2. ť�� get�ϰ� get�� ������ ����� ���� put, üũ 1
			3. 2������ �ٽ� �ݺ�. (üũ�Ǿ� ���� ��� ����)
	* ���峪�� (Spanning tree)
		��� ������ �湮 ��� ������ �湮ġ �ʴ´�. (n, n-1)
		- ��� ���� ��ȸ�� �ּҺ�� (�װ�, ����ȸ��, �����ٸ�)
			ex) �켱���� Ž��, Kruskal, Prim �˰���

		- �� ������ ����� ����ġ ���� ���� �۰�
			ex) dijkstra �˰���

		Kruskal �˰���
			���� ũ���� ����ġ�� �������� ������ �����, ���� ������ �߰�
			���ʷ� Ȯ���ϸ鼭 cycle�� ������ �ʴ� ������ �߰��ϴ� ���

		Prim �˰���
			������ Ȯ���ϸ鼭 �������� �������ִµ�
			���� �� ��ó ���� �� ���� ����ġ�� ���� ������ ������ ����.

*/
