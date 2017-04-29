#ifndef __TICTACTOERANDOMPLAYER
#define __TICTACTOERANDOMPLAYER

#include "../ticTacToePlayer.h"
#include "../ticTacToeGameState.h"

class TicTacToeRandomPlayer : public TicTacToePlayer
{
  public:

  std::string getName() const
  {
    return "Random Player";
  }
  
  Player * clone() const
  {
    return new TicTacToeRandomPlayer;
  }
  
  void getMove(GameState * gameState)
  {
    this->gameDefinition.makeRandomMove(gameState, this->getPlayerValue());
  }
};

#endif