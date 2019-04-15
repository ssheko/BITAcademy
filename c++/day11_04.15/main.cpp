#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <string>
#pragma warning (disable:4996)

using namespace std;	// using ���ù�
using std::cout;		// using ����

/* namespace, static */
//namespace mystd {	// mystd��� ������ ����ڴ�.
//	int a = 10;
//	namespace mystdin {
//		int a = 20;
//	}
//}
//int a = 30;	// ��������
//class Num {
//private:
//	static int praaa;	// static ����Լ��� ���ؼ��� ����
//	int aaa;
//public:
//	static int ubaaa;	// Ŭ������.ubaaa	��ü��.ubaaa �� ���ؼ��� ����
//	int a;	// (�� ����) ����ʵ� (static�� �����Ѵٸ� �� ����)
//
//	Num(int a) :a(a) {}	// ����Ʈ ������
//	void set_aaa(int aaa);
//	int get_aaa(void) const	// ��������� ���� ���ϰڴ�.
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
//int Num::ubaaa = 0;	// ���� ��������� ���� �ʿ� �ݵ��
//
//void Num::set_aaa(int aaa) {
//	this->aaa = aaa;
//}
//int main()
//{
//	namespace myin = mystd::mystdin;	// �� ª�� ǥ��
//	Num ob(40);
//	int a = 100;
//	cout << a << endl;
//	cout << mystd::a << endl;
//	cout << mystd::mystdin::a << endl;	// :: ��������(�ؼ�) ������
//	cout << ::a << endl;	// �������� a
//	cout << ob.a << endl;
//	cout << myin::a << endl;
//	ob.set_aaa(50);
//	cout << ob.get_aaa() << endl;
//	cout << Num::ubaaa << endl;	// Ŭ���������� ����������� ����
//	cout << ob.ubaaa << endl;	// ��ü�� ����������� ����
//	cout << Num::get_private_aaa() << endl;		// Ŭ���������� ����������� ����
//	cout << ob.get_private_aaa() << endl;		// ��ü�� ����������� ����
//
//}

/* 
	class Car ���¸� ������� �Ѵ�.
	������ ���� 3���� ��� ������ �ִ�.
	power
	gas
	brake
	Car ob0;				//10 , 10, 10
	Car ob1(200)			//200, 10, 10
	Car ob2(200, 30)	  //200, 30, 10
	Car ob3(200, 30 , 40) //200, 30, 40 
	�ǵ��� �����ڸ� �����Ͻÿ�
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
	������ �����Ҵ�, 2���� �迭
*/
//int main()
//{
//	// int *p = (int*)malloc(sizeof(int));
//	int *p = new int;
//	delete p;
//
//	int *p1 = new int[4];	// p1�� �迭 ����ϴ�
//	delete[] p1;
//
//	// 2�����迭?	// cpp�� 1���������� �迭�� ���� �� ����
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
	���ϴ� ũ���� matrix�� ����� Ŭ���� �����
	Ŭ������: matrix
	------------
	- rows: int	// -private
	- cols: int
	- mat : int**
	------------

	+ matrix(int, int)		// +public
	+~matrix()				// �Ҹ��ڴ� �Ű����� ����
	+elem(int, int) :int&	// return�� = int&. �ش� ��� ����
	+getRows()	: int			// �� ���� ����
	+getCols() : int			// �� ���� ����
	+print():				// matrix ���
	+setRand()				// rand() �Լ��� �̿��ؼ� �� ä���
	+maxpixel() : int		// matrix ���� �� ���� ū �� ã�� ����
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

