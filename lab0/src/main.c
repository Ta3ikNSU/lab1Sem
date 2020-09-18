#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

char transferSecondInt(unsigned long long number, int numberSystemEnd) {
	char gap[44] = { 0 };
	int i = -1;
	while (number > 0) {
		i += 1;
		int temp = number % numberSystemEnd;
		if (temp < 10) {
			gap[i] = temp + '0';
		}
		else { gap[i] = temp - 10 + 'A'; }
		number = number / numberSystemEnd;
	}
	int ind = 0;
	for (int i = 43; i >= 0; i--) {
		if (ind == 0) {
			if (gap[i] != '\0') { ind = 1; printf("%c", gap[i]); }
			else { ind = 0; }
		}
		else {
			printf("%c", gap[i]);
		}
	}
	return(0);
}

char transferSecondFloat(double number, int numberSystemEnd) {
	char gap[13] = { 0 };
	int point = 0;
	for (int i = 0; i < 13; i++) {
		int temp = floor(number * numberSystemEnd);
		if (temp < 10) {
			gap[i] = temp + '0';
		}
		else { 
			gap[i] = temp - 10 + 'A'; 
		}
		number = number * numberSystemEnd - floor(number * numberSystemEnd);

		if (temp != 0) {
			point = 1;
		} else {
			continue; 
			};
	}
	if (point != 0) {
		int ind = 0;
		int j = 12;
		int i = 12;
		while (ind == 0) {
			if (gap[i] == '0') {
				j -= 1; 
			}
			else {
				ind = 1; 
			}
			i--;
		}
		printf(".");
		for (int i = 0; i <= j; i++) printf("%c", gap[i]);
	} 
	else { 
		printf(".000000000000"); 
	}
	return(0);
}

unsigned long long convertInt(char s[], int pointNumber, int numberSystemStart) {
	unsigned long long number = 0;
	unsigned long long factor = 1;
	for (int i = pointNumber - 1; i > -1; i--) {
		int gap = 0;
		gap = (int)(s[i]);
		if (gap >= 'A') {
			gap = gap - 'A' + 10;
		}
		else {
			gap = gap - '0';
		}
		number = number + gap * factor;
		factor = factor * numberSystemStart;
	}
	return(number);
}


double convertFloat(char s[], int pointNumber, int Index, int numberSystemStart) {
	double number_dpob = 0;
	double factor = 1;
	for (int i = 1; i + pointNumber < Index; i++) {
		int gap = (int)(s[pointNumber + i]);
		if (gap >= 'A') {
			gap = gap - 'A' + 10;
		}
		else {
			gap = gap - '0';
		}
		factor = factor / numberSystemStart;
		number_dpob = number_dpob + gap * factor;
	}
	return(number_dpob);
}

int rules(int numberSystemStart, int numberSystemEnd, char s[], int pointNumber, int index) {
	int k = 0;
	if ((numberSystemStart > 16) || (numberSystemEnd > 16) || (numberSystemEnd < 2) || (numberSystemStart < 2)) k = 1;
	for (int i = 0; i < index; i++) {
		if (i != pointNumber) {
			int gap = (int)(s[i]);
			if (numberSystemStart < 10) {
				if ((gap < '0') || (gap >= '0' + numberSystemStart)) k = 1;
			}
			else {
				if ((gap < '0') || ((gap > '9') && (gap < 'A')) || (gap > numberSystemStart - 10 + 'A')) {
					k = 1;
				}
				else {
					break;
				}
			}
		}
	}
	if (k == 1) {
		printf("bad input");
		return(0);
	}
	return(1);
}

int main() {
	int numberSystemStart;
	int numberSystemEnd;
	int index = 0;
	int pointNumber = 0;

	char s[14];
	if ((scanf("%d %d %13s", &numberSystemStart, &numberSystemEnd, s)) != 3) {
		printf("bad input"); return(0);
	}
	index = strlen(s);

	int ind = 0;
	for (int i = 0; i < index; i++) {
		if (s[i] == '.') {
			pointNumber = i;
			ind = 1;
		}
	}

	if ((pointNumber == index - 1) && (ind == 1) && ((convertInt(s, pointNumber, numberSystemStart)) == 0)) {
		printf("bad input");
		return(0);
	}
	for (int i = 0; i < index; i++) s[i] = toupper(s[i]);

	if (pointNumber == 0) pointNumber = index;
	if (rules(numberSystemStart, numberSystemEnd, s, pointNumber, index) == 0) return(0);
	unsigned long long int temp = 0;
	temp = (convertInt(s, pointNumber, numberSystemStart));
	if (convertInt(s, pointNumber, numberSystemStart) != 0) {
		transferSecondInt(temp, numberSystemEnd);
	}
	else {
		printf("0");
	}
	if ((convertFloat(s, pointNumber, index, numberSystemStart)) != 0) {
		transferSecondFloat((convertFloat(s, pointNumber, index, numberSystemStart)), numberSystemEnd);
	}
	return(0);
}
