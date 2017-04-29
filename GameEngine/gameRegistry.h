#ifndef __GAMEREGISTRY
#define __GAMEREGISTRY

#include <vector>

#include "game.h"

#include "../Games/TicTacToe/ticTacToeGame.h"
#include "../Games/ConnectFour/connectFourGame.h"

class GameRegistry
{
  public:
  
  GameRegistry()
  {
    this->games.push_back(& ticTacToe);
    this->games.push_back(& connectFour);
  }
  
  std::vector<Game *> games;
  
  private:
  
  TicTacToeGame ticTacToe;
  ConnectFourGame connectFour;
};

#endif