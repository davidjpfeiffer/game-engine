#ifndef __BOARDVALUE
#define __BOARDVALUE

#include "playerValue.h"

enum BoardPieceValue {Empty, O, X};

class BoardValue
{
  public:
  
  BoardValue(BoardPieceValue boardPieceValue)
  {
    set(boardPieceValue);
  }
  
  friend bool operator== (const BoardValue & left, const BoardValue & right)
  {
    return left.boardPieceValue == right.boardPieceValue && left.playerValue == right.playerValue;
  }
  
  friend bool operator!= (const BoardValue & left, const BoardValue & right)
  {
    return left.boardPieceValue != right.boardPieceValue || left.playerValue != right.playerValue;
  }
  
  void set(BoardPieceValue boardPieceValue)
  {
    this->boardPieceValue = boardPieceValue;
    if (boardPieceValue == BoardPieceValue::O)
    {
      this->playerValueSet = true;
      this->playerValue = PlayerValue::PlayerOne;
    }
    else if (boardPieceValue == BoardPieceValue::X) this->playerValue = PlayerValue::PlayerTwo;
  }
  
  bool isEmpty()
  {
    return this->boardPieceValue == BoardPieceValue::Empty;
  }
  
  bool isPlayerBoardValue(const PlayerValue & playerValue)
  {
    return this->playerValue == playerValue;
  }
  
  private:
  
  bool boardPieceValueSet = false, playerValueSet = false;
  
  BoardPieceValue boardPieceValue;
  PlayerValue playerValue;
}

#endif