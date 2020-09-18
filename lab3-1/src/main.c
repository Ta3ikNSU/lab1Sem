#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>

void quickSort(int* array, int start, int end)
{
	int i = start, j = end;
	int d;
	int m = array[(start + end) / 2];
	while (i <= j)
	{
		for (; array[i] < m; i++);
		for (; array[j] > m; j--);
		if (i <= j)
		{
			d = array[i];
			array[i++] = array[j];
			array[j--] = d;
		}
	}
	if (start < j) quickSort(array, start, j);
	if (i < end) quickSort(array, i, end);
}

int main()
{
	int n;
	if (1 != scanf("%d", &n)) return(0);
	int* array;
	array = malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++)
	{
		if (1 != scanf("%d", &array[i])) return(0);
	}
	quickSort(array, 0, n - 1);
	for (int i = 0; i < n; i++)
	{
		printf("%d ", array[i]);
	}
	free(array);
	return(0);
}
