#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <string>
#pragma warning (disable:4996)

using namespace std;	// using ���ù�
using std::cout;		// using ����

/* operator ������ �����ε� */
//class Number {
//	int fir;
//	int sec;
//public:
//	Number(int a, int b):fir(a), sec(b) {}
//	void setFirNumber(int data) { fir = data;  };
//	int getFirNumber(void) const {
//		return fir;
//	};
//	void setSecNumber(int data) { sec = data;  };
//	int getSecNumber(void) const {
//		return sec;
//	};
//	//friend bool operator==(const Number a, const Number b);
//	//bool operator==(Number &ob2) {
//	//	return (fir == ob2.getFirNumber()) && (sec == ob2.getSecNumber());
//	//}
//	friend Number operator+(int num, Number a);
//	Number operator+(int num) {	// a = a+5;
//		fir += num;
//		sec += num;
//		return *this;
//	}
//};
//
//bool operator==(const Number a, const Number b)
//{
//	//return (a.fir == b.fir) && (a.sec == b.sec);	// friend ����Ǿ� ���� ��� ����
//	return (a.getFirNumber() == b.getFirNumber()) && (a.getSecNumber() == b.getSecNumber());
//}
//
////Number operator+(Number a, int num) {
////	a.setFirNumber(a.getFirNumber() + num);
////	a.setSecNumber(a.getSecNumber() + num);
////	return a;
////}
//Number operator+(int num, Number a) {	// a = 5+a;
//	//a.setFirNumber(a.getFirNumber() + num);
//	//a.setSecNumber(a.getSecNumber() + num);
//	a.fir += num;
//	a.sec += num;
//	//return a;
//	return Number(a.fir + num, a.sec + num);
//}
//int main()
//{
//	Number a(10, 20);
//	Number b(10, 20);
//
//	if (a == b)	// if(operator==(a,b))	����
//		cout << "true" << endl;
//	else
//		cout << "false" << endl;
//
//	a = a + 2;	// a.operator+(5)
//	a = 5 + a;	// 5.operator+(a)	error �߻� -> operator+(5, a)���·�. 5�� ��ü�� �ƴϱ� ������ operator+�� friend �Լ��� �����ؾ� ��.
//	cout << a.getFirNumber() << ' ' << a.getSecNumber() << endl;
//	// ����Լ��� ó���� //if(a.operator==(b))
//
//}
//

/* ����Ʈ ������ �����ε� */
//class AAA {
//	int num;
//public:
//	AAA(int n) :num(n) {}
//	void setAAA(int n) { num = n; }
//	//friend class smart;
//	friend ostream &operator << (ostream &os, const AAA &rf) {
//		os << rf.num;
//		return os;
//	}
//};
//
//class smart {
//	AAA *p;
//public:
//	smart(AAA *p) :p(p) {}
//	~smart() {
//		delete p;
//		cout << "auto delete" << endl;
//	}
//	AAA& operator*() {	// ob.operator*()
//		return *p;
//	}
//	AAA* operator->() {	// ob.operator->()->setAAA(20)
//		return p;	// ��ü�� �ּ� ����
//	}
//	//int& operator*() {
//	//	return p->num;
//	//}
//};
//
//int main()
//{
//	smart ob(new AAA(10));	// ������ ��ü�� ���δ� ����ƮŬ���� (����Ʈ ������)
//	//*ob = 10;	// ob.operator*()
//	cout << ob.operator*() << endl;	// ob.operator*()
//	ob->setAAA(20);	// �ּҰ� ���ϵ� ������ �ּҸ� �������� setAAA ȣ��
//	cout << *ob << endl;
//}

/* 
	������ �����ε� ����
	soldier �̸��� ���̾�� sdName[]�� ���̾���� �Է�
	glove  �̸��� ö�尩 gvName[]�� ö�尩�� �Է�
	weapon �̸��� ��Ư�޷������̴�.wpName[]�� ��Ư�޷����� �Էµȴ�.
	
	
	soldier�� glove�� ������ ������ glove�� weapon�� ������ �ִ�.
	�ᱹ ���̾���� ö�尩�� �� ���¿��� ��Ư�޷������� ���� �ִ� ��Ȳ�̴�.
	
	soldier�� �ִ� -> �����ڸ� �����ε��Ͽ� �Ͽ� ���̾� ���� ��Ư�޷�������
	����ϵ��� �����Ͻÿ�.
	
	int main()
	{
	 soldier sd1("���̾��", "ö�尩", "��Ư�޷�����");
	 cout << sd1->wpName << endl;
	 return 0;
	}
	*/
//
//class weapon {
//public:
//	char* wpName;	// weapon �̸�
//	weapon(const char* name) {
//		wpName = new char[10];
//		strcpy(wpName, name);
//	}
//};
//
//class glove {
//	char *gvName;	// glove �̸�
//	weapon *wp;
//public:
//	glove(const char* name, const char* wpName) {
//		gvName = new char[10];
//		strcpy(gvName, name);
//		wp = new weapon(wpName);
//	}
//	friend class soldier;
//};
//
//class soldier {
//	char *sdName;	// soldier �̸�
//	glove *gv;
//public:
//	soldier(const char* sd_Name, const char* gvName, const char* wpName) {
//		sdName = new char[10];
//		gv = new glove(gvName, wpName);
//		strcpy(sdName, sd_Name);
//	}
//	weapon* operator->() const{
//		return this->gv->wp;
//	}
//};
//
//int main()
//{
//	soldier sd1("���̾��", "ö�尩", "��Ư�޷�����");
//	cout << sd1->wpName << endl;
//
//	return 0;
//}

//class weapon {
//	string wpName;
//public:
//	weapon() {}
//	weapon(string wpN) {
//		wpName = wpN;
//	}
//	string get_wpName(void)
//	{
//		return wpName;
//	}
//};
//class glove {
//	string gvName;
//	weapon wp;
//public:
//	glove() {}
//	glove(string gvN, string wN) :wp(wN)
//	{
//		gvName = gvN;
//	}
//	weapon& get_weapon(void)
//	{
//		return wp;
//	}
//};
//class soldier {
//	string sdName;
//	glove gv;
//public:
//
//	soldier(string sdN, string gvN, string wpN) :gv(gvN, wpN)
//	{
//		sdName = sdN;
//	}
//	weapon* operator -> ()
//	{
//		return &gv.get_weapon();
//	}
//};
//
//int main()
//{
//	// const char *name = "���̾��";
//	soldier sd1("���̾��", "ö�尩", "��Ư�޷�����");
//
//	cout << sd1->get_wpName() << endl;
//
//	cout << sd1.operator->()->get_wpName() << endl;
//	return 0;
//}