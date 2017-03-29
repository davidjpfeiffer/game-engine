#ifndef __CONNECTFOURBOARD
#define __CONNECTFOURBOARD

#include <iostream>
#include <vector>
#include <stdexcept>

#include "connectFourBoardValue.h"

class ConnectFourBoard
{
  public:

  static const unsigned BOARD_HEIGHT = 6;
  static const unsigned BOARD_WIDTH = 7;
  
  ConnectFourBoard()
  {
    this->reset();
  }

  ConnectFourBoardValue get(unsigned row, unsigned column) const
  {
    if (!isValidRowAndColumn(row, column))
    {
      throw std::out_of_range("Index out of range at Connect Four Board get method");
    }
    
    return this->board[row][column];
  }
  
  void set(unsigned row, unsigned column, ConnectFourBoardValue boardValue)
  {
    if (isValidRowAndColumn(row, column))
    {
      this->board[row][column] = boardValue;
    }
  }
  
  void set(unsigned column, ConnectFourBoardValue boardValue)
  {
    unsigned row = getFirstEmptyRow(column);
    set(row, column, boardValue);
  }
  
  void reset()
  {
    for(unsigned row = 0; row < BOARD_HEIGHT; row++)
    {
      for(unsigned column = 0; column < BOARD_WIDTH; column++)
      {
        this->board[row][column] = ConnectFourBoardValueEmpty;
      }
    }
  }
  
  void print() const
  {
    std::cout << "\n-----------------------------\n";
    for(unsigned row = 0; row < BOARD_HEIGHT; row++)
    {
      for(unsigned column = 0; column < BOARD_WIDTH; column++)
      {
        switch(this->board[row][column])
        {
          case ConnectFourBoardValueEmpty:
            std::cout << "|   ";
            break;
          case ConnectFourBoardValuePlayerOne:
            std::cout << "| 1 ";
            break;
          case ConnectFourBoardValuePlayerTwo:
            std::cout << "| 2 ";
            break;
        }
      }
      std::cout << "|\n-----------------------------\n";
    }
    std::cout << '\n';
  }
  
  std::vector<unsigned> getAvailableMoves() const
  {
    std::vector<unsigned> availableMoves;

    for (unsigned column = 0; column < BOARD_WIDTH; column++)
    {
      if (this->board[0][column] == ConnectFourBoardValueEmpty)
      {
        availableMoves.push_back(column);
      }
    }

    return availableMoves;
  }

  static bool isValidRow(unsigned row)
  {
    return row < BOARD_HEIGHT;
  }

  static bool isValidColumn(unsigned column)
  {
    return column < BOARD_WIDTH;
  }
  
  static bool isValidRowAndColumn(unsigned row, unsigned column)
  {
    return isValidRow(row) && isValidColumn(column);
  }
  
  private:
  
  ConnectFourBoardValue board [BOARD_HEIGHT][BOARD_WIDTH];
  
  unsigned getFirstEmptyRow(unsigned column)
  {
    unsigned row = 0;
    
    while(isValidRow(row + 1) && this->board[row + 1][column] == ConnectFourBoardValueEmpty)
    {
      row++;
    }
    
    return row;
  }
};

#endif