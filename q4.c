#include "q4Def.h"


chessPosList* findknightPathCoveringAllBoard(pathTree* path_tree)
{
	ui height, size = MAX_COL * MAX_ROW;
	chessPosList* resList;
	BOOL found_path = FALSE;

	resList = findknightPathCoveringAllBoardHelper(path_tree->root, &height);

	if (size != height) /*didn't found path covering all board - return NULL*/
	{
		freeTreeNodeListCell(resList);
		resList = NULL;
	}

	return resList;
}

chessPosList* findknightPathCoveringAllBoardHelper(TreeNode* root, ui* height)
{
	ui temp_heigh = 0, max_heigh = 0;
	chessPosList* res_list, * max_list;
	chessPosCell* cell;
	treeNodeListCell* child;

	if (root == NULL)
	{
		*height = 0;
		return NULL;
	}

	res_list = (chessPosList*)malloc(sizeof(chessPosList));
	check_allocation(res_list);

	cell = createNewChessPosCell(root->position, NULL);

	if (root->next_possible_position == NULL)
	{
		/*only root - without childs..*/
		*height = 1;
		res_list->head = res_list->tail = cell;
		return res_list;
	}

	child = root->next_possible_position;
	max_list = findknightPathCoveringAllBoardHelper(child->node, &max_heigh);
	child = child->next;

	while (child != NULL)
	{
		res_list = findknightPathCoveringAllBoardHelper(child->node, &temp_heigh);

		if (temp_heigh > max_heigh)
		{
			max_heigh = temp_heigh;
			freeTreeNodeListCell(max_list);
			max_list = res_list;
		}
		else
			freeTreeNodeListCell(res_list);

		child = child->next;
	}

	*height = max_heigh + 1;/*+1 for the root*/
	insertCellToStartChessPosList(&max_list, cell);

	return max_list;
}

void concat_lists(chessPosList** dest, chessPosList** src)
{
	/*concat function, add src list to end of dest*/
	chessPosList* local_dest, * local_src;
	local_dest = *dest;
	local_src = *src;

	if (local_dest->head == NULL) /* dest is empety*/
		local_dest->head = local_src->head;
	else
		local_dest->tail->next = local_src->head;

	local_dest->tail = local_src->tail;
	*dest = local_dest;
}

void insertCellToEndChessPosList(chessPosList** lst, chessPosCell* cell)
{
	chessPosList* local_lst;
	local_lst = *lst;

	if (local_lst->head == NULL) /*emepty list*/
	{
		local_lst->head = local_lst->tail = cell;
		local_lst->head->next = NULL;
	}
	else
	{
		local_lst->tail->next = cell;
		local_lst->tail = cell;
	}
}

void insertCellToStartChessPosList(chessPosList** lst, chessPosCell* cell)
{
	chessPosCell* save;
	chessPosList* local_lst;
	local_lst = *lst;

	if (local_lst->head == NULL)
	{
		local_lst->head = cell;
		local_lst->head->next = NULL;
	}
	else
	{
		save = local_lst->head;
		local_lst->head = cell;
		cell->next = save;
	}
	*lst = local_lst;
}

void freeTreeNodeListCell(chessPosList* lst)
{
	chessPosCell* curr, * save;
	curr = lst->head;

	while (curr != NULL)
	{
		save = curr;
		curr = curr->next;
		free(save);
	}

	free(lst);
}

void insertNodeToEndChessPosList(chessPosList* lst, chessPosCell* node)
{
	if (isEmptyList(lst))
	{
		lst->head = node;
		lst->tail = node;
	}
	else
	{
		lst->tail->next = node;
		lst->tail = node;
	}
}

chessPosCell* createNewChessPosCell(chessPos position, chessPosCell* next)
{
	chessPosCell* new_cell;

	new_cell = (chessPosCell*)malloc(sizeof(chessPosCell));
	check_allocation(new_cell);

	new_cell->next = next;
	copy_position(new_cell->position, position);

	return new_cell;
}
