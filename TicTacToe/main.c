# include <stdio.h>


void drawGrid (char *selections)
{
  for ( int i = 1; i <= 18; i++ )
	{
		char currentChar = selections [i / 2];
		if (i % 6 == 0)
		{
		  printf("\n");
		}
		else if ( (i % 2) == 0)
        {
            printf("|");
        }
        else
        {
            if(currentChar == '0')
                {
                    printf("_");
                }
            else
                {
                    printf("%c", currentChar);
                }
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
  printf("\n");
	return 0;
}
