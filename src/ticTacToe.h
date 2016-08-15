#ifndef __TICTACTOE
#define __TICTACTOE

#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include "board.h"
#include "utilities.h"

enum GameResult {Tie, PlayerOneWin, PlayerTwoWin};

class TicTacToe
{

public:
  
  // Abstract Game Class Methods
  
  static bool isOver(const Board & board)
  {
    return numAvailableMoves(board) == 0 || boardIsInWinningState(board);
  }
  
  static bool isValidMove(const Board & board, const Board & boardAfterMove, const BoardValue & playerBoardValue)
  {
    if (numDifferencesBetweenBoards(board, boardAfterMove) == 1)
    {
      for (unsigned i = 0; i < BOARD_SIZE; i++)
      {
        for (unsigned j = 0; j < BOARD_SIZE; j++)
        {
          if (board.get(i, j) != boardAfterMove.get(i, j))
          {
            if (board.get(i, j) != BoardValue::Empty)
            {
              return false;
            }
            if (boardAfterMove.get(i, j) == playerBoardValue)
            {
              return true;
            }
          }
        }
      }
    }

    return false;
  }
  
  static void printBoard(const Board & board)
  {
    std::cout << '\n';
    for (unsigned i = 0; i < BOARD_SIZE; i++)
    {
      std::cout << "###########################\n";
      std::cout << "###     ###     ###     ###\n";
      std::cout << "###";
      for (unsigned j = 0; j < BOARD_SIZE; j++)
      {
        switch (board.get(i, j))
        {
          case BoardValue::Empty:
            std::cout << "     ###";
            break;
          case BoardValue::PlayerOne:
            std::cout << "  O  ###";
            break;
          case BoardValue::PlayerTwo:
            std::cout << "  X  ###";
            break;
        }
      }
      std::cout << "\n###     ###     ###     ###\n";
    }
    std::cout << "###########################\n\n";
  }
  
  // Custom Methods
  
  static bool boardIsInWinningState(const Board & board)
  {
    return playerOneHasWon(board) || playerTwoHasWon(board);
  }
  
  static bool playerOneHasWon(const Board & board)
  {
    return playerHasWon(board, BoardValue::PlayerOne);
  }
  
  static bool playerTwoHasWon(const Board & board)
  {
    return playerHasWon(board, BoardValue::PlayerTwo);
  }
  
  static unsigned numAvailableMoves(const Board & board)
  {
    unsigned availableMoves = 0;

    for (unsigned i = 0; i < BOARD_SIZE; i++)
    {
      for (unsigned j = 0; j < BOARD_SIZE; j++)
      {
        if (board.get(i, j) == BoardValue::Empty)
        {
          availableMoves++;
        }
      }
    }

    return availableMoves;
  }
  
  static unsigned numDifferencesBetweenBoards(const Board & boardOne, const Board & boardTwo)
  {
    unsigned numDifferences = 0;

    for (unsigned i = 0; i < BOARD_SIZE; i++)
    {
      for (unsigned j = 0; j < BOARD_SIZE; j++)
      {
        if (boardOne.get(i, j) != boardTwo.get(i, j))
        {
          numDifferences++;
        }
      }
    }

    return numDifferences;
  }
  
  static Board makeRandomMove(const Board & board, BoardValue playerBoardValue)
  {
    Board newBoard = board;
    
    std::vector<std::pair<unsigned, unsigned> > availableMoves;

    for (unsigned i = 0; i < BOARD_SIZE; i++)
    {
      for (unsigned j = 0; j < BOARD_SIZE; j++)
      {
        if (board.get(i, j) == BoardValue::Empty)
        {
          availableMoves.push_back(std::make_pair(i, j));
        }
      }
    }

    unsigned randomMove = getRandomNumber(availableMoves.size() - 1);

    newBoard.set(availableMoves[randomMove].first, availableMoves[randomMove].second, playerBoardValue);

    return newBoard;
  }

  static int getBoardValueAsInt(BoardValue boardValue)
  {
    switch (boardValue)
    {
      case BoardValue::PlayerOne:
        return 1;
      case BoardValue::PlayerTwo:
        return 2;
      default:
        return 0;
    }
  }

  static char getBoardValueAsChar(BoardValue boardValue)
  {
    switch (boardValue)
    {
      case BoardValue::PlayerOne:
        return '1';
      case BoardValue::PlayerTwo:
        return '2';
      default:
        return '0';
    }
  }
  
private:

  static bool playerHasWon(const Board & board, BoardValue playerBoardValue)
  {
    for (unsigned row = 0; row < BOARD_SIZE; row++)
    {
      if (board.get(row, 0) == playerBoardValue && board.get(row, 1) == playerBoardValue && board.get(row, 2) == playerBoardValue)
      {
        return true;
      }
    }

    for (unsigned column = 0; column < BOARD_SIZE; column++)
    {
      if (board.get(0, column) == playerBoardValue && board.get(1, column) == playerBoardValue && board.get(2, column) == playerBoardValue)
      {
        return true;
      }
    }

    if (board.get(0, 0) == playerBoardValue && board.get(1, 1) == playerBoardValue && board.get(2, 2) == playerBoardValue)
    {
      return true;
    }

    if (board.get(0, 2) == playerBoardValue && board.get(1, 1) == playerBoardValue && board.get(2, 0) == playerBoardValue)
    {
      return true;
    }

    return false;
  }
};

#endif