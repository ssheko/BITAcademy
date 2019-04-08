#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#pragma warning(disable:4996)	// �������� ���� �ʰڴ�.


/*
=====  M E N U  =====
  1. ������Ȳ ���
  2. ������Ȳ ��������
  3. ��ǰ ã��
  4. ����
 =====================
 �޴��� �����Ͻÿ�  :
*/
typedef struct list
{
	char item[16];
	int price;
	int count;
	int total;
	struct list *next;
} List;

List* head, *tail;

int totalItem = 19;
//main()
//{
//	int num;
//	char ch;
//	char name[10];
//
//	FILE *fwp, *frp;	// ������ ����. a.txt �ּҰ����� �ƴ� �ٸ� �ּҰ��� ���� ���� �ִ�.
//	fwp = fopen("a.txt", "w");	// ��½�Ʈ�� fwp
//
//	fprintf(fwp, "%d %c ", 1, 'A');
//
//	fclose(fwp);
//
//	frp = fopen("a.txt", "r");		// �Է½�Ʈ�� frp
//	fscanf(frp, "%d %c", &num, &ch);
//	fclose(frp);
//
//	fwp = fopen("a.txt", "a");	// "a": append ; ������ �������� ���� �߰�.
//	scanf("%s", &name);
//	fprintf(fwp, "%s\n", name);
//	fclose(fwp);
//
//	frp = fopen("a.txt", "r");
//	fscanf(frp, "%d %c", &num, &ch);
//	fscanf(frp, "%s", &name);
//	fclose(frp);
//
//	printf("%s\n", name);
//}

void initList()
{
	head = (List*)malloc(sizeof(List));
	tail = (List*)malloc(sizeof(List));

	head->next = tail;
	tail->next = tail;
}

void find_add_list(char *name, int data) {
	List *traverse = head->next;

	while (traverse != tail && strcmp(traverse->item, name) != 0) {	// ã�� ��尡 tail�� �ƴϰ� item���� name�� ���� ���� ���
		traverse = traverse->next;
	}

	if (traverse == tail)
		return;

	if (!strcmp(traverse->item, name)) {	// name�� ���� item���� ã���� ���
		traverse->count = data;
		traverse->total = data * traverse->price;
	}
}

List* findList(char *name) {
	List *traverse = head->next;

	while (traverse != tail && strcmp(traverse->item, name) != 0) {	// ã�� ��尡 tail�� �ƴϰ� item���� name�� ���� ���� ���
		traverse = traverse->next;
	}

	if (traverse == tail)
		return NULL;

	if (!strcmp(traverse->item, name))	// name�� ���� item���� ã���� ���
		return traverse;

	return NULL;
}

short deleteList(char *name) {
	List *traverse = head->next;
	List *prev = head;

	while (traverse != tail && strcmp(traverse->item, name) != 0) {	// ã�� ��尡 tail�� �ƴϰ� item���� name�� ���� ���� ���
		prev = prev->next;
		traverse = traverse->next;
	}

	if (traverse == tail)
		return 0;

	if (!strcmp(traverse->item, name)) {	// name�� ���� item���� ã���� ���
		prev->next = traverse->next;
		free(traverse);
		totalItem--;
		return 1;
	}

	return 0;

}

void makeList() {	
	List *traverse = head;
	List *newNode;
	char name[16];
	int count;

	FILE *frp;
	frp = fopen("item.txt", "r");
	while (!feof(frp)) {
		newNode = (List*)malloc(sizeof(List));
		fscanf(frp, "%s %d\n", &newNode->item, &newNode->price);
		newNode->next = traverse->next;
		traverse->next = newNode;
		traverse = traverse->next;
	}
	fclose(frp);

	frp = fopen("sales.txt", "r");
	traverse = head;
	while (!feof(frp)) {
		newNode = (List*)malloc(sizeof(List));
		fscanf(frp, "%s %d\n", &name, &count);
		find_add_list(name, count);
	}
	fclose(frp);
}

//============================================
//�Ｚ���� �¶���  ���� ��Ȳ
//============================================
//��ǰ��          �ܰ�    ����       �ݾ�
//--------------------------------------------
void printList() {
	List *traverse = head->next;
	int curr = 0;
	int sum = 0;
	printf("============================================\n");
	printf("\t�Ｚ���� �¶���  ���� ��Ȳ\n");
	printf("============================================\n");
	printf("��ǰ��          �ܰ�    ����       �ݾ�\n");
	printf("--------------------------------------------\n");
	while (traverse != tail) {
		printf("%2d%15s%8d%8d%12d\n", ++curr, traverse->item, traverse->price, traverse->count, traverse->total);
		traverse = traverse->next;
		sum += traverse->total;
	}
	printf("============================================\n");
	printf("�����հ�\t\t\n");
}

