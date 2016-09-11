// Copyright Tobias Faller 2016

#ifndef PROJEKT_BOXSTATE_H_
#define PROJEKT_BOXSTATE_H_

#include "Coordinate.h"

namespace Sokoban {

/*
 * Defines the state of a box.
 * If lockedX / lockedY are set, then the box is currently not movable in
 * this dimension (pushed against a wall / box).
 * If hardLockedX / hardLockedY is set, then the box can't be moved away from
 * this wall.
 * So if hardlockedX and hardLockedY is set then this box is not movable
 * anymore.
 */
struct BoxState {
  Coordinate position;

  /*
   * The state of these boxes are only used by the solver algorithm to save
   * computation-time.
   */
  bool lockedX;
  bool lockedY;

  bool hardLockedX;
  bool hardLockedY;
};

}  // namespace Sokoban

#endif  // PROJEKT_BOXSTATE_H_
