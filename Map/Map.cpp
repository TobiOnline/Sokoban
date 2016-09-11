// Copyright Tobias Faller 2016

#include "Map.h"

namespace Sokoban {

Map::Map(const State* state, const StaticMap* map, uint32_t width,
      uint32_t height)
    : _initState(state), _map(map), _width(width), _height(height) { }

Map::~Map() {
  delete _initState;
  delete _map;
}

const State* Map::getInitialState() const {
  return _initState;
}
const StaticMap* Map::getMap() const {
  return _map;
}

uint32_t Map::getWidth() const {
  return _width;
}

uint32_t Map::getHeight() const {
  return _height;
}

}  // namespace Sokoban
