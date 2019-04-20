#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <string>
#pragma warning (disable:4996)

using namespace std;	// using 지시문
using std::cout;		// using 선언

class Person
{
private:
	char perName[10];
	int perAge;
public:
	Person() {}
	Person(char* perName, int perAge) :perAge(perAge) //, perName(perName)
	{
		setName(perName);
	}
	void setName(const char *name) {
		strcpy(perName, name);
	}
	 char* getName(void) {
		return perName;
	}
	void setAge(int age) {
		perAge = age;
	}
	int getAge(void) {
		return perAge;
	}
};

class Subject 
{
protected:
	char subjName[5];
	int subjScore;
public:
	Subject() {}
	Subject(const char* subjName, int subjScore=0): subjScore(subjScore)//, subjName(subjName)
	{
		setName(subjName);
	}
	void setName(const char *perName) {
		strcpy(subjName, perName);
	}
	const char* getName(void) {
		return subjName;
	}
	void setScore(int age) {
		subjScore = age;
	}
	int getScore(void) {
		return subjScore;
	}

};

class Student : public Person
{
protected:
	Subject* p_sub;
	static int last_id_Number;
	int id_Number;
	int id_Total;
	float id_Average;
public:
	Student() {}
	Student(char* studentName, int studentAge, int id_Total=0, float id_Average=0) : Person(studentName, studentAge),id_Total(id_Total), id_Average(id_Average){
		p_sub = new Subject[3];
		Subject subj("국어");
		p_sub[0] = subj;
		Subject subj2("영어");
		p_sub[1] = subj2;
		Subject subj3("수학");
		p_sub[2] = subj3;
		id_Number = last_id_Number++;
	}
	//~Student() {
	//	delete[] p_sub;
	//	cout << "Student 소멸" << endl;
	//}
	void setID(int num) {
		id_Number = num;
	}
	int getID(void) {
		return id_Number;
	}
	void setTotal(int total) {
		id_Total = total;
	}
	int getTotal(void) {
		return id_Total;
	}
	void setAverage(float average) {
		id_Average = average;
	}
	float getAverage(void) {
		return id_Average;
	}
	int getLastNumber() {
		return last_id_Number;
	}
	Subject getSubject(int id) {
		return p_sub[id];
	}
	void setSubject(int id, int score) {
		p_sub[id].setScore(score);
	}
};

int Student::last_id_Number = 0;

class GradeHandler
{
protected:
	char* universityName;
	Student *students;
	int studentTop;
public:
	GradeHandler() {}
	GradeHandler(char* universityName, int count) {
		students = new Student[count];
		strcpy(universityName, universityName);
	}
	/*GradeHandler(char* studentName, int studentAge){
		Student newStudent(studentName, studentAge);
		students[newStudent.getID()] = newStudent;
		strcpy(universityName, "어쩐대");
	}
	GradeHandler(Student* student, char* universityName) {
		students = student;
		strcpy(universityName, "어쩐대");
	}*/
	~GradeHandler() {
		delete[] students;
		cout << "GradeHandler 소멸" << endl;
	}

	Student getStudent(int id) {
		return students[id];
	}

	int setStudent(char* name, int age) {
		Student newStudent(name, age);
		students[newStudent.getID()] = newStudent;
		return newStudent.getID();
	}
	void setStudent(int id, int age, char* name) {
		students[id].setAge(age);
		students[id].setName(name);
	}

	Student* getStudent() {
		return students;
	}
	void setStudent(Student *s) {
		students = s;
	}
	int getlastNumber()
	{
		return students[0].getLastNumber();
	}

