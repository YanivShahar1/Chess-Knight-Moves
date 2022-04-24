#ifndef __GenericFunctionsDef_H
#define __GenericFunctionsDef_H
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "template.h"

#define MAX_ROW 5
#define MAX_COL 5
#define EMPETY_CELL '0'
#define FULL_CELL '1'
#define ILLEGAL_MOVE 1
#define NO_FILE -1
#define COVER_ALL_BOARD 2
#define REGULAR_PATH 3

typedef char chessPos[2];
typedef unsigned int ui;
typedef unsigned char BYTE;

typedef int BOOL;
#define TRUE 1
#define FALSE 0

void check_allocation(void* arr); /*This function : check dinamic allocations*/

void checkFile(FILE* f); /*This function : if the file opens successfully*/

#endif