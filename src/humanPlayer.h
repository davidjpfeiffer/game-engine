#ifndef __HUMANPLAYER
#define __HUMANPLAYER

#include <iostream>
#include <string>
#include "player.h"
#include "utilities.h"

class HumanPlayer : public Player
{
public:

  Board getMove(const Board & board)
  {
    Board newBoard;
    bool validMoveMade = false;
    unsigned row, column, indexOfRow, indexOfColumn;

    std::cout << this->getName() << "'s turn!\n";

    while (!validMoveMade)
    {
      std::cout << "Enter the row: ";
      std::cin >> row;
      indexOfRow = row - 1;

      std::cout << "Enter the column: ";
      std::cin >> column;
      indexOfColumn = column - 1;

      newBoard = createCopyOfBoard(board);

      if (validRowAndColumn(indexOfRow, indexOfColumn))
      {
        newBoard[indexOfRow][indexOfColumn] = this->getBoardValue();
        validMoveMade = validMove(board, newBoard, this->getBoardValue());
      }
      else
      {
        std::cout << "Row and column must be between 1 and 3 inclusive.\n";
      }

      if (!validMoveMade)
      {
        std::cout << "That was not a valid move. Please try again.\n";
      }
    }

    return newBoard;
  }
};


#endif