#include "stdafx.h"
#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <malloc.h>
#include <conio.h>

#define MAXLENGTH 256
#define _CRT_SECURE_NO_WARNINGS

int main()
{
	setlocale(LC_ALL, "RUSSIAN");

	char nameOfFile[MAXLENGTH] = { 0 };
	printf("������� ��� �����: ");
	scanf("%s", &nameOfFile);

	printf("\n������� ��������� ����� ������: ");
	int stringLength;
	scanf("%d", &stringLength);
	printf("\n");

	/* ����������� ��������� �� ������ ��� ����� */
	FILE *filePoint = NULL;
	filePoint = fopen(nameOfFile, "r");

	int fileLength = 0;
	while( fgetc(filePoint) != EOF )
		fileLength++;

	/* �������� ������ ��� ��������� ������ */
	char *fileString;
	fileString = (char *)calloc(fileLength + 1, sizeof(char)); 
	
	/* ���������� ��������� ������� � ������ �� ������ ������*/
	fseek(filePoint, -fileLength, SEEK_END); 

	/* ��������� � ��������� ������ */
	int i;
	for (i = 0; i < fileLength; i++)
		fileString[i] = fgetc(filePoint);
	i = 0;

	/* ������� ����� */
	int current = 0;
	int lastSpace0 = 0;
	int lastSpace1 = 0;
	while (fileLength - current > stringLength)
	{
		lastSpace0 = lastSpace1;
		lastSpace1 += stringLength;
		for (i = current; i < current + stringLength; i++)
			if (fileString[i] == ' ')
				lastSpace1 = i + 1;
		for (i = current; i < lastSpace1; i++)
			printf("%c", fileString[i]);
		current += (lastSpace1 - lastSpace0);
		printf("\n");
	}
	if (fileLength != current) 
		for (i = current; i < fileLength; i++)
			printf("%c", fileString[i]);
	printf("\n");

	fclose(filePoint);
	getch();
	return 0;
}

