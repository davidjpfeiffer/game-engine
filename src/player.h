#ifndef __PLAYER
#define __PLAYER

#include <string>
#include <cstring>
#include "gameState.h"

class Player
{
private:

  BoardValue boardValue;
  BoardValue opponentBoardValue;
  
public:

  virtual GameState getMove(const GameState &) = 0;

  std::string getName() const
  {
    if (this->boardValue == BoardValue::PlayerOne) return "Player 1";
    else return "Player 2";
  }
  
  void setBoardValue(BoardValue boardValue)
  {
    this->boardValue = boardValue;
    this->opponentBoardValue = this->boardValue == BoardValue::PlayerTwo ? BoardValue::PlayerOne : BoardValue::PlayerTwo;
  }

  BoardValue getBoardValue() const
  {
    return this->boardValue;
  }

  BoardValue getOpponentBoardValue() const
  {
    return this->opponentBoardValue;
  }
};

#endif