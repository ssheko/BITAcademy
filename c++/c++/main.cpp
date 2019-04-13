#include <iostream>

using namespace std;

void swap1(int *pa, int *pb)
{
	int tmp;
	tmp = *pa;
	*pa = *pb;
	*pb = tmp;
}

void swap2(int &rpa, int &rpb)
{
	int tmp;
	tmp = rpa;
	rpa = rpb;
	rpb = tmp;
}


int main()
{
	int a = 10, b = 5;

	swap1(&a, &b);
	cout << a << ' ' << b << endl;

	swap2(a, b);
	cout << a << ' ' << b << endl;

	return 0;
}