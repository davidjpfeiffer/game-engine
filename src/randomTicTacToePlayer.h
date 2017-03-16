#ifndef __RANDOMTICTACTOEPLAYER
#define __RANDOMTICTACTOEPLAYER

#include "ticTacToePlayer.h"
#include "ticTacToeGameState.h"

class RandomTicTacToePlayer : public TicTacToePlayer
{
  public:

  void getMove(GameState * gameState)
  {
    this->game.makeRandomMove(gameState, this->getPlayerValue());
  }
};

#endif