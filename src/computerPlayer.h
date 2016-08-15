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
    Board mainBoard = board;
    Board theoreticalBoard;

    // If we can win, take win
    for (unsigned i = 0; i < BOARD_SIZE; i++)
    {
      for (unsigned j = 0; j < BOARD_SIZE; j++)
      {
        theoreticalBoard = board;
        if (theoreticalBoard.get(i, j) == BoardValue::Empty)
        {
          theoreticalBoard.set(i, j, this->getBoardValue());
          if (IHaveWonOnBoard(theoreticalBoard))
          {
            mainBoard.set(i, j, this->getBoardValue());
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
        theoreticalBoard = board;
        if (theoreticalBoard.get(i, j) == BoardValue::Empty)
        {
          theoreticalBoard.set(i, j, this->getOpponentBoardValue());
          if (opponentHasWonOnBoard(theoreticalBoard))
          {
            mainBoard.set(i, j, this->getBoardValue());
            return mainBoard;
          }
        }
      }
    }

    // If middle available, take middle
    if (mainBoard.get(1, 1) == BoardValue::Empty)
    {
      mainBoard.set(1, 1, this->getBoardValue());
      return mainBoard;
    }

    // Offensive Strategy
    if (mainBoard.get(1, 1) == this->getBoardValue() && TicTacToe::numAvailableMoves(board) == 7)
    {
      if (mainBoard.get(0, 1) == this->getOpponentBoardValue())
      {
        mainBoard.set(2, 2, this->getBoardValue());
        return mainBoard;
      }
      else if (mainBoard.get(1, 2) == this->getOpponentBoardValue())
      {
        mainBoard.set(2, 0, this->getBoardValue());
        return mainBoard;
      }
      else if (mainBoard.get(2, 1) == this->getOpponentBoardValue())
      {
        mainBoard.set(0, 0, this->getBoardValue());
        return mainBoard;
      }
      else if (mainBoard.get(1, 0) == this->getOpponentBoardValue())
      {
        mainBoard.set(2, 2, this->getBoardValue());
        return mainBoard;
      }
    }

    // Defensive Strategy
    if (mainBoard.get(1, 0) == this->getOpponentBoardValue() && mainBoard.get(2, 1) == this->getOpponentBoardValue() && mainBoard.get(2, 0) == BoardValue::Empty)
    {
      mainBoard.set(2, 0, this->getBoardValue());
      return mainBoard;
    }
    else if (mainBoard.get(1, 0) == this->getOpponentBoardValue() && mainBoard.get(0, 1) == this->getOpponentBoardValue() && mainBoard.get(0, 0) == BoardValue::Empty)
    {
      mainBoard.set(0, 0, this->getBoardValue());
      return mainBoard;
    }
    else if (mainBoard.get(0, 1) == this->getOpponentBoardValue() && mainBoard.get(1, 2) == this->getOpponentBoardValue() && mainBoard.get(0, 2) == BoardValue::Empty)
    {
      mainBoard.set(0, 2, this->getBoardValue());
      return mainBoard;
    }
    else if (mainBoard.get(2, 1) == this->getOpponentBoardValue() && mainBoard.get(1, 2) == this->getOpponentBoardValue() && mainBoard.get(2, 2) == BoardValue::Empty)
    {
      mainBoard.set(2, 2, this->getBoardValue());
      return mainBoard;
    }

    // If corner available, take corner
    if (mainBoard.get(0, 0) == BoardValue::Empty)
    {
      mainBoard.set(0, 0, this->getBoardValue());
      return mainBoard;
    }
    else if (mainBoard.get(0, 2) == BoardValue::Empty)
    {
      mainBoard.set(0, 2, this->getBoardValue());
      return mainBoard;
    }
    else if (mainBoard.get(2, 0) == BoardValue::Empty)
    {
      mainBoard.set(2, 0, this->getBoardValue());
      return mainBoard;
    }
    else if (mainBoard.get(2, 2) == BoardValue::Empty)
    {
      mainBoard.set(2, 2, this->getBoardValue());
      return mainBoard;
    }

    // Default to random move
    return TicTacToe::makeRandomMove(board, this->getBoardValue());
  }
  
private:

  bool IHaveWonOnBoard(const Board & board)
  {
    if (this->getBoardValue() == BoardValue::PlayerOne) return TicTacToe::playerOneHasWon(board);
    else return TicTacToe::playerTwoHasWon(board);
  }

  bool opponentHasWonOnBoard(const Board & board)
  {
    if (this->getOpponentBoardValue() == BoardValue::PlayerOne) return TicTacToe::playerOneHasWon(board);
    else return TicTacToe::playerTwoHasWon(board);
  }
};

#endif