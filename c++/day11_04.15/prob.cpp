#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <string>
#pragma warning (disable:4996)

using namespace std;	// using ���ù�
using std::cout;		// using ����

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
		Subject subj("����");
		p_sub[0] = subj;
		Subject subj2("����");
		p_sub[1] = subj2;
		Subject subj3("����");
		p_sub[2] = subj3;
		id_Number = last_id_Number++;
	}
	//~Student() {
	//	delete[] p_sub;
	//	cout << "Student �Ҹ�" << endl;
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
		strcpy(universityName, "��¾��");
	}
	GradeHandler(Student* student, char* universityName) {
		students = student;
		strcpy(universityName, "��¾��");
	}*/
	~GradeHandler() {
		delete[] students;
		cout << "GradeHandler �Ҹ�" << endl;
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
personŬ������ private ������  �̸��� ���̸� ���´�.
���class person
�̸� perName
���� perAge

���� class subject
������ subjName
����   subjScore


�л� Ŭ������ person Ŭ���� ��ӹް�  �й�(const),����, ����� ���´�.
������� ����, ����, ������ �⺻������ ���´�. ����Ŭ������ ����� ���´�.
�л�class student
subject *p_sub
�й� id_Number
���� id_Total
��� id_Average

gradeHandlerŬ�������� �б���� �л�Ŭ������ ��ü�迭�� ���´�.
�� �� ��ü�迭�� ���� �Է��� �޴´�.(�б����� �л����� �ٸ��Ƿ�)
��������class gradeHandler
�б��� UVsityName
student ��ü�迭
int studentTop


���� ��)

�б���� �л����� �Է��Ͻÿ�.
�б���:  ��¾��
�л���:  10
MAIN
 1. �л�����
 2. ��������
���� ::

1. �л�����
  - �л��߰�(�ڵ������й��� �����Ѵ�.)
	-- �л��� : ������
	-- ��   �� : 20
	[4]���� ������(20) �л��� �߰���
  - �л�����(�л���� �й����� �㰡-�̸��� ����, ����)
	-- �л���: ������
	-- ��   ��:  4
	-- �л��� : ������
	-- ��   �� : 19
  [4] ������(20)�� ������(19)�� ������

  - �л�����(�л���� �й����� �㰡- ������ �й��� [*]�� ǥ�õǸ� ������ ���´�)
2. ��������
  - ���л�����Ʈ�� ������ش�.(������ ���ٸ� 0���� ���)
 �й� �̸�(����)    ����   ����   ����   ����  ���
 [0]  ���׳�(22)      0       0      0       0       0
 [1]  �ճ���(32)      0       0      0       0       0
 [2]  ������(25)      0       0      0       0       0
 [3]  �����(27)      0       0      0       0       0
 [4]  ������(19)      0       0      0       0       0
  - �����߰�
	-- �й��Է� : 4   (�й��Է½� ���� �л��̸� MAINȭ������ ���ư���)
 ** ������ �л� **
 -- �������� : 70
 -- �������� : 80
 -- �������� : 90
 [4]  ������(19)      70     80     90      240     80
*/
int main()
{
	char *universityName, *studentName, *newStudentName;
	int totalStudent, choice, innerChoice, studentAge, studentID, prevStudentAge;
	int score, scoreSum, totalSuject = 3;
	Student currStudent;
	char subjectList[3][5] = { "����","����","����" };
	universityName = new char[10];
	studentName = new char[10];
	newStudentName = new char[10];
	
	cout << "�б���� �л����� �Է��Ͻÿ�." << endl;
	cout << "�б���: ";
	cin >> universityName;
	cout << "�л���: ";
	cin >> totalStudent;

	GradeHandler gradeHandler(universityName, totalStudent);

	while (1) {
		cout << "1. �л�����\n2. ��������\n���� :: ";
		cin >> choice;
		switch (choice) {
			// �л� ����
		case 1:
			cout << "1. �л��߰�\n2. �л�����\n3. �л�����\n���� :: ";
			cin >> innerChoice;
			switch (innerChoice) {
				// �л� �߰�
			case 1:
				cout << "-- �л��� : ";
				cin >> studentName;
				cout << "-- ��  �� : ";
				cin >> studentAge;

				studentID = gradeHandler.setStudent(studentName, studentAge);
				
				printf("[%d]���� %s(%d) �л��� �߰���\n", studentID, gradeHandler.getStudent(studentID).getName(), gradeHandler.getStudent(studentID).getAge());
				break;
				// �л� ����
			case 2:
				cout << "-- �л��� : ";
				cin >> studentName;
				cout << "-- ��  �� : ";
				cin >> studentID;

				cout << "-- �л��� : ";
				cin >> newStudentName;
				cout << "-- ��  �� : ";
				cin >> studentAge;

				prevStudentAge = gradeHandler.getStudent(studentID).getAge();
				gradeHandler.setStudent(studentID, studentAge, newStudentName);

				printf("[%d] %s(%d)�� %s(%d)�� ������\n", studentID, studentName, prevStudentAge, gradeHandler.getStudent(studentID).getName(), gradeHandler.getStudent(studentID).getAge());
				break;
				// �л� ����
			case 3:
				cout << "-- �л��� : ";
				cin >> studentName;
				cout << "-- ��  �� : ";
				cin >> studentID;
				strcpy(newStudentName, "none");
				prevStudentAge = gradeHandler.getStudent(studentID).getAge();
				gradeHandler.setStudent(studentID, 0, newStudentName);
				printf("[%d] %s(%d) ����\n", studentID, studentName, prevStudentAge);
				break;
			default:
				break;
			}
			break;
		case 2:
			printf("�й�\t�̸�(����)\t����\t����\t����\t����\t���\n");
			for (int i = 0; i < gradeHandler.getlastNumber(); i++) {
				currStudent = gradeHandler.getStudent(i);
				if(currStudent.getAge() == 0)
					printf("[*]\t%s(?)\t\t%d\t%d\t%d\t%d\t%.1f\n", currStudent.getName(), currStudent.getSubject(0).getScore(), currStudent.getSubject(1).getScore(), currStudent.getSubject(2).getScore(), currStudent.getTotal(), currStudent.getAverage());
				else
					printf("[%d]\t%s(%d)\t%d\t%d\t%d\t%d\t%.1f\n", currStudent.getID(), currStudent.getName(), currStudent.getAge(), currStudent.getSubject(0).getScore(), currStudent.getSubject(1).getScore(), currStudent.getSubject(2).getScore(), currStudent.getTotal(), currStudent.getAverage());
			}

			cout << "- �����߰�" << endl;
			cout << "-- �й��Է� : ";
			cin >> studentID;
			currStudent = gradeHandler.getStudent(studentID);
			if (currStudent.getName() == NULL)
				continue;
			printf("** %s �л� **\n", currStudent.getName());

			scoreSum = 0;
			for (int i = 0; i < totalSuject; i++) {
				printf("-- %s ���� : ", subjectList[i]);
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