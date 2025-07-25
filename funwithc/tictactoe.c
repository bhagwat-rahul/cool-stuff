#include <stdio.h>
#include <stdlib.h>

/*
 Min max algos are these things where you can assign points to good / bad moves.
 We want to implement something like this.
 So what we want to do is have a func that 'plays' out the entire game and adds points on a good move and removes points on a bad move.
 AI then plays the move w highest points.
 Calc points as follows:- if ai wins a situation, the last move is valued at + 1 else -1 (0 for draw).
 System to calc points for non last moves is kinda weird and i don't understand yet. (involves recursion)
 Kinda complex, but heres how we can start:-

 Step 1:-
 Ask user if they want to play against AI + if they want to be player 1 or 2 (0 is 2 humans.)
 Then in makeMoves, if human move take input if aiMove run aiMove function which is like so:-
 make an Array of available moves that contains all numbers ai can move to.
 ai will at random pick one available move.

 Step 2:-
 To make smarter, make both ai and human pick moves till game ends running the minimax algo.
 Then make ai play most optimal move.

 win combos:-
 012
 345
 678
 036
 147
 258
 048
 246
 */

int getAIMove(char *selections) {
  int available, validMoves[9], validMoveCount = 0;
  for (available = 0; available <= 8; available++) {
    if (selections[available] == '0') {
      validMoves[validMoveCount++] = available;
    }
  }
  int aiMoveIndex = (rand() % validMoveCount);
  int aiMove = validMoves[aiMoveIndex] + 1;
  printf("AI plays %d\n", aiMove);
  return aiMove;
}

int makeMoves(char *selections, int multiplayer, int gameCounter) {
  int move, inputValid = 0;
  if ((multiplayer == 0) || (multiplayer == 1 && gameCounter % 2 == 0) ||
      (multiplayer == 2 && gameCounter % 2 != 0)) {
    printf("To make a move enter a number from 1-9 to place your symbol\n");
    inputValid = scanf("%d", &move);
  } else {
    inputValid = 1;
    move = getAIMove(selections);
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

int getPlayerCount() {
  int multiplayer = 0, multiplayerInputValid = 0;
  printf(
      "Do you want to be player 1, 2 or is this 2 humans (0 for 2 humans)!\n");
  multiplayerInputValid = scanf("%d", &multiplayer);
  while (multiplayerInputValid != 1 || multiplayer < 0 || multiplayer > 2) {
    if (multiplayerInputValid != 1) {
      while (getchar() != '\n')
        ;
    }
    printf("Invalid input! Try again!\n");
    multiplayerInputValid = scanf("%d", &multiplayer);
  }
  return multiplayer;
}

int main() {
  char selections[9];
  int multiplayer = getPlayerCount();
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
