#ifndef __GAMESTATE
#define __GAMESTATE

class GameState
{
  public:

  virtual void reset() = 0;
  
  virtual void print() const = 0;
};

#endif