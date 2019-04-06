typedef struct tag {
	int fir;
	int sec;
}TAG;

TAG put(int a, int b)
{
	TAG tmp;

	tmp.fir = a;
	tmp.sec = b;
	return tmp;
}