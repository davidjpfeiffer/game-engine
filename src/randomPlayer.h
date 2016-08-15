#ifndef __RANDOMPLAYER
#define __RANDOMPLAYER

#include <string>
#include "player.h"
#include "ticTacToe.h"

class RandomPlayer : public Player
{
public:

  Board getMove(const Board & board)
  {
    return this->game.makeRandomMove(board, this->getBoardValue());
  }
};

#endif