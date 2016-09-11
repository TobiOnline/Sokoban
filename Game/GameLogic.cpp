// Copyright Tobias Faller 2016

#include "GameLogic.h"

#include <utility>
#include <set>
#include <ctime>

#include "../Coordinate.h"

#include "../Map/Map.h"
#include "../Map/State.h"
#include "../Map/StaticMap.h"

#include "../Stack/Stack.h"
#include "../Stack/StackFrame.h"

namespace Sokoban {

GameLogic::GameLogic()
    : _startTime(), _endTime(), _finished(false), _steps(0),
      _undoUsage(0), _undoCount(0) {
  _map = nullptr;
  _state = nullptr;
}
GameLogic::~GameLogic() {
  if (_state)
    delete _state;
}

void GameLogic::reset(const Map* map) {
  if (_state)
    delete _state;

  // Copy state to make it mutable
  // (use _map, porb. future: smartpointer?)
  _state = new State(*(map->getInitialState()));
  _map = map->getMap();

  _steps = 0;
  _finished = false;
  clock_gettime(CLOCK_MONOTONIC, &_startTime);
}

bool GameLogic::update(SokobanGameLogic::Command command) {
  if (_finished)
    return false;

  std::unordered_map<Coordinate, BoxState>* boxes = _state->getBoxes();
  Coordinate playerPos = Coordinate(_state->getPlayerPosition());

  StackFrame frame;

  switch (command) {
  case SokobanGameLogic::Command::Up:
  {
    frame.setDirection(Direction::Up);

    // Walk agains border
    if (playerPos.y < 1)
      break;

    // Walk against wall
    if (_map->isBlock(playerPos.x, playerPos.y - 1))
      break;

    // Push box
    if (boxes->count(Coordinate(playerPos.x, playerPos.y - 1)) > 0) {
      // Push box against border
      if (playerPos.y < 2)
        break;

      // Push box against wall
      if (_map->isBlock(playerPos.x, playerPos.y - 2))
        break;

      // Push box against box
      if (boxes->count(Coordinate(playerPos.x, playerPos.y - 2)) > 0)
        break;

      for (;;) {
        std::unordered_map<Coordinate, BoxState>::iterator it
          = boxes->find(Coordinate(playerPos.x, playerPos.y - 1));
        if (it == boxes->end())
          break;

        Coordinate newBoxPosition = Coordinate(it->first);
        BoxState newBoxState = BoxState(it->second);

        // remove box from map
        boxes->erase(it->first);

        newBoxPosition.y--;
        newBoxState.position.y--;

        // re-insert with new index
        boxes->insert(std::pair<Coordinate, BoxState>(newBoxPosition,
            newBoxState));
      }

      frame.setMoveBox(true);

      // Check if box was moved onto target
      if (boxes->count(Coordinate(playerPos.x, playerPos.y - 2)) > 0
          && _map->isTarget(playerPos.x, playerPos.y - 2) && checkFinished())
        _finished = true;
    }  // end push box

    // move player
    _state->setPlayerPosition(Coordinate(playerPos.x, playerPos.y - 1));
    _steps++;

    _stack.push(frame);
    if (_undoUsage > 0) {
      _undoUsage--;
    }
    return true;
  }  // end case Up
  case SokobanGameLogic::Command::Down:
  {
    frame.setDirection(Direction::Down);

    // Walk agains border
    if (playerPos.y + 1 >= _map->getHeight())
      break;

    // Walk against wall
    if (_map->isBlock(playerPos.x, playerPos.y + 1))
      break;

    // Push box
    if (boxes->count(Coordinate(playerPos.x, playerPos.y + 1)) > 0) {
      // Push box against border
      if (playerPos.y + 2 >= _map->getHeight())
        break;

      // Push box against wall
      if (_map->isBlock(playerPos.x, playerPos.y + 2))
        break;

      // Push box against box
      if (boxes->count(Coordinate(playerPos.x, playerPos.y + 2)) > 0)
        break;

      for (;;) {
        std::unordered_map<Coordinate, BoxState>::iterator it
          = boxes->find(Coordinate(playerPos.x, playerPos.y + 1));
        if (it == boxes->end())
          break;

        Coordinate newBoxPosition = Coordinate(it->first);
        BoxState newBoxState = BoxState(it->second);

        // remove box from map
        boxes->erase(it->first);

        newBoxPosition.y++;
        newBoxState.position.y++;

        // re-insert with new index
        boxes->insert(std::pair<Coordinate, BoxState>(newBoxPosition,
            newBoxState));
      }

      frame.setMoveBox(true);

      // Check if box was moved onto target
      if (boxes->count(Coordinate(playerPos.x, playerPos.y + 2)) > 0
          && _map->isTarget(playerPos.x, playerPos.y + 2) && checkFinished())
        _finished = true;
    }  // end push box

    // move player
    _state->setPlayerPosition(Coordinate(playerPos.x, playerPos.y + 1));
    _steps++;

    _stack.push(frame);
    if (_undoUsage > 0) {
      _undoUsage--;
    }
    return true;
  }  // end case Down
  case SokobanGameLogic::Command::Left:
  {
    frame.setDirection(Direction::Left);

    // Walk agains border
    if (playerPos.x < 1)
      break;

    // Walk against wall
    if (_map->isBlock(playerPos.x - 1, playerPos.y))
      break;

    // Push box
    if (boxes->count(Coordinate(playerPos.x - 1, playerPos.y)) > 0) {
      // Push box against border
      if (playerPos.x < 2)
        break;

      // Push box against wall
      if (_map->isBlock(playerPos.x - 2, playerPos.y))
        break;

      // Push box against box
      if (boxes->count(Coordinate(playerPos.x - 2, playerPos.y)) > 0)
        break;

      for (;;) {
        std::unordered_map<Coordinate, BoxState>::iterator it
          = boxes->find(Coordinate(playerPos.x - 1, playerPos.y));
        if (it == boxes->end())
          break;

        Coordinate newBoxPosition = Coordinate(it->first);
        BoxState newBoxState = BoxState(it->second);

        // remove box from map
        boxes->erase(it->first);

        newBoxPosition.x--;
        newBoxState.position.x--;

        // re-insert with new index
        boxes->insert(std::pair<Coordinate, BoxState>(newBoxPosition,
            newBoxState));
      }

      frame.setMoveBox(true);

      // Check if box was moved onto target
      if (boxes->count(Coordinate(playerPos.x - 2, playerPos.y)) > 0
          && _map->isTarget(playerPos.x - 2, playerPos.y) && checkFinished())
        _finished = true;
    }  // end push box

    // move player
    _state->setPlayerPosition(Coordinate(playerPos.x - 1, playerPos.y));
    _steps++;

    _stack.push(frame);
    if (_undoUsage > 0) {
      _undoUsage--;
    }
    return true;
  }  // end case Left
  case SokobanGameLogic::Command::Right:
  {
    frame.setDirection(Direction::Right);

    // Walk agains border
    if (playerPos.x + 1 >= _map->getWidth())
      break;

    // Walk against wall
    if (_map->isBlock(playerPos.x + 1, playerPos.y))
      break;

    // Push box
    if (boxes->count(Coordinate(playerPos.x + 1, playerPos.y)) > 0) {
      // Push box against border
      if (playerPos.x + 2 >= _map->getWidth())
        break;

      // Push box against wall
      if (_map->isBlock(playerPos.x + 2, playerPos.y))
        break;

      // Push box against box
      if (boxes->count(Coordinate(playerPos.x + 2, playerPos.y)) > 0)
        break;

      for (;;) {
        std::unordered_map<Coordinate, BoxState>::iterator it
          = boxes->find(Coordinate(playerPos.x + 1, playerPos.y));
        if (it == boxes->end())
          break;

        Coordinate newBoxPosition = Coordinate(it->first);
        BoxState newBoxState = BoxState(it->second);

        // remove box from map
        boxes->erase(it->first);

        newBoxPosition.x++;
        newBoxState.position.x++;

        // re-insert with new index
        boxes->insert(std::pair<Coordinate, BoxState>(newBoxPosition,
            newBoxState));
      }

      frame.setMoveBox(true);

      // Check if box was moved onto target
      if (boxes->count(Coordinate(playerPos.x + 2, playerPos.y)) > 0
          && _map->isTarget(playerPos.x + 2, playerPos.y))
        checkFinished();
    }  // end push box

    // move player
    _state->setPlayerPosition(Coordinate(playerPos.x + 1, playerPos.y));
    _steps++;

    _stack.push(frame);
    if (_undoUsage > 0) {
      _undoUsage--;
    }
    return true;
  }  // end case Right
  case SokobanGameLogic::Command::Undo:
    if ((_undoUsage >= _undoCount) || _stack.isEmpty())
      return false;

    _undoUsage++;
    _stack.pop(&frame);

    int32_t modX = 0;
    int32_t modY = 0;

    switch (frame.getDirection()) {
    case Direction::Up:
      modY = 1;
      break;
    case Direction::Down:
      modY = -1;
      break;
    case Direction::Left:
      modX = 1;
      break;
    case Direction::Right:
      modX = -1;
      break;
    }

    _state->setPlayerPosition(
        Coordinate(playerPos.x + modX, playerPos.y + modY));

    if (frame.isMoveBox()) {
      for (;;) {
        std::unordered_map<Coordinate, BoxState>::iterator it
          = boxes->find(Coordinate(playerPos.x - modX, playerPos.y - modY));
        if (it == boxes->end())
          break;

        BoxState newBoxState = BoxState(it->second);

        // remove box from map
        boxes->erase(it->first);

        newBoxState.position = Coordinate(playerPos);

        // re-insert with new index
        boxes->insert(std::pair<Coordinate, BoxState>(playerPos, newBoxState));
      }
    }
    return true;
  }

  return false;
}

const State* GameLogic::getState() const {
  return _state;
}

bool GameLogic::isFinished() const {
  return _finished;
}

bool GameLogic::checkFinished() {
  std::unordered_map<Coordinate, BoxState>* boxes = _state->getBoxes();

  // Check if all targets have a box on top
  std::set<Coordinate>::const_iterator it = _map->getTargets()->cbegin();
  const std::set<Coordinate>::const_iterator end = _map->getTargets()->cend();

  while (it != end) {
    if (boxes->count(*it) == 0)
      return false;

    ++it;
  }

  // All coordinates iterated an no return
  // -> Each target has a box
  clock_gettime(CLOCK_MONOTONIC, &_endTime);
  _finished = true;
  return true;
}

double GameLogic::getTime() const {
  double deltaTime;

  if (_finished) {
    deltaTime = (_endTime.tv_sec - _startTime.tv_sec);
    deltaTime += (_endTime.tv_nsec - _startTime.tv_nsec) / 1000000000.0;
  } else {
    struct timespec currentTime;
    clock_gettime(CLOCK_MONOTONIC, &currentTime);

    deltaTime = (currentTime.tv_sec - _startTime.tv_sec);
    deltaTime += (currentTime.tv_nsec - _startTime.tv_nsec) / 1000000000.0;
  }

  return deltaTime;
}

uint32_t GameLogic::getSteps() const {
  return _steps;
}

void GameLogic::setUndoCount(uint32_t count) {
  _undoCount = count;
}

uint32_t GameLogic::getUndoCount() const {
  return _undoCount;
}

}  // namespace Sokoban
