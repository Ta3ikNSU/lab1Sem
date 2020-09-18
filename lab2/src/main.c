#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int char2Digit(char ch) {
	int temp = (int)ch - '0';
	return(temp);
}

int compare_ints(const void* a, const void* b)
{
	const int* arg1 = a;
	const int* arg2 = b;

	return *arg1 - *arg2;
}

int main() {
	char p[11];
	int n = 0;
	if (scanf("%10s", p) != 1) return (0);
	if (scanf("%d", &n) != 1) return (0);
	int length = strlen(p);
	int flagEqualityOfAllarrayayElements = 0;
	

	for (int i = length - 1; i > 0; i--) {
		if (p[i] == p[i - 1]) {
			flagEqualityOfAllarrayayElements = 0;
		}
		else {
			flagEqualityOfAllarrayayElements = 1;
			continue;
		}
	}


	for (int i = length - 1; i > 0; i--) {
		if ((p[i] > '9') || (p[i - 1] > '9') || (p[i] < '0') || (p[i - 1] < '0')) {
			printf("bad input");
			return(0);
		}
	}

	if ((flagEqualityOfAllarrayayElements == 0) && (length != 1)) {
		printf("bad input");
		return 0;
	}
	if ((length == 1) || (n == 0)) return 0;

	int flagarrayaySortIdentifier = 0;
	for (int i = length - 1; i > 0; i--) {
		if (p[i] < p[i - 1]) {
			flagarrayaySortIdentifier = 0;
		}
		else {
			flagarrayaySortIdentifier = 1;
			break;
		}
	}
	if (flagarrayaySortIdentifier == 0) return(0);
	int flagNeedSorting = 1;
	while (n > 0) {
		for (int i = length - 1; i > 0; i--) {
			if (p[i] > p[i - 1]) {
				int array[10];
				flagNeedSorting = 1;
				int index = i;
				int min = char2Digit(p[i]);
				if (i == length - 1) {
					char ch = p[i - 1];
					p[i - 1] = p[i];
					p[i] = ch;
				}
				else {
					for (int j = length - 1; j > i; j--) {
						if ((char2Digit(p[j]) < min) && (char2Digit(p[j]) > char2Digit(p[i - 1]))) {
							min = char2Digit(p[j]);
							index = j;
						}
					}
					char ch = p[i - 1];
					p[i - 1] = p[index];
					p[index] = ch;
					for (int j = 0; j < length - i; j++) {
						array[j] = char2Digit(p[i + j]);
					}
					qsort(array, length - i, sizeof(int), compare_ints);
					for (int j = 0; j < length - i; j++) p[i + j] = array[j] + '0';
				}
				break;
			}
		}
		if (flagNeedSorting == 0) {
			return 0;
		}
		else {
			flagNeedSorting = 0;
			n--;
		}
		printf("%s\n", p);
	}
	return(0);
}
