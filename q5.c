#include "q5Def.h"

void saveListToBinFile(char* fileName, chessPosList* posList)
{
	int bit = 0;
	short int size_of_list = 0;
	chessPosCell* cell;
	BYTE row, col, write = 0x00;
	FILE* file;

	cell = posList->head;

	file = fopen(fileName, "wb");
	checkFile(file);

	fwrite(&size_of_list, sizeof(short int), 1, file);/*save place for the len of list*/

	while (cell != NULL)
	{
		size_of_list++;
		row = (BYTE)((cell->position)[0] - 'A');
		write_byte_to_file(file, &bit, &write, row);
		col = (BYTE)((cell->position)[1] - '1');
		write_byte_to_file(file, &bit, &write, col);
		cell = cell->next;
	}
	if (bit < 8) /*if bit is less than 8 so we need to write the last bytes*/
		fwrite(&write, sizeof(BYTE), 1, file);

	rewind(file);
	fwrite(&size_of_list, sizeof(short int), 1, file);/*write len of list*/
	fclose(file);
}

void write_byte_to_file(FILE* file, int* bit, BYTE* write, BYTE data)
{
	BYTE new_data, save;
	new_data = save = 0x00;

	if (*bit == 6)
	{
		save = data << 7; /*save the last bit for the next byte*/
		new_data = data >> 1;
		(*write) |= new_data;
		/*FULL BYTE*/
		fwrite(write, sizeof(BYTE), 1, file);
		(*write) = 0x00; /*init write*/
		(*write) |= save;
		*bit = 1;
	}
	else if (*bit == 7)
	{
		save = data << 6; /*save the 6th and 7th bits for the next byte*/
		new_data = data >> 2;
		(*write) |= new_data;
		/*FULL BYTE*/
		fwrite(write, sizeof(BYTE), 1, file);
		(*write) = 0x00; /*init write*/
		(*write) |= save;
		*bit = 2;
	}
	else
	{
		new_data = data << (5 - (*bit));
		(*write) |= new_data;
		(*bit) += 3;

		if ((*bit) == 8) /*FULL BYTE*/
		{
			fwrite(write, sizeof(BYTE), 1, file);
			(*write) = 0x00; /*init write*/
			(*bit) = 0;
		}
	}
}