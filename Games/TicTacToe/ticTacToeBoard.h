#ifndef __TICTACTOEBOARD
#define __TICTACTOEBOARD

#include <vector>
#include <utility>
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
    for (unsigned row = 0; row < BOARD_SIZE; row++)
    {
      std::cout << "###########################\n";
      std::cout << "###     ###     ###     ###\n";
      std::cout << "###";
      for (unsigned column = 0; column < BOARD_SIZE; column++)
      {
        switch (this->board[row][column])
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
  
  std::vector<std::pair<unsigned, unsigned> > getAvailableMoves() const
  {
    std::vector<std::pair<unsigned, unsigned> > availableMoves;

    for (unsigned row = 0; row < BOARD_SIZE; row++)
    {
      for (unsigned column = 0; column < BOARD_SIZE; column++)
      {
        if (this->board[row][column] == TicTacToeBoardValueEmpty)
        {
          availableMoves.push_back(std::make_pair(row, column));
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