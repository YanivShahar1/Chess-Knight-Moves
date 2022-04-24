#ifndef __q6Def_H
#define __q6Def_H 
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "q5Def.h"

typedef unsigned char BYTE;

BYTE* get_bytes_from_binary_file(FILE* file, int* size);

int checkAndDisplayPathFromFile(char* fileName);

chessPosList* convert_array_to_list(BYTE* arr, int size);

void freeList(chessPosList* list);

BOOL possible_move(chessPosCell* cell, int row, int col, BOOL* head);

void take_char_from_bytes_arr(BYTE* arr, int* data, int* byte, int* bit);

void check_if_legal_list_and_count_cells(chessPosList* posList, BOOL* legal_move, int* count_pos);

#endif
