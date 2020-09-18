#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>

struct ListSymbol
{
	unsigned char symbol;
	unsigned long long position;
	struct ListSymbol* next;
	struct ListSymbol* previous;
};

int readTemplate(unsigned char* temp)
{
	int lengthTemplate = 0;
	int get;
	while (((get = getchar()) != '\n') && (get != EOF))
	{
		temp[lengthTemplate] = (unsigned char)get;
		lengthTemplate++;
	}
	return(lengthTemplate);
}

struct ListSymbol* firstTextScannig(int lengthTemplate, struct ListSymbol* head)
{
	if (head == NULL) return(NULL);
	struct ListSymbol* pointer = head;
	pointer->position = 1;
	pointer->next = NULL;
	pointer->previous = NULL;
	int get = getchar();
	if (get == EOF) return NULL;
	pointer->symbol = (unsigned char)get;
	for (int i = 1; i < lengthTemplate; i++)
	{
		get = getchar();
		if ((EOF) == get) return(NULL);
		if (pointer == NULL) return(NULL);
		struct ListSymbol* prevPointer = pointer;
		pointer->next = pointer;
		pointer = (struct ListSymbol*)(malloc(sizeof(struct ListSymbol)));
		if (pointer == NULL) return(NULL);
		prevPointer->next = pointer;
		pointer->next = NULL;
		pointer->previous = prevPointer;
		pointer->symbol = (unsigned char)get;
		pointer->position = ((prevPointer->position) + 1);

	}
	return(pointer);
}

void comparison(struct ListSymbol* head, unsigned char* temp, int lengthTemplate)
{
	struct ListSymbol* pointer = head;
	int index = lengthTemplate - 1;
	while (lengthTemplate > 0) {
		printf("%llu ", pointer->position);
		if (temp[index - (lengthTemplate - 1)] == (pointer->symbol))
		{
			lengthTemplate--;
			pointer = pointer->next;

		}
		else {
			break;
		}
	}
	return;
}

short int TextScannig(struct ListSymbol* tail, struct ListSymbol* head)
{
	if ((tail == NULL) || (head == NULL)) return 0;
	short int endOfTextFlag = 1;
	int get = 0;
	if (EOF == (get = getchar()))
	{
		endOfTextFlag = 0;
	}
	else
	{
		(tail->position = tail->previous->position + 1);
		tail->symbol = (unsigned char)get;
	}
	return(endOfTextFlag);
}

struct ListSymbol* structuralChainTransformations(struct ListSymbol* head, struct ListSymbol* tail)
{
	if ((head == NULL) || (tail == NULL)) return(NULL);
	struct ListSymbol* pointer = head->next;
	head->previous = tail;
	tail->next = head;
	tail = head;
	head = pointer;
	head->previous = NULL;
	tail->next = NULL;
	return(head);
}

void cleanStruct(struct ListSymbol* head)
{
	while (head->next != NULL)
	{
		head = head->next;
		free(head->previous);
	}
	free(head);
}

unsigned long long hastTemplate(unsigned char* temp, int length, unsigned long long* degree3)
{
	unsigned long long hash = 0;
	for (int i = 0; i < length; i++) {
		hash = hash + (unsigned long long)(((int)(temp[i] % 3)) * degree3[i]);
	}
	return(hash);
}

void arrayDegree3(unsigned long long* degree3, int lengthTemplate)
{
	degree3[0] = 1;
	for (int i = 1; i < lengthTemplate; i++)
	{
		degree3[i] = degree3[i - 1] * 3;
	}
	return;
}

unsigned long long firstCalculateHashBuffer(struct ListSymbol* head, unsigned long long* degree3)
{
	if (NULL == head)  exit(0);
	unsigned long long hashBuffer = 0;
	int indexInArrayDegree3 = 0;
	struct ListSymbol* pointer = head;
	while (pointer != NULL)
	{
		hashBuffer = hashBuffer + ((int)pointer->symbol) % 3 * degree3[indexInArrayDegree3];
		indexInArrayDegree3++;
		pointer = pointer->next;
	}
	return(hashBuffer);
}

unsigned long long calculateHashBuffer(struct ListSymbol* tail, int lengthTemplate, unsigned long long* degree3, unsigned long long lastHash)
{
	unsigned long long hashBuffer = 0;
	hashBuffer = lastHash / 3 + (((int)(tail->symbol)) % 3) * degree3[lengthTemplate - 1];
	return(hashBuffer);
}

int main()
{
	struct ListSymbol* tail, * head;
	unsigned char temp[17];
	int lengthTemplate = readTemplate(temp);
	unsigned long long degree3[16];
	arrayDegree3(degree3, lengthTemplate);
	unsigned long long hashTemp = (unsigned long long) hastTemplate(temp, lengthTemplate, degree3);
	printf("%llu ", hashTemp);
	head = (struct ListSymbol*)(malloc(sizeof(struct ListSymbol)));
	if (NULL == (tail = firstTextScannig(lengthTemplate, head)))
	{
		cleanStruct(head);
		return 0;
	}
	short int endOfTextFlag = 1;
	if (0 == lengthTemplate) return(0);
	/*
	if endOfTextFlag==0 then end
	if endOfTextFlag==1 then continue
	*/
	unsigned long long hashBuffer = firstCalculateHashBuffer(head, degree3);
	while (endOfTextFlag == 1)
	{
		if (hashBuffer == hashTemp)
		{
			comparison(head, temp, lengthTemplate);
		}
		head = structuralChainTransformations(head, tail);
		if (tail->next != NULL) tail = tail->next;
		endOfTextFlag = TextScannig(tail, head);
		hashBuffer = calculateHashBuffer(tail, lengthTemplate, degree3, hashBuffer);
	}
	cleanStruct(head);
	return(0);
}
