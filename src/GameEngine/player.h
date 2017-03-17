#ifndef __PLAYER
#define __PLAYER

#include <string>
#include <cstring>

#include "gameState.h"
#include "playerValue.h"

class Player
{ 
  private:

  PlayerValue playerValue;
  PlayerValue opponentPlayerValue;
  
  bool playerValueSet = false;
  
  protected:
  
  virtual void onPlayerValueSet(const PlayerValue & playerValue) = 0;
  
  public:
  
  virtual void getMove(GameState *) = 0;
  
  virtual Player * clone() const = 0;
  
  virtual std::string getName() const = 0;
  
  void setPlayerValue(const PlayerValue & playerValue)
  {
    if (this->playerValueSet == false)
    {
      this->playerValue = playerValue;
      this->opponentPlayerValue = playerValue == PlayerValue::PlayerOne ? PlayerValue::PlayerTwo : PlayerValue::PlayerOne;
      
      this->playerValueSet = true;
      
      onPlayerValueSet(playerValue);
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
  
  std::string getPlayerValueAsString() const
  {
    return this->playerValue == PlayerValue::PlayerOne ? "Player One" : "Player Two";
  }
};

#endif