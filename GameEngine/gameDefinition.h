#ifndef __GAMEDEFINITION
#define __GAMEDEFINITION

#include <vector>

#include "player.h"

class GameDefinition
{
  public:
  
  virtual bool isOver(GameState * gameState) const = 0;
  
  virtual bool isValidMove(GameState * beforeMove, GameState * afterMove, const PlayerValue & playerValue) const = 0;
  
  virtual bool playerHasWon(GameState * gameState, const PlayerValue & playerValue) const = 0;
  
  virtual void setInitialGameState(GameState ** gameState) const = 0;
};

#endif