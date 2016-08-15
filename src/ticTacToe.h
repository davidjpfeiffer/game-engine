#ifndef __TICTACTOE
#define __TICTACTOE

#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include "utilities.h"

const unsigned BOARD_SIZE = 3;

enum GameResult {Tie, PlayerOneWin, PlayerTwoWin};
enum BoardValue {Empty, PlayerOne, PlayerTwo};

typedef std::vector<std::vector<BoardValue> > Board;

class TicTacToe
{

public:
  
  // Abstract Game Class Methods
  
  bool isOver(const Board & board)
  {
    return numAvailableMoves(board) == 0 || boardIsInWinningState(board);
  }
  
  bool isValidMove(const Board & board, const Board & boardAfterMove, const BoardValue & playerBoardValue)
  {
    if (numDifferencesBetweenBoards(board, boardAfterMove) == 1)
    {
      for (unsigned i = 0; i < BOARD_SIZE; i++)
      {
        for (unsigned j = 0; j < BOARD_SIZE; j++)
        {
          if (board[i][j] != boardAfterMove[i][j])
          {
            if (board[i][j] != BoardValue::Empty)
            {
              return false;
            }
            if (boardAfterMove[i][j] == playerBoardValue)
            {
              return true;
            }
          }
        }
      }
    }

    return false;
  }
  
  Board getEmptyBoard()
  {
    return {{ BoardValue::Empty, BoardValue::Empty, BoardValue::Empty },
      { BoardValue::Empty, BoardValue::Empty, BoardValue::Empty },
      { BoardValue::Empty, BoardValue::Empty, BoardValue::Empty }
    };
  }
  
  Board getCopyOfBoard(const Board & board)
  {
    Board copy = getEmptyBoard();

    std::copy(board.begin(), board.begin() + BOARD_SIZE, copy.begin());

    return copy;
  }
  
  void printBoard(const Board & board)
  {
    std::cout << '\n';
    for (unsigned i = 0; i < BOARD_SIZE; i++)
    {
      std::cout << "###########################\n";
      std::cout << "###     ###     ###     ###\n";
      std::cout << "###";
      for (unsigned j = 0; j < BOARD_SIZE; j++)
      {
        switch (board[i][j])
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
  
  bool boardIsInWinningState(const Board & board)
  {
    return playerOneHasWon(board) || playerTwoHasWon(board);
  }
  
  bool playerOneHasWon(const Board & board)
  {
    return playerHasWon(board, BoardValue::PlayerOne);
  }
  
  bool playerTwoHasWon(const Board & board)
  {
    return playerHasWon(board, BoardValue::PlayerTwo);
  }
  
  unsigned numAvailableMoves(const Board & board)
  {
    unsigned availableMoves = 0;

    for (unsigned i = 0; i < BOARD_SIZE; i++)
    {
      for (unsigned j = 0; j < BOARD_SIZE; j++)
      {
        if (board[i][j] == BoardValue::Empty)
        {
          availableMoves++;
        }
      }
    }

    return availableMoves;
  }
  
  unsigned numDifferencesBetweenBoards(const Board & boardOne, const Board & boardTwo)
  {
    unsigned numDifferences = 0;

    for (unsigned i = 0; i < BOARD_SIZE; i++)
    {
      for (unsigned j = 0; j < BOARD_SIZE; j++)
      {
        if (boardOne[i][j] != boardTwo[i][j])
        {
          numDifferences++;
        }
      }
    }

    return numDifferences;
  }
  
  bool isValidRow(int row)
  {
    return row >= 0 && row < BOARD_SIZE;
  }

  bool isValidColumn(int column)
  {
    return column >= 0 && column < BOARD_SIZE;
  }

  bool isValidRowAndColumn(int row, int column)
  {
    return isValidRow(row) && isValidColumn(column);
  }
  
  Board makeRandomMove(const Board & board, BoardValue playerBoardValue)
  {
    Board newBoard = getCopyOfBoard(board);
    std::vector<std::pair<unsigned, unsigned> > availableMoves;

    for (unsigned i = 0; i < BOARD_SIZE; i++)
    {
      for (unsigned j = 0; j < BOARD_SIZE; j++)
      {
        if (board[i][j] == BoardValue::Empty)
        {
          availableMoves.push_back(std::make_pair(i, j));
        }
      }
    }

    unsigned randomMove = getRandomNumber(availableMoves.size() - 1);

    newBoard[availableMoves[randomMove].first][availableMoves[randomMove].second] = playerBoardValue;

    return newBoard;
  }

  int getBoardValueAsInt(BoardValue boardValue)
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

  char getBoardValueAsChar(BoardValue boardValue)
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

  bool playerHasWon(const Board & board, BoardValue playerBoardValue)
  {
    for (unsigned row = 0; row < BOARD_SIZE; row++)
    {
      if (board[row][0] == playerBoardValue && board[row][1] == playerBoardValue && board[row][2] == playerBoardValue)
      {
        return true;
      }
    }

    for (unsigned column = 0; column < BOARD_SIZE; column++)
    {
      if (board[0][column] == playerBoardValue && board[1][column] == playerBoardValue && board[2][column] == playerBoardValue)
      {
        return true;
      }
    }

    if (board[0][0] == playerBoardValue && board[1][1] == playerBoardValue && board[2][2] == playerBoardValue)
    {
      return true;
    }

    if (board[0][2] == playerBoardValue && board[1][1] == playerBoardValue && board[2][0] == playerBoardValue)
    {
      return true;
    }

    return false;
  }
};

#endif