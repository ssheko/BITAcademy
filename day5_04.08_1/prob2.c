#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#pragma warning(disable:4996)	// 새문법을 쓰지 않겠다.


/*
=====  M E N U  =====
  1. 매출현황 출력
  2. 매출현황 내보내기
  3. 상품 찾기
  4. 종료
 =====================
 메뉴를 선택하시오  :
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
//	FILE *fwp, *frp;	// 포인터 변수. a.txt 주소값만이 아닌 다른 주소값을 가질 수도 있다.
//	fwp = fopen("a.txt", "w");	// 출력스트림 fwp
//
//	fprintf(fwp, "%d %c ", 1, 'A');
//
//	fclose(fwp);
//
//	frp = fopen("a.txt", "r");		// 입력스트림 frp
//	fscanf(frp, "%d %c", &num, &ch);
//	fclose(frp);
//
//	fwp = fopen("a.txt", "a");	// "a": append ; 파일의 마지막에 문자 추가.
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

	while (traverse != tail && strcmp(traverse->item, name) != 0) {	// 찾는 노드가 tail이 아니고 item값이 name과 같지 않을 경우
		traverse = traverse->next;
	}

	if (traverse == tail)
		return;

	if (!strcmp(traverse->item, name)) {	// name과 같은 item값을 찾았을 경우
		traverse->count = data;
		traverse->total = data * traverse->price;
	}
}

List* findList(char *name) {
	List *traverse = head->next;

	while (traverse != tail && strcmp(traverse->item, name) != 0) {	// 찾는 노드가 tail이 아니고 item값이 name과 같지 않을 경우
		traverse = traverse->next;
	}

	if (traverse == tail)
		return NULL;

	if (!strcmp(traverse->item, name))	// name과 같은 item값을 찾았을 경우
		return traverse;

	return NULL;
}

short deleteList(char *name) {
	List *traverse = head->next;
	List *prev = head;

	while (traverse != tail && strcmp(traverse->item, name) != 0) {	// 찾는 노드가 tail이 아니고 item값이 name과 같지 않을 경우
		prev = prev->next;
		traverse = traverse->next;
	}

	if (traverse == tail)
		return 0;

	if (!strcmp(traverse->item, name)) {	// name과 같은 item값을 찾았을 경우
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
//삼성전자 온라인  매출 현황
//============================================
//상품명          단가    개수       금액
//--------------------------------------------
void printList() {
	List *traverse = head->next;
	int curr = 0;
	int sum = 0;
	printf("============================================\n");
	printf("\t삼성전자 온라인  매출 현황\n");
	printf("============================================\n");
	printf("상품명          단가    개수       금액\n");
	printf("--------------------------------------------\n");
	while (traverse != tail) {
		printf("%2d%15s%8d%8d%12d\n", ++curr, traverse->item, traverse->price, traverse->count, traverse->total);
		traverse = traverse->next;
		sum += traverse->total;
	}
	printf("============================================\n");
	printf("매출합계\t\t\n");
}

//================
//파일로내보내기 완성
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
	printf("파일로내보내기 완성\n");
	printf("================\n");
	printf("================\n");
}

//검색상품 입력 : 
//============================================
//상품명          단가    개수       금액
//--------------------------------------------
//DVD    65      12        780
//============================================
void findItem()
{
	List *fd;
	char item[16];
	printf("검색상품 입력 : ");
	scanf("%s", &item);
	fd = findList(item);

	if (fd == NULL) {
		printf("찾는 상품이 없습니다.\n");
		return;
	}

	printf("============================================\n");
	printf("상품명          단가    개수       금액\n");
	printf("--------------------------------------------\n");
	printf("%15s%8d%8d%12d\n", fd->item, fd->price, fd->count, fd->total);
	printf("============================================\n");

}

void deleteItem()
{
	short retVal = 0;
	char item[16];
	printf("삭제할 상품 입력 : ");
	scanf("%s", &item);
	retVal = deleteList(item);

	if (retVal) {
		printf("삭제했습니다.\n");
	}
	else {
		printf("삭제할 상품이 없습니다.\n");
		return;
	}

}

void printArray(List **listArray) {
	printf("============================================\n");
	printf("\t삼성전자 온라인  매출 현황\n");
	printf("============================================\n");
	printf("상품명\t\t단가\t개수\t금액\n");
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
	printf("정렬할 기준을 선택해주세요. 1. 상품명 2. 단가 3. 개수 4. 금액  ");
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
		printf("  1. 매출현황 출력\n");
		printf("  2. 매출현황 내보내기\n");
		printf("  3. 상품 찾기\n");
		printf("  4. 상품 삭제\n");
		printf("  5. 매출현황 배열\n");
		printf("  6. 정렬\n");
		printf("  7. 종료\n");
		printf("=====================\n");
		printf(" 메뉴를 선택하시오  :");
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
