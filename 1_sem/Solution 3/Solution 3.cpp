#include "stdafx.h"
#include <stdio.h>
#include <locale.h>
#include <conio.h>

#define TRUE 1
#define FALSE 0

int binary_length(int x) 
{
	int len = 0;
	while (x >> len != 0)
			++len;
	return len;
}

int main(void)
{
	setlocale(LC_ALL, "RUSSIAN");

	int n, i, j, length = 0, flag, current, mask;
	printf("¬ведите натуральное число n: ");
	scanf("%d", &n);
	if (n > 0)
	{
		printf("1\n");
		for (i = 3; i <= n; i += 2)
		{
			flag = TRUE;
			j = 1;
			length = binary_length(i);
			current = i;
			if (length % 2 == 0) 
			{
				mask = (i >> length/2) << length/2;
				current = (mask << 1) + (i - mask);
			} 
			while ((flag == TRUE)&&(j <= length/2)) 
			{
				if (((current >> (length/2-j)) % 2) != ((current >> (length/2+j)) % 2))
					flag = FALSE;
				++j;
			}
			if (flag == TRUE) 
				printf("%d\n", i);
		}
	}
	else 
		printf("ќшибка: введено не натуральное число.\n"); 
	getch();
	return 0;
}