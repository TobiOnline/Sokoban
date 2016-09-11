// Copyright Tobias Faller 2016

#ifndef PROJEKT_MAP_STATE_H_
#define PROJEKT_MAP_STATE_H_

#include <stdint.h>

#include <unordered_map>

#include "../BoxState.h"
#include "../Coordinate.h"

namespace Sokoban {

/**
 * Data-object to store the position of the player and the movable boxes.
 * For easier computation the dead lock state of the boxes are stored in
 * the BoxState structure.
 */
class State {
 private:
  Coordinate _player;
  std::unordered_map<Coordinate, BoxState> _boxes;

  /*
   * Protected constructor for copying.
   */
  explicit State(const State* state);

 public:
  /*
   * Creates a new state.
   */
  State();

  /*
   * Destroys this state and its data.
   */
  ~State();

  /*
   * Returns the coordinates of the player.
   */
  Coordinate getPlayerPosition() const;

  /*
   * Sets the coordinates of the player.
   */
  void setPlayerPosition(Coordinate playerPosition);

  /*
   * Returns the list of boxes and their states.
   */
  const std::unordered_map<Coordinate, BoxState>* getBoxes() const;
  std::unordered_map<Coordinate, BoxState>* getBoxes();

  /*
   * Creates a copy of this State.
   */
  State* clone() const;
};

}  // namespace Sokoban

#endif  // PROJEKT_MAP_STATE_H_
