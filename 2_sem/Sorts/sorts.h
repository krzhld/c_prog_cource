#pragma once
#include <string.h>

#define swap(a, b) {int tmp = a; a = b; b = tmp;}

int Power(int a, int n);

void SelectionSortExchange(int array[], int size);

void SelectionSortShift(int array[], int size);

void InsertionSortFromLeftToRight(int array[], int size);

void InsertionSortFromRightToLeft(int array[], int size);

void InsertionSortBinary(int array[], int size);

void InsertionSortTwoWayWithAdditMemory(int array[], int size);

void BubbleSortDefault(int array[], int size);

void BubbleSortMinusOne(int array[], int size);

void BubbleSortStopIfThereWerentShifts(int array[], int size);

void CocktailSort(int array[], int size);

void CombSort(int array[], int size);

void ShellSortOrig(int array[], int size);

void ShellSortHibbord(int array[], int size);

void ShellSortSedgewick(int array[], int size);

void ShellSortPratt(int array[], int size);

void Merge(int array[], int size);

void MergeSortDepthFirst(int array[], int size);

void MergeSortBreathFirst(int arr[], int size);

void QuickSortLomuto(int array[], int size);

void QuickSortHoara(int array[], int size);

void HeapSortUp(int array[], int size);

void HeapSortDown(int array[], int size);

void CountingSortBasic(int array[], int size);

void CountingSortWithKey(int array[], int size);

void CountingSortAlternative(int array[], int size);

int RankGetter(int number, int digitBase, int rank);

int GetMax(int array[], int size);

void RadixSort(int array[], int size);

void BucketSort(int array[], int size);