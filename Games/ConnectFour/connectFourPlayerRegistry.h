#ifndef __CONNECTFOURPLAYERREGISTRY
#define __CONNECTFOURPLAYERREGISTRY

#include "../../GameEngine/playerRegistry.h"

#include "./Players/connectFourComputerPlayer.h"
#include "./Players/connectFourHumanPlayer.h"
#include "./Players/connectFourRandomPlayer.h"

class ConnectFourPlayerRegistry : public PlayerRegistry
{
  public:
  
  ConnectFourPlayerRegistry()
  {
    players.push_back(& computerPlayer);
    players.push_back(& humanPlayer);
    players.push_back(& randomPlayer);
  }
  
  private:
  
  ConnectFourComputerPlayer computerPlayer;
  ConnectFourHumanPlayer humanPlayer;
  ConnectFourRandomPlayer randomPlayer;
};

#endif