	void setScore(int studentID, int id, int score)
	{
		students[studentID].setSubject(id, score);
	}
	void setTotalAverage(int studentID, int total, float avg)
	{
		students[studentID].setTotal(total);
		students[studentID].setAverage(avg);
	}
};
/*
person클래스는 private 형태의  이름과 나이를 갖는다.
사람class person
이름 perName
나이 perAge

과목 class subject
전공명 subjName
점수   subjScore


학생 클래스는 person 클래를 상속받고  학번(const),총점, 평균을 갖는다.
과목명은 국어, 영어, 수학을 기본적으로 갖는다. 과목클래스를 멤버로 갖는다.
학생class student
subject *p_sub
학번 id_Number
총점 id_Total
평균 id_Average

gradeHandler클래스에는 학교명과 학생클래스의 객체배열을 갖는다.
이 때 객체배열의 수는 입력을 받는다.(학교마다 학생수가 다르므로)
성적관리class gradeHandler
학교명 UVsityName
student 객체배열
int studentTop


실행 예)

학교명과 학생수를 입력하시오.
학교명:  어쩐대
학생수:  10
MAIN
 1. 학생관리
 2. 성적관리
선택 ::

1. 학생관리
  - 학생추가(자동으로학번이 증가한다.)
	-- 학생명 : 무진정
	-- 나   이 : 20
	[4]으로 무진정(20) 학생이 추가됨
  - 학생수정(학생명과 학번으로 허가-이름만 수정, 나이)
	-- 학생명: 무진정
	-- 학   번:  4
	-- 학생명 : 무진장
	-- 나   이 : 19
  [4] 무진정(20)이 무진장(19)로 수정됨

  - 학생삭제(학생명과 학번으로 허가- 삭제시 학번에 [*]이 표시되며 성적은 남는다)
2. 성적관리
  - 재학생리스트를 출력해준다.(점수가 없다면 0으로 출력)
 학번 이름(나이)    국어   영어   수학   총점  평균
 [0]  안테나(22)      0       0      0       0       0
 [1]  손낙지(32)      0       0      0       0       0
 [2]  누군고(25)      0       0      0       0       0
 [3]  고기판(27)      0       0      0       0       0
 [4]  무진장(19)      0       0      0       0       0
  - 성적추가
	-- 학번입력 : 4   (학번입력시 없는 학생이면 MAIN화면으로 돌아가기)
 ** 무진장 학생 **
 -- 국어점수 : 70
 -- 영어점수 : 80
 -- 수학점수 : 90
 [4]  무진장(19)      70     80     90      240     80
*/
int main()
{
	char *universityName, *studentName, *newStudentName;
	int totalStudent, choice, innerChoice, studentAge, studentID, prevStudentAge;
	int score, scoreSum, totalSuject = 3;
	Student currStudent;
	char subjectList[3][5] = { "국어","영어","수학" };
	universityName = new char[10];
	studentName = new char[10];
	newStudentName = new char[10];
	
	cout << "학교명과 학생수를 입력하시오." << endl;
	cout << "학교명: ";
	cin >> universityName;
	cout << "학생수: ";
	cin >> totalStudent;

	GradeHandler gradeHandler(universityName, totalStudent);

	while (1) {
		cout << "1. 학생관리\n2. 성적관리\n선택 :: ";
		cin >> choice;
		switch (choice) {
			// 학생 관리
		case 1:
			cout << "1. 학생추가\n2. 학생수정\n3. 학생삭제\n선택 :: ";
			cin >> innerChoice;
			switch (innerChoice) {
				// 학생 추가
			case 1:
				cout << "-- 학생명 : ";
				cin >> studentName;
				cout << "-- 나  이 : ";
				cin >> studentAge;

				studentID = gradeHandler.setStudent(studentName, studentAge);
				
				printf("[%d]으로 %s(%d) 학생이 추가됨\n", studentID, gradeHandler.getStudent(studentID).getName(), gradeHandler.getStudent(studentID).getAge());
				break;
				// 학생 수정
			case 2:
				cout << "-- 학생명 : ";
				cin >> studentName;
				cout << "-- 학  번 : ";
				cin >> studentID;

				cout << "-- 학생명 : ";
				cin >> newStudentName;
				cout << "-- 나  이 : ";
				cin >> studentAge;

				prevStudentAge = gradeHandler.getStudent(studentID).getAge();
				gradeHandler.setStudent(studentID, studentAge, newStudentName);

				printf("[%d] %s(%d)이 %s(%d)로 수정됨\n", studentID, studentName, prevStudentAge, gradeHandler.getStudent(studentID).getName(), gradeHandler.getStudent(studentID).getAge());
				break;
				// 학생 삭제
			case 3:
				cout << "-- 학생명 : ";
				cin >> studentName;
				cout << "-- 학  번 : ";
				cin >> studentID;
				strcpy(newStudentName, "none");
				prevStudentAge = gradeHandler.getStudent(studentID).getAge();
				gradeHandler.setStudent(studentID, 0, newStudentName);
				printf("[%d] %s(%d) 삭제\n", studentID, studentName, prevStudentAge);
				break;
			default:
				break;
			}
			break;
		case 2:
			printf("학번\t이름(나이)\t국어\t영어\t수학\t총점\t평균\n");
			for (int i = 0; i < gradeHandler.getlastNumber(); i++) {
				currStudent = gradeHandler.getStudent(i);
				if(currStudent.getAge() == 0)
					printf("[*]\t%s(?)\t\t%d\t%d\t%d\t%d\t%.1f\n", currStudent.getName(), currStudent.getSubject(0).getScore(), currStudent.getSubject(1).getScore(), currStudent.getSubject(2).getScore(), currStudent.getTotal(), currStudent.getAverage());
				else
					printf("[%d]\t%s(%d)\t%d\t%d\t%d\t%d\t%.1f\n", currStudent.getID(), currStudent.getName(), currStudent.getAge(), currStudent.getSubject(0).getScore(), currStudent.getSubject(1).getScore(), currStudent.getSubject(2).getScore(), currStudent.getTotal(), currStudent.getAverage());
			}

			cout << "- 성적추가" << endl;
			cout << "-- 학번입력 : ";
			cin >> studentID;
			currStudent = gradeHandler.getStudent(studentID);
			if (currStudent.getName() == NULL)
				continue;
			printf("** %s 학생 **\n", currStudent.getName());

			scoreSum = 0;
			for (int i = 0; i < totalSuject; i++) {
				printf("-- %s 점수 : ", subjectList[i]);
				cin >> score;
				currStudent.setSubject(i, score);

				scoreSum += score;
			}
			gradeHandler.setTotalAverage(studentID, scoreSum, scoreSum / totalSuject);
			currStudent = gradeHandler.getStudent(studentID);
			
			printf("[%d]\t%s(%d)\t%d\t%d\t%d\t%d\t%.1f\n", currStudent.getID(), currStudent.getName(), currStudent.getAge(), currStudent.getSubject(0).getScore(), currStudent.getSubject(1).getScore(), currStudent.getSubject(2).getScore(), currStudent.getTotal(), currStudent.getAverage());

			break;
		default:
			break;
		}
	}
	delete[] universityName;
	delete[] studentName;
		delete[]  newStudentName;
}