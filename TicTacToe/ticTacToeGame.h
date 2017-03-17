#ifndef __TICTACTOEGAME
#define __TICTACTOEGAME

#include <iostream>
#include <vector>

#include "../GameEngine/game.h"

#include "ticTacToeGameDefinition.h"
#include "ticTacToePlayerRegistry.h"

class TicTacToeGame : public Game
{
  public:
  
  TicTacToeGame()
  {
    this->gameDefinition = new TicTacToeGameDefinition;
    this->playerRegistry = new TicTacToePlayerRegistry;
  }
  
  ~TicTacToeGame()
  {
    delete this->gameDefinition;
    delete this->playerRegistry;
  }
};

#endif