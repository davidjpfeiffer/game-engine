#ifndef __BOARD
#define __BOARD

#include <vector>
#include "utilities.h"

const unsigned BOARD_SIZE = 3;

enum BoardValue {Empty, PlayerOne, PlayerTwo};

class Board
{
public:

  Board()
  {
    reset();
  }

  BoardValue get(int row, int column) const
  {
    if (isValidRowAndColumn(row, column)) return this->board[row][column];
    else exitWithErrorMessage("Invalid row and column");
  }
  
  void set(int row, int column, BoardValue boardValue)
  {
    if (isValidRowAndColumn(row, column)) this->board[row][column] = boardValue;
    else exitWithErrorMessage("Invalid row and column");
  }
  
  void reset()
  {
    this->board = {{ BoardValue::Empty, BoardValue::Empty, BoardValue::Empty },
      { BoardValue::Empty, BoardValue::Empty, BoardValue::Empty },
      { BoardValue::Empty, BoardValue::Empty, BoardValue::Empty }
    };
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
};

#endif