#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <string>
#pragma warning (disable:4996)

using namespace std;	// using ���ù�
using std::cout;		// using ����

/* ���ø� */
//template <typename T> T add(T a, T b) {} // �Լ����ø�	// �Լ��� ���� ���ø�
//add<int>(10, 20); // ���� ȣ��
//add(10, 20); // ���� ȣ��
//int add<char>(char a, char b){}// ���ۿ� ���� ������� ����
//template<>char* add(char *a, char *b){} //����Ư��ȭ			���� template ���� �Ұ�. add ���� <> ���� ����
//template<>char* add<>(char *a, char *b) {} //����Ư��ȭ
//template<>char* add<char*>(char *a, char *b) {} //����Ư��ȭ
//------------------------------------------------------------
//template <typenae T> class point {} //Ŭ�������ø�	// Ŭ������ ���� ���ø�
//template <typenae T> class point { pubic: T add(T a, T b); } //Ŭ�۾��� ����Լ� ����	// add �Լ��� ���� Ÿ�� T
//template <typenae T> T point<T>::add(T a, T b) {} //Ŭ�۾��� ����Լ� ����				// point ���� add�Լ��� ���� Ÿ��T	// typename T, <T>, (T a, T b)	==> �� ������ T�� �ǹ̰� �ٸ�
//point<int> ob(3, 4);
//point<other*> ob(3, 4);
//point<other<int>*> ob(3, 4);  //typedef other<int>* TTR;
//template <>class point<int>{};//Ŭ��Ư��ȭ		// class point<int> �� <int> ���� �Ұ�
//template <>class point<int, char> {};//Ŭ��Ư��ȭ
//template <typename T> class point<T, char> {};//Ŭ�ۺκ�Ư��ȭ
//template <typename T, int size> class point{};//Ŭ�� ����
//template <typename T=int, int size=10> class point {};//Ŭ�� ����Ʈ����
//template <typename T, typename T>   T func2(T a, T b);  // ����, T�� �ߺ� ���� 
//template <typename T, typename U, typename V>   U func2(T a, V b);  // ����, U�� ���μ��� ������ ����	// �Ű����� Ÿ�Կ� U�� �־�� �Ѵ�. ����Ÿ���� U�ʹ� ��� ����.

/*
	��� Ÿ�Կ� ���� 2���� ���� ���ϴ� add �Լ� ���ø� ����
	���ܷ� string���� ��� �Լ� ���ø� Ư��ȭ�� ����
	�� ���ڿ��� ���̽ÿ�
*/

//template<typename T>T add(T a, T b) {
//	T c;
//	c = a + b;
//	return c;
//}
//template<>string add<>(string a, string b) {
//	//string c;
//	//c = a + b;
//	//return c;
//	return a.append(b);
//}
//
//int main() {
//	int a = 10, b = 2;
//	float aa = 10.2, bb = 2.3;
//	cout << add(a , b) << endl;
//	cout << add(aa , bb) << endl;
//	string s1 = "aaa", s2 = "bbb";
//	cout << add(s1, s2) << endl;
//
//	return 0;
//}

/* 
	�� ���� ǥ���ϴ� fir�� sec�� ��������� ���� Ŭ���� ���ø��� �����Ͻÿ�.
	����Լ��� max�� ȣ���� ��� ū ���� ����Ͻÿ�.

	���� �� ���� char *���� ���޵� ��� Ŭ���� ���ø� Ư��ȭ�� �����Ͽ�
	����Լ��� max�� �� char * �� ���ĺ� ���� ū ���� ����Ͻÿ�.
*/
//
//template <typename T> 
//class point {
//	T fir; T sec;
//public: 
//	point(T f, T s) : fir(f), sec(s){}
//	T max(void);
//};
//template<typename T>
//T point<T>::max(void) {
//	return (fir >= sec) ? fir : sec;
//}
//
////template<typename T>T point<T>::max(T a, T b) {
////	if (a >= b)
////		return a;
////	else
////		return b;
////}
//template <>
//class point<char *> {
//	char* fir;
//	char* sec;
//public: 
//	point(const char* f, const char* s){
//		fir = new char[strlen(f)];
//		sec = new char[strlen(s)];
//		strcpy(fir, f);
//		strcpy(sec, s);
//	}
//	char* max(void)
//	{
//		return (strcmp(fir, sec) > 0) ? fir : sec;
//	}
//};
//int main()
//{
//	point<int> p(10, 3);
//	cout << p.max() << endl;
//
//	point<char*>ps("a", "b");
//	cout << ps.max() << endl;
//}


/* STL vector */
////vector////////////////////////////////////////////////////////////////////
//#include <iostream>
//#include <vector>
//using namespace std;
//
//template <typename T>
//ostream& operator << (ostream& os, vector<T>& v) {
//	os << "<";
//	for (int i = 0; i < v.size(); i++)
//		os << v[i] << " ";
//	os << ">";
//	return os;
//}
//void main()
//{
//	vector<int> vec(10);
//	for (int i = 0; i < vec.size(); i++)
//		vec[i] = rand() % 100;
//	cout << "Before: " << vec << endl;
//
//
//	for (vector<int>::iterator it = vec.begin(); it != vec.end(); ) {
//		if (*it % 2 == 0)
//			it = vec.erase(it);
//		else ++it;
//	}
//	cout << "After : " << vec << endl;
//}

