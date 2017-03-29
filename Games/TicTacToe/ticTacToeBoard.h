#ifndef __TICTACTOEBOARD
#define __TICTACTOEBOARD

#include <stdexcept>

#include "ticTacToeBoardValue.h"

class TicTacToeBoard
{
  public:

  static const unsigned BOARD_SIZE = 3;
  
  TicTacToeBoard()
  {
    this->reset();
  }

  TicTacToeBoardValue get(unsigned row, unsigned column) const
  {
    if (!isValidRowAndColumn(row, column))
    {
      throw std::out_of_range("Index out of range at Tic Tac Toe Board get method");
    }
    
    return this->board[row][column];
  }
  
  void set(unsigned row, unsigned column, TicTacToeBoardValue boardValue)
  {
    if (isValidRowAndColumn(row, column))
    {
      this->board[row][column] = boardValue;
    }
  }
  
  void reset()
  {
    for(unsigned row = 0; row < BOARD_SIZE; row++)
    {
      for(unsigned column = 0; column < BOARD_SIZE; column++)
      {
        this->board[row][column] = TicTacToeBoardValueEmpty;
      }
    }
  }
  
  void print() const
  {
    std::cout << '\n';
    for (unsigned i = 0; i < BOARD_SIZE; i++)
    {
      std::cout << "###########################\n";
      std::cout << "###     ###     ###     ###\n";
      std::cout << "###";
      for (unsigned j = 0; j < BOARD_SIZE; j++)
      {
        switch (this->board[i][j])
        {
          case TicTacToeBoardValueEmpty:
            std::cout << "     ###";
            break;
          case TicTacToeBoardValuePlayerOne:
            std::cout << "  O  ###";
            break;
          case TicTacToeBoardValuePlayerTwo:
            std::cout << "  X  ###";
            break;
        }
      }
      std::cout << "\n###     ###     ###     ###\n";
    }
    std::cout << "###########################\n\n";
  }
  
  unsigned numberOfAvailableMoves() const
  {
    unsigned availableMoves = 0;

    for (unsigned i = 0; i < BOARD_SIZE; i++)
    {
      for (unsigned j = 0; j < BOARD_SIZE; j++)
      {
        if (this->board[i][j] == TicTacToeBoardValueEmpty)
        {
          availableMoves++;
        }
      }
    }

    return availableMoves;
  }

  static bool isValidRow(unsigned row)
  {
    return row < BOARD_SIZE;
  }

  static bool isValidColumn(unsigned column)
  {
    return column < BOARD_SIZE;
  }
  
  static bool isValidRowAndColumn(unsigned row, unsigned column)
  {
    return isValidRow(row) && isValidColumn(column);
  }
  
  private:

  TicTacToeBoardValue board [BOARD_SIZE][BOARD_SIZE];
};

#endif