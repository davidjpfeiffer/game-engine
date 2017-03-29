#ifndef __CONNECTFOURGAMEDEFINITION
#define __CONNECTFOURGAMEDEFINITION

#include <vector>

#include "../../GameEngine/gameDefinition.h"
#include "../../GameEngine/Utilities/randomNumberGenerator.h"

#include "connectFourGameState.h"
#include "connectFourBoard.h"

class ConnectFourGameDefinition : public GameDefinition
{
  public:
  
  bool isOver(GameState * gameState) const
  {
    return noAvailableMoves(gameState) || playerOneHasWon(gameState) || playerTwoHasWon(gameState);
  }
  
  bool isValidMove(GameState * p_gameStateBeforeMove, GameState * p_gameStateAfterMove, const PlayerValue & playerValue) const
  {
    ConnectFourGameState * gameStateBeforeMove = (ConnectFourGameState *)p_gameStateBeforeMove;
    ConnectFourGameState * gameStateAfterMove = (ConnectFourGameState *)p_gameStateAfterMove;
    ConnectFourBoardValue playerBoardValue = playerValueToBoardValue(playerValue);
    
    if(numberOfMovesMade(gameStateBeforeMove, gameStateAfterMove) == 1)
    {
      for(unsigned row = 0; row < ConnectFourBoard::BOARD_HEIGHT; row++)
      {
        for(unsigned column = 0; column < ConnectFourBoard::BOARD_WIDTH; column++)
        {
          if(gameStateBeforeMove->board.get(row, column) != gameStateAfterMove->board.get(row, column))
          {
            if (gameStateBeforeMove->board.get(row, column) != ConnectFourBoardValueEmpty)
            {
              return false;
            }
            if (gameStateAfterMove->board.get(row, column) == playerBoardValue)
            {
              unsigned currentRow = row;
              
              while(ConnectFourBoard::isValidRow(++currentRow))
              {
                if (gameStateBeforeMove->board.get(currentRow, column) == ConnectFourBoardValueEmpty)
                {
                  return false;
                }
              }
              
              return true;
            }
          }
        }
      }
    }
    
    return false;
  }
  
  bool playerHasWon(GameState * p_gameState, const PlayerValue & playerValue) const
  {
    ConnectFourGameState * gameState = (ConnectFourGameState *)p_gameState;
    ConnectFourBoardValue playerBoardValue = playerValueToBoardValue(playerValue);
    
    unsigned consecutiveBoardValues = 0, currentRow, currentColumn;
    
    for(unsigned row = 0; row < ConnectFourBoard::BOARD_HEIGHT; row++)
    {
      for(unsigned column = 0; column < ConnectFourBoard::BOARD_WIDTH; column++)
      {
        if (gameState->board.get(row, column) != ConnectFourBoardValueEmpty)
        {
          // Up and Down
          
          currentRow = row;
          currentColumn = column;
          
          while(ConnectFourBoard::isValidRowAndColumn(currentRow, currentColumn) && gameState->board.get(currentRow, currentColumn) == playerBoardValue)
          {
            currentRow++;
            consecutiveBoardValues++;
          }
          
          currentRow = row;
          currentColumn = column;
          
          while(ConnectFourBoard::isValidRowAndColumn(currentRow, currentColumn) && gameState->board.get(currentRow, currentColumn) == playerBoardValue)
          {
            currentRow--;
            consecutiveBoardValues++;
          }
          
          if (consecutiveBoardValues > 4)
          {
            return true;
          }
          else
          {
            consecutiveBoardValues = 0;
          }
          
          // Left and Right
          
          currentRow = row;
          currentColumn = column;
          
          while(ConnectFourBoard::isValidRowAndColumn(currentRow, currentColumn) && gameState->board.get(currentRow, currentColumn) == playerBoardValue)
          {
            currentColumn--;
            consecutiveBoardValues++;
          }
          
          currentRow = row;
          currentColumn = column;
          
          while(ConnectFourBoard::isValidRowAndColumn(currentRow, currentColumn) && gameState->board.get(currentRow, currentColumn) == playerBoardValue)
          {
            currentColumn++;
            consecutiveBoardValues++;
          }
          
          if (consecutiveBoardValues > 4)
          {
            return true;
          }
          else
          {
            consecutiveBoardValues = 0;
          }
          
          // Increasing Diagonal
          
          currentRow = row;
          currentColumn = column;
          
          while(ConnectFourBoard::isValidRowAndColumn(currentRow, currentColumn) && gameState->board.get(currentRow, currentColumn) == playerBoardValue)
          {
            currentRow++;
            currentColumn++;
            consecutiveBoardValues++;
          }
          
          currentRow = row;
          currentColumn = column;
          
          while(ConnectFourBoard::isValidRowAndColumn(currentRow, currentColumn) && gameState->board.get(currentRow, currentColumn) == playerBoardValue)
          {
            currentRow--;
            currentColumn--;
            consecutiveBoardValues++;
          }
          
          if (consecutiveBoardValues > 4)
          {
            return true;
          }
          else
          {
            consecutiveBoardValues = 0;
          }
          
          // Decreasing Diagonal
          
          currentRow = row;
          currentColumn = column;
          
          while(ConnectFourBoard::isValidRowAndColumn(currentRow, currentColumn) && gameState->board.get(currentRow, currentColumn) == playerBoardValue)
          {
            currentRow--;
            currentColumn++;
            consecutiveBoardValues++;
          }
          
          currentRow = row;
          currentColumn = column;
          
          while(ConnectFourBoard::isValidRowAndColumn(currentRow, currentColumn) && gameState->board.get(currentRow, currentColumn) == playerBoardValue)
          {
            currentRow++;
            currentColumn--;
            consecutiveBoardValues++;
          }
          
          if (consecutiveBoardValues > 4)
          {
            return true;
          }
          else
          {
            consecutiveBoardValues = 0;
          }
        }
      }
    }
    
    return false;
  }
  
