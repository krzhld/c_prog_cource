#define _CRT_SECURE_NO_WARNINGS 
#pragma once
#include <string.h>

#define TRUE 1
#define FALSE 0

#define FILENAME (strrchr(__FILE__, '\\') + 1) 

#ifdef _DEBUG
void Assert(int condition, const char* message, const char* fileName, int line);
#define ASSERT(condition, message) \
Assert(condition, message, FILENAME, __LINE__);
#endif

#ifdef NDEBUG
#define ASSERT(condition, message)
#endif

#define FATALERROR(condition, message, returnValue) \
FatalError(condition, message, returnValue, FILENAME, __LINE__);

int FatalError(int condition, const char* message, int returnValue, const char* fileName, int line);

void SystemOpen(int numberAsserts);

void SystemClose(void);