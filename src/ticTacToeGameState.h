#ifndef __TICTACTOEGAMESTATE
#define __TICTACTOEGAMESTATE

#include "gameState.h"
#include "ticTacToeBoard.h"

class TicTacToeGameState : public GameState
{
  public:

  TicTacToeBoard board;
  
  void reset()
  {
    this->board.reset();
  }
  
  void print() const
  {
    this->board.print();
  }
};

#endif