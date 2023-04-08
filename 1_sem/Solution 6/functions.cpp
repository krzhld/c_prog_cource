#include "functions.h"

FILE_S* input_s;
FILE_S* output_s;

FILE_S* SystemInit(int buffer_size)
{
	FILE_S* fileobject = (FILE_S*)calloc(1, sizeof(FILE_S));
	fileobject->current = (char*)calloc(buffer_size + 1, sizeof(char));
	fileobject->end = fileobject->current + buffer_size + 1;
	fileobject->name = (FILE*)calloc(1, sizeof(FILE));
	return fileobject;
}

char* BufferInit(int buffer_size)
{
	char* buffer = (char*)calloc(buffer_size + 1, sizeof(char*));
	return buffer;
}

FILE_S* SystemClose()
{
	input_s->current = NULL;
	input_s->end = NULL;
	output_s->current = NULL;
	output_s->end = NULL;
	printf("System has been closed\n");
	return NULL;
}

FILE* open(char* name, const char* mode)
{
	FILE* opened_file = (FILE*)calloc(1, sizeof(FILE));
	opened_file = fopen(name, mode);
	return opened_file;
}

FILE* close()
{
	return NULL;
}

void read(FILE_S* file, void* buffer, int size_to_read)
{
	while ((file->end - file->current)&&(!feof(file->name)))
	{
		*file->current = fgetc(file->name);
		file->current++;
	}
	file->current--;
	*file->current = '\0';
	file->current = file->end - size_to_read - 1;
	buffer = memcpy(buffer, file->current, size_to_read);
	output_s = file;
}

void write(FILE_S* file, void* buffer, int size_to_write)
{
	file->current = (char*)memcpy(file->current, buffer, size_to_write);
	while (file->end - file->current)
	{
		fputc(*file->current, file->name);
		file->current++;
	}
	file->current = file->end - size_to_write - 1;
	input_s = file;
}