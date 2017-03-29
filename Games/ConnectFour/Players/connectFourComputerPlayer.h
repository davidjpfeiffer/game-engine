#ifndef __TICTACTOECOMPUTERPLAYER
#define __TICTACTOECOMPUTERPLAYER

#include "connectFourPlayer.h"
#include "connectFourGameState.h"

class ConnectFourComputerPlayer : public ConnectFourPlayer
{
  public:

  std::string getName() const
  {
    return "Computer Player";
  }
  
  Player * clone() const
  {
    return new ConnectFourComputerPlayer;
  }
  
  void getMove(GameState * p_gameState) const
  {
    this->gameDefinition.makeRandomMove(p_gameState, this->getPlayerValue());
  }
};

#endif