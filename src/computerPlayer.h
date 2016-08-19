#ifndef __COMPUTERPLAYER
#define __COMPUTERPLAYER

#include "player.h"

class ComputerPlayer : public Player
{
public:

  GameState getMove(const GameState & gameState)
  {
    GameState move = gameState;
    GameState theoreticalGameState;

    // If we can win, take win
    
    for (unsigned i = 0; i < BOARD_SIZE; i++)
    {
      for (unsigned j = 0; j < BOARD_SIZE; j++)
      {
        theoreticalGameState.board = gameState.board;
        if (theoreticalGameState.board.get(i, j) == BoardValue::Empty)
        {
          theoreticalGameState.board.set(i, j, this->getBoardValue());
          if (thisPlayerHasWon(theoreticalGameState))
          {
            move.board.set(i, j, this->getBoardValue());
            return move;
          }
        }

      }
    }

    // If they can win, prevent win
    
    for (unsigned i = 0; i < BOARD_SIZE; i++)
    {
      for (unsigned j = 0; j < BOARD_SIZE; j++)
      {
        theoreticalGameState.board = gameState.board;
        if (theoreticalGameState.board.get(i, j) == BoardValue::Empty)
        {
          theoreticalGameState.board.set(i, j, this->getOpponentBoardValue());
          if (otherPlayerHasWon(theoreticalGameState))
          {
            move.board.set(i, j, this->getBoardValue());
            return move;
          }
        }
      }
    }

    // If middle available, take middle
    
    if (move.board.get(1, 1) == BoardValue::Empty)
    {
      move.board.set(1, 1, this->getBoardValue());
      return move;
    }

    // Offensive Strategy
    
    if (move.board.get(1, 1) == this->getBoardValue() && gameState.board.numberOfAvailableMoves() == 7)
    {
      if (move.board.get(0, 1) == this->getOpponentBoardValue())
      {
        move.board.set(2, 2, this->getBoardValue());
        return move;
      }
      else if (move.board.get(1, 2) == this->getOpponentBoardValue())
      {
        move.board.set(2, 0, this->getBoardValue());
        return move;
      }
      else if (move.board.get(2, 1) == this->getOpponentBoardValue())
      {
        move.board.set(0, 0, this->getBoardValue());
        return move;
      }
      else if (move.board.get(1, 0) == this->getOpponentBoardValue())
      {
        move.board.set(2, 2, this->getBoardValue());
        return move;
      }
    }

    // Defensive Strategy
    
    if (move.board.get(1, 0) == this->getOpponentBoardValue() && move.board.get(2, 1) == this->getOpponentBoardValue() && move.board.get(2, 0) == BoardValue::Empty)
    {
      move.board.set(2, 0, this->getBoardValue());
      return move;
    }
    else if (move.board.get(1, 0) == this->getOpponentBoardValue() && move.board.get(0, 1) == this->getOpponentBoardValue() && move.board.get(0, 0) == BoardValue::Empty)
    {
      move.board.set(0, 0, this->getBoardValue());
      return move;
    }
    else if (move.board.get(0, 1) == this->getOpponentBoardValue() && move.board.get(1, 2) == this->getOpponentBoardValue() && move.board.get(0, 2) == BoardValue::Empty)
    {
      move.board.set(0, 2, this->getBoardValue());
      return move;
    }
    else if (move.board.get(2, 1) == this->getOpponentBoardValue() && move.board.get(1, 2) == this->getOpponentBoardValue() && move.board.get(2, 2) == BoardValue::Empty)
    {
      move.board.set(2, 2, this->getBoardValue());
      return move;
    }

    // If corner available, take corner
    
    if (move.board.get(0, 0) == BoardValue::Empty)
    {
      move.board.set(0, 0, this->getBoardValue());
      return move;
    }
    else if (move.board.get(0, 2) == BoardValue::Empty)
    {
      move.board.set(0, 2, this->getBoardValue());
      return move;
    }
    else if (move.board.get(2, 0) == BoardValue::Empty)
    {
      move.board.set(2, 0, this->getBoardValue());
      return move;
    }
    else if (move.board.get(2, 2) == BoardValue::Empty)
    {
      move.board.set(2, 2, this->getBoardValue());
      return move;
    }

    // Default to random move
    
    return TicTacToe::makeRandomMove(gameState, this->getPlayerValue());
  }
  
private:

  bool thisPlayerHasWon(const GameState & gameState)
  {
    return TicTacToe::playerHasWon(gameState, this->getPlayerValue());
  }

  bool otherPlayerHasWon(const GameState & gameState)
  {
    return TicTacToe::playerHasWon(gameState, this->getOpponentPlayerValue());
  }
};

#endif