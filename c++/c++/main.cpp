#include <iostream>
#include <cstdio>
#pragma warning (disable:4996)

using namespace std;	// using 지시문
using std::cout;		// using 선언

/* Swap */
//// pointer
//void swap1(int *pa, int *pb)
//{
//	int tmp;
//	tmp = *pa;
//	*pa = *pb;
//	*pb = tmp;
//}
//
//// reference 
//void swap2(int &rpa, int &rpb)
//{
//	int tmp;
//	tmp = rpa;
//	rpa = rpb;
//	rpb = tmp;
//}
//
//// reference pointer
//void swap3(int *(&rpa), int *(&rpb)) {
//	int *tmp;
//	tmp = rpa;
//	rpa = rpb;
//	rpb = tmp;
//}
//
//int main()
//{
//	int a = 10, b = 5;
//
//	int *pa = &a;
//	int *pb = &b;
//
//	swap1(&a, &b);
//	cout << a << ' ' << b << endl;
//
//	swap2(a, b);
//	cout << a << ' ' << b << endl;
//
//	swap3(pa, pb);
//	cout << *pa << ' ' << *pb << endl;
//
//	return 0;
//}

/* 구조체 포인터 Swap */
//struct Number {
//	int fir;
//	int sec;
//};
//
//Number& NumberAdd(Number &a, Number &b)
//{
//	Number *rp = (Number*)malloc(sizeof(Number));
//	rp->fir = a.fir + b.fir;
//	rp->sec = a.sec + b.sec;
//	return *rp;
//}
//
//int main()
//{
//	Number *pa = (Number*)malloc(sizeof(Number));
//	Number *pb = (Number*)malloc(sizeof(Number));
//	pa->fir = 1;
//	pa->sec = 2;
//	pb->fir = 10;
//	pb->sec = 20;
//
//	//NumberAdd(*pa, *pb);
//	Number &rpa = NumberAdd(*pa, *pb);
//	cout << rpa.fir << ' ' << rpa.sec << endl;
//	// rpa로 출력 후 rpa가 가리키는 메모리를 삭제하시오.
//	
//	free(pa);
//	free(pb);
//	free(&rpa);
//}

/* const */
//int main()
//{
//	const int a = 10;
//	const int *p = &a;
//	const int *(&rp) = p;
//	// p를 이용해서 10 출력
//	cout << *p << endl;
//	// rp를 이용해서 10 출력
//	cout << *rp << endl;
//}

/* 참조변수, 포인터 */
//void func1(int *(&ppa))
//{
//	*ppa = 10;
//}
//
//void func2(int *ppa)
//{
//	*ppa = 20;
//}
//
//int main()
//{
//	int a = 10;
//	int *pa = &a;
//
//	func1(pa);
//	cout << *pa << endl;
//	func2(pa);
//	cout << *pa << endl;
//}

/* 레퍼런스 */
//int& func1(int &ra)	// &ra = a
//{
//	ra += 10;
//	return ra;
//}
//
//int func2(int &ra)	// &ra = a
//{
//	ra += 10;
//	return ra;
//}
//
//int main()
//{
//	int a = 10;
//	int &rb = func1(a);	// &rb = ra		// 레퍼런스를 레퍼런스로
//	rb += 10;
//	cout << a << endl;
//
//	a = 10;
//	int rc = func1(a);	// 레퍼런스를 일반변수로 (함수쪽 값이 복사)
//	cout << a << endl;
//
//	a = 10;
//	int rd = func2(a);	// 값을 일반변수로 받음 (함수쪽 값이 복사)
//	cout << rd << endl;
//	
//	a = 10;
//	const int& re = func2(a);	// 값을 레퍼런스로 받음 (상수는 error)	: const를 붙이면 해결
//	cout << re << endl;
//}

/* 디폴트 생성자, 유저 정의 생성자 */
//class Number
//{
//private:		// 생략 가능
//	int fst;
//public:
//	int snd;
//
//	Number() {}	// 디폴트 생성자
//	Number(int rfst) {	// 유저 정의 생성자	: 생성자 오버로딩
//		fst = rfst;
//		snd = 20;
//	}
//
//	void view(void)
//	{
//		cout << fst << endl;
//	}
//};
//
//int main()
//{
//	Number oba;	// 유저 정의 생성자를 만들게 되면 디폴트 생성자가 없어서 오류 발생
//	Number obb(10);
//
//	obb.view();
//	cout << obb.snd << endl;
//	//cout << obb.fst << endl;	// error
//}

/* 생성자 */
//struct shallow {
//	int key;
//	char *p;
//};
//
//struct deep {
//	int key;
//	char p[10];
//};
//
//int main()
//{
//	shallow a = { 10, "AAA" }, b;
//	deep c = { 20, "CCC" }, d;
//
//	b = a;	// 구조체 대표적 특징: 대입연산자 가능
//
//	d = c;
//}

