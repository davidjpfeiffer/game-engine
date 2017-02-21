#ifndef __TICTACTOEGAMESTATE
#define __TICTACTOEGAMESTATE

#include "gameState.h"
#include "ticTacToeBoard.h"

class TicTacToeGameState : public GameState
{
public:

  TicTacToeBoard board;
  
  virtual void reset()
  {
    this->board.reset();
  }
  
  virtual void print() const
  {
    this->board.print();
  }
};

#endif