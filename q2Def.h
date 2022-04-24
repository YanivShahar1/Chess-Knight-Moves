#ifndef __q2Def_H
#define __q2Def_H 
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "q1Def.h"

typedef struct _chessPosCell
{
	chessPos position;
	struct _chessPosCell* next;

}chessPosCell;

typedef struct _chessPosList
{
	chessPosCell* head;
	chessPosCell* tail;
}chessPosList;

void display(chessPosList* lst);

BOOL is_equal(chessPos pos1, chessPos pos2);

BOOL isEmptyList(chessPosList* lst);

void remove_cell_from_list(chessPosCell* cell, chessPosList* lst);

void init_board(char board[][MAX_COL]);

void print_board(char board[MAX_ROW][MAX_COL]);

void print_line();

void update_board_and_remove_dup_cells(char board[][MAX_COL], chessPosList* lst);

ui numOfDigits(ui num);

#endif