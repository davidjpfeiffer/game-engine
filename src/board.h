#ifndef __BOARD
#define __BOARD

#include <vector>
#include "boardValue.h"
#include "utilities.h"

const unsigned BOARD_SIZE = 3;

class Board
{
public:

  Board()
  {
    for(unsigned row = 0; row < BOARD_SIZE; row++)
      this->board.push_back({ BoardValue::Empty, BoardValue::Empty, BoardValue::Empty });
  }

  BoardValue get(unsigned row, unsigned column) const
  {
    handleInvalidRowOrColumn(row, column);
    
    return this->board[row][column];
  }
  
  void set(unsigned row, unsigned column, BoardValue boardValue)
  {
    handleInvalidRowOrColumn(row, column);
    
    this->board[row][column] = boardValue;
  }
  
  void reset()
  {
    for(unsigned row = 0; row < BOARD_SIZE; row++)
      for(unsigned column = 0; column < BOARD_SIZE; column++)
        this->board[row][column] = BoardValue::Empty;
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
          case BoardValue::Empty:
            std::cout << "     ###";
            break;
          case BoardValue::O:
            std::cout << "  O  ###";
            break;
          case BoardValue::X:
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
        if (this->board[i][j] == BoardValue::Empty)
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

  std::vector<std::vector<BoardValue> > board;
  
  void handleInvalidRowOrColumn(unsigned row, unsigned column) const
  {
    if (!isValidRowAndColumn(row, column)) exitWithErrorMessage("Invalid row or column");
  }
};

#endif