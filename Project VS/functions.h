/** @file */
#ifndef FUNCTONS
#define FUNCTIONS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "struct.h"

/** Function checks if passed pesel is correct
 @param pesel
 @return boolean value which shows if pesel is correct
 */
bool IsPSLGood(char *pesel);
/** Function displays info from passed pesel
 @param pesel
*/
void PrintInfo(char *pesel, char* filename);
int JumpToSpace(char *start, int toEnd);
/** Function saves found PESELS in list
 @param f input file
 @param pHead head of a list
*/
void *GetPSL(FILE *f, NodeType **pHead);
/** Function shows all info from saved pesels
 @param pHead first element of a list
*/
void ShowList(NodeType *pHead, char* filename);
void DeleteList(NodeType **pHead);
void AssignFilenames(int argc, char* argv[], char** outputfile, char **inputfile);
#endif