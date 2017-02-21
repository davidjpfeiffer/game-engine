#ifndef __GAME
#define __GAME

#include <vector>
#include "player.h"

class Game
{
public:

  virtual void setupPlayers(Player & playerOne, Player & playerTwo) = 0;
  
  virtual bool isOver(GameState * gameState) = 0;
  
  virtual bool isValidMove(GameState * gameStateBeforeMove, GameState * gameStateAfterMove, const PlayerValue & playerValue) = 0;
  
  virtual bool playerHasWon(GameState * gameState, const PlayerValue & playerValue) = 0;
  
  // virtual GameState * getCopyOfGameState(GameState * gameState);
};

#endif