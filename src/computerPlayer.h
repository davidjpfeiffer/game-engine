#ifndef __COMPUTERPLAYER
#define __COMPUTERPLAYER

#include <string>
#include "player.h"
#include "ticTacToe.h"

class ComputerPlayer : public Player
{
public:

  Board getMove(const Board & board)
  {
    Board mainBoard = this->game.getCopyOfBoard(board);
    Board theoreticalBoard;

    // If we can win, take win
    for (unsigned i = 0; i < BOARD_SIZE; i++)
    {
      for (unsigned j = 0; j < BOARD_SIZE; j++)
      {
        theoreticalBoard = this->game.getCopyOfBoard(board);
        if (theoreticalBoard[i][j] == BoardValue::Empty)
        {
          theoreticalBoard[i][j] = this->getBoardValue();
          if (IHaveWonOnBoard(theoreticalBoard))
          {
            mainBoard[i][j] = this->getBoardValue();
            return mainBoard;
          }
        }

      }
    }

    // If they can win, prevent win
    for (unsigned i = 0; i < BOARD_SIZE; i++)
    {
      for (unsigned j = 0; j < BOARD_SIZE; j++)
      {
        theoreticalBoard = this->game.getCopyOfBoard(board);
        if (theoreticalBoard[i][j] == BoardValue::Empty)
        {
          theoreticalBoard[i][j] = this->getOpponentBoardValue();
          if (opponentHasWonOnBoard(theoreticalBoard))
          {
            mainBoard[i][j] = this->getBoardValue();
            return mainBoard;
          }
        }
      }
    }

    // If middle available, take middle
    if (mainBoard[1][1] == BoardValue::Empty)
    {
      mainBoard[1][1] = this->getBoardValue();
      return mainBoard;
    }

    // Offensive Strategy
    if (mainBoard[1][1] == this->getBoardValue() && this->game.numAvailableMoves(board) == 7)
    {
      if (mainBoard[0][1] == this->getOpponentBoardValue())
      {
        mainBoard[2][2] = this->getBoardValue();
        return mainBoard;
      }
      else if (mainBoard[1][2] == this->getOpponentBoardValue())
      {
        mainBoard[2][0] = this->getBoardValue();
        return mainBoard;
      }
      else if (mainBoard[2][1] == this->getOpponentBoardValue())
      {
        mainBoard[0][0] = this->getBoardValue();
        return mainBoard;
      }
      else if (mainBoard[1][0] == this->getOpponentBoardValue())
      {
        mainBoard[2][2] = this->getBoardValue();
        return mainBoard;
      }
    }

    // Defensive Strategy
    if (mainBoard[1][0] == this->getOpponentBoardValue() && mainBoard[2][1] == this->getOpponentBoardValue() && mainBoard[2][0] == BoardValue::Empty)
    {
      mainBoard[2][0] = this->getBoardValue();
      return mainBoard;
    }
    else if (mainBoard[1][0] == this->getOpponentBoardValue() && mainBoard[0][1] == this->getOpponentBoardValue() && mainBoard[0][0] == BoardValue::Empty)
    {
      mainBoard[0][0] = this->getBoardValue();
      return mainBoard;
    }
    else if (mainBoard[0][1] == this->getOpponentBoardValue() && mainBoard[1][2] == this->getOpponentBoardValue() && mainBoard[0][2] == BoardValue::Empty)
    {
      mainBoard[0][2] = this->getBoardValue();
      return mainBoard;
    }
    else if (mainBoard[2][1] == this->getOpponentBoardValue() && mainBoard[1][2] == this->getOpponentBoardValue() && mainBoard[2][2] == BoardValue::Empty)
    {
      mainBoard[2][2] = this->getBoardValue();
      return mainBoard;
    }

    // If corner available, take corner
    if (mainBoard[0][0] == BoardValue::Empty)
    {
      mainBoard[0][0] = this->getBoardValue();
      return mainBoard;
    }
    else if (mainBoard[0][2] == BoardValue::Empty)
    {
      mainBoard[0][2] = this->getBoardValue();
      return mainBoard;
    }
    else if (mainBoard[2][0] == BoardValue::Empty)
    {
      mainBoard[2][0] = this->getBoardValue();
      return mainBoard;
    }
    else if (mainBoard[2][2] == BoardValue::Empty)
    {
      mainBoard[2][2] = this->getBoardValue();
      return mainBoard;
    }

    // Default to random move
    return this->game.makeRandomMove(board, this->getBoardValue());
  }
  
private:

  bool IHaveWonOnBoard(const Board & board)
  {
    if (this->getBoardValue() == BoardValue::PlayerOne) return this->game.playerOneHasWon(board);
    else return this->game.playerTwoHasWon(board);
  }

  bool opponentHasWonOnBoard(const Board & board)
  {
    if (this->getOpponentBoardValue() == BoardValue::PlayerOne) return this->game.playerOneHasWon(board);
    else return this->game.playerTwoHasWon(board);
  }
};

#endif