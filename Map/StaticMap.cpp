// Copyright Tobias Faller 2016

#include "StaticMap.h"

#include <string.h>

#include <set>

namespace Sokoban {

StaticMap::StaticMap(uint32_t width, uint32_t height)
      : _width(width), _height(height), _targets() {
  uint32_t size = width * height;
  size = (size / 4) + ((size % 4) ? 1 : 0);

  _map = new uint8_t[size];
  memset(_map, 0, size * sizeof(uint8_t));
}
StaticMap::StaticMap(const StaticMap* map)
    : _width(map->_width), _height(map->_height), _targets(map->_targets) {
  uint32_t size = _width * _height;
  size = (size / 4) + ((size % 4) ? 1 : 0);

  _map = new uint8_t[size];
  memcpy(_map, map->_map, size);
}
StaticMap::~StaticMap() {
  delete[] _map;
}

StaticType StaticMap::get(uint32_t x, uint32_t y) const {
  if ((x >= _width) || (y >= _height))
    throw INDEX_OUT_OF_BOUNDS;

  uint32_t index = (x + y * _width);

  switch ((_map[index / 4] >> ((index % 4) * 2)) & 0x03) {
  case StaticType::Nothing:
    return StaticType::Nothing;
  case StaticType::Block:
    return StaticType::Block;
  default:
    return StaticType::Target;
  }
}
void StaticMap::set(uint32_t x, uint32_t y, StaticType type) {
  if ((x >= _width) || (y >= _height))
    throw INDEX_OUT_OF_BOUNDS;

  switch (type) {
  case StaticType::Target:
    if (_targets.count(Coordinate(x, y)) == 0)
      _targets.insert(Coordinate(x, y));
    break;
  default:
    if (_targets.count(Coordinate(x, y)) > 0)
      _targets.erase(Coordinate(x, y));
    break;
  }

  uint32_t index = (x + y * _width);
  _map[index / 4] &= ~(0x03 << ((index % 4) * 2));
  _map[index / 4] |= (type << ((index % 4) * 2));
}

bool StaticMap::isEmpty(uint32_t x, uint32_t y) const {
  if ((x >= _width) || (y >= _height))
    throw INDEX_OUT_OF_BOUNDS;

  uint32_t index = (x + y * _width);
  return (((_map[index / 4] >> ((index % 4) * 2)) & 0x03)
      == StaticType::Nothing);
}
bool StaticMap::isBlock(uint32_t x, uint32_t y) const {
  if ((x >= _width) || (y >= _height))
    throw INDEX_OUT_OF_BOUNDS;

  uint32_t index = (x + y * _width);
  return (((_map[index / 4] >> ((index % 4) * 2)) & 0x03)
      == StaticType::Block);
}
bool StaticMap::isTarget(uint32_t x, uint32_t y) const {
  if ((x >= _width) || (y >= _height))
    throw INDEX_OUT_OF_BOUNDS;

  uint32_t index = (x + y * _width);
  return (((_map[index / 4] >> ((index % 4) * 2)) & 0x03)
      >= StaticType::Target);
}

StaticType StaticMap::get(Coordinate position) const {
  return this->get(position.x, position.y);
}
void StaticMap::set(Coordinate position, StaticType type) {
  this->set(position.x, position.y, type);
}

bool StaticMap::isEmpty(Coordinate position) const {
  return this->isEmpty(position.x, position.y);
}
bool StaticMap::isBlock(Coordinate position) const {
  return this->isBlock(position.x, position.y);
}
bool StaticMap::isTarget(Coordinate position) const {
  return this->isTarget(position.x, position.y);
}

uint32_t StaticMap::getWidth() const {
  return _width;
}
uint32_t StaticMap::getHeight() const {
  return _height;
}

StaticMap* StaticMap::clone() const {
  return new StaticMap(this);
}

const std::set<Coordinate>* StaticMap::getTargets() const {
  return &_targets;
}

}  // namespace Sokoban
