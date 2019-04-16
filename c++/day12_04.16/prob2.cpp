#include <iostream>
#include <cstdlib>
using namespace std;
class Point
{
private:
	int xpos, ypos;
public:
	Point(int x = 0, int y = 0) : xpos(x), ypos(y) {  }
	friend ostream& operator<<(ostream& os, const Point& pos);
	friend ostream& operator<<(ostream& os, const Point* pos);
};
ostream& operator<<(ostream& os, const Point& pos)
{
	os << '[' << pos.xpos << ", " << pos.ypos << ']' << endl;
	return os;
}
ostream& operator<<(ostream& os, const Point* pos)
{
	os << '[' << pos->xpos << ", " << pos->ypos << ']' << endl;
	return os;
}
typedef Point * PP_T;
class PointHandler
{
private:
	PP_T * arr;
	int arrlen;
	PointHandler(const PointHandler& arr) { }
	PointHandler& operator=(const PointHandler& arr) { }
public:
	PointHandler(int len) :arrlen(len)//, arr(new PP_T[arrlen])
	{
		arr = new PP_T[len];
	}
	PP_T& operator[] (int idx)
	{
		return arr[idx];
	}
	PP_T operator[] (int idx) const
	{
		return arr[idx];
	}
	int GetArrLen() const
	{
		return arrlen;
	}
	~PointHandler()
	{
		delete[]arr;
	}
};
int main(void)
{
	PointHandler arr(3);
	arr[0] = new Point(3, 4);
	arr[1] = new Point(5, 6);
	arr[2] = new Point(7, 8);
	for (int i = 0; i < arr.GetArrLen(); i++)
		//cout << *(arr[i]); //cout<<arr[i]가 되어도 같은 출력이되도록 << 연산자를  오버로딩 하시오
		cout << arr[i];
	delete arr[0];
	delete arr[1];
	delete arr[2];
	return 0;
}


