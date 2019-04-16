#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <string>
#pragma warning (disable:4996)

using namespace std;	// using 지시문
using std::cout;		// using 선언



/*
	//이름과 전번을 저장하는 tel 클래스(이름,전번)를 만들고
//
//tel클래스 객체를 20개 저장하는 배열을 멤버로 갖는
//telhandler 클래스가 있다.
//main함수
//telhandler 형 객체;
//
//[]연산자를 오버로딩하여
//
//객체명["김기백"] 를 출력하면 김기백의 789가 리턴되게 하시오
//
//이름   전번
"배상우", 111

"소준영", 666

"손병국", 909

"고승희", 222

"구민교", 808

"김기백", 789

"김다희", 404

"박선애", 303
"박성경", 987
"신동열", 333
"이경수", 202
"조희은", 555
"황상진", 456
"강상헌", 654
"이호세", 777
"전하람", 101

"이승연", 999

"조민희", 123

"이인찬", 321

"지도현", 707
*/
class tel {
	char* name;
	int telphone;
public:
	tel() {}
	tel(const char* n, int t) :telphone(t) {
		name = new char[10];
		strcpy(name, n);
	}
	//~tel() {
	//	delete[] name;
	//}
	char* getName() {
		return name;
	}
	void setName(char *n) {
		strcpy(name, n);
	}
	void setTelphone(int phone) {
		telphone = phone;
	}
	int getTelphone() {
		return telphone;
	}
};
class telhandler {
	static int total;
	tel *telList;
public:
	telhandler() {
		telList = new tel[20];
	}
	telhandler(const char* n, int t) {
		tel newTel(n, t);
		telList[total] = newTel;
		total++;
	}

	int getTelphone(int idx) {
		return telList[idx].getTelphone();
	}

	void setTel(const char* n, int t) {
		tel newTel(n, t);
		telList[total] = newTel;
		total++;	// telList[total++] = tel(n,t);
	}	
	int getIdx(char *name) {
		int idx = -1;
		for (int i = 0; i < total; i++) {
			if (!strcmp(name, telList[i].getName()))
				return idx;
		}
		return idx;
	}
	//tel operator[](int num) const{
	//	return telList[num];
	//}
	int operator[](const char *name) const {
		//int idx = getIdx(name);

		int idx = -1;
		for (int i = 0; i < total; i++) {
			if (!strcmp(name, telList[i].getName()))
				return telList[i].getTelphone();
		}
		if (idx == -1)
			return 0;
	}
};

int telhandler::total = 0;

int main()
{
	telhandler ph;
	
	char name[20][10] = { "배상우", "소준영", "손병국",  "고승희", "구민교",  "김기백",
		"김다희",  "박선애",  "박성경",   "신동열",   "이경수",  
		"조희은",  "황상진", "강상헌", "이호세",  "전하람",  
		"이승연", "조민희", "이인찬",   "지도현" };
	int phone[20] = { 909 , 222,  808,789,  404, 303,987,  333,  202, 555, 456,654,  777, 101, 999,  123,  321, 707 };
	for(int i=0; i<19; i++)
		ph.setTel(name[i], phone[i]);

	//cout << ph.getTelphone(1) << endl;
		cout << ph["김기백"] << endl;
	return 0;
}