#ifndef __TICTACTOEPLAYER
#define __TICTACTOEPLAYER

#include "../../GameEngine/Player.h"

#include "ticTacToeGameDefinition.h"
#include "ticTacToeBoardValue.h"

class TicTacToePlayer : public Player
{
  private:
  
  TicTacToeBoardValue boardValue;
  TicTacToeBoardValue opponentBoardValue;
  
  void onPlayerValueSet(const PlayerValue & p_playerValue)
  {
    this->boardValue = p_playerValue == PlayerValue::PlayerOne ? TicTacToeBoardValuePlayerOne : TicTacToeBoardValuePlayerTwo;
    this->opponentBoardValue = p_playerValue == PlayerValue::PlayerOne ? TicTacToeBoardValuePlayerTwo : TicTacToeBoardValuePlayerOne;
  }
  
  protected:
  
  TicTacToeGameDefinition gameDefinition;
  
  public:
  
  TicTacToeBoardValue getBoardValue() const
  {
    return this->boardValue;
  }
  
  TicTacToeBoardValue getOpponentBoardValue() const
  {
    return this->opponentBoardValue;
  }
};

#endif