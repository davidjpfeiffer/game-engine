#ifndef __HUMANPLAYER
#define __HUMANPLAYER

#include <iostream>
#include "player.h"

class HumanPlayer : public Player
{
public:

  GameState getMove(const GameState & gameState)
  {
    GameState gameStateAfterMove;
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

      gameStateAfterMove.board = gameState.board;

      if (Board::isValidRowAndColumn(indexOfRow, indexOfColumn))
      {
        gameStateAfterMove.board.set(indexOfRow, indexOfColumn, this->getBoardValue());
        validMoveMade = TicTacToe::isValidMove(gameState, gameStateAfterMove, this->getBoardValue());
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

    return gameStateAfterMove;
  }
};


#endif