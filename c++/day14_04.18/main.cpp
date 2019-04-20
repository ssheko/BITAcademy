#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <string>
#pragma warning (disable:4996)

using namespace std;	// using ���ù�
using std::cout;		// using ����

						
/* �Լ� ȣ�� ������ �����ε�(() ������) */
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

/* ��� ��ü�� ��ȯ�ϴ� [] ������ �����ε� */
//class Array
//{
//	int *arr;
//	int size;
//	int capacity;
//
//	// ���� �Լ� ����(���� ������, ���� ���� ������)
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
//	cout << ar[0] << endl;	// ar.operator[](int) ȣ��
//	cout << endl;
//
//	const Array& ar2 = ar;	// �б� ���길 ������ const ��ü
//	cout << ar2[0] << endl;	// ar.operator[](int) const ȣ��
//	cout << endl;
//
//	ar[0] = 100;	// ar.operator[](int) ȣ��
//	// ar2[0] = 100;	// ��� ��ü(��)�� ��ȯ�ϹǷ� ������ �� ����.
//
//	return 0;
//}

/* ����Ʈ ������ PointPtr Ŭ���� */
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
//	Point* p1 = new Point(2, 3);	// �Ϲ� ������
//	PointPtr p2 = new Point(5, 5);	// ����Ʈ ������
//
//	p1->Print();	// p1->Print() ȣ��
//	p2->Print();	// p2.operator->()->Print() ȣ��
//	cout << endl;
//
//	(*p1).Print();	// (*p1).Print() ȣ��
//	(*p2).Print();	// p2.operator*().Print() ȣ��
//
//	delete p1;
//
//	return 0;
//}

/* explicit Ű���� */
//class Point {
//	int x;
//	int y;
//public:
//	// �Ͻ����� ������ ����ȯ�� �ǵ����� �ʴ� �� ���ڸ� ���� �����ڴ� ��� explicit �����ڷ�
//	explicit Point(int _x = 0, int _y = 0) :x(_x), y(_y) {}
//	void Print() const { cout << x << ',' << y << endl; }
//};
//
//int main()
//{
//	Point pt;
//	pt.Print();
//
//	// pt = 10;	// �Ͻ��� ������ ȣ�� �Ұ���. explicit�� ���� ��� pt = Point(10);�� ����
//	pt = Point(10);	// ����� ������ ȣ�⸸ ����
//	pt.Print();
//
//	return 0;
//}

/* Ÿ�� ��ȯ ������ �����ε��� �̿��� Ÿ�� ��ȯ 
	Ÿ�� ��ȯ �����ڴ� �����ڳ� �Ҹ���ó�� ��ȯ Ÿ���� �������� ����.
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
//		cout << "operator A() ȣ��" << endl;
//		return A();
//	}
//	operator int()
//	{
//		cout << "operator int() ȣ��" << endl;
//		return 10;
//	}
//	operator double()
//	{
//		cout << "operator double() ȣ��" << endl;
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
//	a = b;	// b.operator A() �Ͻ��� ȣ��
//	n = b;	// b.operator int() �Ͻ��� ȣ��
//	d = b;	// b.operator double() �Ͻ��� ȣ��
//
//	cout << endl;
//	a = b.operator A();	// ����� ȣ��
//	n = b.operator int();	// ����� ȣ��
//	d = b.operator double();	// ����� ȣ��
//
//	return 0;
//}


/* String -> const char* Ÿ�� ��ȯ ������ */
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

/* String Ŭ���� ����/���� ���� */
//class String {	// ���⼭ String Ŭ������ =������ ���� ���縦 ������.
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
//class String {	// ���⼭ String Ŭ������ =������ ���� ���縦 ������.
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
//	s = sz;	// s = String(sz);�� �Ϲ����� �����ڸ� �̿��� Ÿ�� ��ȯ
//	cout << s << endl;
//
//	return 0;
//}

/* ��ü, �ּҷ� ��� �Լ� ȣ�� */
class Point {
	int x;
	int y;
public:
	explicit Point(int _x = 0, int _y = 0) :x(_x), y(_y) {}
	void Print() const { cout << x << ',' << y << endl; }
	void PrintInt(int n) { cout << "�׽�Ʈ ���� : " << n << endl; }
};

int main()
{
	Point pt(2, 3);
	Point *p = &pt;

	void (Point::*pf1)() const;	// ��� �Լ� ������ ����
	pf1 = &Point::Print;

	void (Point::*pf2)(int);	// ��� �Լ� ������ ����
	pf2 = &Point::PrintInt;

	pt.Print();
	pt.PrintInt(10);
	cout << endl;

	(pt.*pf1)();	// ��ü�� ��� �Լ� �����͸� �̿��� ȣ��
	(pt.*pf2)(10);	// ��ü�� ��� �Լ� �����͸� �̿��� ȣ��
	cout << endl;

	(p->*pf1)();	// �ּҷ� ��� �Լ� �����͸� �̿��� ȣ��
	(p->*pf2)(10);	// �ּҷ� ��� �Լ� �����͸� �̿��� ȣ��

	(*p.*pf1)();

	return 0;
}

