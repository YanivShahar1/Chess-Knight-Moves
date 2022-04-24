#ifndef __q5Def_H
#define __q5Def_H 
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "q4Def.h"


typedef unsigned char BYTE;

void saveListToBinFile(char* fileName, chessPosList* posList);

void write_byte_to_file(FILE* file, int* bit, BYTE* write, BYTE data);

#endif

