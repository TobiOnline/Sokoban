// Copyright Tobias Faller 2016

#ifndef PROJEKT_GAME_GAMELOGIC_H_
#define PROJEKT_GAME_GAMELOGIC_H_

#include <stdint.h>

#include "../Map/Map.h"
#include "../Map/State.h"
#include "../Map/StaticMap.h"

#include "../Stack/Stack.h"
#include "../Stack/StackFrame.h"

namespace Sokoban {

namespace SokobanGameLogic {

/*
 * Provides the number of commands useable in-game.
 */
enum Command {
  Up, Down, Left, Right, Undo
};

}

/*
 * Provides the basic sokoban logics.
 * E.g: Pushing boxes and detecting if the level was successfully finished.
 */
class GameLogic {
 private:
  struct timespec _startTime;
  struct timespec _endTime;
  bool _finished;
  uint32_t _steps;

  uint32_t _undoUsage;
  uint32_t _undoCount;
  Stack _stack;

  const StaticMap* _map;
  State* _state;

  /*
   * Checks if all targets have a box on top.
   */
  bool checkFinished();

 public:
  /*
   * Creates a new GameLogic object without a map loaded.
   */
  GameLogic();

  /*
   * Destroys this GameLogic object and possibly the saved state.
   */
  ~GameLogic();

  /*
   * Resets the internal state to the provided one
   */
  void reset(const Map* map);

  /*
   * Updates the current state.
   * Returns true if the state changed.
   */
  bool update(SokobanGameLogic::Command command);

  /*
   * Returns the current state.
   */
  const State* getState() const;

  /*
   * Returns if this level is currently solved.
   */
  bool isFinished() const;

  /*
   * Returns the current time taken to solve the level.
   * If the level is finished the stopped time is returned.
   */
  double getTime() const;

  /*
   * Returns the number of steps needed to solve the level.
   */
  uint32_t getSteps() const;

  /*
   * Sets the number of undo operations.
   */
  void setUndoCount(uint32_t count);

  /*
   * Returns the number of undo operations.
   */
  uint32_t getUndoCount() const;
};

}  // namespace Sokoban

#endif  // PROJEKT_GAME_GAMELOGIC_H_