/* 절차를 객체형태로 구현하시오 */
///* 원본 */
////Number DisplayAndRead(const char* msg) {
////	Number temp;
////	printf("  %s ", msg);
////	scanf("%d %d", &temp.fir, &temp.sec);
////	return temp;
////}
////void printData(const char* msg, Number rev) {
////	printf("  %s %d + %d\n", msg, rev.fir, rev.sec);
////}
////Number addition(Number a, Number b) {
////	Number temp;
////	temp.fir = a.fir + b.fir;
////	temp.sec = a.sec + b.sec;
////	return temp;
////}
////int main()
////{
////	Number a, b, c;
////	a = DisplayAndRead("A =", a);
////	b = DisplayAndRead("B =");
////	c = addition(a, b);
////	printData("  A  = ", a);
////	printData("  B  = ", b);
////	printData(" A+B = ", c);
////	return 0;
////}
//
//
///* 수정 */
//struct  Number
//{
//	int fir;
//	int sec;
//};
//
//class NumberClass {
//private:
//public:
//	//NumberClass();
//	//NumberClass(Number num);
//	Number num;
//	void DisplayAndRead(const char* msg)
//	{
//		int inputFir, inputSec;
//		printf("  %s ", msg);
//		scanf("%d %d", &inputFir, &inputSec);
//		num.fir = inputFir;
//		num.sec = inputSec;
//	}
//	void printData(const char* msg)
//	{
//		printf("  %s %d + %d\n", msg, num.fir, num.sec);
//	}
//	void addition(Number a, Number b) {
//		num.fir = a.fir + b.fir;
//		num.sec = a.sec + b.sec;
//		//printf("%d %d", num.fir, num.sec);
//	}
//};
//int main()
//{
//	NumberClass a, b, c;
//	a.DisplayAndRead("A =");
//	b.DisplayAndRead("B =");
//	c.addition(a.num, b.num);
//	a.printData("  A  = ");
//	b.printData("  B  = ");
//	c.printData(" A+B = ");
//	return 0;
//}

/* 캡슐화 */
///* 원본 */
////main함수에서 밥,국,김을 따로따로 불편하게 먹고 있습니다.
////Wrap 클래스를 만들어 
////main함수에서 brunch객체를 사용하여 wrap 객체에 담긴
////밥,국, 김을 한번에 먹으시오.
//class bob {
//public:
//	void eat()
//	{
//		cout << "밥먹다" << endl;
//	}
//};
//
//class kok {
//public:
//	void eat()
//	{
//		cout << "국먹다" << endl;
//	}
//};
//
//class kim {
//public:
//	void eat()
//	{
//		cout << "김먹다" << endl;
//	}
//};
//
//class Wrap {
//	
//};
//
//class Brunch {
//public:
//	void eattherice(bob &rb) { rb.eat(); }
//	void eatthesoup(kok &rok) { rok.eat(); }
//	void eatthekim(kim &rk) { rk.eat(); }
//};
//int main()
//{
//	Brunch bb;
//	bob ob;
//	kok ok;
//	kim im;
//
//	bb.eattherice(ob);
//	bb.eatthesoup(ok);
//	bb.eatthekim(im);
//
//}

///* 수정 */
////main함수에서 밥,국,김을 따로따로 불편하게 먹고 있습니다.
////Wrap 클래스를 만들어 
////main함수에서 brunch객체를 사용하여 wrap 객체에 담긴
////밥,국, 김을 한번에 먹으시오.
//class bob {
//public:
//	void eat()
//	{
//		cout << "밥먹다" << endl;
//	}
//};
//
//class kok {
//public:
//	void eat()
//	{
//		cout << "국먹다" << endl;
//	}
//};
//
//class kim {
//public:
//	void eat()
//	{
//		cout << "김먹다" << endl;
//	}
//};
//
//class Wrap {
////public:
//	bob w_bob;
//	kok w_kok;
//	kim w_kim;
//public:
//	void eat()
//	{
//		w_bob.eat();
//		w_kok.eat();
//		w_kim.eat();
//	}
//};
//
//class Brunch {
//public:
//	void eattherice(bob &rb) { rb.eat(); }
//	void eatthesoup(kok &rok) { rok.eat(); }
//	void eatthekim(kim &rk) { rk.eat(); }
//	void eatAll(Wrap &rw) { rw.eat(); }
//};
//int main()
//{
//	bob ob;
//	kok ok;
//	kim im;
//
//	Wrap wrap;
//
//	Brunch bb;
//	/*
//	bb.eattherice(ob);
//	bb.eatthesoup(ok);
//	bb.eatthekim(im);
//*/
//	bb.eatAll(wrap);
//
//}
//

