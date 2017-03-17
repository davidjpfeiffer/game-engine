#ifndef __RANDOMTICTACTOEPLAYER
#define __RANDOMTICTACTOEPLAYER

#include "ticTacToePlayer.h"
#include "ticTacToeGameState.h"

class RandomTicTacToePlayer : public TicTacToePlayer
{
  public:

  std::string getName() const
  {
    return "Random Player";
  }
  
  Player * clone() const
  {
    return new RandomTicTacToePlayer;
  }
  
  void getMove(GameState * gameState)
  {
    this->game.makeRandomMove(gameState, this->getPlayerValue());
  }
};

#endif