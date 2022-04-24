#ifndef __q3Def_H
#define __q3Def_H 
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "q2Def.h"


typedef struct _treeNodeListCell treeNodeListCell;

typedef struct _treeNode
{
	chessPos position;
	treeNodeListCell* next_possible_position; /*øùéîú îé÷åîéí*/
}TreeNode;

typedef struct _treeNodeListCell
{
	TreeNode* node;
	struct _treeNodeListCell* next;
}treeNodeListCell;

typedef struct _pathTree
{
	TreeNode* root;
} pathTree;


pathTree findAllPossibleKnightPaths(chessPos* startingPosition);

void findAllPossibleKnightPathsHelper(TreeNode* root, char isAppear[MAX_ROW][MAX_COL], chessPosArray*** KnightMoves);

TreeNode* create_tree_node(chessPos pos, treeNodeListCell* next);

treeNodeListCell* create_treeNodeListCell(TreeNode* node, treeNodeListCell* next);

ui find_row_from_pos(chessPos pos);

ui find_col_from_pos(chessPos pos);

#endif