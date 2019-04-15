#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <string>
#pragma warning (disable:4996)

using namespace std;	// using 지시문
using std::cout;		// using 선언

/* namespace, static */
//namespace mystd {	// mystd라는 공간을 만들겠다.
//	int a = 10;
//	namespace mystdin {
//		int a = 20;
//	}
//}
//int a = 30;	// 전역변수
//class Num {
//private:
//	static int praaa;	// static 멤버함수를 통해서만 접근
//	int aaa;
//public:
//	static int ubaaa;	// 클래스명.ubaaa	객체명.ubaaa 를 통해서만 접근
//	int a;	// (비 정적) 멤버필드 (static을 생각한다면 비 정적)
//
//	Num(int a) :a(a) {}	// 디폴트 생성자
//	void set_aaa(int aaa);
//	int get_aaa(void) const	// 멤버변수를 수정 안하겠다.
//	{
//		return aaa;
//	}
//	static int get_private_aaa(void)
//	{
//		return praaa;
//	}
//};
//
//int Num::praaa = 200;
//int Num::ubaaa = 0;	// 정적 멤버변수의 선언 필요 반드시
//
//void Num::set_aaa(int aaa) {
//	this->aaa = aaa;
//}
//int main()
//{
//	namespace myin = mystd::mystdin;	// 길어서 짧게 표현
//	Num ob(40);
//	int a = 100;
//	cout << a << endl;
//	cout << mystd::a << endl;
//	cout << mystd::mystdin::a << endl;	// :: 범위지정(해소) 연산자
//	cout << ::a << endl;	// 전역변수 a
//	cout << ob.a << endl;
//	cout << myin::a << endl;
//	ob.set_aaa(50);
//	cout << ob.get_aaa() << endl;
//	cout << Num::ubaaa << endl;	// 클래스명으로 정적멤버변수 접근
//	cout << ob.ubaaa << endl;	// 객체로 정적멤버변수 접근
//	cout << Num::get_private_aaa() << endl;		// 클래스명으로 정적멤버변수 접근
//	cout << ob.get_private_aaa() << endl;		// 객체로 정적멤버변수 접근
//
//}

/* 
	class Car 형태를 만들려고 한다.
	다음과 같이 3개의 멤버 변수가 있다.
	power
	gas
	brake
	Car ob0;				//10 , 10, 10
	Car ob1(200)			//200, 10, 10
	Car ob2(200, 30)	  //200, 30, 10
	Car ob3(200, 30 , 40) //200, 30, 40 
	되도록 생성자를 구현하시오
*/
//class Car
//{
//public:
//	int power = 10;
//	int gas = 10;
//	int brake = 10;
//
//	//Car() {}
//	//Car(int p) { power = p; };
//	//Car(int p, int g) { power = p;  gas = g; };
//	//Car(int p, int g, int b) { power = p;  gas = g; brake = b; };
//	//Car(int p) :power(p) {}
//	//Car(int p, int g) :power(p),gas(g) {}
//	//Car(int p, int g, int b) :power(p),gas(g),brake(b) {}
//
//	Car(int power=10, int gas = 10, int b = 10) :power(power),gas(gas),brake(brake) {}
//	void show_car(void) const {
//		cout << power << ' ' << gas << ' ' << brake << endl;
//	}
//
//};
//int main()
//{
//	Car ob0;
//	Car ob1(200);
//	Car ob2(200, 30);
//	Car ob3(200, 30, 40);
//
//	ob0.show_car();
//	ob1.show_car();
//	ob2.show_car();
//	ob3.show_car();
//}

/*
	포인터 동적할당, 2차원 배열
*/
//int main()
//{
//	// int *p = (int*)malloc(sizeof(int));
//	int *p = new int;
//	delete p;
//
//	int *p1 = new int[4];	// p1이 배열 사용하는
//	delete[] p1;
//
//	// 2차원배열?	// cpp는 1차원형태의 배열만 만들 수 있음
//	int **p2 = new int*[3];
//
//	p2[0] = new int[5];
//	p2[1] = new int[5];
//	p2[2] = new int[5];
//
//	delete[] p2[0];
//	delete[] p2[1];
//	delete[] p2[2];
//	delete[] p2;
//
//}

