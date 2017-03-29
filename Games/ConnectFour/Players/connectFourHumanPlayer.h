#ifndef __TICTACTOEHUMANPLAYER
#define __TICTACTOEHUMANPLAYER

#include <iostream>

#include "connectFourPlayer.h"
#include "connectFourGameState.h"

class ConnectFourHumanPlayer : public ConnectFourPlayer
{
  public:
  
  std::string getName() const
  {
    return "Human Player";
  }

  Player * clone() const
  {
    return new ConnectFourHumanPlayer;
  }
  
  void getMove(GameState * p_gameState) const
  {
    this->gameDefinition.makeRandomMove(p_gameState, this->getPlayerValue());
  }
};


#endif