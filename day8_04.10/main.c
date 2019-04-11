//#ifndef HEADER
//#define HEADER
//#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>
//#include <string.h>
//#include <windows.h>
//#pragma warning(disable:4996)	// �������� ���� �ʰڴ�.
//
//#endif
//#define STACK_SIZE 10
///*
// �ڷᱸ�� (�ڷḦ ��� ������ ���ΰ�) �� ����
//	* ��� �ڷᱸ���� �ݵ�� �ʱ�ȭ �Լ��� �ִ�.
//	1. list (������ �ִ� ����)
//		1-1. ����: select, bubble, insert, indirect-insert, shell, merge, quick Sort
//		1-2. circular list, double linked list
//		1-3. linux kernel (linked list)
//	2. stack (last input first out : LIFO)
//		2-1. �Լ� �� ���� ���� ���� (�ݹ� �Լ��� ����)
//	3. queue (FIFO) - �������
//	4. tree	(���� ����Ʈ��, binary tree) - linux (Red-black T)
//			- Tree sort
//		4-1. �Ｚ��: �����ʱ�ȭ (hash-Tree�� �籸��)	// hash, tree �� �� ����
//	5. graph
//*/
//
///*
//void(*signal(int signum, void(*handler)(int)))(int);
//  1  3   5              4                       2
//	1. void
//	2. (int)
//	3. *	// ���� �Լ�(1, 2)�� ����Ű�� ������
//	4. (int sn, void(*h)(int))	// �����͸� �����ϴ� �Լ�
//	5. signal
//
//	�������� �ʴ�(1) �Լ�(2)�� ����Ű�� ������(3)�� �����ϴ� �Լ�(4) signal(5)
//
//*/
///* �Լ� ���� */
////void func(int a) {
////	puts("func");
////}
////
////// void�� �����ϴ� �Լ��� ����Ű�� �����͸� �����ϴ� �Լ� signal
////void(* signal() )(int) 	// �Լ��� �����͸� �����ؾ� ��. // char * signal // int * signal ����
////{
////	return func;
////}
////
////main()
////{
////	(signal())(10);
////}
//
///* typedef �Լ� ���� */
////typedef void v;		// void�� ���� v
////typedef v fv(int);	// �Լ�Ÿ�� fv
////typedef fv *pfv;	// fvŸ���� ����Ű�� ������ pfv
////typedef pfv fpfv();	// signal���¿� ���� �Լ� Ÿ��.
////
////void func(int a) {
////	puts("func");
////}
////
////fpfv signal;	//void(*signal())(int); ����� ���� ����
////
////main()
////{
////	(signal())(10);
////}
////
////pfv signal()	// void(*signal())(int)�� ���� ����
////{
////	return func;
////}
//
///*
//	int a[2][3]
//
//*/
////
////typedef int i;	// intŸ���� i��
////typedef i ai[3];	// intŸ���� i�� ai[3]�迭�� ����
////typedef ai aai[2];	// ai[3]�迭�� aai[2]�迭�� ����
////aai a;	// int a[2][3];�� ����.
//
//
///*
//	int (*(*)())();
//*/
////typedef int i;			// int
////typedef i fi();			// int		   ()
////typedef fi *pfi;			// int (*	  )()
////typedef pfi fpfi();		// int (*   ())()
////typedef fpfi *pfpfi;		// int (*(*)())()
////pfpfi p;
//
///* 
//	char *(*(*var)())[10] 
//*/
////typedef char* c;			// char *
////typedef c ac[10];			// char *		   [10]
////typedef ac *pac;			// char *(*       )[10]
////typedef pac fpac();		// char *(*		())[10]
////typedef fpac *pfpac;		// char *(*(*  )())[10]
////pfpac var;				// char *(*(*  )())[10]
//
///* �Լ� ������ �迭 typedef */
////#ifndef HEADER
////#define HEADER
////#include <stdio.h>
////#include <stdlib.h>
////#include <time.h>
////#include <windows.h>  
////#endif
////#define loop(v, lo, hi) for((v)=(lo); (v)<(hi); (v)++)
////
////int sum(int a, int b)  { return a+b; }
////int sub(int a, int b)  { return a-b; }
////int multi(int a, int b){ return a*b; }
////int divv(int a, int b) { return a/b; }
////int mod(int a, int b)  { return a%b; }
////
////// calculator3�� typedef_calculator3�� ������ ������ �ϵ��� FP, FPP�� typedef�� �̿��Ͽ� �ۼ��ϼ���.
////// FP typedef_calculator3(FPP fp, int arr_size) 
////typedef int(*FP)(int, int);   // FP �ۼ�
////typedef int(*FPP[])(int, int);   // FPP �ۼ�	// typedef FP *FPP; �� ����
//////
//////typedef int i;
//////typedef i fi(int, int);
//////typedef fi *pfi;
//////typedef pfi apfi[];  // FPP �ۼ� int(*fpa[])(int, int)
//////apfi FPP;
////
////// calculator3��  �Լ� ������ �迭�� �Ű������� �ް� �Լ� �����͸� ��ȯ�ϴ� �Լ� 
////// typedef_calculator3�� ������ ������ �ǵ��� calculator3�� ��� �κ��� �ۼ��մϴ�.
////// typedef ������
//////  calculator3(fpa, sizeof(fpa)/sizeof(fpa[0]))(10,3) 
////int(* calculator3 (int(*fp[])(int, int),  int arr_size))(int, int) {
////      int low = 0;
////      int high = arr_size-1; 
////      int random_Num = random_Num = rand() % (high + 1 - low) + low;; //���� �߻������� low���� high �������� ��µǴ� �ڵ�
////      return fp[random_Num];
////}
//////
//////myfp_t calculator3 (int(*fpa[])(int, int),  int arr_size) {
//////      int low = 0;
//////      int high = arr_size-1; 
//////      int random_Num = ________; //���� �߻������� low���� high �������� ��µǴ� �ڵ�
//////      return fp[random_Num];
//////}
////
////FP typedef_calculator3(FPP fp, int arr_size) {      
////   return calculator3(fp, arr_size);
////}
////
////// calculator2�� �Լ� ������ �迭�� �Ű����� �޴� �Լ�
//////    calculator2 �Լ��� arr_size �������� �����߻�
//////    ��Ģ������ ���� �ǿ����ڴ� 11,7�� ����
//////    ������ ���� �Լ� ���� �� ���
//////    ����� �Լ� �����͸� ��ȯ�� 
////// calculator2(fpa, optor, sizeof(fpa)/sizeof(fpa[0]));
////int calculator2 (int(*fp[])(int, int), char* optor, int arr_size){
////    int random_Num;
//// int fir=11,sec=7;
////    int low = 0;
////    int high = arr_size-1; 
////    
////    printf("���� �߻� ���� %d ~ %d\n", low, high);
////     
////    //random_Num = rand(low, high); //���� �߻������� low���� high �������� ��µǴ� �ڵ�
////    random_Num = rand() % (high + 1 - low) + low; //���� �߻������� low���� high �������� ��µǴ� �ڵ�
////
////    printf("���� : %d\n", random_Num);
////    printf("�Լ� ���� : %d %c %d = %d\n", fir, optor[random_Num], sec, fp[random_Num](fir, sec) );
////    return random_Num; 
////}   
////
////int typedef_calculator2 (FPP fp, char* optor, int arr_size) {
////    return calculator2(fp, optor, arr_size);
////} 
////  
//////calculator�� �Լ� ������ �迭�� �μ��� �޴� �Լ� 
//////fir��sec������ ��� ��Ģ������ ���� ����Ͻÿ�
////// calculator(fpa, sizeof(fpa) / sizeof(fpa[0]));
////int calculator(int(*fp[])(int, int), int size) {	//int(**fp)(int, int) �� ����
////	int dx;
////	int fir = 11, sec = 7;
////
////	for(int i=0; i< size; i++)
////		printf("%d ", fp[i](fir, sec));
////
////	puts("");
////}
////
////int typedef_calculator(FPP fp, int arr_size) {
////    return calculator(fp, arr_size);
////}
////
////int main(void){
////    int (*fpa[])(int,int) = {sum, sub, multi, divv, mod};  // 1. fpa�� �Լ� ������ �迭 
////	char optor[] = { '+', '-', '*', '/', '%' };
////    int dx;
////
////  
////    srand(time(NULL));  
////    
////    // typedef �� ������� ���� �Լ� ȣ�� 
////    calculator(fpa, sizeof(fpa)/sizeof(fpa[0]));
////    
////    calculator2(fpa, optor, sizeof(fpa)/sizeof(fpa[0]));
////    loop(dx,0,5)
////    {
////        Sleep(300);    
////        printf("random RUN!! : %d\n", calculator3(fpa, sizeof(fpa)/sizeof(fpa[0]))(10,3) );
////    }
////
////    // typedef �� ����� �Լ� ȣ��     
////    typedef_calculator(fpa, sizeof(fpa)/sizeof(fpa[0]));
////   
////    typedef_calculator2(fpa, optor, sizeof(fpa)/sizeof(fpa[0]));
////     loop(dx,0,5) 
////    {
////        Sleep(300);     
////        printf("random RUN!! : %d\n", typedef_calculator3(fpa, sizeof(fpa)/sizeof(fpa[0]))(10,3) );
////    }
////}
//
///* Queue */
////#define	QUEUE_SIZE 5
////// queue�� ������ ��Ҵ� �����͸� ���� �ʰ�, ť�� �� �� �ִ����� ���θ� �˱� ���� ���.
////// ȯ�� ť���� rear�� front�� �̵����� ��, front == rear�� ��찡 ť�� ����ִ��� ť�� �� ���� �̵��ߴ��� �� �� ���� ����.
////int queue[QUEUE_SIZE];	// ���Լ���
////int front, rear;
////short isFull;
////void init_queue(void)
////{
////	front = rear = 0;
////	isFull = 0;
////}
////
////void put(int data)
////{
////	if ((rear+1)%QUEUE_SIZE == front) {	// front -1 �� ������ ����־�� �Ѵ�.
////		printf("Overflow\n");
////		//rear = 0;
////		return;
////	}
////	queue[rear] = data;
////	rear = ++rear % QUEUE_SIZE;
////	//queue[rear++] = data;
////}
////
////int get(void)
////{
////	int save;
////	//if (isFull) {
////	//	puts("queue is full\n");
////	//	return 99;
////	//}
////
////	if (front == rear) {
////		puts("queue empty\n");
////		return -1;
////	}
////	//if (front + 1 == QUEUE_SIZE - 1)
////	//	front = 0;
////
////	save = front;
////	front = ++front % QUEUE_SIZE;
////	return queue[save];
////}
////
////void printQueue(void) {
////	int start = front;
////	int end = rear;
////	while (start != end) {
////		printf("%d ", queue[start]);
////		start = ((start + 1) % QUEUE_SIZE);
////	}
////
////	puts("");
////
////	for (int i = front; i != rear; i = ++i % QUEUE_SIZE) {
////		printf("%d ", queue[i]);
////	}
////	puts("");
////}
////
////main()
////{
////	// ��� �ڷᱸ���� �ʱ�ȭ
////	init_queue();
////
////	put(1);
////	put(2);
////	put(3);
////	put(4);
////	put(5);
////	printf("%d\n", get());
////	printf("%d\n", get());
////	put(4);
////	put(5);
////	printQueue();
////	//printf("%d\n", get());
////	////put(5);
////	////printf("%d %d \n", get(), get());
////	//printf("%d\n", get());
////	//printf("%d\n", get());
////}
//
///* 
//	Tree 
//	�켱���� ť priority Queue (heap) // tree->�迭�� �� ��
//*/
//
//struct _tree {
//	int key;
//	struct _tree *left;
//	struct _tree *right;
//};
//
//struct _tree *head, *tail;
//
///* ����Լ��� ����� Ʈ�� ��ȸ */
//// ���θ�, �θ�, �ڽ�, ����
//// ���� (�� �ܰ� ��)
////
////int get_depth(struct _tree *p, int dep)
////{
////	int l_dep, r_dep;
////	l_dep = r_dep = dep;
////
////	if (p->left != NULL)
////		l_dep = get_depth(p->left, dep + 1);
////	if (p->right != NULL)
////		r_dep = get_depth(p->right, dep + 1);
////	//if (l_dep >= r_dep)
////	//	return l_dep;
////
////	return (l_dep >= r_dep) ? l_dep : r_dep;
////}
////
////void preorder(struct _tree *p) {
////	if (p != NULL)
////	{
////		printf("%d ", p->key);
////		preorder(p->left);
////		preorder(p->right);
////	}
////}
////
////void inorder(struct _tree *p) {	// tree ����	// bst (����Ž��Ʈ��)
////	if (p != NULL)
////	{
////		inorder(p->left);
////		printf("%d ", p->key);
////		inorder(p->right);
////	}
////}
////
////void postorder(struct _tree *p) {
////	if (p != NULL)
////	{
////		postorder(p->left);
////		postorder(p->right);
////		printf("%d ", p->key);
////	}
////}
////
//
//int STACK[STACK_SIZE];
//int top = 0;
//
///*
//	������ ����� ������ȸ
//		1. ��Ʈ�� push
//		2. stack�� ������� ������ pop()�ؼ� key ���
//		3. pop�� �༮�� ������ ���� �ڽ� ������ push �� 2������ �ݺ�
//*/
//void push(int data)
//{
//	if ((top + 1) > STACK_SIZE) {
//		printf("Stack overflow\n");
//		return;
//	}
//
//	STACK[top++];
//}
//
//int pop() {
//	if (top <= 0) {
//		printf("Stack underflow\n");
//		return;
//	}
//
//	return STACK[--top];
//}
//
//// �ϴ� ������
//void preorder(struct _tree *p) {
//	//int 
//	printf("%d ", p->key);
//	if (top != 0) {
//		printf("%d ", pop());
//	}
//
//
//}
//
//
//main()
//{
//	// ����ü ����
//	struct _tree a1 = { 1,NULL, NULL }, 
//		b2 = { 2,NULL, NULL }, 
//		c3 = { 3,NULL, NULL }, 
//		d4 = { 4,NULL, NULL }, 
//		e5 = { 5,NULL, NULL }, 
//		f6 = { 6,NULL, NULL },	
//		g7 = { 7,NULL, NULL },	
//		h8 = { 8,NULL, NULL },	
//		i9 = { 9,NULL, NULL };	
//
//	//c3.left = &a1;
//	//a1.right = &b2;
//	//c3.right = &d4;
//	//d4.right = &e5;
//	a1.left = &b2;
//	b2.right = &c3;
//	c3.left = &d4;
//	a1.right = &e5;
//	e5.left = &f6;
//	f6.left = &g7;
//	f6.right = &h8;
//	h8.left = &i9;
//
//	preorder(&a1);	// ������ȸ: ��Ʈ Ÿ�� ���� ������
//	puts("");
//	inorder(&a1);	// ������ȸ: ���� ��Ʈ ������
//	puts("");
//	postorder(&a1);	// ������ȸ: ���� ������ ��Ʈ
//	puts("");
//	printf("%d\n", get_depth(&a1, 0));	// ��ü Ʈ�� depth
//	printf("%d\n", get_depth(a1.left, 0));	// ���� Ʈ�� depth
//	printf("%d\n", get_depth(a1.right, 0));	// ������ Ʈ�� depth
//
//}
//
///*
//	������ ����� ������ȸ
//		1. ��Ʈ(4���� ������ �ڽ�)�� push
//		2. ���� �ڽ��� ������ ��� push
//		3. �� �̻� ���� ���� �ڽ��� ������ stack���� pop()
//		4. pop�� �༮�� �������� �� 1��ó�� �ݺ�
//*/
//
///*
//	ť�� �̿��� ������ȸ
//		1. ��Ʈ�� queue�� put()
//		2. ť�� ������� ������ ����.
//		3. �� ����� ���� ������ �ڽ� ������ put()
//		4. �� 2������ �ݺ�
//	tree�� ����ü �迭 �����̹Ƿ� queue�� ����ü ������ �迭 ���¿��� �Ѵ�.
//*/
////int QUEUE[5];
////struct _tree *QUEUE[5];	// ����ü ������ �迭
////// �̷� ���·� �����ؾ� ��
////void level(struct _tree *p)
////{
////	put(p);
////	while (!empty_queue())
////	{
////		t = get();
////		printf("%d ", t->key);
////		if (t->left != NULL)
////			put(t->left);
////		if (t->right != NULL)
////			put(t->right);
////	}
////}
