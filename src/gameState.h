#ifndef __GAMESTATE
#define __GAMESTATE

#include "board.h"

class GameState
{
public:

  Board board;
  
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