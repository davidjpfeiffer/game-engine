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
    for(int row = 0; row < BOARD_SIZE; row++)
      this->board.push_back({ BoardValue::Empty, BoardValue::Empty, BoardValue::Empty });
  }

  BoardValue get(int row, int column) const
  {
    handleInvalidRowOrColumn(row, column);
    
    return this->board[row][column];
  }
  
  void set(int row, int column, BoardValue boardValue)
  {
    handleInvalidRowOrColumn(row, column);
    
    this->board[row][column] = boardValue;
  }
  
  void reset()
  {
    for(int row = 0; row < BOARD_SIZE; row++)
      for(int column = 0; column < BOARD_SIZE; column++)
        this->board[row][column] = BoardValue::Empty;
  }
  
  void print()
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
  
  int numberOfAvailableMoves() const
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

  static bool isValidRow(int row)
  {
    return row >= 0 && row < BOARD_SIZE;
  }

  static bool isValidColumn(int column)
  {
    return column >= 0 && column < BOARD_SIZE;
  }

  static bool isValidRowAndColumn(int row, int column)
  {
    return isValidRow(row) && isValidColumn(column);
  }
  
private:

  std::vector<std::vector<BoardValue> > board;
  
  void handleInvalidRowOrColumn(int row, int column) const
  {
    if (!isValidRowAndColumn(row, column)) exitWithErrorMessage("Invalid row or column");
  }
};

#endif