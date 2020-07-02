/** @file */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "functions.h"

int main(int argc, char* argv[])
{
	char* p_control = _strdup(argv[1]);
	char* inputFilename = "read.txt";
	char* outputFilename = "write.txt";
	AssignFilenames(argc, argv, &outputFilename, &inputFilename);
	FILE* f;
	NodeType* pHead = NULL;
	
	f = fopen(inputFilename, "r");
	if (f)
	{
		GetPSL(f, &pHead);
		ShowList(pHead, outputFilename);
		DeleteList(&pHead);

		fclose(f);
	}
	else
	{
		puts("Zla nazwa pliku");
	}

	return 0;
}