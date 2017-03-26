#ifndef __PLAYERREGISTRY
#define __PLAYERREGISTRY

#include <iostream>
#include <vector>
#include <string>

#include "player.h"

class PlayerRegistry
{
  public:
  
  std::vector<Player *> players;
  
};

#endif