/*
	원하는 크기의 matrix를 만드는 클래스 만들기
	클래스명: matrix
	------------
	- rows: int	// -private
	- cols: int
	- mat : int**
	------------

	+ matrix(int, int)		// +public
	+~matrix()				// 소멸자는 매개변수 없음
	+elem(int, int) :int&	// return값 = int&. 해당 요소 리턴
	+getRows()	: int			// 행 길이 리턴
	+getCols() : int			// 열 길이 리턴
	+print():				// matrix 출력
	+setRand()				// rand() 함수를 이용해서 값 채우기
	+maxpixel() : int		// matrix 내부 중 가장 큰 값 찾아 리턴
*/
//
//class matrix
//{
//private:
//	int rows;
//	int cols;
//	int** mat;
//public:
//	matrix(int r, int c) : rows(r), cols(c) { 
//		//rows = r; cols = c; 
//		mat = new int*[rows];
//		for (int i = 0; i < rows; i++) {
//			mat[i] = new int[cols];
//		}
//		setRand();
//	}
//	~matrix()
//	{
//		for (int i = 0; i < rows; i++) {
//			delete[] mat[i];
//		}
//		delete []mat;
//	}
//	int& elem(int r, int c) {
//		return mat[r][c];
//	}
//	int getRows() {
//		return rows;
//	}
//	int getCols() {
//		return cols;
//	}
//	void print() {
//		for (int i = 0; i < rows; i++) {
//			for (int j = 0; j < cols; j++) {
//				printf("%3d", mat[i][j]);
//				//cout << mat[i][j] << ' ';
//			}
//			cout << endl;
//		}
//	}
//	void setRand()
//	{
//		int randNum;
//		for (int i = 0; i < rows; i++) {
//			for (int j = 0; j < cols; j++) {
//				randNum = rand() % (rows*cols) + 1;
//				mat[i][j] = randNum;
//			}
//		}
//	}
//
//	int maxpixel()
//	{
//		int max = mat[0][0];
//
//		for (int i = 0; i < rows; i++) {
//			for (int j = 0; j < cols; j++) {
//				if (max < mat[i][j])
//					max = mat[i][j];
//			}
//		}
//		return max;
//	}
//};
//
//int main()
//{
//	srand((unsigned int)time(NULL));
//	matrix m(7, 5);
//	m.print();
//	cout << endl;
//	cout << m.maxpixel() << endl;
//}

