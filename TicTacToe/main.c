# include <stdio.h>

void printBoard(char board[])
{
    for (int line = 0; line<3 ;line++)
        {
            for (int field = 0; field < 5; field++ )
                {
                    if (field % 2 != 0)
                        {
                            printf("|");
                        }
                    else
                        {
                            if (board[line*field] == ('X' | 'O'))
                                {
                                    printf( "%d" ,board[line*field]);
                                }
                            if  (line == 2)
                                {
                                    printf(" ");
                                }
                            else
                                {
                                    printf("_");
                                }
                        }
                }
            printf("\n");
        }
}

int makeMoves()
{
    printf("Enter a number from 1-9 to place your symbol\n");
    int move;
    scanf("%d", &move);
    printf("\n");
    return move;
}

int checkWin(char board[])
{
    if
    (
        (board[0] == board[1] == board[2]) || (board[3] == board[4] == board[5]) || (board[6] == board[7] == board[8]) || (board[0] == board[3] == board[6]) || (board[1] == board[4] == board[7]) || (board[2] == board[5] == board[8]) || (board[0] == board[4] == board[8])
    )
        {
            printf("Win!");
            return 1;
        }

    else
        {
            return 0;
        }
}

int main ()
{
    // TODO: Print current board state, remove func to print empty init state separately
    char board[9] = {'0', '1', '2', '3', '4', '5', '6', '7', '8'};
    int moveCounter = 0;
    printf("Welcome to tictactoe \n\n");
    while (moveCounter<=8 && checkWin(board) == 0)
    {
            printBoard(board);
            int moveMade = makeMoves();
            if(moveCounter % 2 == 0 )
                {
                    board[moveMade] = 'X';
                }
            else
                {
                    board[moveMade] = 'O';
                }
    }
    return 0;
}
