#ifndef __TICTACTOERANDOMPLAYER
#define __TICTACTOERANDOMPLAYER

#include "connectFourPlayer.h"
#include "connectFourGameState.h"

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
  
  void getMove(GameState * p_gameState) const
  {
    this->gameDefinition.makeRandomMove(p_gameState, this->getPlayerValue());
  }
};

#endif