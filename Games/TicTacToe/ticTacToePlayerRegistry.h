#ifndef __TICTACTOEPLAYERREGISTRY
#define __TICTACTOEPLAYERREGISTRY

#include "../../GameEngine/playerRegistry.h"

#include "./Players/ticTacToeComputerPlayer.h"
#include "./Players/ticTacToeHumanPlayer.h"
#include "./Players/ticTacToeRandomPlayer.h"

class TicTacToePlayerRegistry : public PlayerRegistry
{
  public:
  
  TicTacToePlayerRegistry()
  {
    // players.push_back(& computerPlayer);
    // players.push_back(& humanPlayer);
    // players.push_back(& randomPlayer);
  }
  
  private:
  
  TicTacToeComputerPlayer computerPlayer;
  TicTacToeHumanPlayer humanPlayer;
  TicTacToeRandomPlayer randomPlayer;
};

#endif