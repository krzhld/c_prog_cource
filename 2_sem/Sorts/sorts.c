#include <stdlib.h>
#include "sorts.h"
#include <math.h>

int Power(int a, int n)
{
	int ans = 1;
	for (int i = 0; i < n; i++)
		ans *= a;
	return ans;
}

void SelectionSortExchange(int array[], int size)
{
	int tmp = 0;
	int minPos = 0;
	for (int i = 0; i < size; i++)
	{
		minPos = i;
		for (int j = i + 1; j < size; j++)
			if (array[minPos] > array[j])
				minPos = j;

		swap(array[minPos], array[i]);
	}
}

void SelectionSortShift(int array[], int size)
{
	int tmp = 0;
	int minPos = 0;
	for (int i = 0; i < size; i++)
	{
		minPos = i;
		for (int j = i + 1; j < size; j++)
			if (array[minPos] > array[j])
				minPos = j;

		for (int counter = 0; counter < minPos - i; counter++)
		{
			tmp = array[i];
			for (int k = i; k < size; k++)
				array[k] = array[k + 1];
			array[size - 1] = tmp;
		}
	}
}

void InsertionSortFromLeftToRight(int array[], int size)
{
	int tmp;
	for (int i = 1; i < size; i++)
	{
		tmp = array[i];
		for (int j = 0; j < i; j++)
		{
			if (tmp < array[j])
			{
				array[i] = array[i - 1];
				for (int k = i - 1; k > j; k--)
					array[k] = array[k - 1];
				array[j] = tmp;
				break;
			}
		}
	}
}

void InsertionSortFromRightToLeft(int array[], int size)
{
	int tmp;
	for (int i = size - 2; i >= 0; i--)
	{
		tmp = array[i];
		for (int j = size - 1; j > i; j--)
		{
			if (tmp > array[j])
			{
				array[i] = array[i + 1];
				for (int k = i; k < j; k++)
					array[k] = array[k + 1];
				array[j] = tmp;
				break;
			}
		}
	}
}

void InsertionSortBinary(int array[], int size)
{
	int index, tmp, l, r, mid;
	for (int i = 1; i < size; i++)
	{
		index = i;
		r = i - 1;
		l = 0;

		while (l <= r)
		{
			mid = (l + r) / 2;
			if (array[i] < array[mid])
			{
				r = mid - 1;
				index = mid;
			}
			else
				l = mid + 1;
		}

		tmp = array[i];
		for (int j = i; j > index; j--)
			array[j] = array[j - 1];
		array[index] = tmp;
	}
}

// ???
void InsertionSortTwoWayWithAdditMemory(int array[], int size)
{
	int med = 0;
	int left = 0;
	int right = 0;

	for (int i = 1; i < size; i++)
	{
		if (array[i] < array[med])
		{
			int k;
			for (k = 1; k <= left; k++)
				if (array[med - k] <= array[i])
					break;
			k--;

			int tmp = array[med + right + 1];
			memcpy(array + (med - k + 1), array + (med - k), (right + k + 1) * sizeof(int));
			array[med - k] = tmp;
			left++;
			med++;
		}
		else
		{
			int k;
			for (k = 1; k <= right; k++)
				if (array[med + k] >= array[i])
					break;
			k--;

			int tmp = array[med + right + 1];
			memcpy(array + (med + k + 2), array + (med + k + 1), (right - k) * sizeof(int));
			array[med + k + 1] = tmp;
			right++;
		}
	}
}

void BubbleSortDefault(int array[], int size)
{
	int tmp = 0;
	for (int i = 0; i < size - 1; i++)
		for (int j = i; j < size - 1; j++)
			if (array[j] > array[j + 1])
			{
				tmp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = tmp;
			}

}

void BubbleSortMinusOne(int array[], int size)
{
	int tmp = 0;
	for (int i = 0; i < size - 1; i++)
		for (int j = 0; j < size - 1 - i; j++)
			if (array[j] > array[j + 1])
			{
				tmp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = tmp;
			}
}

void BubbleSortStopIfThereWerentShifts(int array[], int size)
{
	int tmp = 0;
	int flag = 0;
	for (int i = 0; i < size - 1; i++)
	{
		flag = 0;
		for (int j = 0; j < size - 1 - i; j++)
		{
			if (array[j] > array[j + 1])
			{
				tmp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = tmp;
				flag = 1;
			}
		}
		if (flag == 0)
			break;
	}

}

