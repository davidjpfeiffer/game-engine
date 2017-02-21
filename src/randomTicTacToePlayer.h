#ifndef __RANDOMTICTACTOEPLAYER
#define __RANDOMTICTACTOEPLAYER

#include "ticTacToePlayer.h"
#include "ticTacToeGameState.h"

class RandomTicTacToePlayer : public TicTacToePlayer
{
public:

  GameState * getMove(GameState * gameState)
  {
    return this->game->makeRandomMove(gameState, this->getPlayerValue());
  }
};

#endif