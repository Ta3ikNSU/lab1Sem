#define _CRT_SECURE_NO_WARNINGS
#define MAX 1000
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


int calc(char* s);
int calcLevel(char* s, int* position);
int getNumber(char* s, int* position);
int functionResult(int number1, char function, int number2);
bool goodInput(char* s);

int calc(char* s) {
	int position = 0;
	return (calcLevel(s, &position));
}

int calcLevel(char* s, int* position) {
	int number1st = 0;
	char function1st = '+';
	int number2st = getNumber(s, position);
	while (s[*position] != ')' && s[*position] != '\0') {
		char function2st = s[(*position)++];
		int number3st = getNumber(s, position);
		if (((function1st == '+') || (function1st == '-')) && ((function2st == '*') || (function2st == '/'))) {
			number2st = functionResult(number2st, function2st, number3st);
		}
		else {
			number1st = functionResult(number1st, function1st, number2st);
			function1st = function2st;
			number2st = number3st;
		}
	}
	(*position)++;
	return (functionResult(number1st, function1st, number2st));
}

int getNumber(char* s, int* position) {
	int number = 0;
	if (s[*position] == '(') {
		(*position)++;
		number = calcLevel(s, position);
	}
	else
		while (s[*position] >= '0' && s[*position] <= '9')
			number = number * 10 + (s[(*position)++] - '0'); //if number > 9;
	return (number);
}


//calculate function result
int functionResult(int number1, char function, int number2) {
	;
	switch (function) {
	case '+': return(number1 + number2); break;
	case '-': return(number1 - number2); break;
	case '*': return(number1 * number2); break;
	case '/':
		if (number2 == 0) {
			printf("%s", "division by zero");
			exit(0);
		}
		return(number1 / number2);
	}
	return(0);
}


//Validation of characters for conditions
bool goodInput(char* s) {
	int passed = 0;
	int i;
	if ((s[0] < '0' || s[0] > '9') && s[0] != '(') return false; //the first element exists
	if (s[0] == '(') passed++;
	for (i = 1; s[i]; i++) {
		switch (s[i]) {
		case '(': {
			if (s[i - 1] == ')' || (s[i - 1] >= '0' && s[i - 1] <= '9')) return false;
			passed++;
			break;
		}
		case ')': {
			if (s[i - 1] == '(' || (s[i - 1] < '0' && s[i - 1] > '9')) return false;
			passed--;
			break; }
		case '+': {if (((s[i - 1] < '0') || (s[i - 1] > '9')) && (s[i - 1] != ')')) return false;
			break; }
		case '-': {if (((s[i - 1] < '0') || (s[i - 1] > '9')) && (s[i - 1] != ')')) return false;
			break; }
		case '*': {if (((s[i - 1] < '0') || (s[i - 1] > '9')) && (s[i - 1] != ')')) return false;
			break; }
		case '/': {if (((s[i - 1] < '0') || (s[i - 1] > '9')) && (s[i - 1] != ')')) return false;
			break; }
		default:
			if (s[i] < '0' || s[i] > '9') {
				return false;
			}
		}
	}
	if ((s[i - 1] < '0' || s[i - 1] > '9') && s[i - 1] != ')') return false;
	if (passed != 0) return (false);
	return true;
}

int main()
{
	char s[MAX + 1];
	int get = 0;
	int i = 0;
	while ((EOF != (get = getchar())) && (get != '\n')) {
		s[i] = (char)get;
		i++;
	}
	s[i] = '\0';
	if (true == goodInput(s)) {
		printf("%d", calc(s));
		return(0);
	}
	else {
		printf("%s", "syntax error");
		return(0);
	}
}
