#ifndef __q1Def_H
#define __q1Def_H 
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "GenericFunctionsDef.h"

typedef struct _chessPosArray
{
	ui size;
	chessPos* position;

}chessPosArray;

void copy_position(chessPos dest, chessPos src);

chessPosArray*** ValidKnightMoves();

chessPosArray* possible_positions(ui r, ui c);

BOOL is_valid_move(ui r, ui c);

void insert_pos_to_res(chessPos* pos, ui r, ui c);

#endif