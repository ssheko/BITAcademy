#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <string>
#pragma warning (disable:4996)

using namespace std;	// using 지시문
using std::cout;		// using 선언

						
/* 함수 호출 연산자 오버로딩(() 연산자) */
//struct FuncObject
//{
//public:
//	void operator()(int arg) const
//	{
//		cout << arg << endl;
//	}
//};
//
//void Print1(int arg) {
//	cout << arg << endl;
//}
//
//int main()
//{
//	void(*Print2)(int) = Print1;
//	FuncObject Print3;
//
//	Print1(10);
//	Print2(20);
//	Print3(40);
//	FuncObject().operator()(10);
//}

/* 상수 객체를 반환하는 [] 연산자 오버로딩 */
//class Array
//{
//	int *arr;
//	int size;
//	int capacity;
//
//	// 복사 함수 생략(복사 생성자, 복사 대입 연산자)
//public:
//	Array(int cap = 100) :arr(0), size(0), capacity(cap)
//	{
//		arr = new int[capacity];
//	}
//
//	~Array()
//	{
//		delete[] arr;
//	}
//
//	void Add(int data) {
//		if (size < capacity)
//			arr[size++] = data;
//	}
//
//	int Size() const
//	{
//		return size;
//	}
//
//	int operator[](int idx) const
//	{
//		return arr[idx];
//	}
//
//	int& operator[](int idx)
//	{
//		return arr[idx];
//	}
//};
//
//int main()
//{
//	Array ar(10);
//	ar.Add(10);
//	ar.Add(20);
//	ar.Add(30);
//
//	cout << ar[0] << endl;	// ar.operator[](int) 호출
//	cout << endl;
//
//	const Array& ar2 = ar;	// 읽기 연산만 가능한 const 객체
//	cout << ar2[0] << endl;	// ar.operator[](int) const 호출
//	cout << endl;
//
//	ar[0] = 100;	// ar.operator[](int) 호출
//	// ar2[0] = 100;	// 상수 객체(값)를 반환하므로 대입할 수 없음.
//
//	return 0;
//}

/* 스마트 포인터 PointPtr 클래스 */
//class Point
//{
//	int x;
//	int y;
//public:
//	Point(int _x = 0, int _y = 0) :x(_x), y(_y) {}
//	void Print() const { cout << x << ',' << y << endl; }
//};
//
//class PointPtr
//{
//	Point *ptr;
//public:
//	PointPtr(Point *p) :ptr(p) {}
//	~PointPtr()
//	{
//		delete ptr;
//	}
//	Point* operator->() const
//	{
//		return ptr;
//	}
//	Point& operator*() const
//	{
//		return *ptr;
//	}
//};
//
//int main()
//{
//	//PointPtr p1 = new Point(2, 3);
//	Point* p1 = new Point(2, 3);	// 일반 포인터
//	PointPtr p2 = new Point(5, 5);	// 스마트 포인터
//
//	p1->Print();	// p1->Print() 호출
//	p2->Print();	// p2.operator->()->Print() 호출
//	cout << endl;
//
//	(*p1).Print();	// (*p1).Print() 호출
//	(*p2).Print();	// p2.operator*().Print() 호출
//
//	delete p1;
//
//	return 0;
//}

/* explicit 키워드 */
//class Point {
//	int x;
//	int y;
//public:
//	// 암시적인 생성자 형변환을 의도하지 않는 한 인자를 갖는 생성자는 모두 explicit 생성자로
//	explicit Point(int _x = 0, int _y = 0) :x(_x), y(_y) {}
//	void Print() const { cout << x << ',' << y << endl; }
//};
//
//int main()
//{
//	Point pt;
//	pt.Print();
//
//	// pt = 10;	// 암시적 생성자 호출 불가능. explicit이 없을 경우 pt = Point(10);과 같음
//	pt = Point(10);	// 명시적 생성자 호출만 가능
//	pt.Print();
//
//	return 0;
//}