/* 복사 생성자 */
//class vector {
//	int count;
//	int *vct;
//public:
//	//vector() {}	// 벡터 클래스의 생성자
//	vector(int cnt) :count(cnt) {	// 벡터 클래스의 크기를 동적으로 count 만큼 할당
//		vct = new int[cnt];
//		//randset_vector();
//	}
//	~vector()
//	{
//		cout << "소멸" << endl;
//		delete[] vct;
//	}
//
//	// 복사 생성자를 명시적으로 한 이유는 멤버필드가 포인터이기 때문
//	vector(const vector &rvt) {	// const는 옵션.	// 복사 생성자를 의미	// 깊은 복사
//		count = rvt.count;
//		vct = new int[count];
//		for (int i = 0; i < count; i++)
//			vct[i] = rvt.vct[i];
//		//randset_vector();
//	}
//	void randset_vector()
//	{
//		for (int i = 0; i < count; i++)
//			vct[i] = rand() % 100 + 1;
//	}
//	void view_vector(const char *vw) {	
//		cout << vw << "= <";	
//		for (int i = 0; i < count; i++)
//			cout << vct[i] << ' ';
//		cout << ">" << endl;
//	}
//};
//
//int main()
//{
//	srand((unsigned int)time(NULL));
//	vector vt(10);	// 10개의 메모리를 가리키는 vct가 만들어진다.
//	vt.randset_vector();
//	vt.view_vector("vt");
//
//	//vector vt2(vt); 와 같음
//	vector vt2 = vt;	// 디폴트 복사생성자가 자동 처리	// 복사 생성자 없이 사용했을 경우 얕은 복사 (포인터 복사)
//	//vt2.randset_vector();
//	vt2.view_vector("vt2");
//	
//	return 0;
//}
/*
	Engine클래스는 마력(horsepower)을 표시한다.
	마력은 120에서 290마력을 값을 가질수 있다.
	가지고 있는 마력을 출력하는 const함수가 있다.
	해당 const함수에서는 마력에 직접적으로 접근할수 없는 상황이다.

	-------------------------------------------

	intercoolerEngine클래스는 engine를 상속한다.
	내부적으로 cooler를 가지고 있다.
	cooler의종류는 *형태로 //"오일" 또는 "물" 형태가 입력된다.
	해당 마력과 쿨러를 출력하는 함수가 있다.
	intercoolerEngine클래스의 객체는 자신과 같은 객체를 그대로
	복사하는 능력이 있다.

	-------------------------------------------

	turboEngine클래스는 intercoolerEngine클래스를 상속한다.
	내부적으로 turborchager를 가지고 있으며
	차저의 종류는 A, B, C type의 문자가 입력된다.

	--------------------------------------------

	1.engine클래스의 객체, 150마력에 해당하는eng1객체를 만들고 출력
	2. intercoolerEngine클래스 객체, 270마력에  "물"을 사용하는 eng2를
	만들고 출력
	3. intercoolerEngine eng3를 eng2로 부터 복사 후 eng3출력
	4. turboEngine클래스의 객체 eng4 는 290마력에 "오일" 그리고 차저는 'B'
	   타입을 사용하는 객체이다.
	   출력방법은 마력, 마력+ 오일, 마력+오일+차저 3가지형태로 출력된다.

	해당 객체에 소멸자에 필요하다면 delete 를 구현하시오
*/
/* my */
//class Engine {
//private:
//	int horsepower;
//	int getEngine(void) const {
//		return horsepower;
//	}
//public:
//	//int getHorsePower() {
//	//	return horsepower;
//	//}
//	Engine() {}
//	Engine(int input) //:horsepower(input) 
//	{
//		if (input < 120)
//			horsepower = 120;
//		else if (input > 290)
//			horsepower = 290;
//		else
//			horsepower = input;
//	}
//	void setEngine(int hp) {
//		horsepower = hp;
//	}
//	int getHorsePower()const {
//		return getEngine();
//	}
//	void printEngine()
//	{
//		cout << getEngine();
//	}
//};
//class interCoolerEngine : public Engine {
//protected:
//	const char* cooler;
//public:
//	interCoolerEngine() {}
//	interCoolerEngine(int hp, const char *co) :Engine(hp), cooler(co) {  }
//	interCoolerEngine(const interCoolerEngine &rie):Engine(rie.getHorsePower()) {
//		cooler = rie.cooler;		
//	}
//	~interCoolerEngine() {
//		//delete[] cooler;
//	}
//	const char* getCooler() {
//		return this->cooler;
//	}
//	const char* getInterCoolerEngine()
//	{		
//		//cout << this->horsepower << ' + ' << cooler << endl;
//		//cout << getEngine() << ' + ' << cooler << endl;
//		return cooler;
//	}
//
//	void printInterCoolerEngine()
//	{
//		//cout << this->horsepower << ' + ' << cooler << endl;
//		cout << Engine::getHorsePower() << " + " << getCooler();
//	}
//};
//
//class turboEngine : public interCoolerEngine {
//protected:
//	char turbocharger;
//public:	
//	turboEngine() {}
//	turboEngine(int hp, const char *co, char input) :turbocharger(input), interCoolerEngine(hp,co) {}
//	void setTurboCharger(char input) {
//		turbocharger = input;
//	}
//	char getTurboEngine()
//	{
//		//cout << this->horsepower << ' + ' << this->cooler << ' + ' << turbocharger << endl;
//		/*getInterCoolerEngine();
//		cout << turbocharger << endl;*/
//		return turbocharger;
//	}
//	void printTurboEngine()
//	{
//		cout << Engine::getHorsePower() << " + " << getCooler() << " + " << getTurboEngine();
//	}
//};
//
//// 	1.engine클래스의 객체, 150마력에 해당하는eng1객체를 만들고 출력
////	2. intercoolerEngine클래스 객체, 270마력에  "물"을 사용하는 eng2를
////	만들고 출력
////	3. intercoolerEngine eng3를 eng2로 부터 복사 후 eng3출력
////	4. turboEngine클래스의 객체 eng4 는 290마력에 "오일" 그리고 차저는 'B'
////	타입을 사용하는 객체이다.
////	출력방법은 마력, 마력 + 오일, 마력 + 오일 + 차저 3가지형태로 출력된다.
//
//int main()
//{
//	Engine eng1(150);
//	interCoolerEngine eng2(270, "물");
//	interCoolerEngine eng3 = eng2;
//	turboEngine eng4(290, "오일", 'B');
//	eng1.printEngine();
//	cout << endl;
//	eng2.printInterCoolerEngine();
//	cout << endl;
//	eng3.printInterCoolerEngine();
//	cout << endl;
//	eng4.printTurboEngine();
//
//	return 0;
//}

