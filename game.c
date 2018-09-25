#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ANSI_COLOR_BLACK   "\x1b[30m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_GREY    "\x1b[37m"
#define ANSI_COLOR_RESET   "\x1b[0m"

void print(int** board);
void print_number(int n);
void setup(int** board);
int insert(int** board);
char get_move(int** board);
int move(int** board, char dir);

void black(char* text);
void red(char* text);
void green(char* text);
void yellow(char* text);
void blue(char* text);
void magenta(char* text);
void cyan(char* text);
void grey(char* text);

int main(int argc, char const *argv[])
{
	// Allocate memory for the board
	int** board = (int **)malloc(5 * sizeof(int *));
	int i;
	for (i = 0; i < 5; i++)
	{
		board[i] = (int *)malloc(5 * sizeof(int));
	}

	setup(board);
	print(board);

	while (1)
	{
		char in = get_move(board);
		if (move(board, in))
		{
			if (insert(board))
			{
				red("Game Over\n");
				free(board);
				return 0;
			}
		}
		print(board);
	}

	return 0;
}


char get_move(int** board)
{
	char in;
	scanf("%c", &in);

	if (in == 'q')
	{
		while(in != 'y' && in != 'n')
		{
			while (getchar() != '\n'); //clear the input buffer
			red("Quit? [y/n]\n");
			scanf("%c", &in);
		}
		
		if (in == 'y')
		{
			free(board);
			exit(0);
		}
		else
		{
			print(board);
			return get_move(board);
		}
	}

	if (in != 'w' && in != 'a' && in != 's' && in != 'd')
	{
		return get_move(board);
	}

	return in;
}


int move(int** board, char dir)
{
	int i;
	int j;
	int k;

	int retval = 0;

	switch (dir)
	{
		case 'w':
			for (i = 0; i < 5; i++)
			{
				for (j = 1; j < 5; j++)
				{
					if (board[i][j] != 0)
					{
						int k_min = -1;
						for (k = j - 1; k >= 0; k--)
						{
							if (board[i][k] == 0 || board[i][k] == board[i][j])
							{
								k_min = k;
								retval = 1;
							}
							else break;
						}
						if (k_min >= 0)
						{
							if (board[i][k_min] == 0)
							{
								// Move the tile to k_min
								board[i][k_min] = board[i][j];
								board[i][j] = 0;
							}
							else //tiles have the same value
							{
								// Combine the tiles
								board[i][k_min] *= 2;
								board[i][j] = 0;
							}
						}
					}
				}
			}		
			break;

		case 's':
			for (j = 4; j >= 0; j--)
			{
				for (i = 0; i < 5; i++)
				{
					int k_max = 5;
					if (board[i][j] != 0)
					{
						for (k = j + 1; k < 5; k++)
						{
							if (board[i][k] == 0 || board[i][k] == board[i][j])
							{
								k_max = k;
								retval = 1;
							}
							else break;
						}
						if (k_max < 5)
						{
							if (board[i][k_max] == 0)
							{
								// Move the tile to k_min
								board[i][k_max] = board[i][j];
								board[i][j] = 0;
							}
							else //tiles have the same value
							{
								// Combine the tiles
								board[i][k_max] *= 2;
								board[i][j] = 0;
							}
						}
					}
				}
			}		
			break;

		case 'a':
			for (j = 0; j < 5; j++)
			{
				for (i = 1; i < 5; i++)
				{
					if (board[i][j] != 0)
					{
						int k_min = -1;
						for (k = i - 1; k >= 0; k--)
						{
							if (board[k][j] == 0 || board[k][j] == board[i][j])
							{
								k_min = k;
								retval = 1;
							}
							else break;
						}
						if (k_min >= 0)
						{
							if (board[k_min][j] == 0)
							{
								// Move the tile to k_min
								board[k_min][j] = board[i][j];
								board[i][j] = 0;
							}
							else //tiles have the same value
							{
								// Combine the tiles
								board[k_min][j] *= 2;
								board[i][j] = 0;
							}
						}
					}
				}
			}
			break;

		case 'd':
			for (j = 0; j < 5; j++)
			{
				for (i = 4; i >= 0; i--)
				{
					if (board[i][j] != 0)
					{
						int k_max = 5;
						for (k = i + 1; k < 5; k++)
						{
							if (board[k][j] == 0 || board[k][j] == board[i][j])
							{
								k_max = k;
								retval = 1;
							}
							else break;
						}
						if (k_max < 5)
						{
							if (board[k_max][j] == 0)
							{
								// Move the tile to k_min
								board[k_max][j] = board[i][j];
								board[i][j] = 0;
							}
							else //tiles have the same value
							{
								// Combine the tiles
								board[k_max][j] *= 2;
								board[i][j] = 0;
							}
						}
					}
				}
			}
			break;

		default:
			break;
	}

	return retval;
}


