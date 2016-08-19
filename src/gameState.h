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
  
  void print()
  {
    this->board.print();
  }
};

#endif