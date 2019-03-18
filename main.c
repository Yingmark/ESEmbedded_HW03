void reset_handler(void)
{	
	func1(1,2,3);
	while (1)
		;
}

void func1(int a, int b, int c)
{
	return a+b+c;
}
