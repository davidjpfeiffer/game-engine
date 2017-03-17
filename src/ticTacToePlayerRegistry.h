#ifndef __TICTACTOEPLAYERREGISTRY
#define __TICTACTOEPLAYERREGISTRY

#include "playerRegistry.h"
#include "randomTicTacToePlayer.h"
#include "humanTicTacToePlayer.h"
#include "computerTicTacToePlayer.h"

class TicTacToePlayerRegistry : public PlayerRegistry
{
  public:
  
  TicTacToePlayerRegistry()
  {
    players.push_back(& randomPlayer);
    players.push_back(& humanPlayer);
    players.push_back(& computerPlayer);
  }
  
  private:
  
  RandomTicTacToePlayer randomPlayer;
  HumanTicTacToePlayer humanPlayer;
  ComputerTicTacToePlayer computerPlayer;
};

#endif