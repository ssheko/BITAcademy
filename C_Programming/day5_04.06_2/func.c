extern int passbook;	// ����	// extern int passbook = 10; --> ����

int get_bank()
{
	return passbook;	// withdraw
}

void set_bank()
{
	passbook++;	// deposit
}
