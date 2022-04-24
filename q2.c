#include "q2Def.h"
#include "GenericFunctionsDef.h"

void display(chessPosList* lst)
{
	char board[MAX_ROW][MAX_COL];

	init_board(board); /*init cells value in board with EMPETY_CELL ( '0' ) */

	update_board_and_remove_dup_cells(board, lst);

	print_board(board);
}

void init_board(char board[][MAX_COL])
{
	/*init board with empety cell*/
	ui r, c;

	for (r = 0; r < MAX_ROW; r++)
		for (c = 0; c < MAX_COL; c++)
			board[r][c] = EMPETY_CELL;
}

void update_board_and_remove_dup_cells(char board[][MAX_COL], chessPosList* lst)
{
	ui row, col, location = 1; /* location in list*/
	chessPosCell* curr_cell;
	chessPosCell* save;

	curr_cell = lst->head;

	while (curr_cell != NULL)
	{
		row = (curr_cell->position)[0] - 'A';
		col = (curr_cell->position)[1] - '0' - 1;

		if (board[row][col] == EMPETY_CELL)
		{
			board[row][col] = location + '0';
			location++;
			curr_cell = curr_cell->next;
		}
		else /* not empty cell --> duplicate cell */
		{
			save = curr_cell;
			curr_cell = curr_cell->next;
			remove_cell_from_list(save, lst);
		}
	}
}

void print_board(char board[MAX_ROW][MAX_COL])
{
	ui row, col, i, save;
	printf("\n");
	printf("      ");
	for (i = 0; i < MAX_COL; i++)
	{
		save = numOfDigits(i + 1);
		printf("%-*d", 4 - save, i + 1);
	}
	printf("\n");
	print_line();
	printf("\n");

	for (row = 0; row < MAX_ROW; row++)
	{

		printf("| %c |", 'A' + row);

		for (col = 0; col < MAX_COL; col++)
		{
			boardBackGround();

			if (board[row][col] == EMPETY_CELL)
				printf("   |");
			else
			{
				boardBackGround();
				printf("%*d ", 2, board[row][col] - '0');
				reset();
				printf("|");
			}
		}
		printf("\n");
		print_line();
		printf("\n");
	}
}

ui numOfDigits(ui num)
{
	/*calculate num of digits in num : */
	ui res = 0;
	while (num > 0)
	{
		res++;
		num /= 10;
	}
	return num;
}

void print_line()
{
	ui i;
	printf("-----");
	for (i = 0; i < MAX_COL * 4; i++)
	{
		printf("-");
	}
}

void remove_cell_from_list(chessPosCell* cell, chessPosList* lst)
{
	/*This function gets cell to remove and the list*/
	/*List have at least 2 cells*/

	chessPosCell* save;
	chessPosCell* curr;
	BOOL found = FALSE;

	if (cell == lst->head) /*we want to remove the first cell*/
	{
		save = lst->head;
		lst->head = lst->head->next;
		free(save);
	}
	else if (cell == lst->tail)/*we want to remove the last cell*/
	{
		curr = lst->head;

		while (curr != NULL && !found) /*search for one cell before the last ( this cell is going to be the new tail )*/
		{
			if (curr->next == lst->tail)
				found = TRUE;

			curr = curr->next;
		}

		save = lst->tail;
		lst->tail = curr;
		lst->tail->next = NULL;
		free(save);
	}
	else /*cell is in the middle*/
	{
		curr = lst->head;

		while (curr != NULL && !found)
		{
			if (curr->next == cell)
				found = TRUE;
			else
				curr = curr->next;
		}
		curr->next = cell->next;
		free(cell);
	}
}

BOOL is_equal(chessPos pos1, chessPos pos2)
{
	/*check if 2 position equal*/
	return(pos1[0] == pos2[0] && pos1[1] == pos2[1]);
}

BOOL isEmptyList(chessPosList* lst)
{
	return(lst->head == NULL && lst->tail == NULL);
}
