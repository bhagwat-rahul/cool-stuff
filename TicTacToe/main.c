# include <stdio.h>


void drawGrid (char *selections)
{
	for ( int i = 0; i < 15; i++ )
	{
		char currentChar = selections [i];
		if (i % 5 == 0)
		{
			printf("\n");
		}
		if ( (i % 2) != 0)
		{
			printf("|");
		}
		else
		{
			printf("_");
		}
	}
	return;
}

int main()
{
	char selections[9];
	for (int i = 0; i <= 8; i++)
	{
		selections[i] = '0';
	}
	drawGrid(selections);
	return 0;
}

