#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAMESIZE 64
#define READ "r"
#define WRITE "w"

typedef struct
{
	char* current;
	char* end;
	FILE* name;
} FILE_S;

FILE_S* SystemInit(int buffer_size);

char* BufferInit(int buffer_size);

FILE_S* SystemClose();

FILE* open(char* name, const char* mode);

FILE* close();

void read(FILE_S* file, void* buffer, int size_to_read);

void write(FILE_S* file, void* buffer, int size_to_write);

#endif FUNCTIONS_H_INCLUDED