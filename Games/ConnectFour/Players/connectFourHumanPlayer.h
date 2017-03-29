#ifndef __CONNECTFOURHUMANPLAYER
#define __CONNECTFOURHUMANPLAYER

#include <iostream>

#include "connectFourPlayer.h"
#include "connectFourGameState.h"

class ConnectFourHumanPlayer : public ConnectFourPlayer
{
  public:
  
  std::string getName() const
  {
    return "Human Player";
  }

  Player * clone() const
  {
    return new ConnectFourHumanPlayer;
  }
  
  void getMove(GameState * p_gameState) const
  {
    ConnectFourGameState * gameState = (ConnectFourGameState *)p_gameState;
    ConnectFourGameState gameStateAfterMove;
    
    bool validMoveMade = false;
    unsigned column, indexOfColumn;

    std::cout << this->getName() << "'s turn!\n";

    while (!validMoveMade)
    {
      std::cout << "Enter the column: ";
      std::cin >> column;
      indexOfColumn = column - 1;

      gameStateAfterMove.board = gameState->board;
      
      if (ConnectFourBoard::isValidColumn(indexOfColumn))
      {
        gameStateAfterMove.board.set(indexOfColumn, this->getBoardValue());
        validMoveMade = this->gameDefinition.isValidMove(gameState, & gameStateAfterMove, this->getPlayerValue());
      }
      else
      {
        std::cout << "Column must be between 1 and 7 inclusive.\n";
      }

      if (!validMoveMade)
      {
        std::cout << "That was not a valid move. Please try again.\n";
      }
    }
    
    gameState->board = gameStateAfterMove.board;
  }
};


#endif