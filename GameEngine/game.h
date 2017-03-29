#ifndef __GAME
#define __GAME

#include <iostream>
#include <string>

#include "gameDefinition.h"
#include "playerRegistry.h"

class Game
{
  public:
  
  GameDefinition * gameDefinition;
  
  PlayerRegistry * playerRegistry;
  
  virtual std::string getName() const = 0;
  
  virtual Game * clone() const = 0;
};

#endif