#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <string>
#pragma warning (disable:4996)

using namespace std;	// using 지시문
using std::cout;		// using 선언

/* operator 연산자 오버로딩 */
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
//	//return (a.fir == b.fir) && (a.sec == b.sec);	// friend 선언되어 있을 경우 가능
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
//	if (a == b)	// if(operator==(a,b))	가능
//		cout << "true" << endl;
//	else
//		cout << "false" << endl;
//
//	a = a + 2;	// a.operator+(5)
//	a = 5 + a;	// 5.operator+(a)	error 발생 -> operator+(5, a)형태로. 5가 객체가 아니기 때문에 operator+를 friend 함수로 구현해야 함.
//	cout << a.getFirNumber() << ' ' << a.getSecNumber() << endl;
//	// 멤버함수로 처리시 //if(a.operator==(b))
//
//}
//

/* 포인트 연산자 오버로딩 */
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
//		return p;	// 객체의 주소 리턴
//	}
//	//int& operator*() {
//	//	return p->num;
//	//}
//};
//
//int main()
//{
//	smart ob(new AAA(10));	// 생성된 객체를 감싸는 스마트클래스 (스마트 포인터)
//	//*ob = 10;	// ob.operator*()
//	cout << ob.operator*() << endl;	// ob.operator*()
//	ob->setAAA(20);	// 주소가 리턴된 다음에 주소를 기준으로 setAAA 호출
//	cout << *ob << endl;
//}

/* 
	연산자 오버로딩 예제
	soldier 이름은 아이언맨 sdName[]에 아이언맨이 입력
	glove  이름은 철장갑 gvName[]에 철장갑이 입력
	weapon 이름은 초특급레이져이다.wpName[]에 초특급레이져 입력된다.
	
	
	soldier는 glove를 가지고 있으면 glove는 weapon를 가지고 있다.
	결국 아이언맨은 철장갑을 낀 상태에서 초특급레이져를 쓰고 있는 상황이다.
	
	soldier에 있는 -> 연산자를 오버로딩하여 하여 아이언 맨이 초특급레이져를
	사용하도록 구현하시오.
	
	int main()
	{
	 soldier sd1("아이언맨", "철장갑", "초특급레이져");
	 cout << sd1->wpName << endl;
	 return 0;
	}
	*/
//
//class weapon {
//public:
//	char* wpName;	// weapon 이름
//	weapon(const char* name) {
//		wpName = new char[10];
//		strcpy(wpName, name);
//	}
//};
//
//class glove {
//	char *gvName;	// glove 이름
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
//	char *sdName;	// soldier 이름
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
//	soldier sd1("아이언맨", "철장갑", "초특급레이져");
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
//	// const char *name = "아이언맨";
//	soldier sd1("아이언맨", "철장갑", "초특급레이져");
//
//	cout << sd1->get_wpName() << endl;
//
//	cout << sd1.operator->()->get_wpName() << endl;
//	return 0;
//}