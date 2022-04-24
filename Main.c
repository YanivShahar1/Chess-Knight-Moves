#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "q7Def.h"
#include "template.h"

void main()
{
	yellow();
	printf("\n\n		Hello and welcom to my Knight Moves program !\n");
	red();
	printf("\nPlease notice ! the board size is 5X5. (rows: A-E, columns: 1-5) \n\n");
	reset();
	Menu();
}