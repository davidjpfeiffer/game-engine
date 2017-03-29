#ifndef __CONNECTFOURGAMESTATE
#define __CONNECTFOURGAMESTATE

#include "../../GameEngine/gameState.h"

#include "connectFourBoard.h"

class ConnectFourGameState : public GameState
{
  public:

  ConnectFourBoard board;
  
  void reset()
  {
    this->board.reset();
  }
  
  void print() const
  {
    this->board.print();
  }
  
  GameState * clone() const
  {
    ConnectFourGameState * gameStateCopy = new ConnectFourGameState;
    gameStateCopy->board = this->board;
    
    return gameStateCopy;
  }
};

#endif