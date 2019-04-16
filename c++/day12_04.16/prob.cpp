#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <string>
#pragma warning (disable:4996)

using namespace std;	// using ���ù�
using std::cout;		// using ����



/*
	//�̸��� ������ �����ϴ� tel Ŭ����(�̸�,����)�� �����
//
//telŬ���� ��ü�� 20�� �����ϴ� �迭�� ����� ����
//telhandler Ŭ������ �ִ�.
//main�Լ�
//telhandler �� ��ü;
//
//[]�����ڸ� �����ε��Ͽ�
//
//��ü��["����"] �� ����ϸ� ������ 789�� ���ϵǰ� �Ͻÿ�
//
//�̸�   ����
"����", 111

"���ؿ�", 666

"�պ���", 909

"�����", 222

"���α�", 808

"����", 789

"�����", 404

"�ڼ���", 303
"�ڼ���", 987
"�ŵ���", 333
"�̰��", 202
"������", 555
"Ȳ����", 456
"������", 654
"��ȣ��", 777
"���϶�", 101

"�̽¿�", 999

"������", 123

"������", 321

"������", 707
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
	
	char name[20][10] = { "����", "���ؿ�", "�պ���",  "�����", "���α�",  "����",
		"�����",  "�ڼ���",  "�ڼ���",   "�ŵ���",   "�̰��",  
		"������",  "Ȳ����", "������", "��ȣ��",  "���϶�",  
		"�̽¿�", "������", "������",   "������" };
	int phone[20] = { 909 , 222,  808,789,  404, 303,987,  333,  202, 555, 456,654,  777, 101, 999,  123,  321, 707 };
	for(int i=0; i<19; i++)
		ph.setTel(name[i], phone[i]);

	//cout << ph.getTelphone(1) << endl;
		cout << ph["����"] << endl;
	return 0;
}