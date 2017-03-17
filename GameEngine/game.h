#ifndef __GAME
#define __GAME

#include <iostream>

#include "gameDefinition.h"
#include "playerRegistry.h"

class Game
{
  public:
  
  GameDefinition * gameDefinition;
  
  PlayerRegistry * playerRegistry;
};

#endif