#include <stdio.h>

#define LEN 3
#define P1 'X'
#define P2 'O'

#define FOREGROUND_WHITE  "\x1b[37m"
#define BACKGROUND_RED  "\x1b[41m"
#define BACKGROUND_GREEN  "\x1b[42m"
#define BACKGROUND_BLUE  "\x1b[44m"
#define RESET_COLOR  "\x1b[0m"

int mat[LEN][LEN] = {{0, 0, 0},
					 {0, 0, 0},
					 {0, 0, 0}};

int xCheck (int, int);
int oCheck (int, int);
void table (void);

int main (void)
{
	int pl1, pl2;
	int x, y;
	
	table ();
	
	for (pl1 = pl2 = 0; ;)
	{
		do
		{
			do
			{
				printf (FOREGROUND_WHITE BACKGROUND_RED "X (x y) >> " RESET_COLOR);
				scanf ("%d %d", &x, &y);
			} while (x > 2 || x < 0 || y > 2 || y < 0);
			
			if ((pl1 = xCheck (x, y)) == 1 || pl1 == -1)	
				break;
		} while (pl1 == 2);

		if (pl1 == 1 || pl1 == -1)
			break;

		table ();		
		
		do
		{
			do	
			{
				printf (FOREGROUND_WHITE  BACKGROUND_BLUE "0 (x y) >> " RESET_COLOR);
				scanf ("%d %d", &x, &y);
			} while (x > 2 || x < 0 || y > 2 || y < 0);
			
			if ((pl2 = oCheck (x, y)) == 1)	
				break;
		} while (pl2 == 2);
		
		if (pl2 == 1)
			break;
			
		table ();
	}
	
	table ();
	
	if (pl1 == 1)
		printf (FOREGROUND_WHITE BACKGROUND_RED  "X vince!" RESET_COLOR);
	else if (pl2 == 1)
		printf (FOREGROUND_WHITE  BACKGROUND_BLUE "O vince!" RESET_COLOR);
	else
		printf (FOREGROUND_WHITE  BACKGROUND_GREEN "Pareggio!" RESET_COLOR);
		
		
	printf ("\n");
	return 0;
}

int xCheck (int x, int y)
{
	int count;
	int i, j, k; 
	
	
	if (mat[x][y] != 0)
		return 2;
		
	mat[x][y] = 1;
	
	for (i = 0; i < LEN; i++)
		for (count = j = 0; j < LEN; j++)
		{
			if (mat[i][j] > 0)
				count++;
			
			if (count == LEN)
				return 1;
		}
		
	for (i = 0; i < LEN; i++)
		for (count = j = 0; j < LEN; j++)
		{
			if (mat[j][i] > 0)
				count++;
			
			if (count == LEN)
				return 1;
		}
		
	for (count = i = j = 0; i < LEN; i++, j++)
		if (mat[i][j] > 0)
			count++;
	
	if (count == LEN)
		return 1;
		
	for (count = i = 0, j = LEN - 1; i < LEN; i++, j--)
		if (mat[i][j] > 0)
			count++;
	
	if (count == LEN)
		return 1;	
	
	for (count = i = 0; i < LEN; i++)
		for (j = 0; j < LEN; j++)
			if (mat[i][j])
				count++;
	
	if (count == 9)
		return -1;
		
	return 0;
}

int oCheck (int x, int y)
{
	int count;
	int i, j, k; 
	
					
	if (mat[x][y] != 0)
		return 2;
		
	mat[x][y] = -1;
	

	for (i = 0; i < LEN; i++)
		for (count = j = 0; j < LEN; j++)
		{
			if (mat[i][j] < 0)
				count++;
			
			if (count == LEN)
				return 1;
		}
		
	for (i = 0; i < LEN; i++)
		for (count = j = 0; j < LEN; j++)
		{
			if (mat[j][i] < 0)
				count++;
			
			if (count == LEN)
				return 1;
		}
		
	for (count = i = j = 0; i < LEN; i++, j++)
		if (mat[i][j] < 0)
			count++;
	
	if (count == LEN)
		return 1;
		
	for (count = i = 0, j = LEN - 1; i < LEN; i++, j--)
		if (mat[i][j] < 0)
			count++;
	
	if (count == LEN)
		return 1;	
	
	
	return 0;
}
void table (void)
{
	int i, j;
	
	printf ("\n\ty0  y1 y2\n\n");
	
	for (i = 0; i < LEN; i++)
	{
		for (j = 0; j < LEN; j++)
		{
			if (!j)
			{
				if (mat[i][j] == 1)
					printf ("x%d\t%c |",i,  P1);
				else if (mat[i][j] == -1)
					printf ("x%d\t%c |", i, P2);
				else
					printf ("x%d\t  |", i);
			}
			else if (j == LEN - 1)
			{
				if (mat[i][j] > 0)
					printf (" | %c\n", P1);
				else if (mat[i][j] < 0)
					printf (" | %c\n", P2);
				else
					printf (" |\n");
			}
			else
			{
				if (mat[i][j] > 0)
					printf (" %c", P1);
				else if (mat[i][j] < 0)
					printf (" %c", P2);
				else
					printf ("  ");
			}
			
		}	
		
		if (i != LEN - 1)
			printf ("\t---------\n");
	}
	printf ("\n\n");
	
		
	return ;
}
// Marco Fiorillo 6/11/2021

