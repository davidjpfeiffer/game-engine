#ifndef __TICTACTOEGAME
#define __TICTACTOEGAME

#include <string>

#include "../../GameEngine/game.h"

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
  
  std::string getName() const
  {
    return "Tic Tac Toe";
  }
  
  Game * clone() const
  {
    return new TicTacToeGame;
  }
};

#endif