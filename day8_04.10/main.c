//#ifndef HEADER
//#define HEADER
//#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>
//#include <string.h>
//#include <windows.h>
//#pragma warning(disable:4996)	// 새문법을 쓰지 않겠다.
//
//#endif
//#define STACK_SIZE 10
///*
// 자료구조 (자료를 어떻게 저장할 것인가) 의 종류
//	* 모든 자료구조는 반드시 초기화 함수가 있다.
//	1. list (순서가 있는 구조)
//		1-1. 정렬: select, bubble, insert, indirect-insert, shell, merge, quick Sort
//		1-2. circular list, double linked list
//		1-3. linux kernel (linked list)
//	2. stack (last input first out : LIFO)
//		2-1. 함수 콜 스택 내부 구조 (콜백 함수의 형태)
//	3. queue (FIFO) - 기수정렬
//	4. tree	(보통 이진트리, binary tree) - linux (Red-black T)
//			- Tree sort
//		4-1. 삼성폰: 공장초기화 (hash-Tree의 재구성)	// hash, tree 둘 다 빠름
//	5. graph
//*/
//
///*
//void(*signal(int signum, void(*handler)(int)))(int);
//  1  3   5              4                       2
//	1. void
//	2. (int)
//	3. *	// 저런 함수(1, 2)를 가리키는 포인터
//	4. (int sn, void(*h)(int))	// 포인터를 리턴하는 함수
//	5. signal
//
//	리턴하지 않는(1) 함수(2)를 가리키는 포인터(3)를 리턴하는 함수(4) signal(5)
//
//*/
///* 함수 선언 */
////void func(int a) {
////	puts("func");
////}
////
////// void를 리턴하는 함수를 가리키는 포인터를 리턴하는 함수 signal
////void(* signal() )(int) 	// 함수의 포인터를 리턴해야 함. // char * signal // int * signal 형식
////{
////	return func;
////}
////
////main()
////{
////	(signal())(10);
////}
//
///* typedef 함수 선언 */
////typedef void v;		// void와 같은 v
////typedef v fv(int);	// 함수타입 fv
////typedef fv *pfv;	// fv타입을 가리키는 포인터 pfv
////typedef pfv fpfv();	// signal형태와 같은 함수 타입.
////
////void func(int a) {
////	puts("func");
////}
////
////fpfv signal;	//void(*signal())(int); 선언과 같은 형태
////
////main()
////{
////	(signal())(10);
////}
////
////pfv signal()	// void(*signal())(int)와 같은 형태
////{
////	return func;
////}
//
///*
//	int a[2][3]
//
//*/
////
////typedef int i;	// int타입을 i로
////typedef i ai[3];	// int타입인 i를 ai[3]배열로 만듬
////typedef ai aai[2];	// ai[3]배열을 aai[2]배열로 만듬
////aai a;	// int a[2][3];와 같다.
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
///* 함수 포인터 배열 typedef */
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
////// calculator3과 typedef_calculator3이 동일한 동작을 하도록 FP, FPP를 typedef를 이용하여 작성하세요.
////// FP typedef_calculator3(FPP fp, int arr_size) 
////typedef int(*FP)(int, int);   // FP 작성
////typedef int(*FPP[])(int, int);   // FPP 작성	// typedef FP *FPP; 와 동일
//////
//////typedef int i;
//////typedef i fi(int, int);
//////typedef fi *pfi;
//////typedef pfi apfi[];  // FPP 작성 int(*fpa[])(int, int)
//////apfi FPP;
////
////// calculator3은  함수 포인터 배열을 매개변수로 받고 함수 포인터를 반환하는 함수 
////// typedef_calculator3과 동일한 선언이 되도록 calculator3의 헤더 부분을 작성합니다.
////// typedef 사용금지
//////  calculator3(fpa, sizeof(fpa)/sizeof(fpa[0]))(10,3) 
////int(* calculator3 (int(*fp[])(int, int),  int arr_size))(int, int) {
////      int low = 0;
////      int high = arr_size-1; 
////      int random_Num = random_Num = rand() % (high + 1 - low) + low;; //난수 발생범위를 low에서 high 범위내에 출력되는 코드
////      return fp[random_Num];
////}
//////
//////myfp_t calculator3 (int(*fpa[])(int, int),  int arr_size) {
//////      int low = 0;
//////      int high = arr_size-1; 
//////      int random_Num = ________; //난수 발생범위를 low에서 high 범위내에 출력되는 코드
//////      return fp[random_Num];
//////}
////
////FP typedef_calculator3(FPP fp, int arr_size) {      
////   return calculator3(fp, arr_size);
////}
////
////// calculator2는 함수 포인터 배열을 매개변수 받는 함수
//////    calculator2 함수는 arr_size 범위내로 난수발샘
//////    사칙연산을 위한 피연산자는 11,7로 고정
//////    난수에 따라 함수 수행 후 출력
//////    수행된 함수 포인터를 반환함 
////// calculator2(fpa, optor, sizeof(fpa)/sizeof(fpa[0]));
////int calculator2 (int(*fp[])(int, int), char* optor, int arr_size){
////    int random_Num;
//// int fir=11,sec=7;
////    int low = 0;
////    int high = arr_size-1; 
////    
////    printf("난수 발생 범위 %d ~ %d\n", low, high);
////     
////    //random_Num = rand(low, high); //난수 발생범위를 low에서 high 범위내에 출력되는 코드
////    random_Num = rand() % (high + 1 - low) + low; //난수 발생범위를 low에서 high 범위내에 출력되는 코드
////
////    printf("난수 : %d\n", random_Num);
////    printf("함수 실행 : %d %c %d = %d\n", fir, optor[random_Num], sec, fp[random_Num](fir, sec) );
////    return random_Num; 
////}   
////
////int typedef_calculator2 (FPP fp, char* optor, int arr_size) {
////    return calculator2(fp, optor, arr_size);
////} 
////  
//////calculator는 함수 포인터 배열을 인수로 받는 함수 
//////fir와sec값으로 모든 사칙연산을 구현 출력하시오
////// calculator(fpa, sizeof(fpa) / sizeof(fpa[0]));
////int calculator(int(*fp[])(int, int), int size) {	//int(**fp)(int, int) 도 가능
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
////    int (*fpa[])(int,int) = {sum, sub, multi, divv, mod};  // 1. fpa는 함수 포인터 배열 
////	char optor[] = { '+', '-', '*', '/', '%' };
////    int dx;
////
////  
////    srand(time(NULL));  
////    
////    // typedef 를 사용하지 않은 함수 호출 
////    calculator(fpa, sizeof(fpa)/sizeof(fpa[0]));
////    
////    calculator2(fpa, optor, sizeof(fpa)/sizeof(fpa[0]));
////    loop(dx,0,5)
////    {
////        Sleep(300);    
////        printf("random RUN!! : %d\n", calculator3(fpa, sizeof(fpa)/sizeof(fpa[0]))(10,3) );
////    }
////
////    // typedef 를 사용한 함수 호출     
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
////// queue의 마지막 요소는 데이터를 넣지 않고, 큐가 꽉 차 있는지의 여부를 알기 위해 사용.
////// 환형 큐에서 rear가 front로 이동했을 때, front == rear인 경우가 큐가 비어있는지 큐가 꽉 차서 이동했는지 알 수 없기 때문.
////int queue[QUEUE_SIZE];	// 선입선출
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
////	if ((rear+1)%QUEUE_SIZE == front) {	// front -1 은 무조건 비어있어야 한다.
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
////	// 모든 자료구조는 초기화
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
//	우선순위 큐 priority Queue (heap) // tree->배열로 된 것
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
///* 재귀함수를 사용한 트리 순회 */
//// 조부모, 부모, 자식, 형제
//// 레벨 (한 단계 밑)
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
////void inorder(struct _tree *p) {	// tree 정렬	// bst (이진탐색트리)
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
//	스택을 사용한 전위순회
//		1. 루트를 push
//		2. stack이 비어있지 않으면 pop()해서 key 출력
//		3. pop한 녀석의 오른쪽 왼쪽 자식 순으로 push 후 2번으로 반복
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
//// 하다 말았음
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
//	// 구조체 변수
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
//	preorder(&a1);	// 전위순회: 루트 타고 왼쪽 오른쪽
//	puts("");
//	inorder(&a1);	// 중위순회: 왼쪽 루트 오른쪽
//	puts("");
//	postorder(&a1);	// 후위순회: 왼쪽 오른쪽 루트
//	puts("");
//	printf("%d\n", get_depth(&a1, 0));	// 전체 트리 depth
//	printf("%d\n", get_depth(a1.left, 0));	// 왼쪽 트리 depth
//	printf("%d\n", get_depth(a1.right, 0));	// 오른쪽 트리 depth
//
//}
//
///*
//	스택을 사용한 중위순회
//		1. 루트(4번의 오른쪽 자식)를 push
//		2. 왼쪽 자식이 있으면 계속 push
//		3. 더 이상 넣을 왼쪽 자식이 없으면 stack에서 pop()
//		4. pop한 녀석의 오른쪽을 위 1번처럼 반복
//*/
//
///*
//	큐를 이용한 층별순회
//		1. 루트를 queue에 put()
//		2. 큐가 비어있지 않으면 뺀다.
//		3. 뺀 노드의 왼쪽 오른쪽 자식 순으로 put()
//		4. 위 2번으로 반복
//	tree가 구조체 배열 형태이므로 queue는 구조체 포인터 배열 형태여야 한다.
//*/
////int QUEUE[5];
////struct _tree *QUEUE[5];	// 구조체 포인터 배열
////// 이런 형태로 구현해야 함
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
