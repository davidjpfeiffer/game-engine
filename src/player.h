#ifndef __PLAYER
#define __PLAYER

#include <string>
#include <cstring>
#include "utilities.h"

class Player
{
private:

  BoardValue playerBoardValue;
  BoardValue opponentBoardValue;

public:

  virtual std::string getName()
  {
    std::string prefix = "Player ";
    char playerNumber = getBoardValueAsChar(this->getPlayerBoardValue());
    return prefix + playerNumber;
  }

  virtual Board getMove(const Board &) = 0;

  void setPlayerBoardValue(BoardValue playerBoardValue)
  {
    this->playerBoardValue = playerBoardValue;
    this->opponentBoardValue = this->playerBoardValue == BoardValue::PlayerTwo ? BoardValue::PlayerOne : BoardValue::PlayerTwo;
  }

  BoardValue getPlayerBoardValue()
  {
    return this->playerBoardValue;
  }

  BoardValue getOpponentBoardValue()
  {
    return this->opponentBoardValue;
  }
};

#endif