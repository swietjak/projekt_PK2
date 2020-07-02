/** @file */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "functions.h"

void AssignFilenames(int argc, char* argv[], char** outputfile, char** inputfile)
{
	for (int i = 1; i < argc; ++i)
	{
		if (!strcmp(argv[i], "-o"))
			*outputfile = argv[i + 1];
		else if (!strcmp(argv[i], "-i"))
			*inputfile = argv[i + 1];
		else
			fprintf(stderr, "Zly przelacznik\nWybierz -o by zalaczyc plik lub -o by wybrac plik docelowy");
		i++;
	}
}

void AddToList(NodeType** pHead, char* pesel)
{
	NodeType* p = (NodeType*)malloc(sizeof(NodeType));
	p->pesel = pesel;
	p->pNext = *pHead;

	*pHead = p;
}

void DeleteList(NodeType** pHead)
{
	if (*pHead)
	{
		DeleteList(&((*pHead)->pNext));
		free(*pHead);
		*pHead = NULL;
	}
}

void ShowList(NodeType* pHead, char* filename)
{
	while (pHead)
	{
		PrintInfo(pHead->pesel, filename);
		pHead = pHead->pNext;
	}
}

bool IsPSLGood(char* pesel)
{
	if (pesel == " ")
		return false;
	else
	{
		int lenPSL = strlen(pesel);
		int value = 0;
		for (int i = 0; i < lenPSL - 1; i++)
		{
			if (i % 4 == 0)
				value += pesel[i] - 48;
			else if (i % 4 == 1)
				value += 3 * (pesel[i] - 48);
			else if (i % 4 == 2)
				value += 7 * (pesel[i] - 48);
			else if (i % 4 == 3)
				value += 9 * (pesel[i] - 48);
		}

		if (pesel[lenPSL - 1] - 48 == 10 - (value % 10))
			return true;
		else
			return false;
	}
}

void PrintInfo(char* pesel, char* filename)
{
	if (IsPSLGood(pesel))
	{
		int year = (pesel[0] - 48) * 10 + pesel[1] - 48;
		int month = (pesel[2] - 48) * 10 + pesel[3] - 48;
		int day = (pesel[4] - 48) * 10 + pesel[5] - 48;
		char gender;

		if (pesel[2] - 48 > 1)
		{
			year += 2000;
			month -= 20;
		}
		else
			year += 1900;

		gender = pesel[2] % 2 == 0 ? 'K' : 'M';
		printf("Pesel: %s\nData urodzenia: %d.%d.%d\nPlec: %c\n", pesel, day, month, year, gender);
		FILE* f;
		f = fopen(filename, "a");
		if (f)
			fprintf(f, "Pesel: %s\nData urodzenia: %d.%d.%d\nPlec: %c\n", pesel, day, month, year, gender);
		else
			fprintf(stderr, "Blad przy otwieraniu pliku");
	}
	else
	{
		printf("Zły pesel\n");
	}
}

int JumpToNextWord(char* start, int toEnd)
{
	if (*(start) == ' ' || *(start) == ',' || *(start) == '\0')
	{
		return 1;
	}
	char* st = start;
	while (*(start) != '\0' && *(start) != ' ' && *(start++) != ',')
		;

	return start - st;
}

void* GetPSL(FILE* f, NodeType** pHead)
{
	char* pesel = malloc(12 * sizeof(char));
	char tmp[1000];
	int j = 0;
	int i = 0;
	while (fgets(tmp, 1000, f))
	{
		i = 0;
		while (i < strlen(tmp))
		{
			if (isdigit(tmp[i]))
			{
				j = 1;
				for (j; j < 13; j++)
				{
					if (!isdigit(tmp[i + j]))
						break;
				}

				if (j == 11)
				{
					char* cpy = tmp + i;
					strncpy(pesel, cpy, 11);
					pesel[11] = '\0';
					AddToList(&(*pHead), pesel);
				}
			}
			i += JumpToNextWord(tmp + i, strlen(tmp) - i - 1);
		}
	}
}

