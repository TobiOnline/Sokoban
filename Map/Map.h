// Copyright Tobias Faller 2016

#ifndef PROJEKT_MAP_MAP_H_
#define PROJEKT_MAP_MAP_H_

#include <gtest/gtest_prod.h>

#include "State.h"
#include "StaticMap.h"

namespace Sokoban {

/*
 * Stores the initial state and the fixed blocks of the map.
 */
class Map {
 private:
  const State* _initState;
  const StaticMap* _map;

  const uint32_t _width;
  const uint32_t _height;

 public:
  /*
   * Constructs a new map with the given movable and static components.
   */
  Map(const State* state, const StaticMap* map, uint32_t width,
      uint32_t height);

  /*
   * Destroys the map with its components.
   */
  ~Map();

  /*
   * Returns the initial state of the map.
   */
  const State* getInitialState() const;

  /*
   * Returns the static components of this map.
   */
  const StaticMap* getMap() const;

  /*
   * Returns the width of the map.
   */
  uint32_t getWidth() const;

  /*
   * Returns the height of the map.
   */
  uint32_t getHeight() const;
};

}  // namespace Sokoban

#endif  // PROJEKT_MAP_MAP_H_
