#ifndef __CONNECTFOURGAME
#define __CONNECTFOURGAME

#include <string>

#include "../../GameEngine/game.h"

#include "connectFourGameDefinition.h"
#include "connectFourPlayerRegistry.h"

class ConnectFourGame : public Game
{
  public:
  
  ConnectFourGame()
  {
    this->gameDefinition = new ConnectFourGameDefinition;
    this->playerRegistry = new ConnectFourPlayerRegistry;
  }
  
  ~ConnectFourGame()
  {
    delete this->gameDefinition;
    delete this->playerRegistry;
  }
  
  std::string getName() const
  {
    return "Connect Four";
  }
  
  Game * clone() const
  {
    return new ConnectFourGame;
  }
};

#endif