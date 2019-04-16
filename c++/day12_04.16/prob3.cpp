#include <iostream>
#include <cstring>
#pragma warning (disable:4996)

using namespace std;	
using std::cout;		


/* string 클래스 전체 만들기 */
class String
{
private:
	int len;
	char * str;
public:
	String();
	String(const char * s);
	String(const String& s);
	~String() {
		delete[] str;
	}
	String& operator= (const String& s);
	String& operator+= (const String& s);
	bool operator== (const String& s);
	String operator+ (const String& s);

	friend ostream& operator<< (ostream& os, const String& s);
	friend istream& operator>> (istream& is, String& s);
};

String::String()
{

}
String::String(const char *s) {	
	len = strlen(s);
	str = new char[len+1];
	strcpy(str, s);
}
String::String(const String& s) {
	len = s.len;
	str = new char[len + 1];
	strcpy(str, s.str);
}
String& String::operator= (const String& s) {
	len = s.len;
	delete[] str;

	str = new char[len + 1];
	strcpy(str, s.str);
	return *this;
}
String& String::operator+= (const String& s) {
	char *dststr = new char[len + 1];
	strcpy(dststr, str);
	len += s.len;
	delete[] str;
	str = new char[len + 1];
	strcpy(str, dststr);
	strcat(str, s.str);

	return *this;
	
		//(*this) = (*this) + s;
		//return (*this);
	
}
bool String::operator== (const String& s) {
	//return strcmp(str, s.str);
	if (len == s.len)
		return true;
	else
		return false;
}
String String::operator+ (const String& s) {
	//String newstr;
	//newstr.len = len + s.len;
	//newstr.str = new char[newstr.len +1];
	//int curr = 0;
	//for (int i = 0; i < len;i++) {
	//	newstr.str[curr++] = str[i];
	//}
	//for (int i = 0; i < s.len;i++) {
	//	newstr.str[curr++] = s.str[i];
	//}
	//newstr.str[curr] = '\n';
	//return newstr;
	char* dststr = new char[len + s.len + 1];
	strcpy(dststr, str);
	strcat(dststr, s.str);
	//String newstr(dststr);

	//return newstr;
	return String(dststr);
}
ostream& operator<< (ostream& os, const String& s) {
	os << s.str;
	return os;
}
istream& operator>> (istream& is, String& s) {
	char* buffer = new char[50];
	is >> buffer;
	s = String(buffer);
	delete[] buffer;
	//is >> s.str;
	return is;
}
int main(void)
{
	String str1 = "I like ";
	String str2 = "string class";
	String str3 = str1 + str2;

	cout << str1 << endl;
	cout << str2 << endl;
	cout << str3 << endl;

	str1 += str2;
	cout << str1 << endl;
	cout << str2 << endl;

	if (str1 == str3)
		cout << "동일 문자열!" << endl;
	else
		cout << "동일하지 않은 문자열!" << endl;

	String str4;
	cout << "문자열 입력: ";
	cin >> str4;
	cout << "입력한 문자열: " << str4 << endl;
	return 0;
}

