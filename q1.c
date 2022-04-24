#include "q1Def.h"
#include "GenericFunctionsDef.h"

void copy_position(chessPos dest, chessPos src)
{
	dest[0] = src[0];
	dest[1] = src[1];
}

chessPosArray*** ValidKnightMoves()
{
	chessPosArray*** res;
	ui r, c;

	res = (chessPosArray***)malloc(sizeof(chessPosArray**) * MAX_ROW);
	check_allocation(res);

	for (r = 0; r < MAX_ROW; r++)
	{
		res[r] = (chessPosArray**)malloc(sizeof(chessPosArray*) * MAX_COL);
		check_allocation(res[r]);

		for (c = 0; c < MAX_COL; c++)
			res[r][c] = possible_positions(r, c);

	}
	return res;

}

chessPosArray* possible_positions(ui r, ui c)
{
	chessPosArray* res;
	chessPos* position;
	ui size = 0;

	res = (chessPosArray*)malloc(sizeof(chessPosArray));
	check_allocation(res);

	position = (chessPos*)malloc(sizeof(chessPos) * 8); /*8 is max size */
	check_allocation(position);

	if (is_valid_move(r + 2, c + 1))
	{
		insert_pos_to_res(position + size, r + 2, c + 1);
		size++;
	}
	if (is_valid_move(r + 2, c - 1))
	{
		insert_pos_to_res(position + size, r + 2, c - 1);
		size++;
	}
	if (is_valid_move(r - 2, c + 1))
	{
		insert_pos_to_res(position + size, r - 2, c + 1);
		size++;
	}
	if (is_valid_move(r - 2, c - 1))
	{
		insert_pos_to_res(position + size, r - 2, c - 1);
		size++;
	}
	if (is_valid_move(r + 1, c + 2))
	{
		insert_pos_to_res(position + size, r + 1, c + 2);
		size++;
	}
	if (is_valid_move(r + 1, c - 2))
	{
		insert_pos_to_res(position + size, r + 1, c - 2);
		size++;
	}
	if (is_valid_move(r - 1, c + 2))
	{
		insert_pos_to_res(position + size, r - 1, c + 2);
		size++;
	}
	if (is_valid_move(r - 1, c - 2))
	{
		insert_pos_to_res(position + size, r - 1, c - 2);
		size++;
	}

	position = (chessPos*)realloc(position, sizeof(chessPos) * size);
	check_allocation(position);

	res->position = position;
	res->size = size;

	return res;
}

void print_position(chessPos position)
{
	printf("%c%c  ", position[0], position[1]);
}

BOOL is_valid_move(ui r, ui c)
{
	return (r >= 0 && r < MAX_ROW&& c >= 0 && c < MAX_COL);
}

void insert_pos_to_res(chessPos* pos, ui r, ui c)
{
	chessPos res;

	res[0] = 'A' + r;
	res[1] = c + '1';

	copy_position(*pos, res);
}