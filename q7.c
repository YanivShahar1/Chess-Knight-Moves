#include "q7Def.h"

void menuPrinter()
{
	printf("\n");
	printf("1.Enter a knight's starting position\n");
	printf("2.Create all possible knight paths\n");
	printf("3.Find a knight path covering all board\n");
	printf("4.Save knight path covering all board to file\n");
	printf("5.Load and display path from file\n");
	printf("6.Exit\n\n");
}

void getChoice(int* choice)
{
	printf("Please choose an option from the menu: ");
	yellow();
	while (scanf("%d", choice) != 1)
	{
		while (getchar() != '\n');
		red();
		printf("Invalid input... please enter a number:");
		reset();
		yellow();
	}
	reset();
	while ( getchar() != '\n');
	printf("\nPress enter to continue:\n ");
}

char* getFileName()
{
	int logSize = 0, phySize = 1;
	char* res, c;

	res = (char*)malloc(phySize * sizeof(char));
	check_allocation(res);

	printf("Please insert file name: ");
	yellow();
	c = getchar();
	while (c != '\n')
	{
		if (logSize == phySize)
		{
			phySize *= 2;
			res = (char*)realloc(res, sizeof(char) * phySize);
		}
		res[logSize++] = c;
		c = getchar();
	}
	res = (char*)realloc(res, sizeof(char*) * (logSize + 1));
	check_allocation(res);
	res[logSize] = '\0';
	reset();
	printf("\n");
	return res;
}

void resOutput(int res)
{
	printf("\n");
	if (res == ILLEGAL_MOVE)
		printf("There is no legal path of a knight\n");
	else if (res == COVER_ALL_BOARD) {
		green();
		printf("Great!! the path covers the all board!\n");
		printf("The path is numbered on the board above\n");
		reset();
	}
	if (res == NO_FILE)
	{
		red();
		printf("Sorry,the file dosen't exist!\n");
		reset();
	}
	if (res == REGULAR_PATH)
		printf("The path dosen't covers the all board\n");
}

void Menu()
{
	int choice, tempChoice, res, waitingCommand;
	chessPos startingPosition;
	pathTree tr;
	chessPosList* lst = NULL;
	char* fileName;
	BOOL flag, finish, mark2, mark3;

	waitingCommand = tempChoice = 0;
	flag = finish = mark2 = mark3 = FALSE;

	menuPrinter();
	getChoice(&choice);

	while (!finish)
	{
		switch (choice)
		{
		case 1:
			printf("starting position (e.g 'C3'): ");
			scanf(" %c%c", &startingPosition[0], &startingPosition[1]);

			startingPosition[0] = toupper(startingPosition[0]);

			flag = is_valid_move(startingPosition[0] - 'A', startingPosition[1] - '1');

			printf("\n");
			while (!flag)
			{
				while ((getchar()) != '\n'); // clean the buffer
				red();
				printf("Invalid move please type again...\n\n");
				reset();
				printf("starting position: ");
				yellow();
				scanf(" %c%c", &startingPosition[0], &startingPosition[1]);
				startingPosition[0] = toupper(startingPosition[0]);
				reset();
				flag = is_valid_move(startingPosition[0] - 'A', startingPosition[1] - '1');
			}

			if (tempChoice != 0)//ther's another choice that the user waiting for but he asked to choose starting position first.. 
				choice = tempChoice;
			else // user chose 1 and now he need to choose his next move
			{
				yellow();
				printf("\n\nWhat is your next move? \n");
				reset();
				menuPrinter();
				getChoice(&choice);
			}
			break;

		case 2:

			if (!flag) // ther's no starting position
			{
				printf("You need to enter starting position first\n");
				tempChoice = choice;
				choice = 1;
				getchar();
			}
			else
			{
				tr = findAllPossibleKnightPaths(&startingPosition);
				mark2 = TRUE; // mark option 2 as done.
				if (tempChoice < 3) /*not 3 or 4*/
				{
					yellow();
					printf("\n\nWhat is your next move? \n");
					reset();
					menuPrinter();
					getChoice(&choice);
				}
				else
				{
					//the user chose 3 ,4 or 5 and this option need to be done.
					choice = tempChoice;
					tempChoice = 0;
				}
				
			}
			break;
		case 3:
			if (!flag)
			{
				printf("You need to enter starting position first\n");
				tempChoice = choice;
				choice = 1;
				getchar();
			}
			else
			{
				if (!mark2)
				{
					tempChoice = choice;
					choice = 2;
				}
				else
				{
					lst = findknightPathCoveringAllBoard(&tr);
					mark3 = TRUE;

					if (lst == NULL)
					{
						red();
						printf("\nThere is no path that covers the entire board\n");
						reset();
						flag = finish = mark2 = mark3 = FALSE;
					}

					if ((tempChoice < 4 && waitingCommand == 0) || lst == NULL) /*not 4*/
					{
						yellow();
						printf("\n\nWhat is your next move? \n");
						reset();
						menuPrinter();
						getChoice(&choice);
					}
					else if (waitingCommand != 0)
						choice = waitingCommand;
					else
						choice = tempChoice;
				}
			}
			break;
		case 4:
			if (!flag)
			{
				printf("You need to enter starting position first! \n\n");
				tempChoice = choice;
				choice = 1;
				getchar();
			}
			else
			{
				if (!mark3)
				{
					tempChoice = choice;
					waitingCommand = tempChoice;
					choice = 3;
				}
				else
				{
					getchar();
					fileName = getFileName();  /*get file name from user*/
					saveListToBinFile(fileName, lst);
					free(fileName);
					free(lst);
					waitingCommand = 0;
					yellow();
					printf("\n\nWhat is your next move? \n");
					reset();
					menuPrinter();
					getChoice(&choice);
				}
			}
			break;
		case 5:
			getchar();
			fileName = getFileName();  /*get file name from user*/
			res = checkAndDisplayPathFromFile(fileName);
			free(fileName);
			resOutput(res);
			flag = finish = mark2 = mark3 = FALSE;
			yellow();
			printf("\n\nWhat is your next move? \n");
			reset();
			menuPrinter();
			getChoice(&choice);
			break;
		case 6:
			finish = TRUE;
			cyan();
			printf("\nThank you!! Goodbye...\n");
			reset();
			exit(0);
			break;
		default:
			red();
			printf("Invalid input...\n");
			reset();
			getChoice(&choice);
			break;
		}
	}
}