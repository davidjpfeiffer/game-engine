#ifndef __HUMANTICTACTOEPLAYER
#define __HUMANTICTACTOEPLAYER

#include <iostream>
#include "ticTacToePlayer.h"
#include "ticTacToeGameState.h"
#include "ticTacToeBoard.h"

class HumanTicTacToePlayer : public TicTacToePlayer
{
  public:

  void getMove(GameState * p_gameState)
  {
    TicTacToeGameState * gameState = (TicTacToeGameState *)p_gameState;
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

      std::cout << "test 1\n";
      
      if (TicTacToeBoard::isValidRowAndColumn(indexOfRow, indexOfColumn))
      {
        gameStateAfterMove.board.set(indexOfRow, indexOfColumn, this->getBoardValue());
        gameStateAfterMove.print();
        gameState->print();
        std::cout << "test 2\n";
        std::cout << "Game is over: " << this->game.isOver(gameState) << '\n';
        std::cout << "Player Value: " << this->getPlayerValue() << '\n';
        std::cout << "Opponent Player Value: " << this->getOpponentPlayerValue() << '\n';
        validMoveMade = this->game.isValidMove(gameState, & gameStateAfterMove, this->getPlayerValue());
        std::cout << "test 3\n";
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

    std::cout << "test 4\n";
    
    gameState->board = gameStateAfterMove.board;
  }
};


#endif