/* 강사님 코드
	error를 잡고 turboEngine클래스를 완성하시오.
*/
//#include <iostream>
//#pragma warning (disable:4996)
//#include <cstdio>
//#include<cstring>
//using namespace std;
//class Engine
//{
//private:
//	int horsepower;
//	int getHP(void) const
//	{
//		return horsepower;
//	}
//public:
//	Engine(int power)
//	{
//		if (120 > power || power > 290)
//		{
//			cout << "불가능한 파워입니다" << endl;
//			horsepower = 0;
//		}
//		else
//			horsepower = power;
//	}
//	Engine(Engine &copy) :horsepower(copy.horsepower)
//	{
//	}
//	int getHorsepower(void) const
//	{
//		return getHP();
//	}
//	void showEngineInfo() const
//	{
//		int power = getHorsepower();
//		if (power != 0)
//			cout << power << endl;
//	}
//	~Engine()
//	{
//		cout << "base" << endl;
//	}
//};
//class intercoolerEngine : public Engine
//{
//private:
//	char *cooler;
//public:
//	intercoolerEngine(int hp, char *col) :Engine(hp)
//	{
//		cooler = new char[strlen(col) + 1];
//		strcpy(cooler, col);
//	}
//	intercoolerEngine(const intercoolerEngine &copy) :Engine(copy.horsepower)
//	{
//		cooler = new char[strlen(copy.cooler) + 1];
//		strcpy(cooler, copy.cooler);
//	}
//	friend void viewcooler(intercoolerEngine &view);
//	void showerICEngine()
//	{
//		showEngineInfo();
//		cout << viewcooler(*this) << endl;
//	}
//	~intercoolerEngine()
//	{
//		delete[]cooler;
//		cout << "deconstructor" << endl;
//	}
//};
//void viewcooler(intercoolerEngine &view)
//{
//	cout << view.cooler << endl;
//}
////class turboEngine{
////private:
//// char charger
////public:
//// turboEngine(int eg, char *col, char type):intercoolerEngine(eg, col), charger(type)
//// {
////
//// }
////
////
//// showTEngineInfo()
//// {
////  cout<<
//// }
////
////
////};
//int main()
//{
//	Engine eng1(150);
//	eng1.showEngineInfo();
//	intercoolerEngine eng2(270, "물");
//	eng2.showerICEngine();
//	intercoolerEngine eng3 = eng2;
//	eng3.showerICEngine();
//	return 0;
//}

/* 대입 연산자 
	클래스 객체가 만들어질 때 자동으로 생성되는 함수 4가지
		생성자, 소멸자, 디폴트복사, 디폴트 대입연산자
*/
//class AAA {
//	int a;
//public:
//	AAA():a(0){}
//	AAA(int a):a(a){}
//
//	void set_a(int data) {
//		a = data;
//	}
//	int get_a(void) {
//		return a;
//	}
//};
//
//class BBB : public AAA {
//	int b;
//public:
//	//BBB() {}
//	BBB(int b) : AAA(), b(b) {}
//	BBB(const BBB& ref) : AAA(ref.get_a), b(ref.b) {}
//
//	void operator=(const BBB& ref)	// 파생(자식) 클래스에서 대입 연산자를 명시적으로 만들면 부모의 디폴트 대입연산자를 명시적으로 호출.
//	{
//		AAA::operator=(ref);	// 부모의 디폴트 대입 호출
//		b = ref.b;
//	}
//	void set_b(int data) {
//		b = data;
//	}
//	int get_b(void)const {
//		return b;
//	}
//};
//
//int main()
//{
//	BBB ob1(20);	// 기본 생성자
//	BBB ob2(ob1);	// 디폴트 복사 생성자
//	BBB ob3 = ob1;	// 디폴트 복사 생성자
//	BBB ob4(40);
//	ob4 = ob1;		// 디폴트 대입연산자	// ob4.operator=(ob1);
//
//	cout << ob1.get_b() << endl;
//	cout << ob4.get_b() << endl;
//}
