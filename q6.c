#include "q6Def.h"



int checkAndDisplayPathFromFile(char* fileName)
{
	chessPosList* posList;
	FILE* list_file;
	int num_of_bytes, count_pos = 1; /*counter that will check if the list covered all the board*/
	BYTE* bytes_arr;
	BOOL legal_move = TRUE;

	list_file = fopen(fileName, "rb");

	if (list_file == NULL)
	{
		return NO_FILE;
	}

	bytes_arr = get_bytes_from_binary_file(list_file, &num_of_bytes);
	fclose(list_file);

	posList = convert_array_to_list(bytes_arr, num_of_bytes);
	free(bytes_arr);


	check_if_legal_list_and_count_cells(posList, &legal_move, &count_pos);

	if (!legal_move)
	{
		freeList(posList); /*free the list*/
		return ILLEGAL_MOVE;
	}

	display(posList); /*the function from Q2 - remove duplicate cells and print chess board*/

	if (count_pos == (MAX_COL * MAX_ROW)) /*the list coverd all the board*/
		return COVER_ALL_BOARD;
	else
		return REGULAR_PATH;
}

void check_if_legal_list_and_count_cells(chessPosList* posList, BOOL* legal_move, int* count_pos)
{
	/*check if the moves in the list is legal, move in the board and by the rules of knight possible moves*/
	/*if illegal update boolian flag to FALSE and return NULL*/

	chessPosCell* cell;
	int cur_row, cur_col;
	char isAppear[MAX_ROW][MAX_COL];
	BOOL head = TRUE;

	if (isEmptyList(posList))
	{
		*count_pos = 0;
		*legal_move = TRUE;
		return;
	}

	init_board(isAppear);/*init with emepty list*/
	cell = posList->head;
	cur_row = find_row_from_pos(cell->position);
	cur_col = find_col_from_pos(cell->position);

	while (cell != NULL)
	{
		if (!(possible_move(cell, cur_row, cur_col, &head)))
		{
			*legal_move = FALSE;
			return;
		}

		if (isAppear[cur_row][cur_col] == EMPETY_CELL)
		{
			isAppear[cur_row][cur_col] = FULL_CELL;
			(*count_pos)++;
		}

		cur_row = find_row_from_pos(cell->position);
		cur_col = find_col_from_pos(cell->position);

		cell = cell->next;
	}
}

BYTE* get_bytes_from_binary_file(FILE* file, int* size)
{
	/*The file is already open*/
	/*we know the size of the list ( the first data on the file is the size of the *list* , the type is short int ) */

	BYTE* res;
	int num_of_bytes, num_of_bits;
	short int list_len;

	fread(&list_len, sizeof(short int), 1, file); /*read size of list*/

	num_of_bits = list_len * 6; /*each position in the list take 6 bytes*/

	if (num_of_bits % 8 == 0)
		num_of_bytes = num_of_bits / 8;
	else
		num_of_bytes = (num_of_bits / 8) + 1;

	res = (BYTE*)malloc(sizeof(BYTE) * num_of_bytes);
	fread(res, sizeof(BYTE), num_of_bytes, file); /*read all the bytes to array*/

	*size = num_of_bytes;

	return res;

}

chessPosList* convert_array_to_list(BYTE* arr, int size)
{
	/*The function convert array of BYTE to list, size of list is size of array / 2 (each position is 2 chars row and col ) */
	/*If there is illegal move, update boolian to false */
	/*if the position isn't appear already, update num of positions*/

	chessPosList* list;
	chessPosCell* cell = NULL;
	chessPos position;
	int row, col;
	int byte = 0, bit = 0;
	BOOL head = TRUE;

	list = (chessPosList*)malloc(sizeof(chessPosList));
	check_allocation(list);
	list->head = NULL;
	list->tail = NULL;

	while (byte < (size - 1) || bit < 6)
	{
		take_char_from_bytes_arr(arr, &row, &byte, &bit);
		position[0] = row + 'A';

		take_char_from_bytes_arr(arr, &col, &byte, &bit);
		position[1] = col + '1';

		if (head) /*first cell in list*/
		{
			head = FALSE;
			cell = createNewChessPosCell(position, NULL);
			insertCellToEndChessPosList(&list, cell);

		}
		else
		{
			cell = createNewChessPosCell(position, NULL);
			insertCellToEndChessPosList(&list, cell);
		}
	}
	return list;
}

void freeList(chessPosList* list)
{
	chessPosCell* cell, * saver;
	if (list == NULL)
		return;

	cell = list->head;
	while (cell != NULL)
	{
		saver = cell;
		cell = cell->next;
		free(saver);
	}

	free(list);
}

BOOL possible_move(chessPosCell* cell, int cur_row, int cur_col, BOOL* head)
{
	/*row and col represent the start position,
	  in cell->position we can find the position that the knight want to move for */

	int next_row, next_col;

	next_row = find_row_from_pos(cell->position);
	next_col = find_col_from_pos(cell->position);

	if (!is_valid_move(next_row, next_col)) /*not in the frame of the board*/
		return FALSE;

	if (*head) /*the first position so we don't need to compare 2 positions*/
	{
		(*head) = FALSE;
		return TRUE;
	}
	else
	{
		/* legal move for knight is :
		   2 rows up/down and 1 col right/left   or   1 row up/down and 2 cols right/left  */
		if ((abs(cur_row - next_row) == 2 && abs(cur_col - next_col) == 1) ||
			(abs(cur_row - next_row) == 1 && abs(cur_col - next_col) == 2))
			return TRUE;
		else
			return FALSE;
	}
}

void take_char_from_bytes_arr(BYTE* arr, int* data, int* byte, int* bit)
{
	BYTE mask, save, temp, new_data;
	save = temp = new_data = 0x00;

	if (*bit == 6)
	{
		mask = 0x03; /*0000 0011*/
		save = arr[*byte];
		save &= mask;
		(*byte)++;
		mask = 0x80;/*1000 0000*/
		temp = arr[*byte];
		temp &= mask;
		temp >>= 7;
		save <<= 1;
		new_data = save | temp;
		(*bit) = 1;
	}
	else if (*bit == 7)
	{
		mask = 0x01; /*0000 0001*/
		save = arr[*byte];
		save &= mask;
		(*byte)++;
		mask = 0xC0;/*1100 0000*/
		temp = arr[*byte];
		temp &= mask;
		temp >>= 6;
		save <<= 2;
		new_data = save | temp;
		(*bit) = 2;
	}
	else
	{

		mask = 0x07; /*0000 0111*/
		new_data = arr[*byte] >> (5 - (*bit));
		new_data = new_data & mask;

		(*bit) += 3;

		if ((*bit) == 8)
		{
			(*byte)++;
			(*bit) = 0;
		}
	}
	*data = (int)new_data;
}

