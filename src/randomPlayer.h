#ifndef __RANDOMPLAYER
#define __RANDOMPLAYER

#include "player.h"

class RandomPlayer : public Player
{
public:

  GameState getMove(const GameState & gameState)
  {
    return TicTacToe::makeRandomMove(gameState, this->getBoardValue());
  }
};

#endif