#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "sorts.h"

void PrintArray(int array[], int size)
{
    for (int i = 0; i < size; i++)
        printf("%d ", array[i]);
    printf("\n\n");
}

int main(void)
{
    int array0[] = { 1, 3, 2, 6, 13, 54, 12, 43, 74, 48, 56, 98, 76 };
    int array1[] = { 1, 3, 2, 6, 13, 54, 12, 43, 74, 48, 56, 98, 76 };
    int array2[] = { 1, 3, 2, 6, 13, 54, 12, 43, 74, 48, 56, 98, 76 };
    int array3[] = { 1, 3, 2, 6, 13, 54, 12, 43, 74, 48, 56, 98, 76 };
    int array4[] = { 1, 3, 2, 6, 13, 54, 12, 43, 74, 48, 56, 98, 76 };
    int array5[] = { 1, 3, 2, 6, 13, 54, 12, 43, 74, 48, 56, 98, 76 };
    int array6[] = { 1, 3, 2, 6, 13, 54, 12, 43, 74, 48, 56, 98, 76 };
    int array7[] = { 1, 3, 2, 6, 13, 54, 12, 43, 74, 48, 56, 98, 76 };
    int array8[] = { 1, 3, 2, 6, 13, 54, 12, 43, 74, 48, 56, 98, 76 };
    int array9[] = { 1, 3, 2, 6, 13, 54, 12, 43, 74, 48, 56, 98, 76 };
    int array10[] = { 1, 3, 2, 6, 13, 54, 12, 43, 74, 48, 56, 98, 76 };
    int array11[] = { 1, 3, 2, 6, 13, 54, 12, 43, 74, 48, 56, 98, 76 };
    int array12[] = { 1, 3, 2, 6, 13, 54, 12, 43, 74, 48, 56, 98, 76 };
    int array13[] = { 1, 3, 2, 6, 13, 54, 12, 43, 74, 48, 56, 98, 76 };
    int array14[] = { 1, 3, 2, 6, 13, 54, 12, 43, 74, 48, 56, 98, 76 };
    int array15[] = { 1, 3, 2, 6, 13, 54, 12, 43, 74, 48, 56, 98, 76 };
    int array16[] = { 1, 3, 2, 6, 13, 54, 12, 43, 74, 48, 56, 98, 76 };
    int array17[] = { 1, 3, 2, 6, 13, 54, 12, 43, 74, 48, 56, 98, 76 };
    int array18[] = { 1, 3, 2, 6, 13, 54, 12, 43, 74, 48, 56, 98, 76 };
    int array19[] = { 1, 3, 2, 6, 13, 54, 12, 43, 74, 48, 56, 98, 76 };
    int array20[] = { 1, 3, 2, 6, 13, 54, 12, 43, 74, 48, 56, 98, 76 };
    int array21[] = { 1, 3, 2, 6, 13, 54, 12, 43, 74, 48, 56, 98, 76 };
    int array22[] = { 1, 3, 2, 6, 13, 54, 12, 43, 74, 48, 56, 98, 76 };
    int array23[] = { 1, 3, 2, 6, 13, 54, 12, 43, 74, 48, 56, 98, 76 };
    int array24[] = { 1, 3, 2, 6, 13, 54, 12, 43, 74, 48, 56, 98, 76 };
    int array25[] = { 1, 3, 2, 6, 13, 54, 12, 43, 74, 48, 56, 98, 76 };
    int array26[] = { 1, 3, 2, 6, 13, 54, 12, 43, 74, 48, 56, 98, 76 };
    int size = sizeof(array0) / sizeof(array0[0]);

    printf("Original series\n");
    PrintArray(array0, size);

    /*SelectionSortExchange(array0, size);
    printf("SelectionSortExchange\n");
    PrintArray(array0, size);

    SelectionSortShift(array1, size);
    printf("SelectionSortShift\n");
    PrintArray(array1, size);

    InsertionSortFromLeftToRight(array2, size);
    printf("InsertionSortFromLeftToRight\n");
    PrintArray(array2, size);

    InsertionSortFromRightToLeft(array3, size);
    printf("InsertionSortFromRightToLeft\n");
    PrintArray(array3, size);

    InsertionSortBinary(array4, size);
    printf("InsertionSortBinary\n");
    PrintArray(array4, size);

    InsertionSortTwoWayWithAdditMemory(array5, size);
    printf("InsertionSortTwoWayWithAdditMemory\n");
    PrintArray(array5, size);

    BubbleSortDefault(array6, size);
    printf("BubbleSortDefault\n");
    PrintArray(array6, size);

    BubbleSortMinusOne(array7, size);
    printf("BubbleSortMinusOne\n");
    PrintArray(array7, size);

    BubbleSortStopIfThereWerentShifts(array8, size);
    printf("BubbleSortStopIfThereWerentShifts\n");
    PrintArray(array8, size);

    CocktailSort(array9, size);
    printf("CocktailSort\n");
    PrintArray(array9, size);

    CombSort(array10, size);
    printf("CombSort\n");
    PrintArray(array10, size);

    ShellSortOrig(array11, size);
    printf("ShellSortOrig\n");
    PrintArray(array11, size);

    ShellSortHibbord(array12, size);
    printf("ShellSortHibbord\n");
    PrintArray(array12, size);*/

    ShellSortSedgewick(array13, size);
    printf("ShellSortSedgewick\n");
    PrintArray(array13, size);

    ShellSortPratt(array14, size);
    printf("ShellSortPratt\n");
    PrintArray(array14, size);

    /*MergeSortDepthFirst(array15, size);
    printf("MergeSortDepthFirst\n");
    PrintArray(array15, size);

    MergeSortBreathFirst(array16, size);
    printf("MergeSortBreathFirst\n");
    PrintArray(array16, size);

    QuickSortLomuto(array17, size);
    printf("QuickSortLomuto\n");
    PrintArray(array17, size);

    QuickSortHoara(array18, size);
    printf("QuickSortHoara\n");
    PrintArray(array18, size);

    HeapSortUp(array19, size);
    printf("HeapSortUp\n");
    PrintArray(array19, size);

    HeapSortDown(array20, size);
    printf("HeapSortDown\n");
    PrintArray(array20, size);

    CountingSortBasic(array21, size);
    printf("CountingSortBasic\n");
    PrintArray(array21, size);

    CountingSortWithKey(array22, size);
    printf("CountingSortWithKey\n");
    PrintArray(array22, size);

    CountingSortAlternative(array23, size);
    printf("CountingSortAlternative\n");
    PrintArray(array23, size);

    RadixSort(array24, size);
    printf("RadixSort\n");
    PrintArray(array24, size);

    BucketSort(array25, size);
    printf("BucketSort\n");
    PrintArray(array25, size);*/

    return 0;
}