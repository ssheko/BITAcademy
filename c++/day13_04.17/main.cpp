#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <string>
#pragma warning (disable:4996)

using namespace std;	// using 지시문
using std::cout;		// using 선언

/* 템플릿 */
//template <typename T> T add(T a, T b) {} // 함수템플릿	// 함수를 찍어내는 템플릿
//add<int>(10, 20); // 템함 호출
//add(10, 20); // 템함 호출
//int add<char>(char a, char b){}// 함템에 의해 만들어진 템함
//template<>char* add(char *a, char *b){} //함템특수화			앞의 template 생략 불가. add 뒤의 <> 생략 가능
//template<>char* add<>(char *a, char *b) {} //함템특수화
//template<>char* add<char*>(char *a, char *b) {} //함템특수화
//------------------------------------------------------------
//template <typenae T> class point {} //클래스템플릿	// 클래스를 찍어내는 템플릿
//template <typenae T> class point { pubic: T add(T a, T b); } //클템안의 멤버함수 선언	// add 함수의 리턴 타입 T
//template <typenae T> T point<T>::add(T a, T b) {} //클템안의 멤버함수 정의				// point 안의 add함수의 리턴 타입T	// typename T, <T>, (T a, T b)	==> 두 가지의 T의 의미가 다름
//point<int> ob(3, 4);
//point<other*> ob(3, 4);
//point<other<int>*> ob(3, 4);  //typedef other<int>* TTR;
//template <>class point<int>{};//클템특수화		// class point<int> 의 <int> 생략 불가
//template <>class point<int, char> {};//클템특수화
//template <typename T> class point<T, char> {};//클템부분특수화
//template <typename T, int size> class point{};//클템 인자
//template <typename T=int, int size=10> class point {};//클템 디폴트인자
//template <typename T, typename T>   T func2(T a, T b);  // 에러, T가 중복 선언 
//template <typename T, typename U, typename V>   U func2(T a, V b);  // 에러, U가 가인수로 사용되지 않음	// 매개변수 타입에 U가 있어야 한다. 리턴타입의 U와는 상관 없음.

/*
	모든 타입에 대한 2개의 수를 더하는 add 함수 템플릿 구현
	예외로 string형일 경우 함수 템플릿 특수화로 구현
	두 문자열을 붙이시오
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
	두 점을 표시하는 fir와 sec을 멤버변수를 가진 클래스 템플릿을 정의하시오.
	멤버함수로 max를 호출할 경우 큰 값을 출력하시오.

	만약 두 점이 char *으로 전달될 경우 클래스 템플릿 특수화를 구현하여
	멤버함수로 max는 두 char * 중 알파벳 순이 큰 값을 출력하시오.
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
//	cout << "deque(인덱스): ";
//	for (int i = 0; i < dq.size(); i++)
//		cout << dq[i] << " ";
//
//	cout << endl << "deque(반복자): ";
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
//	cout << "문장을 입력하세요 : ";
//	getline(cin, line);
//	for (int i = 0; i < line.length(); i++)
//		st.push(line[i]);
//	cout << "입력 = " << line << endl;
//	cout << "출력 = ";
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
//	cout << "피보나치 수의 개수를 입력하세요: ";
//	cin >> count;
//
//	cout << "피보나치 수열 = ";
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
//	set<int> simple;		// 중복 없음
//	multiset<int> multiple;	// 중복 허용
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
//	myDic["hello"] = "안녕하세요?";
//	myDic["world"] = "아름다운 세상";
//	myDic["data"] = "자료";
//	myDic["structure"] = "구조";
//	myDic["list"] = "리스트";
//
//	for (dp = myDic.begin(); dp != myDic.end(); ++dp)
//		cout << setw(12) << dp->first << " == " + dp->second + "\n";
//
//	dp = myDic.find("structure");
//	if (dp == myDic.end())
//		cout << "[검색 실패] 찾는 단어가 없습니다.\n";
//	else cout << "[검색 성공] " << dp->first + " " + dp->second << endl;
//
//	if (myDic.find("C++") == myDic.end())
//		cout << "[검색 실패] 찾는 단어가 없습니다.\n";
//
//	myDic.erase("structure");
//
//	for (dp = myDic.begin(); dp != myDic.end(); ++dp)
//		cout << setw(12) << dp->first << " == " + dp->second + "\n";
//}