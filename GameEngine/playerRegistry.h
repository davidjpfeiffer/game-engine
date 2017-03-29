#ifndef __PLAYERREGISTRY
#define __PLAYERREGISTRY

#include <vector>

#include "player.h"

class PlayerRegistry
{
  public:
  
  std::vector<Player *> players;
  
};

#endif