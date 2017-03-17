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
  
  GameState * clone() const
  {
    TicTacToeGameState * gameStateCopy = new TicTacToeGameState;
    gameStateCopy->board = this->board;
    
    return gameStateCopy;
  }
};

#endif