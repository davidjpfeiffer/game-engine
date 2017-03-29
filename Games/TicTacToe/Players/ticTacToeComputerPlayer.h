#ifndef __TICTACTOECOMPUTERPLAYER
#define __TICTACTOECOMPUTERPLAYER

#include "ticTacToePlayer.h"
#include "ticTacToeGameState.h"
#include "ticTacToeBoardValue.h"

class TicTacToeComputerPlayer : public TicTacToePlayer
{
  public:

  std::string getName() const
  {
    return "Computer Player";
  }
  
  Player * clone() const
  {
    return new TicTacToeComputerPlayer;
  }
  
  void getMove(GameState * p_gameState) const
  {
    TicTacToeGameState * gameState = (TicTacToeGameState *)p_gameState;
    TicTacToeGameState theoreticalGameState;
    
    // If we can win, take win
    
    for (unsigned i = 0; i < TicTacToeBoard::BOARD_SIZE; i++)
    {
      for (unsigned j = 0; j < TicTacToeBoard::BOARD_SIZE; j++)
      {
        theoreticalGameState.board = gameState->board;
        if (theoreticalGameState.board.get(i, j) == TicTacToeBoardValueEmpty)
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
    
    for (unsigned i = 0; i < TicTacToeBoard::BOARD_SIZE; i++)
    {
      for (unsigned j = 0; j < TicTacToeBoard::BOARD_SIZE; j++)
      {
        theoreticalGameState.board = gameState->board;
        if (theoreticalGameState.board.get(i, j) == TicTacToeBoardValueEmpty)
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
    
    if (gameState->board.get(1, 1) == TicTacToeBoardValueEmpty)
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
    
    if (gameState->board.get(1, 0) == this->getOpponentBoardValue() && gameState->board.get(2, 1) == this->getOpponentBoardValue() && gameState->board.get(2, 0) == TicTacToeBoardValueEmpty)
    {
      gameState->board.set(2, 0, this->getBoardValue());
      return;
    }
    else if (gameState->board.get(1, 0) == this->getOpponentBoardValue() && gameState->board.get(0, 1) == this->getOpponentBoardValue() && gameState->board.get(0, 0) == TicTacToeBoardValueEmpty)
    {
      gameState->board.set(0, 0, this->getBoardValue());
      return;
    }
    else if (gameState->board.get(0, 1) == this->getOpponentBoardValue() && gameState->board.get(1, 2) == this->getOpponentBoardValue() && gameState->board.get(0, 2) == TicTacToeBoardValueEmpty)
    {
      gameState->board.set(0, 2, this->getBoardValue());
      return;
    }
    else if (gameState->board.get(2, 1) == this->getOpponentBoardValue() && gameState->board.get(1, 2) == this->getOpponentBoardValue() && gameState->board.get(2, 2) == TicTacToeBoardValueEmpty)
    {
      gameState->board.set(2, 2, this->getBoardValue());
      return;
    }

    // If corner available, take corner
    
    if (gameState->board.get(0, 0) == TicTacToeBoardValueEmpty)
    {
      gameState->board.set(0, 0, this->getBoardValue());
      return;
    }
    else if (gameState->board.get(0, 2) == TicTacToeBoardValueEmpty)
    {
      gameState->board.set(0, 2, this->getBoardValue());
      return;
    }
    else if (gameState->board.get(2, 0) == TicTacToeBoardValueEmpty)
    {
      gameState->board.set(2, 0, this->getBoardValue());
      return;
    }
    else if (gameState->board.get(2, 2) == TicTacToeBoardValueEmpty)
    {
      gameState->board.set(2, 2, this->getBoardValue());
      return;
    }

    // Default to random move
    
    this->gameDefinition.makeRandomMove(gameState, this->getPlayerValue());
  }
  
  private:

  bool thisPlayerHasWon(TicTacToeGameState * gameState) const
  {
    return this->gameDefinition.playerHasWon(gameState, this->getPlayerValue());
  }

  bool otherPlayerHasWon(TicTacToeGameState * gameState) const
  {
    return this->gameDefinition.playerHasWon(gameState, this->getOpponentPlayerValue());
  }
};

#endif