//================
//���Ϸγ������� �ϼ�
//================
//================
void writeText()
{
	FILE *fwp;
	List *traverse = head->next;

	fwp = fopen("output.txt", "w");

	while (traverse != tail) {
		fprintf(fwp, "%s %d %d %d\n", traverse->item, traverse->price, traverse->count, traverse->total);
		traverse = traverse->next;
	}

	fclose(fwp);
	printf("================\n");
	printf("���Ϸγ������� �ϼ�\n");
	printf("================\n");
	printf("================\n");
}

//�˻���ǰ �Է� : 
//============================================
//��ǰ��          �ܰ�    ����       �ݾ�
//--------------------------------------------
//DVD    65      12        780
//============================================
void findItem()
{
	List *fd;
	char item[16];
	printf("�˻���ǰ �Է� : ");
	scanf("%s", &item);
	fd = findList(item);

	if (fd == NULL) {
		printf("ã�� ��ǰ�� �����ϴ�.\n");
		return;
	}

	printf("============================================\n");
	printf("��ǰ��          �ܰ�    ����       �ݾ�\n");
	printf("--------------------------------------------\n");
	printf("%15s%8d%8d%12d\n", fd->item, fd->price, fd->count, fd->total);
	printf("============================================\n");

}

void deleteItem()
{
	short retVal = 0;
	char item[16];
	printf("������ ��ǰ �Է� : ");
	scanf("%s", &item);
	retVal = deleteList(item);

	if (retVal) {
		printf("�����߽��ϴ�.\n");
	}
	else {
		printf("������ ��ǰ�� �����ϴ�.\n");
		return;
	}

}

void printArray(List **listArray) {
	printf("============================================\n");
	printf("\t�Ｚ���� �¶���  ���� ��Ȳ\n");
	printf("============================================\n");
	printf("��ǰ��\t\t�ܰ�\t����\t�ݾ�\n");
	printf("--------------------------------------------\n");
	for (int i = 0; i < totalItem; i++) {
		printf("%2d%15s%8d%8d%12d\n", i, listArray[i]->item, listArray[i]->price, listArray[i]->count, listArray[i]->total);
	}
}

void toArray(List **p) {
	List* traverse = head->next;
	int i = 0;

	while (traverse != tail) {
		*p++ = traverse;
		traverse = traverse->next;
	}
}

typedef int(*p_t)(const void*, const void*);

int cmp_node(const void *a, const void *b) {
	return strcmp((*(List**)a)->item, (*(List**)b)->item);
}
int cmp_price(const void *a, const void *b) {
	return ((*(List**)a)->price - (*(List**)b)->price);
}
int cmp_count(const void *a, const void *b) {
	return ((*(List**)a)->count - (*(List**)b)->count);
}
int cmp_total(const void *a, const void *b) {
	return ((*(List**)a)->total-(*(List**)b)->total);
}

void sortArray(List **p) {
	int input;
	printf("������ ������ �������ּ���. 1. ��ǰ�� 2. �ܰ� 3. ���� 4. �ݾ�  ");
	scanf("%d", &input);
	//int(*p_t[4])(const void*, const void*) = { cmp_node, cmp_price, cmp_count, cmp_total };
	p_t pf[] = { cmp_node, cmp_price, cmp_count, cmp_total };
	qsort(p, totalItem, sizeof(p[0]), *(pf +input-1));
}

main()
{
	int key = 0;
	List* listArray[19];
	//List *(*pArray) = listArray;

	initList();
	makeList();
	
	while(1){
		printf("=====  M E N U  =====\n");
		printf("  1. ������Ȳ ���\n");
		printf("  2. ������Ȳ ��������\n");
		printf("  3. ��ǰ ã��\n");
		printf("  4. ��ǰ ����\n");
		printf("  5. ������Ȳ �迭\n");
		printf("  6. ����\n");
		printf("  7. ����\n");
		printf("=====================\n");
		printf(" �޴��� �����Ͻÿ�  :");
		scanf("%d", &key);
		if (key == 7)
			break;
		switch (key) {
		case 1:
			printList();
			break;
		case 2:
			writeText();
			break;
		case 3:
			findItem();
			break;
		case 4:
			deleteItem();
			break;
		case 5:
			toArray(listArray);
			printArray(listArray);
			break;
		case 6:
			toArray(listArray);
			sortArray(listArray);
			printArray(listArray);
			break;
		default:
			break;
		}

		puts("");
	}
}
