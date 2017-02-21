#ifndef __TICTACTOEPLAYER
#define __TICTACTOEPLAYER

#include "ticTacToe.h"
#include "ticTacToeBoardValue.h"

class TicTacToePlayer : public Player
{
private:

  void onPlayerValueSet(const PlayerValue & playerValue)
  {
    this->playerBoardValue = playerValue == PlayerValue::PlayerOne ? TicTacToeBoardValue::O : TicTacToeBoardValue::X;
    this->opponentBoardValue = playerValue == PlayerValue::PlayerOne ? TicTacToeBoardValue::X : TicTacToeBoardValue::O;
  }
  
protected:

  TicTacToeBoardValue playerBoardValue;
  TicTacToeBoardValue opponentBoardValue;
  
  TicTacToe * game;
  
public:

  TicTacToeBoardValue getBoardValue() const
  {
    return this->playerBoardValue;
  }
  
  TicTacToeBoardValue getOpponentBoardValue() const
  {
    return this->opponentBoardValue;
  }
};

#endif