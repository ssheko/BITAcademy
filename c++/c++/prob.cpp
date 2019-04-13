#include <iostream>
#include <cstdio>
#include <string>
#pragma warning (disable:4996)

using namespace std;	// using ���ù�
using std::cout;		// using ����


class engine {
private:
	int km;
	char mode;
public:
	void speed_engine(int km, const char *mode); //���� �ӵ� ���
	void stop_engine(void);   //�������� ���
	void set_km(int rkm);
	void set_mode(char rmode);
	int get_km(void);
	char get_mode(void);

};

class black_box {
private:
	engine * history;    //engine������ history
	int count = 0;
public:
	~black_box() { delete[] history; }

	void make_history_size(black_box &his);								//���� history�� �־�� �� engine�迭�� �����.(20��)

	void update_history(black_box &his, int rkm, const char *rmode); //������� �Է¸�尡 �߻��Ҷ����� history�� �����Ѵ�.

	void display_history();										//history������ ������ش�.

	
};

class car {
public:
	black_box * eye;		//���ȿ� ���ڽ� ����� ���� ���� �ְ� ���� �� �ִ�.
public:
	engine * sedan, *sports; //���� �ɼǿ� ���� �������·� ��� , ������ ��� �ɼ��ΰ�� ��������� ���ð����ϰڴ�.

	~car() { delete eye; }
	void selectModeSpeed(black_box &his, engine &eg, int rkm, const char *rmode) {
		eg.set_km(rkm);
		eg.set_mode(*rmode);
		his.update_history(his, rkm, rmode);

	}
	void autoStop(void);	//��ֹ��� ���� �ڵ� �����Ѵ� (���)

	void make_bbox(void);	 //���Ŭ������ �����//��ڳ��ο� engine������ history�� 20�� �����. 

};

void engine::speed_engine(int km, const char *mode)
{
	cout << mode << "���� " << km << "km�� �޸��ϴ�." << endl;
}

void engine::stop_engine(void)
{
	cout << "������ �����Ǿ����ϴ�." << endl;
}

void  engine::set_km(int rkm) {
	km = rkm;
}
void  engine::set_mode(char rmode) {
	mode = rmode;
}
int   engine::get_km(void) {
	return km;
}
char  engine::get_mode(void) {
	return mode;
}

void black_box::make_history_size(black_box &his) {
	his.history = new engine[20];
}
void black_box::update_history(black_box &his, int rkm, const char *rmode) {
	his.history[count].set_km(rkm);
	his.history[count++].set_mode(*rmode);
}
void black_box::display_history() {
	for (int i = 0; i < count; i++) {
		cout << history[i].get_km() << ' ' <<  history[i].get_mode() << endl;
	}
}

void car::autoStop(void) {
	cout << "�ڵ� �����մϴ�." << endl;
}
void car::make_bbox(void) {
	eye = new black_box();
	eye->make_history_size(*eye);
}

int main()
{
	char menuList[3][20] = { "[e]co   ��������", "[s]port ��������", "[h]istory " };
	char inputMode;
	int inputSpeed;
	int count = 0;
	car obCar;
	obCar.sedan = new engine;
	obCar.sports = new engine;

	
	obCar.make_bbox();
	while (1) {
		cout << "-------------------" << endl;
		for (int i = 0; i < 3; i++)
			cout << menuList[i] << endl;
		cout << "-------------------" << endl;
		cout << "���ϴ� �ڵ��� ��带 �����Ͻÿ�" << endl;
		cin >> inputMode;
		getchar();
		switch (inputMode) {
		case 'e':
			cout << "���ڸ�带 �����ϼ̽��ϴ�." << endl;
			break;
		case 's':
			cout << "��������带 �����ϼ̽��ϴ�." << endl;
			break;
		case 'h':
			cout << "�����丮 ��带 �����ϼ̽��ϴ�." << endl;
			obCar.eye->display_history();
			continue;
			break;
		default:
			break;
		}

		cout << "�ӵ��� �Է��Ͻÿ�: ";
		cin >> inputSpeed;
		getchar();
		if(inputMode == 'e') {
			obCar.selectModeSpeed(*obCar.eye, *obCar.sedan, inputSpeed, &inputMode);
			cout << obCar.sedan->get_km() << ' ' << obCar.sedan->get_mode() << endl;
		}
		else if (inputMode = 's') {
			obCar.selectModeSpeed(*obCar.eye, *obCar.sports, inputSpeed, &inputMode);
			cout << obCar.sports->get_km() << ' ' << obCar.sports->get_mode() << endl;
		}

		
	}
	delete obCar.sedan;
	delete obCar.sports;
	return 0;
}