#ifndef __GAME
#define __GAME

#include <vector>
#include "player.h"

class Game
{
  public:
  
  virtual void setupPlayers(Player & playerOne, Player & playerTwo) = 0;
  
  virtual void initializeGameState(GameState **) = 0;
  
  // dont need this method, just use above to alloc memory
  virtual GameState * getCopyOfGameState(GameState *) = 0;
  
  virtual bool isOver(GameState * gameState) = 0;
  
  virtual bool isValidMove(GameState * gameStateBeforeMove, GameState * gameStateAfterMove, const PlayerValue & playerValue) = 0;
  
  virtual bool playerHasWon(GameState * gameState, const PlayerValue & playerValue) = 0;
};

#endif