/* 타입 변환 연산자 오버로딩을 이용한 타입 변환 
	타입 변환 연산자는 생성자나 소멸자처럼 반환 타입을 지정하지 않음.
*/
//class A
//{
//
//};
//
//class B
//{
//public:	
//	operator A()
//	{
//		cout << "operator A() 호출" << endl;
//		return A();
//	}
//	operator int()
//	{
//		cout << "operator int() 호출" << endl;
//		return 10;
//	}
//	operator double()
//	{
//		cout << "operator double() 호출" << endl;
//		return 5.5;
//	}
//};
//
//int main()
//{
//	A a;
//	int n;
//	double d;
//
//	B b;
//	a = b;	// b.operator A() 암시적 호출
//	n = b;	// b.operator int() 암시적 호출
//	d = b;	// b.operator double() 암시적 호출
//
//	cout << endl;
//	a = b.operator A();	// 명시적 호출
//	n = b.operator int();	// 명시적 호출
//	d = b.operator double();	// 명시적 호출
//
//	return 0;
//}


/* String -> const char* 타입 변환 연산자 */
//class String {
//	char buf[100];
//public:
//	String(const char* sz)
//	{
//		strcpy(buf, sz);
//	}
//	operator const char* () const
//	{
//		return buf;
//	}
//};
//
//int main()
//{
//	String s("Hello");
//	const char *sz = s;
//
//	cout << sz << endl;
//}

/* String 클래스 얕은/깊은 복사 */
//class String {	// 여기서 String 클래스의 =연산은 얕은 복사를 수행함.
//	char *buf;
//	//char buf[100];
//public:
//	String(const char* sz) {
//		strcpy(buf, sz);
//	}
//	friend ostream& operator << (ostream& os, const String &str) {
//		os << str.buf << endl;
//		return os;
//	}
//};
//
//class String {	// 여기서 String 클래스의 =연산은 얕은 복사를 수행함.
//	char *buf;
//	//char buf[100];
//public:
//	String(const char* sz) {
//		buf = new char[strlen(sz) + 1];
//	}
//	~String() {
//		delete[] buf;
//	}
//	const String& operator=(const String& arg) {
//		delete[] buf;
//		buf = new char[strlen(arg.buf) + 1];
//		strcpy(buf, arg.buf);
//
//		return *this;
//	}
//	friend ostream& operator << (ostream& os, const String &str) {
//		os << str.buf << endl;
//		return os;
//	}
//};
//
//
//int main()
//{
//	const char* sz = "Hello";
//	String s("Hi");
//	cout << s << endl;
//	
//	s = sz;	// s = String(sz);로 암묵적인 생성자를 이용한 타입 변환
//	cout << s << endl;
//
//	return 0;
//}

/* 객체, 주소로 멤버 함수 호출 */
class Point {
	int x;
	int y;
public:
	explicit Point(int _x = 0, int _y = 0) :x(_x), y(_y) {}
	void Print() const { cout << x << ',' << y << endl; }
	void PrintInt(int n) { cout << "테스트 정수 : " << n << endl; }
};

int main()
{
	Point pt(2, 3);
	Point *p = &pt;

	void (Point::*pf1)() const;	// 멤버 함수 포인터 선언
	pf1 = &Point::Print;

	void (Point::*pf2)(int);	// 멤버 함수 포인터 선언
	pf2 = &Point::PrintInt;

	pt.Print();
	pt.PrintInt(10);
	cout << endl;

	(pt.*pf1)();	// 객체로 멤버 함수 포인터를 이용한 호출
	(pt.*pf2)(10);	// 객체로 멤버 함수 포인터를 이용한 호출
	cout << endl;

	(p->*pf1)();	// 주소로 멤버 함수 포인터를 이용한 호출
	(p->*pf2)(10);	// 주소로 멤버 함수 포인터를 이용한 호출

	(*p.*pf1)();

	return 0;
}

