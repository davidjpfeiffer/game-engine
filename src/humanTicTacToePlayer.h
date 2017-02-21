#ifndef __HUMANTICTACTOEPLAYER
#define __HUMANTICTACTOEPLAYER

#include <iostream>
#include "ticTacToePlayer.h"
#include "ticTacToeGameState.h"
#include "ticTacToeBoard.h"

class HumanTicTacToePlayer : public TicTacToePlayer
{
public:

  GameState * getMove(const TicTacToeGameState * gameState)
  {
    TicTacToeGameState gameStateAfterMove;
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

      gameStateAfterMove.board = gameState->board;

      if (TicTacToeBoard::isValidRowAndColumn(indexOfRow, indexOfColumn))
      {
        gameStateAfterMove.board.set(indexOfRow, indexOfColumn, this->getBoardValue());
        validMoveMade = this->game->isValidMove(gameState, & gameStateAfterMove, this->getPlayerValue());
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

    return & gameStateAfterMove;
  }
};


#endif