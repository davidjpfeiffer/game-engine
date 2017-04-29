#ifndef __CONNECTFOURRANDOMPLAYER
#define __CONNECTFOURRANDOMPLAYER

#include "../connectFourPlayer.h"
#include "../connectFourGameState.h"

class ConnectFourRandomPlayer : public ConnectFourPlayer
{
  public:

  std::string getName() const
  {
    return "Random Player";
  }
  
  Player * clone() const
  {
    return new ConnectFourRandomPlayer;
  }
  
  void getMove(GameState * p_gameState)
  {
    this->gameDefinition.makeRandomMove(p_gameState, this->getPlayerValue());
  }
};

#endif