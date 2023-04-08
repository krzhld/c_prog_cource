#include "Assert.h"
#include <stdlib.h>
#include <stdio.h>

struct {
	int curNumberAsserts;
	int maxNumberAsserts;
	char** messages;
} systemAsserts = { 0, 0, NULL };

void Assert(int condition, const char* message, const char* fileName, int line)
{
	static int isSkipped = FALSE;

	if (isSkipped)
		return;

	for (int i = 0; i < systemAsserts.curNumberAsserts; ++i)
	{
		if (!strcmp(systemAsserts.messages[i], message))
			return;
	}

	if (systemAsserts.curNumberAsserts >= systemAsserts.maxNumberAsserts || systemAsserts.maxNumberAsserts == 0)
	{
		printf("Too much asserts\n");
		exit(1);
	}

	if (!condition)
	{
		printf("Assert in %s on line %d \nmessage: %s", fileName, line, message);

		printf("What you'd like to do? \n"
		"1: skip this assert next time \n"
		"2: skip all asserts \n"
		"3: quit program \n");

		int answer = 0;
		while (answer != 1 && answer != 2 && answer != 3)
		{
			scanf("%d", &answer);
			printf("\n");
			
			switch (answer)
			{
			case 1:
				++systemAsserts.curNumberAsserts;
				char** buffer = (char**)realloc(systemAsserts.messages, systemAsserts.curNumberAsserts * sizeof(char*));
				if (buffer == NULL)
				{
					printf("MemoryError \n");
					exit(2);
				}
				else
					systemAsserts.messages = buffer;

				systemAsserts.messages[systemAsserts.curNumberAsserts - 1] = (char*)calloc(strlen(message) + 1, sizeof(char));
				if (systemAsserts.messages[systemAsserts.curNumberAsserts - 1] == NULL)
				{
					printf("MemoryError \n");
					exit(2);
				}
				sprintf(systemAsserts.messages[systemAsserts.curNumberAsserts - 1], "%s", message);
				
				break;
			case 2:
				isSkipped = TRUE;
				return;
				break;
			case 3:
				exit(0);
				break;
			}
		}


	}
}

int FatalError(int condition, const char* message, int returnValue, const char* fileName, int line)
{
	if (!condition)
	{
		printf("FatalError in %s on line %d \nmessage: %s", fileName, line, message);
		return returnValue;
	}
	return 0;
}

void SystemOpen(int numberAsserts)
{
	systemAsserts.maxNumberAsserts = numberAsserts;
}

void SystemClose(void)
{
	if (systemAsserts.messages != NULL)
		free(systemAsserts.messages);
}