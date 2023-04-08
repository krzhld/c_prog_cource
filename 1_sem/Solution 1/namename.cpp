#include <stdafx.h>
#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>

#define LENGTH 256
#define SIGN 60 // это знак "меньше"

#define TRUE 1
#define FALSE 0

int main(void)
{
	setlocale(LC_ALL, "RUSSIAN");
	char inputString[LENGTH];
	char outputString[LENGTH];
	char fieldForLetters[LENGTH];
	int counter = 0;
	int i;
	int isAnyLetter = FALSE;

	printf("¬ведите строку из не более чем 255 символов\n");
	gets(inputString); //перва€ строчка заполн€етс€, втора€ строчка - наш ответ
	if (strlen(inputString) < LENGTH)
    {
		for (i = 0; i < strlen(inputString); ++i)
		{
            if (isalpha(inputString[i]) != FALSE)
            {
                fieldForLetters[counter] = inputString[i];
                outputString[i] = SIGN;
                counter++;
                isAnyLetter = TRUE;
            }
            else
                outputString[i] = inputString[i];
		}
        if (isAnyLetter == TRUE)
            counter--;
        for (i = 0; i < strlen(inputString); ++i)
        {
            if (outputString[i] == SIGN)
            {
			outputString[i] = fieldForLetters[counter];
			counter--;
            }
        }
  outputString[i] = 0;
	puts(outputString);
	}
	else printf("Ќу € же просил...");
	getch();
	return 0;
}