  void setInitialGameState(GameState ** gameState) const
  {
    * gameState = new ConnectFourGameState;
  }
  
  void makeRandomMove(GameState * p_gameState, const PlayerValue & playerValue) const
  {
    ConnectFourGameState * gameState = (ConnectFourGameState *)p_gameState;
    ConnectFourBoardValue playerBoardValue = playerValueToBoardValue(playerValue);
    
    std::vector<unsigned> availableMoves;
    ConnectFourGameState theoreticalGameState;
    
    for(unsigned column = 0; column < ConnectFourBoard::BOARD_WIDTH; column++)
    {
      theoreticalGameState.board = gameState->board;
      theoreticalGameState.board.set(column, playerBoardValue);
      if (isValidMove(gameState, & theoreticalGameState, playerValue))
      {
        availableMoves.push_back(column);
      }
    }
    
    unsigned randomMove = RandomNumberGenerator::instance()->get(availableMoves.size() - 1);
    
    gameState->board.set(availableMoves[randomMove], playerBoardValue);
  }
  
  private:
  
  bool noAvailableMoves(GameState * p_gameState) const
  {
    ConnectFourGameState * gameState = (ConnectFourGameState *)p_gameState;
    
    return gameState->board.numberOfAvailableMoves() == 0;
  }
  
  bool playerOneHasWon(GameState * gameState) const
  {
    return playerHasWon(gameState, PlayerValue::PlayerOne);
  }
  
  bool playerTwoHasWon(GameState * gameState) const
  {
    return playerHasWon(gameState, PlayerValue::PlayerTwo);
  }
  
  ConnectFourBoardValue playerValueToBoardValue(PlayerValue playerValue) const
  {
    return playerValue == PlayerValue::PlayerOne ? ConnectFourBoardValuePlayerOne : ConnectFourBoardValuePlayerTwo;
  }
  
  PlayerValue boardValueToPlayerValue(ConnectFourBoardValue boardValue) const
  {
    return boardValue == ConnectFourBoardValuePlayerOne ? PlayerValue::PlayerOne : PlayerValue::PlayerTwo;
  }
  
  unsigned numberOfMovesMade(ConnectFourGameState * before, ConnectFourGameState * after) const
  {
    unsigned count = 0;
    
    for(unsigned row = 0; row < ConnectFourBoard::BOARD_HEIGHT; row++)
    {
      for(unsigned column = 0; column < ConnectFourBoard::BOARD_WIDTH; column++)
      {
        if(before->board.get(row, column) != after->board.get(row, column))
        {
          count++;
        }
      }
    }
    
    return count;
  }
};

#endif