/* ���� ������ */
//class vector {
//	int count;
//	int *vct;
//public:
//	//vector() {}	// ���� Ŭ������ ������
//	vector(int cnt) :count(cnt) {	// ���� Ŭ������ ũ�⸦ �������� count ��ŭ �Ҵ�
//		vct = new int[cnt];
//		//randset_vector();
//	}
//	~vector()
//	{
//		cout << "�Ҹ�" << endl;
//		delete[] vct;
//	}
//
//	// ���� �����ڸ� ��������� �� ������ ����ʵ尡 �������̱� ����
//	vector(const vector &rvt) {	// const�� �ɼ�.	// ���� �����ڸ� �ǹ�	// ���� ����
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
//	vector vt(10);	// 10���� �޸𸮸� ����Ű�� vct�� ���������.
//	vt.randset_vector();
//	vt.view_vector("vt");
//
//	//vector vt2(vt); �� ����
//	vector vt2 = vt;	// ����Ʈ ��������ڰ� �ڵ� ó��	// ���� ������ ���� ������� ��� ���� ���� (������ ����)
//	//vt2.randset_vector();
//	vt2.view_vector("vt2");
//	
//	return 0;
//}
/*
	EngineŬ������ ����(horsepower)�� ǥ���Ѵ�.
	������ 120���� 290������ ���� ������ �ִ�.
	������ �ִ� ������ ����ϴ� const�Լ��� �ִ�.
	�ش� const�Լ������� ���¿� ���������� �����Ҽ� ���� ��Ȳ�̴�.

	-------------------------------------------

	intercoolerEngineŬ������ engine�� ����Ѵ�.
	���������� cooler�� ������ �ִ�.
	cooler�������� *���·� //"����" �Ǵ� "��" ���°� �Էµȴ�.
	�ش� ���°� �𷯸� ����ϴ� �Լ��� �ִ�.
	intercoolerEngineŬ������ ��ü�� �ڽŰ� ���� ��ü�� �״��
	�����ϴ� �ɷ��� �ִ�.

	-------------------------------------------

	turboEngineŬ������ intercoolerEngineŬ������ ����Ѵ�.
	���������� turborchager�� ������ ������
	������ ������ A, B, C type�� ���ڰ� �Էµȴ�.

	--------------------------------------------

	1.engineŬ������ ��ü, 150���¿� �ش��ϴ�eng1��ü�� ����� ���
	2. intercoolerEngineŬ���� ��ü, 270���¿�  "��"�� ����ϴ� eng2��
	����� ���
	3. intercoolerEngine eng3�� eng2�� ���� ���� �� eng3���
	4. turboEngineŬ������ ��ü eng4 �� 290���¿� "����" �׸��� ������ 'B'
	   Ÿ���� ����ϴ� ��ü�̴�.
	   ��¹���� ����, ����+ ����, ����+����+���� 3�������·� ��µȴ�.

	�ش� ��ü�� �Ҹ��ڿ� �ʿ��ϴٸ� delete �� �����Ͻÿ�
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
//// 	1.engineŬ������ ��ü, 150���¿� �ش��ϴ�eng1��ü�� ����� ���
////	2. intercoolerEngineŬ���� ��ü, 270���¿�  "��"�� ����ϴ� eng2��
////	����� ���
////	3. intercoolerEngine eng3�� eng2�� ���� ���� �� eng3���
////	4. turboEngineŬ������ ��ü eng4 �� 290���¿� "����" �׸��� ������ 'B'
////	Ÿ���� ����ϴ� ��ü�̴�.
////	��¹���� ����, ���� + ����, ���� + ���� + ���� 3�������·� ��µȴ�.
//
//int main()
//{
//	Engine eng1(150);
//	interCoolerEngine eng2(270, "��");
//	interCoolerEngine eng3 = eng2;
//	turboEngine eng4(290, "����", 'B');
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

/* ����� �ڵ�
	error�� ��� turboEngineŬ������ �ϼ��Ͻÿ�.
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
//			cout << "�Ұ����� �Ŀ��Դϴ�" << endl;
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
//	intercoolerEngine eng2(270, "��");
//	eng2.showerICEngine();
//	intercoolerEngine eng3 = eng2;
//	eng3.showerICEngine();
//	return 0;
//}

/* ���� ������ 
	Ŭ���� ��ü�� ������� �� �ڵ����� �����Ǵ� �Լ� 4����
		������, �Ҹ���, ����Ʈ����, ����Ʈ ���Կ�����
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
//	void operator=(const BBB& ref)	// �Ļ�(�ڽ�) Ŭ�������� ���� �����ڸ� ��������� ����� �θ��� ����Ʈ ���Կ����ڸ� ��������� ȣ��.
//	{
//		AAA::operator=(ref);	// �θ��� ����Ʈ ���� ȣ��
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
//	BBB ob1(20);	// �⺻ ������
//	BBB ob2(ob1);	// ����Ʈ ���� ������
//	BBB ob3 = ob1;	// ����Ʈ ���� ������
//	BBB ob4(40);
//	ob4 = ob1;		// ����Ʈ ���Կ�����	// ob4.operator=(ob1);
//
//	cout << ob1.get_b() << endl;
//	cout << ob4.get_b() << endl;
//}
