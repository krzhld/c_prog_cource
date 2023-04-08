#ifndef FUNCTIONS_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define EOB -3 //end of blocks
#define MAX 40

void** malloc_s(int size);
void free_s(void* memory);
int* firstFit(int* blockSize, int blocks, int* processSize, int processes);
void readFromFile(int* i_blockSize, int* i_processSize, int* blocks, int* processes);

#endif