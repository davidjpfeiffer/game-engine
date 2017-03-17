#ifndef __COMPUTERTICTACTOEPLAYERPLAYER
#define __COMPUTERTICTACTOEPLAYERPLAYER

#include "ticTacToePlayer.h"
#include "ticTacToeGameState.h"
#include "TicTacToeBoardValue.h"

class ComputerTicTacToePlayer : public TicTacToePlayer
{
  public:

  std::string getName() const
  {
    return "Computer Player";
  }
  
  Player * clone() const
  {
    return new ComputerTicTacToePlayer;
  }
  
  void getMove(GameState * p_gameState)
  {
    TicTacToeGameState * gameState = (TicTacToeGameState *)p_gameState;
    TicTacToeGameState theoreticalGameState;

    // If we can win, take win
    
    for (unsigned i = 0; i < BOARD_SIZE; i++)
    {
      for (unsigned j = 0; j < BOARD_SIZE; j++)
      {
        theoreticalGameState.board = gameState->board;
        if (theoreticalGameState.board.get(i, j) == TicTacToeBoardValue::Empty)
        {
          theoreticalGameState.board.set(i, j, this->getBoardValue());
          if (thisPlayerHasWon(& theoreticalGameState))
          {
            gameState->board.set(i, j, this->getBoardValue());
            return;
          }
        }

      }
    }

    // If they can win, prevent win
    
    for (unsigned i = 0; i < BOARD_SIZE; i++)
    {
      for (unsigned j = 0; j < BOARD_SIZE; j++)
      {
        theoreticalGameState.board = gameState->board;
        if (theoreticalGameState.board.get(i, j) == TicTacToeBoardValue::Empty)
        {
          theoreticalGameState.board.set(i, j, this->getOpponentBoardValue());
          if (otherPlayerHasWon(& theoreticalGameState))
          {
            gameState->board.set(i, j, this->getBoardValue());
            return;
          }
        }
      }
    }

    // If middle available, take middle
    
    if (gameState->board.get(1, 1) == TicTacToeBoardValue::Empty)
    {
      gameState->board.set(1, 1, this->getBoardValue());
      return;
    }

    // Offensive Strategy
    
    if (gameState->board.get(1, 1) == this->getBoardValue() && gameState->board.numberOfAvailableMoves() == 7)
    {
      if (gameState->board.get(0, 1) == this->getOpponentBoardValue())
      {
        gameState->board.set(2, 2, this->getBoardValue());
        return;
      }
      else if (gameState->board.get(1, 2) == this->getOpponentBoardValue())
      {
        gameState->board.set(2, 0, this->getBoardValue());
        return;
      }
      else if (gameState->board.get(2, 1) == this->getOpponentBoardValue())
      {
        gameState->board.set(0, 0, this->getBoardValue());
        return;
      }
      else if (gameState->board.get(1, 0) == this->getOpponentBoardValue())
      {
        gameState->board.set(2, 2, this->getBoardValue());
        return;
      }
    }

    // Defensive Strategy
    
    if (gameState->board.get(1, 0) == this->getOpponentBoardValue() && gameState->board.get(2, 1) == this->getOpponentBoardValue() && gameState->board.get(2, 0) == TicTacToeBoardValue::Empty)
    {
      gameState->board.set(2, 0, this->getBoardValue());
      return;
    }
    else if (gameState->board.get(1, 0) == this->getOpponentBoardValue() && gameState->board.get(0, 1) == this->getOpponentBoardValue() && gameState->board.get(0, 0) == TicTacToeBoardValue::Empty)
    {
      gameState->board.set(0, 0, this->getBoardValue());
      return;
    }
    else if (gameState->board.get(0, 1) == this->getOpponentBoardValue() && gameState->board.get(1, 2) == this->getOpponentBoardValue() && gameState->board.get(0, 2) == TicTacToeBoardValue::Empty)
    {
      gameState->board.set(0, 2, this->getBoardValue());
      return;
    }
    else if (gameState->board.get(2, 1) == this->getOpponentBoardValue() && gameState->board.get(1, 2) == this->getOpponentBoardValue() && gameState->board.get(2, 2) == TicTacToeBoardValue::Empty)
    {
      gameState->board.set(2, 2, this->getBoardValue());
      return;
    }

    // If corner available, take corner
    
    if (gameState->board.get(0, 0) == TicTacToeBoardValue::Empty)
    {
      gameState->board.set(0, 0, this->getBoardValue());
      return;
    }
    else if (gameState->board.get(0, 2) == TicTacToeBoardValue::Empty)
    {
      gameState->board.set(0, 2, this->getBoardValue());
      return;
    }
    else if (gameState->board.get(2, 0) == TicTacToeBoardValue::Empty)
    {
      gameState->board.set(2, 0, this->getBoardValue());
      return;
    }
    else if (gameState->board.get(2, 2) == TicTacToeBoardValue::Empty)
    {
      gameState->board.set(2, 2, this->getBoardValue());
      return;
    }

    // Default to random move
    
    this->game.makeRandomMove(gameState, this->getPlayerValue());
  }
  
  private:

  bool thisPlayerHasWon(TicTacToeGameState * gameState)
  {
    return this->game.playerHasWon(gameState, this->getPlayerValue());
  }

  bool otherPlayerHasWon(TicTacToeGameState * gameState)
  {
    return this->game.playerHasWon(gameState, this->getOpponentPlayerValue());
  }
};

#endif