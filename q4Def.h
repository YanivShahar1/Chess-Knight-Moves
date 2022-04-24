#ifndef __q4Def_H
#define __q4Def_H 
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "q2Def.h"
#include "q3Def.h"



chessPosList* findknightPathCoveringAllBoard(pathTree* path_tree);

chessPosList* findknightPathCoveringAllBoardHelper(TreeNode* root, ui* height);

void freeTreeNodeListCell(chessPosList* lst);

void insertCellToStartChessPosList(chessPosList** lst, chessPosCell* cell);

void concat_lists(chessPosList** dest, chessPosList** src);

void insertCellToEndChessPosList(chessPosList** lst, chessPosCell* cell);

chessPosCell* createNewChessPosCell(chessPos position, chessPosCell* next);

#endif