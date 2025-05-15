#include <stdio.h>
#include <stdlib.h>

int getAIMove(char *selections) {
  int available, validMoves[9], validMoveCount = 0;
  for (available = 0; available <= 8; available++) {
    if (selections[available] == '0') {
      validMoves[validMoveCount] = available;
      validMoveCount++;
    }
  }
  int aiMoveIndex = (rand() % validMoveCount);
  int aiMove = validMoves[aiMoveIndex];
  return aiMove;
}

int makeMoves(char *selections, int multiplayer, int gameCounter) {
  int move, inputValid;
  if (multiplayer == 0) {
    printf("To make a move enter a number from 1-9 to place your symbol\n");
    inputValid = scanf("%d", &move);
  } else if (multiplayer == 1) {
    if (gameCounter % 2 == 0) {
      printf("To make a move enter a number from 1-9 to place your symbol\n");
      inputValid = scanf("%d", &move);
    } else {
      inputValid = 1;
      move = getAIMove(selections);
    }
  } else if (multiplayer == 2) {
    if (gameCounter % 2 != 0) {
      printf("To make a move enter a number from 1-9 to place your symbol\n");
      inputValid = scanf("%d", &move);
    } else {
      inputValid = 1;
      move = getAIMove(selections);
    }
  }
  while (inputValid != 1 || move < 1 || move > 9 ||
         selections[move - 1] != '0') {
    if (inputValid != 1) {
      while (getchar() != '\n')
        ;
    }
    printf("Invalid move! Remake a move.\n");
    inputValid = scanf("%d", &move);
  }
  return move;
}

char checkWin(char *selections) {
  char winningChar = '0';
  if (selections[0] == selections[1] && selections[1] == selections[2]) {
    winningChar = selections[0];
  } else if (selections[3] == selections[4] && selections[4] == selections[5]) {
    winningChar = selections[3];
  } else if (selections[6] == selections[7] && selections[7] == selections[8]) {
    winningChar = selections[6];
  } else if (selections[0] == selections[3] && selections[3] == selections[6]) {
    winningChar = selections[0];
  } else if (selections[1] == selections[4] && selections[4] == selections[7]) {
    winningChar = selections[1];
  } else if (selections[2] == selections[5] && selections[5] == selections[8]) {
    winningChar = selections[2];
  } else if (selections[0] == selections[4] && selections[4] == selections[8]) {
    winningChar = selections[0];
  } else if (selections[2] == selections[4] && selections[4] == selections[6]) {
    winningChar = selections[2];
  }
  return winningChar;
}

void drawGrid(char *selections) {
  for (int i = 1; i <= 18; i++) {
    char currentChar = selections[(i - 1) / 2];
    if (i % 6 == 0) {
      printf("\n");
    } else if ((i % 2) == 0) {
      printf("|");
    } else {
      if (currentChar == '0') {
        if (i >= 12) {
          printf(" ");
        } else {
          printf("_");
        }
      } else {
        if (i >= 12) {
          printf("%c", currentChar);
        } else {
          printf("\033[4m%c\033[0m", currentChar);
        }
      }
    }
  }
  printf("\n");
  return;
}

int main() {
  char selections[9];
  int multiplayer = 0;
  printf(
      "Do you want to be player 1, 2 or is this 2 humans (0 for 2 humans)!\n");
  scanf("%d", &multiplayer);
  for (int i = 0; i <= 8; i++) {
    selections[i] = '0';
  }
  for (int gameCounter = 0; gameCounter <= 8; gameCounter++) {
    drawGrid(selections);
    int moveMade = makeMoves(selections, multiplayer, gameCounter) - 1;
    if (gameCounter % 2 == 0) {
      selections[moveMade] = 'X';
    } else {
      selections[moveMade] = 'O';
    }
    printf("\n");
    char winCheck = checkWin(selections);
    if (winCheck != '0') {
      drawGrid(selections);
      printf("%c wins!\n", winCheck);
      return 0;
    }
  }
  drawGrid(selections);
  printf("It's a draw!\n");
  return 0;
}
