#ifndef __GAME
#define __GAME

#include <vector>
#include "player.h"

class Game
{
  public:
  
  virtual void newGameState(GameState ** gameState) = 0;
  
  virtual void copyGameState(GameState * original, GameState * copy) = 0;
  
  virtual bool isNotOver(GameState * gameState) = 0;
  
  virtual bool isValidMove(GameState * gameStateBeforeMove, GameState * gameStateAfterMove, const PlayerValue & playerValue) = 0;
  
  virtual bool playerHasWon(GameState * gameState, const PlayerValue & playerValue) = 0;
};

#endif