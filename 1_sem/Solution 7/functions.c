#include "functions.h"

void** malloc_s(int size)
{
	void** ptr;
	ptr = (void**)malloc(sizeof(int*)*4);
	ptr[0] = malloc(sizeof(int));
	ptr[1] = malloc(sizeof(int));
	ptr[2] = malloc(size*sizeof(int));
	ptr[3] = malloc(size*sizeof(int));
	return ptr;
}

void free_s(void* memory)
{
	memory = NULL;
}

int* firstFit(int* blockSize, int blocks, int* processSize, int processes)
{
	int* allocation = (int*)calloc(processes, sizeof(int));
	memset(allocation, -1, processes*sizeof(int));

	int* ptr_blockSize = (int*)calloc(blocks, sizeof(int));
	memcpy(ptr_blockSize, blockSize, blocks*sizeof(int));

	for (int process = 0; process < processes; process++)
	{
		for (int block = 0; block < blocks; block++)
		{
			if (ptr_blockSize[block] >= 5*processSize[process])
			{
				ptr_blockSize = (int*)realloc(ptr_blockSize, (blocks + 1)*sizeof(int));
				allocation[process] = block;
				ptr_blockSize[blocks] = ptr_blockSize[block] / 5;
				ptr_blockSize[block] -= ptr_blockSize[blocks];
				ptr_blockSize[block] -= processSize[process];
				blocks++;
				break;
			}
			else if (ptr_blockSize[block] >= processSize[process])
			{
				allocation[process] = block;
				ptr_blockSize[block] -= processSize[process];
				break;
			}
		}
	}

	ptr_blockSize[blocks] = EOB;

	printf("\nProccess No.\tProcess Size\tBlock no.\n");

	for (int i = 0; i < processes; i++)
	{
		printf("%d:\t\t%d\t\t", i+1, *(processSize+i));
		if (*(allocation+i) != -1)
			printf("%d\n", *(allocation + i)+1);
		else
			printf("Not allocated\n");
	}
	printf("\n");
	free(allocation);
	return ptr_blockSize;
}

void readFromFile(int* i_blockSize, int* i_processSize, int* i_blocks, int* i_processes)
{
	int blocks, processes;

	FILE* fp = fopen("source.txt", "rt");
	if (fp == NULL)
		printf("Error reading\n");
	fseek(fp, 0, SEEK_SET);

	fscanf(fp, "%d", i_blocks);

	for (int i = 0; i < *i_blocks; i++)
		fscanf(fp, "%d", i_blockSize+i);

	fscanf(fp, "%d", i_processes);


	for (int i = 0; i < *i_processes; i++)
		fscanf(fp, "%d", i_processSize+i);

	fclose(fp);
}