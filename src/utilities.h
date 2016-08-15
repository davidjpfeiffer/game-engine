#ifndef __UTILITIES
#define __UTILITIES

#include <iostream>
#include <vector>
#include <utility>
#include <string>

// void printBoard(const Board & board);
// Board createCopyOfBoard(const Board & original);
// Board createEmptyBoard();
// bool playerHasWon(const Board & board, BoardValue playerBoardValue);
// bool boardIsInWinningState(const Board & board);
// unsigned numAvailableMoves(const Board & board);
// unsigned numDifferencesBetweenBoards(const Board & boardOne, const Board & boardTwo);
// bool validRow(int row);
// bool validColumn(int column);
// bool validRowAndColumn(int row, int column);
// bool validMove(const Board & board, const Board & boardAfterPlayerMove, BoardValue playerBoardValue);
// Board makeRandomMove(const Board & board);
// int getBoardValueAsInt(BoardValue boardValue);
// char getBoardValueAsChar(BoardValue boardValue);
// unsigned getRandomNumber(unsigned mod);
// void exitWithErrorMessage(std::string errorMessage);

unsigned getRandomNumber(unsigned mod)
{
  if (mod == 0)
  {
    return 0;
  }
  else
  {
    return rand() % mod;
  }
}

void exitWithErrorMessage(std::string errorMessage)
{
  std::cout << errorMessage << '\n';
  exit(1);
}

#endif