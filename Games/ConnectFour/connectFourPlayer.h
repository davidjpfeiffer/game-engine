#ifndef __CONNECTFOURPLAYER
#define __CONNECTFOURPLAYER

#include "../../GameEngine/Player.h"

#include "connectFourBoardValue.h"
#include "connectFourGameDefinition.h"

class ConnectFourPlayer : public Player
{
  private:
  
  ConnectFourBoardValue boardValue;
  ConnectFourBoardValue opponentBoardValue;
  
  void onPlayerValueSet(const PlayerValue & p_playerValue)
  {
    this->boardValue = p_playerValue == PlayerValue::PlayerOne ? ConnectFourBoardValuePlayerOne : ConnectFourBoardValuePlayerTwo;
    this->opponentBoardValue = p_playerValue == PlayerValue::PlayerOne ? ConnectFourBoardValuePlayerTwo : ConnectFourBoardValuePlayerOne;
  }
  
  protected:
  
  ConnectFourGameDefinition gameDefinition;
  
  public:
  
  ConnectFourBoardValue getBoardValue() const
  {
    return this->boardValue;
  }
  
  ConnectFourBoardValue getOpponentBoardValue() const
  {
    return this->opponentBoardValue;
  }
};

#endif