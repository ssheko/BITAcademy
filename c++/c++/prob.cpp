#include <iostream>
#include <cstdio>
#include <string>
#pragma warning (disable:4996)

using namespace std;	// using 지시문
using std::cout;		// using 선언


class engine {
private:
	int km;
	char mode;
public:
	void speed_engine(int km, const char *mode); //모드와 속도 출력
	void stop_engine(void);   //엔진정지 출력
	void set_km(int rkm);
	void set_mode(char rmode);
	int get_km(void);
	char get_mode(void);

};

class black_box {
private:
	engine * history;    //engine형태의 history
	int count = 0;
public:
	~black_box() { delete[] history; }

	void make_history_size(black_box &his);								//실제 history로 넣어야 할 engine배열을 만든다.(20개)

	void update_history(black_box &his, int rkm, const char *rmode); //사용자의 입력모드가 발생할때마다 history를 누적한다.

	void display_history();										//history내역을 출력해준다.

	
};

class car {
public:
	black_box * eye;		//차안에 블랙박스 기능을 넣을 수도 있고 뺄수 도 있다.
public:
	engine * sedan, *sports; //차의 옵션에 따라 세단형태로 출발 , 스포츠 모드 옵션인경우 스포츠모드 선택가능하겠다.

	~car() { delete eye; }
	void selectModeSpeed(black_box &his, engine &eg, int rkm, const char *rmode) {
		eg.set_km(rkm);
		eg.set_mode(*rmode);
		his.update_history(his, rkm, rmode);

	}
	void autoStop(void);	//장애물을 보고 자동 정지한다 (출력)

	void make_bbox(void);	 //블박클래스를 만들고//블박내부에 engine형태의 history를 20개 만든다. 

};

void engine::speed_engine(int km, const char *mode)
{
	cout << mode << "모드로 " << km << "km로 달립니다." << endl;
}

void engine::stop_engine(void)
{
	cout << "엔진이 정지되었습니다." << endl;
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
	cout << "자동 정지합니다." << endl;
}
void car::make_bbox(void) {
	eye = new black_box();
	eye->make_history_size(*eye);
}

int main()
{
	char menuList[3][20] = { "[e]co   연비주행", "[s]port 과속주행", "[h]istory " };
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
		cout << "원하는 자동차 모드를 선택하시오" << endl;
		cin >> inputMode;
		getchar();
		switch (inputMode) {
		case 'e':
			cout << "에코모드를 선택하셨습니다." << endl;
			break;
		case 's':
			cout << "스포츠모드를 선택하셨습니다." << endl;
			break;
		case 'h':
			cout << "히스토리 모드를 선택하셨습니다." << endl;
			obCar.eye->display_history();
			continue;
			break;
		default:
			break;
		}

		cout << "속도를 입력하시오: ";
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