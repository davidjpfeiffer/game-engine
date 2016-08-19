#ifndef __COMPUTERPLAYER
#define __COMPUTERPLAYER

#include "player.h"

class ComputerPlayer : public Player
{
public:

  GameState getMove(const GameState & gameState)
  {
    GameState gameStateAfterMove = gameState;
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
            gameStateAfterMove.board.set(i, j, this->getBoardValue());
            return gameStateAfterMove;
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
            gameStateAfterMove.board.set(i, j, this->getBoardValue());
            return gameStateAfterMove;
          }
        }
      }
    }

    // If middle available, take middle
    
    if (gameStateAfterMove.board.get(1, 1) == BoardValue::Empty)
    {
      gameStateAfterMove.board.set(1, 1, this->getBoardValue());
      return gameStateAfterMove;
    }

    // Offensive Strategy
    
    if (gameStateAfterMove.board.get(1, 1) == this->getBoardValue() && gameState.board.numberOfAvailableMoves() == 7)
    {
      if (gameStateAfterMove.board.get(0, 1) == this->getOpponentBoardValue())
      {
        gameStateAfterMove.board.set(2, 2, this->getBoardValue());
        return gameStateAfterMove;
      }
      else if (gameStateAfterMove.board.get(1, 2) == this->getOpponentBoardValue())
      {
        gameStateAfterMove.board.set(2, 0, this->getBoardValue());
        return gameStateAfterMove;
      }
      else if (gameStateAfterMove.board.get(2, 1) == this->getOpponentBoardValue())
      {
        gameStateAfterMove.board.set(0, 0, this->getBoardValue());
        return gameStateAfterMove;
      }
      else if (gameStateAfterMove.board.get(1, 0) == this->getOpponentBoardValue())
      {
        gameStateAfterMove.board.set(2, 2, this->getBoardValue());
        return gameStateAfterMove;
      }
    }

    // Defensive Strategy
    
    if (gameStateAfterMove.board.get(1, 0) == this->getOpponentBoardValue() && gameStateAfterMove.board.get(2, 1) == this->getOpponentBoardValue() && gameStateAfterMove.board.get(2, 0) == BoardValue::Empty)
    {
      gameStateAfterMove.board.set(2, 0, this->getBoardValue());
      return gameStateAfterMove;
    }
    else if (gameStateAfterMove.board.get(1, 0) == this->getOpponentBoardValue() && gameStateAfterMove.board.get(0, 1) == this->getOpponentBoardValue() && gameStateAfterMove.board.get(0, 0) == BoardValue::Empty)
    {
      gameStateAfterMove.board.set(0, 0, this->getBoardValue());
      return gameStateAfterMove;
    }
    else if (gameStateAfterMove.board.get(0, 1) == this->getOpponentBoardValue() && gameStateAfterMove.board.get(1, 2) == this->getOpponentBoardValue() && gameStateAfterMove.board.get(0, 2) == BoardValue::Empty)
    {
      gameStateAfterMove.board.set(0, 2, this->getBoardValue());
      return gameStateAfterMove;
    }
    else if (gameStateAfterMove.board.get(2, 1) == this->getOpponentBoardValue() && gameStateAfterMove.board.get(1, 2) == this->getOpponentBoardValue() && gameStateAfterMove.board.get(2, 2) == BoardValue::Empty)
    {
      gameStateAfterMove.board.set(2, 2, this->getBoardValue());
      return gameStateAfterMove;
    }

    // If corner available, take corner
    
    if (gameStateAfterMove.board.get(0, 0) == BoardValue::Empty)
    {
      gameStateAfterMove.board.set(0, 0, this->getBoardValue());
      return gameStateAfterMove;
    }
    else if (gameStateAfterMove.board.get(0, 2) == BoardValue::Empty)
    {
      gameStateAfterMove.board.set(0, 2, this->getBoardValue());
      return gameStateAfterMove;
    }
    else if (gameStateAfterMove.board.get(2, 0) == BoardValue::Empty)
    {
      gameStateAfterMove.board.set(2, 0, this->getBoardValue());
      return gameStateAfterMove;
    }
    else if (gameStateAfterMove.board.get(2, 2) == BoardValue::Empty)
    {
      gameStateAfterMove.board.set(2, 2, this->getBoardValue());
      return gameStateAfterMove;
    }

    // Default to random move
    
    return TicTacToe::makeRandomMove(gameState, this->getBoardValue());
  }
  
private:

  bool thisPlayerHasWon(const GameState & gameState)
  {
    if (this->getBoardValue() == BoardValue::PlayerOne) return TicTacToe::playerOneHasWon(gameState);
    else return TicTacToe::playerTwoHasWon(gameState);
  }

  bool otherPlayerHasWon(const GameState & gameState)
  {
    if (this->getOpponentBoardValue() == BoardValue::PlayerOne) return TicTacToe::playerOneHasWon(gameState);
    else return TicTacToe::playerTwoHasWon(gameState);
  }
};

#endif