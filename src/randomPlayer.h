#ifndef __RANDOMPLAYER
#define __RANDOMPLAYER

#include "ticTacToePlayer.h"

class RandomPlayer : public TicTacToePlayer
{
public:

  GameState getMove(const GameState & gameState)
  {
    return this->game->makeRandomMove(gameState, this->getPlayerValue());
  }
};

#endif