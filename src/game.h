#ifndef __GAME
#define __GAME

#include <vector>
#include "player.h"

class Game
{
public:

  virtual void setupPlayers(Player & playerOne, Player & playerTwo) = 0;
  
  virtual bool isOver(const GameState & gameState) = 0;
  
  virtual bool isValidMove(const GameState & gameStateBeforeMove, const GameState & gameStateAfterMove, const PlayerValue & playerValue) = 0;
  
  virtual bool playerHasWon(const GameState & gameState, const PlayerValue & playerValue) = 0;
};

#endif