/* STL list (double linked list) */
//#include <iostream>
//#include <list>
//#include<string>
//using namespace std;
//
//template <typename T>
//void printContainer(T& v, string msg = "container") {
//	cout << msg << "<";
//	for (auto it = v.begin(); it != v.end(); ++it)
//		cout << *it << " ";
//	cout << ">\n";
//}
//int main()
//{
//	list<int> sortList;
//	for (int i = 0; i < 10; i++) {
//		int val = rand() % 100;
//		auto curr = sortList.begin();
//		for (; curr != sortList.end(); ++curr)
//			if (val >= *curr) break;
//		sortList.insert(curr, val);
//	}
//	printContainer(sortList, "Sorted List: ");
//	return 0;
//}

/* STL deque */
//#include <iostream>
//#include <deque>
//using namespace std;
//
//void main()
//{
//	deque<int> dq;
//	for (int i = 0; i < 10; i++) {
//		int val = rand() % 100 + 1;
//		if (val % 2 == 0) dq.push_back(val);
//		else dq.push_front(val);
//	}
//	cout << "deque(�ε���): ";
//	for (int i = 0; i < dq.size(); i++)
//		cout << dq[i] << " ";
//
//	cout << endl << "deque(�ݺ���): ";
//	for (auto curr = dq.begin(); curr != dq.end(); ++curr)
//		cout << *curr << " ";
//	cout << endl;
//}


/* STL stack */
//#include <iostream>
//#include <stack>
//#include <string>
//using namespace std;
//
//void main()
//{
//	stack<char> st;
//	string line;
//	cout << "������ �Է��ϼ��� : ";
//	getline(cin, line);
//	for (int i = 0; i < line.length(); i++)
//		st.push(line[i]);
//	cout << "�Է� = " << line << endl;
//	cout << "��� = ";
//	while (!st.empty()) {
//		cout << st.top();
//		st.pop();
//	}
//	cout << endl;
//}


/* STL queue */
//#include <iostream>
//#include <queue>
//using namespace std;
//
//void main()
//{
//	queue<int> que;
//	int count;
//	cout << "�Ǻ���ġ ���� ������ �Է��ϼ���: ";
//	cin >> count;
//
//	cout << "�Ǻ���ġ ���� = ";
//	que.push(0);
//	que.push(1);
//	for (int i = 0; i < count; i++) {
//		int fibo = que.front();
//		que.pop();
//		cout << fibo << " ";
//		que.push(fibo + que.front());
//	}
//	cout << endl;
//}


///* STL priority queue */
//
/* STL set */
//#include <iostream>
//#include <set>
//using namespace std;
//
//
//template <typename T>
//void printContainer(T& v, const char* msg = "container") {
//	cout << msg << "<";
//	//for (T::iterator it = v.begin(); it != v.end(); ++it)
//	for (auto it = v.begin(); it != v.end(); ++it)
//		cout << *it << " ";
//	cout << ">\n";
//}
//
//void main()
//{
//	set<int> simple;		// �ߺ� ����
//	multiset<int> multiple;	// �ߺ� ���
//
//	for (int i = 10; i < 15; i++)
//		simple.insert(i);
//
//	multiple.insert(simple.begin(), simple.end());
//	for (int i = 13; i < 18; i++)
//		multiple.insert(i);
//
//	printContainer(simple, "Simple   Set = ");
//	printContainer(multiple, "Multiple Set = ");
//	cout << "simple.count(14)   = " << simple.count(14) << endl;
//	cout << "multiple.count(14) = " << multiple.count(14) << endl;
//}

/* STL map */
//map////////////////////////////////////////////////////////////////////
//
//#include <iostream>
//#include <iomanip>
//#include <map>
//#include <string>
//using namespace std;
//
//void main()
//{
//	map<string, string> myDic;
//	map<string, string>::iterator dp;
//	myDic["hello"] = "�ȳ��ϼ���?";
//	myDic["world"] = "�Ƹ��ٿ� ����";
//	myDic["data"] = "�ڷ�";
//	myDic["structure"] = "����";
//	myDic["list"] = "����Ʈ";
//
//	for (dp = myDic.begin(); dp != myDic.end(); ++dp)
//		cout << setw(12) << dp->first << " == " + dp->second + "\n";
//
//	dp = myDic.find("structure");
//	if (dp == myDic.end())
//		cout << "[�˻� ����] ã�� �ܾ �����ϴ�.\n";
//	else cout << "[�˻� ����] " << dp->first + " " + dp->second << endl;
//
//	if (myDic.find("C++") == myDic.end())
//		cout << "[�˻� ����] ã�� �ܾ �����ϴ�.\n";
//
//	myDic.erase("structure");
//
//	for (dp = myDic.begin(); dp != myDic.end(); ++dp)
//		cout << setw(12) << dp->first << " == " + dp->second + "\n";
//}