#include "functions.h"

int main(void)
{
	printf("Insert how many symbols you'd like to read and write\n");
	int size;
	scanf("%d", &size);

	char name[NAMESIZE];
	void* my_buffer = BufferInit(size);

	printf("How many files you'd like to read\n");
	int number_files;
	scanf("%d", &number_files);

	FILE_S* readfile = NULL;
	FILE_S* writefile = NULL;

	readfile = SystemInit(size); 
	writefile = SystemInit(size);

	/*main loop*/
	while (number_files--)
	{
		printf("-----------------------------------------------------\n");
		do 
		{
			printf("Insert the name of file to read with .txt\n");
			scanf("%s", name);
			readfile->name = open(name, READ);
		}
		while(readfile->name == NULL);
		read(readfile, my_buffer, size);

		printf("Insert the name of file to write\n");
		scanf("%s", name);
		writefile->name = open(name, WRITE);

		write(writefile, my_buffer, size);

		readfile->name = close();
		writefile->name = close();
	}
	my_buffer = close();
	readfile = SystemClose();
	writefile = readfile;
	getchar();
	return 0;
}