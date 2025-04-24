# include <stdio.h>

int makeMoves(char *selections)
{
    printf("To make a move enter a number from 1-9 to place your symbol\n");
    int move;
    scanf("%d", &move);
    return move;
}

char checkWin(char *selections)
{
    char winningChar = '0';
    if (selections[0] == selections[1] && selections[1] == selections[2]) { winningChar = selections[0]; }
    if (selections[3] == selections[4] && selections[4] == selections[5]) { winningChar = selections[3]; }
    if (selections[6] == selections[7] && selections[7] == selections[8]) { winningChar = selections[6]; }
    if (selections[0] == selections[3] && selections[3] == selections[6]) { winningChar = selections[0]; }
    if (selections[1] == selections[4] && selections[4] == selections[7]) { winningChar = selections[1]; }
    if (selections[2] == selections[5] && selections[5] == selections[8]) { winningChar = selections[2]; }
    if (selections[0] == selections[4] && selections[4] == selections[8]) { winningChar = selections[0]; }
    if (selections[2] == selections[4] && selections[4] == selections[6]) { winningChar = selections[2]; }
    return winningChar;
}

void drawGrid (char *selections)
{
  for ( int i = 1; i <= 18; i++ )
	{
		char currentChar = selections [ (i - 1) / 2 ];
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
                    if (i >= 12)
                        {
                            printf("%c", currentChar);
                        }
                    else
                        {
                            printf("\033[4m%c\033[0m", currentChar);
                        }
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
	for (int gameCounter = 0; gameCounter <= 8; gameCounter++)
	{
	drawGrid(selections);
	int moveMade = makeMoves(selections);
	if (gameCounter % 2 == 0)
	{
	selections[moveMade - 1] = 'X';
	}
	else
	{
	selections[moveMade - 1] = 'O';
	}
    printf("\n");
    char winCheck = checkWin(selections);
    if (winCheck == '0')
        {
            continue;
        }
    else
        {
           drawGrid(selections);
           printf("%c wins!\n", winCheck);
           return 0;
        }
	}
	printf("It's a draw!");
	return 0;
}
