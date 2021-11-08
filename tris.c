#include <stdio.h>
#include <stdlib.h>

#define LEN 3
#define P1 'X'
#define P2 'O'

#define FOREGROUND_RED "\x1b[31m"
#define FOREGROUND_GREEN "\x1b[32m"
#define FOREGROUND_YELLOW "\x1b[33m"
#define FOREGROUND_BLUE "\x1b[34m"
#define FOREGROUND_MAGENTA "\x1b[35m"
#define FOREGROUND_CYAN "\x1b[36m"
#define FOREGROUND_WHITE "\x1b[37m"

#define BACKGROUND_RED "\x1b[41m"
#define BACKGROUND_GREEN "\x1b[42m"
#define BACKGROUND_YELLOW "\x1b[43m"
#define BACKGROUND_BLUE "\x1b[44m"
#define BACKGROUND_MAGENTA "\x1b[45m"
#define BACKGROUND_CYAN "\x1b[46m"
#define BACKGROUND_WHITE "\x1b[47m"

#define RESET_COLOR "\x1b[0m"

char *file = "record.txt";

int mat[LEN][LEN] = {{0, 0, 0},
					 {0, 0, 0},
					 {0, 0, 0}};

int system (const char *);

int xCheck (int, int);
int oCheck (int, int);
void table (void);
void menu (void);

int main (void)
{
	int pl1, pl2;
	int matches;
	int cross;
	int circle;
	int draws;
	int i, j, x, y;
	
	FILE *fp;

	menu ();

	table ();
	
	for (pl1 = pl2 = 0; ;)
	{
		do
		{
			do
			{
				printf (FOREGROUND_RED "X (x y)" RESET_COLOR FOREGROUND_YELLOW " >> ");
				scanf ("%d %d", &x, &y);
				printf (RESET_COLOR);
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
				printf (FOREGROUND_BLUE "0 (x y)" RESET_COLOR FOREGROUND_YELLOW " >> ");
				scanf ("%d %d", &x, &y);
				printf (RESET_COLOR);
			} while (x > 2 || x < 0 || y > 2 || y < 0);
			
			if ((pl2 = oCheck (x, y)) == 1)	
				break;
		} while (pl2 == 2);
		
		if (pl2 == 1)
			break;
			
		table ();
	}
	
	table ();

	for (i = 0; i < LEN; i++)
		for (j = 0; j < LEN; j++)
			mat[i][j] = 0;

	if (pl1 == 1)
	{
		printf (FOREGROUND_WHITE BACKGROUND_RED  "X vince!" RESET_COLOR);

		fp = fopen (file, "r");
		fscanf (fp, "%d %d %d %d", &matches, &cross, &circle, &draws);
		fclose (fp);

		fp = fopen (file, "w");
		fprintf(fp, "%d %d %d %d", matches + 1, cross + 1, circle, draws);
		fclose (fp);

		main();
	}
	else if (pl2 == 1)
	{
		printf (FOREGROUND_WHITE  BACKGROUND_BLUE "O vince!" RESET_COLOR);

		fp = fopen(file, "r");
		fscanf(fp, "%d %d %d %d", &matches, &cross, &circle, &draws);
		fclose(fp);

		fp = fopen(file, "w");
		fprintf(fp, "%d %d %d %d", matches + 1, cross, circle + 1, draws);
		fclose(fp);

		main();
	}
	else
	{
		printf (FOREGROUND_WHITE  BACKGROUND_GREEN "Pareggio!" RESET_COLOR);

		fp = fopen(file, "r");
		fscanf (fp, "%d %d %d %d", &matches, &cross, &circle, &draws);
		fclose (fp);

		fp = fopen(file, "w");
		fprintf(fp, "%d %d %d %d", matches + 1, cross, circle, draws + 1);
		fclose(fp);

		main ();
	}	
		
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
	printf(RESET_COLOR);
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
	
	system ("clear");
	printf (FOREGROUND_GREEN "\n\ty0  y1 y2\n\n" RESET_COLOR);
	
	for (i = 0; i < LEN; i++)
	{
		for (j = 0; j < LEN; j++)
		{
			if (!j)
			{
				if (mat[i][j] == 1)
					printf(FOREGROUND_GREEN "x%d\t" FOREGROUND_RED "%c"RESET_COLOR " |", i, P1);
				else if (mat[i][j] == -1)
					printf(FOREGROUND_GREEN "x%d\t" FOREGROUND_BLUE "%c"RESET_COLOR " |", i, P2);
				else
					printf (FOREGROUND_GREEN "x%d\t" RESET_COLOR "  |", i);
			}
			else if (j == LEN - 1)
			{
				if (mat[i][j] > 0)
					printf(" | " FOREGROUND_RED "%c\n" RESET_COLOR, P1);
				else if (mat[i][j] < 0)
					printf (" | " FOREGROUND_BLUE "%c\n" RESET_COLOR, P2);
				else
					printf (" |\n");
			}
			else
			{
				if (mat[i][j] > 0)
					printf (FOREGROUND_RED " %c" RESET_COLOR, P1);
				else if (mat[i][j] < 0)
					printf (FOREGROUND_BLUE " %c" RESET_COLOR, P2);
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

void menu (void)
{
	int c;
	int matches;
	int cross;
	int circle;
	int draws;

	FILE *fp;


	do
	{
		system("clear");

		printf (FOREGROUND_CYAN "\n\nMENU DI GIOCO\n\n" RESET_COLOR);
		printf (FOREGROUND_MAGENTA "0." RESET_COLOR " Uscire\n");
		printf (FOREGROUND_MAGENTA  "1." RESET_COLOR " Nuova partita\n");
		printf (FOREGROUND_MAGENTA "2." RESET_COLOR " Record\n");
		printf (FOREGROUND_MAGENTA "3." RESET_COLOR " Cancellare dati\n");
		printf (FOREGROUND_YELLOW ">> ");
		scanf("%d", &c);
		printf (RESET_COLOR);
		getchar();

		switch (c)
		{
			case 0:
				system("clear");
				exit (0);
				break;

			case 1:
				system ("clear");
				return ;
				break;

			case 2:
				fp = fopen (file, "r");
				fscanf (fp, "%d %d %d %d", &matches, &cross, &circle, &draws);
				system ("clear");
				printf (FOREGROUND_RED "Record\n\n" RESET_COLOR);
				printf (FOREGROUND_MAGENTA "Partite giocate" FOREGROUND_YELLOW " >> %d\n\n" RESET_COLOR , matches);
				printf (FOREGROUND_CYAN "Vittorie 'X'" FOREGROUND_YELLOW "    >> %d\n" RESET_COLOR, cross);
				printf (FOREGROUND_CYAN "Vittorie '0'" FOREGROUND_YELLOW "    >> %d\n" RESET_COLOR, circle);
				printf (FOREGROUND_CYAN "Pareggi" FOREGROUND_YELLOW "         >> %d\n" RESET_COLOR, draws);
				printf ("\nPremere invio per tornare al menu ");
				getchar();
				fclose(fp);
				break;

			case 3:
				fp = fopen (file, "w");
				fprintf (fp, "0 0 0 0");
				system ("clear");
				printf (FOREGROUND_CYAN "Reset dei dati avvenuto con successo\n" RESET_COLOR);
				printf ("\nPremere invio per tornare al menu ");
				getchar ();
				fclose (fp);
				break;

			default:
				system ("clear");
				break;
		}
	} while (c);

	return ;
}
// Marco Fiorillo 6/11/2021