void CocktailSort(int array[], int size)
{
	int tmp = 0;
	int flag = 0;
	int l = 0;
	int r = size - 1;
	while (1)
	{
		if (l >= r)
			break;

		flag = 0;
		for (int i = l; i < r; i++)
			if (array[i] > array[i + 1])
			{
				tmp = array[i];
				array[i] = array[i + 1];
				array[i + 1] = tmp;
				flag = 1;
			}

		if (flag == 0)
			break;

		r--;
		flag = 0;
		for (int i = r; i > l; i--)
			if (array[i] < array[i - 1])
			{
				tmp = array[i];
				array[i] = array[i - 1];
				array[i - 1] = tmp;
				flag = 1;
			}

		if (flag == 0)
			break;

		l++;
	}
}

void CombSort(int array[], int size)
{
	const float dstep = 1.3f;

	int step = (int)(size / dstep);
	int cur = 0; // текущий левый сосед
	int tmp = 0;

	while (step >= 1)
	{
		if (cur + step < size)
		{
			if (array[cur] > array[cur + step]);
							cur++;
		}
		else
		{
			cur = 0;
			step = (int)(step / dstep);
		}
	}
}

void ShellSortOrig(int array[], int size)
{
	int delta = size / 2;
	int tmp = 0;

	while (delta >= 1)
	{
		for (int i = 0; i < delta; i++)
		{
			for (int j = i + delta; j < size; j += delta)
			{
				int k = j;
				while ((k - delta >= 0) && (array[k] < array[k - delta]))
				{
					tmp = array[k];
					array[k] = array[k - delta];
					array[k - delta] = tmp;
					k -= delta;
				}
			}
		}
		delta /= 2;
	}
}

void ShellSortHibbord(int array[], int size)
{
	int delta = 0;
	int n = 0;
	while ((int)pow(2, n) - 1 < size)
		++n;
	--n;
	delta = pow(2, n) - 1;

	int tmp = 0;

	while (delta >= 1)
	{
		for (int i = 0; i < delta; i++)
		{
			for (int j = i + delta; j < size; j += delta)
			{
				int k = j;
				while ((k - delta >= 0) && (array[k] < array[k - delta]))
				{
					tmp = array[k];
					array[k] = array[k - delta];
					array[k - delta] = tmp;
					k -= delta;
				}
			}
		}
		delta = ((delta + 1) / 2) - 1;
	}
}

void ShellSortSedgewick(int array[], int size)
{
	int delta = 0;
	int p = 1;
	while (Power(4, p) + 3 * Power(2, p - 1) + 1 < size)
		++p;
	--p;
	delta = Power(4, p) + 3 * Power(2, p - 1) + 1;

	int tmp = 0;

	while (delta >= 1)
	{
		for (int i = 0; i < delta; i++)
		{
			for (int j = i + delta; j < size; j += delta)
			{
				int k = j;
				while ((k - delta >= 0) && (array[k] < array[k - delta]))
				{
					tmp = array[k];
					array[k] = array[k - delta];
					array[k - delta] = tmp;
					k -= delta;
				}
			}
		}
		--p;
		if (p == 0)
			delta = 1;
		if (p == -1)
			return;
		if (p > 0)
			delta = Power(4, p) + 3 * Power(2, p - 1) + 1;
	}
}

// wasnt written and i dont want to write
void ShellSortPratt(int array[], int size)
{

}

void Merge(int array[], int size)
{
	int i = 0;
	int k = size / 2;
	int buffIter = 0;
	int* buff = (int*)malloc(size * sizeof(int));
	while ((i < size / 2) && (k < size))
	{
		if (array[i] > array[k])
		{
			buff[buffIter] = array[k];
			k++;
		}
		else
		{
			buff[buffIter] = array[i];
			i++;
		}
		buffIter++;
	}
	while (i < size / 2)
	{
		buff[buffIter] = array[i];
		i++;
		buffIter++;
	}
	while (k < size)
	{
		buff[buffIter] = array[k];
		k++;
		buffIter++;
	}

	memcpy(array, buff, size * sizeof(int));
	free(buff);
}

