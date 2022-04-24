#include "q3Def.h"

pathTree findAllPossibleKnightPaths(chessPos* startingPosition)
{
	pathTree res_tree;
	chessPosArray*** AllpossibleKnightMoves = ValidKnightMoves(); /*all valid knight moves */
	char isAppear[MAX_ROW][MAX_COL]; /*non duplicate values board helper*/
	init_board(isAppear);/*init board with '0' */
	res_tree.root = create_tree_node(*startingPosition, NULL);
	int row, col;

	row = find_row_from_pos(*startingPosition);
	col = find_col_from_pos(*startingPosition);
	isAppear[row][col] = FULL_CELL;

	findAllPossibleKnightPathsHelper(res_tree.root, isAppear, AllpossibleKnightMoves);

	return res_tree;

}


void findAllPossibleKnightPathsHelper(TreeNode* root, char isAppear[MAX_ROW][MAX_COL], chessPosArray*** KnightMoves)
{
	chessPosArray* curr_arr; /*pointer to chessPosArray*/
	chessPos* positions_arr; /*array of pointer*/
	treeNodeListCell* curr_cell = NULL;
	TreeNode* node;
	int row, col, root_row, root_col, arr_size, arr_ind;
	BOOL head = TRUE;

	root_row = find_row_from_pos(root->position);
	root_col = find_col_from_pos(root->position);
	curr_arr = KnightMoves[root_row][root_col];
	arr_size = curr_arr->size;
	positions_arr = curr_arr->position;

	for (arr_ind = 0; arr_ind < arr_size; arr_ind++)
	{
		row = find_row_from_pos(positions_arr[arr_ind]);
		col = find_col_from_pos(positions_arr[arr_ind]);

		if (isAppear[row][col] == EMPETY_CELL)
		{
			isAppear[row][col] = FULL_CELL;/*update isAppear*/
			node = create_tree_node(positions_arr[arr_ind], NULL);

			if (head)
			{
				root->next_possible_position = curr_cell = create_treeNodeListCell(node, NULL);
				head = FALSE;
			}
			else
			{
				curr_cell->next = create_treeNodeListCell(node, NULL);
				curr_cell = curr_cell->next;
			}
			findAllPossibleKnightPathsHelper(curr_cell->node, isAppear, KnightMoves);
		}
	}

	/*finished one path and in another path the knight can go to this cell*/
	isAppear[root_row][root_col] = EMPETY_CELL;
}

treeNodeListCell* create_treeNodeListCell(TreeNode* node, treeNodeListCell* next)
{
	treeNodeListCell* res;

	res = (treeNodeListCell*)malloc(sizeof(treeNodeListCell));
	check_allocation(res);

	res->next = (treeNodeListCell*)malloc(sizeof(treeNodeListCell));
	check_allocation(res->next);
	res->next = NULL;
	res->node = node;

	return res;

}

TreeNode* create_tree_node(chessPos pos, treeNodeListCell* next)
{
	TreeNode* res;
	res = (TreeNode*)malloc(sizeof(TreeNode));
	check_allocation(res);

	res->next_possible_position = NULL;
	res->position[0] = pos[0];
	res->position[1] = pos[1];

	return res;
}

ui find_row_from_pos(chessPos pos)
{
	return pos[0] - 'A';
}

ui find_col_from_pos(chessPos pos)
{
	return pos[1] - '1';
}
