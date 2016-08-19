#ifndef __PLAYER
#define __PLAYER

#include <string>
#include <cstring>
#include "gameState.h"
#include "playerValue.h"

class Player
{
private:

  BoardValue playerBoardValue;
  BoardValue opponentBoardValue;

  PlayerValue playerValue;
  PlayerValue opponentPlayerValue;
  
  bool playerValueSet = false;
  
public:

  virtual GameState getMove(const GameState &) = 0;

  std::string getName() const
  {
    if (this->playerValue == PlayerValue::PlayerOne) return "Player 1";
    else return "Player 2";
  }
  
  void setPlayerValue(const PlayerValue & playerValue)
  {
    if (!this->playerValueSet)
    {
      this->playerBoardValue = playerValue == PlayerValue::PlayerOne ? BoardValue::O : BoardValue::X;
      this->opponentBoardValue = playerValue == PlayerValue::PlayerOne ? BoardValue::X : BoardValue::O;
      
      this->playerValue = playerValue;
      this->opponentPlayerValue = playerValue == PlayerValue::PlayerOne ? PlayerValue::PlayerTwo : PlayerValue::PlayerOne;
      
      this->playerValueSet = true;
    }
  }
  
  PlayerValue getPlayerValue() const
  {
    return this->playerValue;
  }
  
  PlayerValue getOpponentPlayerValue() const
  {
    return this->opponentPlayerValue;
  }
  
  BoardValue getBoardValue() const
  {
    return this->playerBoardValue;
  }
  
  BoardValue getOpponentBoardValue() const
  {
    return this->opponentBoardValue;
  }
};

#endif