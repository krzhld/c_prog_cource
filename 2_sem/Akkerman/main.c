#include <stdio.h>

long int Akk(int m, int n)
{
	if (m == 0)
		return n + 1;
	if (m > 0 && n == 0)
		return Akk(m - 1, 1);
	if (m > 0 && n > 0)
		return Akk(m - 1, Akk(m, n - 1));
}

int main(void)
{
	printf("%ld", Akk(3, 10));
	return 0;
}