void setup(int** board)
{
	int i;
	for (i = 0; i < 2; i++)
		insert(board);
}


int insert(int** board)
{
	int empty_total = -1;
	int i;
	int j;
	for (i = 0; i < 5; i++)
	{
		for (j = 0; j < 5; j++)
		{
			if (board[i][j] == 0) empty_total++;
		}
	}

	if (empty_total == -1) return 1;

	srand(time(NULL));
	int random = rand() % empty_total;

	int counter = 0;
	for (i = 0; i < 5; i++)
	{
		for (j = 0; j < 5; j++)
		{
			if (board[i][j] == 0)
			{
				if (counter == random)
				{
					board[i][j] = 2;
					return 0;
				}
				else counter++;
			}
		}
	}

	return 0;	
}

void print(int** board)
{
	grey("+----+----+----+----+----+\n");
	int i;
	int j;
	for (j = 0; j < 5; j++)
	{
		for (i = 0; i < 5; i++)
		{
			grey("|");
			print_number(board[i][j]);
		}
		grey("|\n");
	}
	grey("+----+----+----+----+----+\n");
}


void print_number(int n)
{
	char num[5];
	switch (n)
	{
		case 0:
			printf("    ");
			break;
		case 2:
			blue("   2");
			break;
		case 4:
			black("   4");
			break;
		case 8:
			green("   8");
			break;
		case 16:
			yellow("  16");
			break;
		case 32:
			red("  32");
			break;
		case 64:
			cyan("  64");
			break;
		case 128:
			cyan(" 128");
			break;
		case 256:
			cyan(" 256");
			break;
		case 512:
			cyan(" 512");
			break;
		case 1024:
			cyan("1024");
			break;
		default:
			sprintf(num, "%d", n);
			magenta(num);
			break;
	}
}


void black(char* text)
{
	printf("%s%s%s", ANSI_COLOR_BLACK, text, ANSI_COLOR_RESET);
}

void red(char* text)
{
	printf("%s%s%s", ANSI_COLOR_RED, text, ANSI_COLOR_RESET);
}

void green(char* text)
{
	printf("%s%s%s", ANSI_COLOR_GREEN, text, ANSI_COLOR_RESET);
}

void yellow(char* text)
{
	printf("%s%s%s", ANSI_COLOR_YELLOW, text, ANSI_COLOR_RESET);
}

void blue(char* text)
{
	printf("%s%s%s", ANSI_COLOR_BLUE, text, ANSI_COLOR_RESET);
}

void magenta(char* text)
{
	printf("%s%s%s", ANSI_COLOR_MAGENTA, text, ANSI_COLOR_RESET);
}

void cyan(char* text)
{
	printf("%s%s%s", ANSI_COLOR_CYAN, text, ANSI_COLOR_RESET);
}

void grey(char* text)
{
	printf("%s%s%s", ANSI_COLOR_GREY, text, ANSI_COLOR_RESET);
}