void MergeSortDepthFirst(int array[], int size)
{
	if (size > 2)
	{
		MergeSortDepthFirst(array, size / 2);
		MergeSortDepthFirst(array + size / 2, size - size / 2);
	}
	Merge(array, size);
}

void MergeSortBreathFirst(int array[], int size) 
{

	int* buff = (int*)malloc(size * sizeof(int));
	memset(buff, '\0', size * sizeof(int));

	int max_size = 2;

	// max_size - максимальный размер подмасива в "слое" обязательно содержит 2 отсортированных массива
	// первый от l_iter до middle_border второй от middle_border до end_border.

	for (int i = 0; i < 4; i++) // вместо 4 (целая часть логарифма size'а по основанию 2) + 1
	{
		int buff_iter = 0;
		for (int k = 0; k < size; k += max_size) 
		{


			//расчёт границ
			int small_arr_size = max_size / 2;

			int middle_border = k + small_arr_size;
			int end_border = k + max_size;
			if (end_border >= size)
				end_border = size;

			int l_iter = k;
			int r_iter = middle_border;

			while (l_iter < middle_border && r_iter < end_border) 
			{
				if (array[l_iter] >= array[r_iter])
				{
					buff[buff_iter] = array[r_iter];
					r_iter++;
				}
				else 
				{
					buff[buff_iter] = array[l_iter];
					l_iter++;
				}
				buff_iter++;
			}

			while (l_iter < middle_border) 
			{
				buff[buff_iter] = array[l_iter];
				l_iter++;
				buff_iter++;
			}

			while (r_iter < end_border) 
			{
				buff[buff_iter] = array[r_iter];
				r_iter++;
				buff_iter++;
			}

		}
		memcpy(array, buff, size * sizeof(int));
		memset(buff, '\0', size * sizeof(int)); //это необязательная операция. Необходима для красивого вывода
		max_size *= 2;
	}
}

void QuickSortLomuto(int array[], int size)
{
	if (size < 2)
		return;

	int pivot = array[size - 1];
	int w = 0;
	int r = 0;
	while (r < size)
	{
		if (array[r] < pivot)
		{
			swap(array[r], array[w]);
			w++;
		}
		r++;
	}

	swap(array[w], array[size - 1]);
	QuickSortLomuto(array, w);
	QuickSortLomuto(array + w + 1, size - w - 1);
}

void QuickSortHoara(int array[], int size)
{
	if (size < 2)
		return;

	int l = 0;
	int r = size - 2;

	int pivot = array[size - 1];

	while (l <= r)
	{
		while (array[l] < pivot)
			l++;
		while ((r >= 0) && (array[r] >= pivot))
			r--;

		if ((l < r) && (array[l] >= pivot) && (array[r] < pivot))
			swap(array[l], array[r]);
	}
	swap(array[l], array[size - 1]);

	QuickSortHoara(array, l);
	QuickSortHoara(array + l + 1, size - l - 1);
}

// ?? and doesnt work
void HeapSortUp(int array[], int size)
{
	for (int unsorted = size; unsorted > 0; unsorted--) {
		for (int k = unsorted / 2 - 1; k >= 0; k--) {
			// parent: arr[k]
			// left_node: arr[k*2 + 1]
			// right_node: arr[k*2 + 2]

			if (unsorted % 2) {
				if (array[k * 2 + 1] < array[k * 2 + 2]) {
					if (array[k * 2 + 2] > array[k])
						swap(array[k * 2 + 2], array[k]);
				}
			}

			if (array[k * 2 + 1] > array[k])
				swap(array[k * 2 + 1], array[k]);

		}
		swap(array[0], array[unsorted - 1]);

	}
}

void FormHeap(int array[], int size)
{
	int root = 0;

	for (int i = size - 1; i > 0; i--)
	{
		if (i % 2)
			root = (i - 1) / 2;
		else
			root = (i - 2) / 2;
		if (array[root] < array[i])
			swap(array[root], array[i]);
	}
}

void HeapSortDown(int array[], int size)
{
	FormHeap(array, size);
	for (int i = size - 1; i >= 0; i--)
	{
		swap(array[0], array[i]);
		FormHeap(array, i);
	}
}

