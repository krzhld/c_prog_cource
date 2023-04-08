#include "Assert.h"
#include <stdlib.h>
#include <stdio.h>
#include "mathfunctions.h"

int main(void)
{
    int error[2];
    double number = 0;

    #ifdef _DEBUG
    int numberAsserts;
    printf("Insert the number of asserts: ");
    scanf_s("%d", &numberAsserts);
    printf("\n");
    SystemOpen(numberAsserts);
    #endif

    ASSERT(0 < -1, "first type\n");

    printf("Insert the natural number: ");
    scanf_s("%lf", &number);
    printf("\n");

    ASSERT(0 < -1, "first type\n");
    ASSERT(0 < -1, "second type\n");

    error[0] = FATALERROR(number > 0, "Nonpositive number!\n", 2);
    error[1] = FATALERROR((number - (int)number) == 0, "Float number!\n", 3);

    if (error[0] != 0 || error[1] != 0)
    {
        SystemClose();
        return error;
    }

    printf("answer = %lf\n", square_root(number));

    return 0;
    
}