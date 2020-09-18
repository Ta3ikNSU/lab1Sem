#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<stdio.h>

void swap(int* a, int* b) {
	int variable = *a;
	*a = *b;
	*b = variable;
}

int readArray(int* arrayHeap, int n) {
	for (int i = 0; i < n; i++)
	{
		if (1 != scanf("%d ", &arrayHeap[i])) return(0);
	}
	return(1);
}

void heapify(int arr[], int n, int i)
{
	int largestIndex = i;
	int l = 2 * i + 1; //LEFT
	int r = 2 * i + 2; //RIGHT 
	if (l < n && arr[l] > arr[largestIndex])
		largestIndex = l;
	if (r < n && arr[r] > arr[largestIndex])
		largestIndex = r;
	if (largestIndex != i)
	{
		swap(&arr[i], &arr[largestIndex]);
		heapify(arr, n, largestIndex);
	}
}


void heapSort(int arr[], int n)
{
	for (int i = n / 2 - 1; i >= 0; i--) {
		heapify(arr, n, i);
	}
	for (int i = n - 1; i >= 0; i--)
	{
		swap(&arr[0], &arr[i]);
		heapify(arr, i, 0);
	}
}

void printArray(int arr[], int n)
{
	for (int i = 0; i < n; i++) printf("%d ", arr[i]);
}


int main()
{
	int n;
	if (1 != scanf("%d", &n)) return(0);
	int* arrayHeap = malloc(sizeof(int) * n);
	if (0 == readArray(arrayHeap, n)) {
		free(arrayHeap);
		return(0);
	}
	heapSort(arrayHeap, n);
	printArray(arrayHeap, n);
	free(arrayHeap);
	return(0);
}