void CountingSortBasic(int array[], int size)
{
	int maxVal = 0;
	for (int i = 0; i < size; i++)
		if (maxVal < array[i])
			maxVal = array[i];

	maxVal++;

	int* countArray = (int*)calloc(maxVal, sizeof(int));

	for (int i = 0; i < size; i++)
		countArray[array[i]]++;

	for (int i = 1; i < maxVal; i++)
		countArray[i] += countArray[i - 1];

	int* newArray;

	if ((newArray = (int*)calloc(size, sizeof(int))) != NULL)
	{
		for (int i = 0; i < size; i++)
		{
			countArray[array[i]]--;
			newArray[countArray[array[i]]] = array[i];
		}
		
		memcpy(array, newArray, size * sizeof(int));
	}

	free(newArray);
	free(countArray);
}

void CountingSortWithKey(int array[], int size)
{
	int max = array[0];
	for (int i = 0; i < size; i++)
		if (array[i] > max)
			max = array[i];

	int* countArray = (int*)calloc(max + 1, sizeof(int));
	if (countArray != NULL)
	{
		for (int i = 0; i < size; i++)
			countArray[array[i]]++;

		for (int i = max; i >= 0; i--)
			countArray[i] = countArray[i - 1];
		countArray[0] = 0;

		for (int i = 1; i <= max; i++)
			countArray[i] += countArray[i - 1];
		countArray[0] = 0;

		int* newArray = (int*)calloc(size, sizeof(int));
		if (newArray != NULL)
		{
			for (int i = 0; i < size; i++)
			{
				newArray[countArray[array[i]]] = array[i];
				countArray[array[i]]++;
			}
			memcpy(array, newArray, size * sizeof(int));
		}
	}
	free(countArray);
}

void CountingSortAlternative(int array[], int size)
{
	int max_val = 0; //максимальное значение элемента в исходном массиве равно длине массива для подсчёта
	for (int i = 0; i < size; i++)
		if (max_val < array[i])
			max_val = array[i];

	max_val++; // +1 элемент т.к. массив с 0 до max_val включая max_val;

	int* countArray = (int*)calloc(max_val, sizeof(int));

	for (int i = 0; i < size; i++) {
		countArray[array[i]]++;
	}


	for (int i = 1; i < max_val; i++) {
		countArray[i] += countArray[i - 1];
	}



	int* newArray;
	if ((newArray = (int*)calloc(size, sizeof(int))) != NULL) {

		for (int i = size - 1; i >= 0; i--) {
			countArray[array[i]]--;
			newArray[countArray[array[i]]] = array[i];
		}

		for (int i = 0; i < size; i++) { //В этой строчке видим отличие от базовой. Идём не с конца, а с начала.
			array[i] = newArray[i];
		}
	}
	free(newArray);

}

int RankGetter(int number, int digitBase, int rank)
{
	return (number % Power(digitBase, rank + 1));
}

int GetMax(int array[], int size)
{
	int max = array[0];
	int i = 0;
	for (; i < size; i++)
		if (array[i] > max)
			max = array[i];
	return max;
}

// ?? and doesnt work
void RadixSort(int array[], int size) // LSD
{
	int max = GetMax(array, size);
	int maxRank = 0;
	int mod = 10;
	int copyMax = max;

	while (copyMax > 0)
	{
		copyMax /= mod;
		maxRank++;
	}

	int copyMaxRank = maxRank;

	while (maxRank)
	{
		int countArray[10] = { 0 };
		for (int i = 0; i < size; i++)
			countArray[RankGetter(array[i], 10, copyMaxRank - maxRank)]++;
		for (int i = 1; i < 10; i++)
			countArray[i] += countArray[i - 1];
		int* newArray = (int*)calloc(size, sizeof(int));
		for (int i = size - 1; i >= 0; i--)
		{
			countArray[RankGetter(array[i], 10, copyMaxRank - maxRank)]--;
			newArray[countArray[RankGetter(array[i], 10, copyMaxRank - maxRank)]] = array[i];
		}
		for (int i = 0; i < size; i++)
			array[i] = newArray[i];
		free(newArray);
		maxRank--;
	}
}

void BucketSort(int array[], int size)
{

}