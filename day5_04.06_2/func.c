extern int passbook;	// 선언	// extern int passbook = 10; --> 정의

int get_bank()
{
	return passbook;	// withdraw
}

void set_bank()
{
	passbook++;	// deposit
}
