// Copyright Tobia Faller 2016

#include "MapBuilder.h"

#include <vector>
#include <algorithm>
#include <utility>
#include <iostream>

#include "../Coordinate.h"

#include "StaticMap.h"
#include "State.h"
#include "Map.h"

using Sokoban::SokobanBuilder::Error;

namespace Sokoban {

MapBuilder::MapBuilder() {
  _blocks = std::vector<Coordinate>();
  _boxes = std::vector<Coordinate>();
  _targets = std::vector<Coordinate>();
  _player = Coordinate(0, 0);

  _width = 1;
  _height = 1;
}
MapBuilder::~MapBuilder() { }

MapBuilder* MapBuilder::addBlock(Coordinate position) {
  _blocks.push_back(position);

  _width = std::max(_width, position.x + 1);
  _height = std::max(_height, position.y + 1);
  return this;
}
MapBuilder* MapBuilder::addTarget(Coordinate position) {
  _targets.push_back(position);

  _width = std::max(_width, position.x + 1);
  _height = std::max(_height, position.y + 1);
  return this;
}
MapBuilder* MapBuilder::addBox(Coordinate position) {
  _boxes.push_back(position);

  _width = std::max(_width, position.x + 1);
  _height = std::max(_height, position.y + 1);
  return this;
}
MapBuilder* MapBuilder::setPlayer(Coordinate position) {
  _player = position;

  _width = std::max(_width, position.x + 1);
  _height = std::max(_height, position.y + 1);
  return this;
}
MapBuilder* MapBuilder::addBlocks(uint32_t fromX, uint32_t fromY, uint32_t toX,
    uint32_t toY) {

  uint32_t xMin = std::min(fromX, toX);
  uint32_t xMax = std::max(fromX, toX);
  uint32_t yMin = std::min(fromY, toY);
  uint32_t yMax = std::max(fromY, toY);

  for (uint32_t i = yMin; i <= yMax; ++i) {
    for (uint32_t j = xMin; j <= xMax; ++j) {
      _blocks.push_back(Coordinate(j, i));
    }
  }

  _width = std::max(_width, xMax + 1);
  _height = std::max(_height, yMax + 1);

  return this;
}

MapBuilder* MapBuilder::addBlock(uint32_t x, uint32_t y) {
  return this->addBlock(Coordinate(x, y));
}
MapBuilder* MapBuilder::addTarget(uint32_t x, uint32_t y) {
  return this->addTarget(Coordinate(x, y));
}
MapBuilder* MapBuilder::addBox(uint32_t x, uint32_t y) {
  return this->addBox(Coordinate(x, y));
}
MapBuilder* MapBuilder::setPlayer(uint32_t x, uint32_t y) {
  return this->setPlayer(Coordinate(x, y));
}
MapBuilder* MapBuilder::addBlocks(Coordinate from, Coordinate to) {
  return this->addBlocks(from.x, from.y, to.x, to.y);
}

MapBuilder* MapBuilder::reset() {
  _blocks.clear();
  _targets.clear();
  _boxes.clear();
  _player.set(0, 0);
  _width = 1;
  _height = 1;

  return this;
}

std::pair<Error, const Map*> MapBuilder::build() const {
  if (_targets.size() > _boxes.size())
    return std::pair<Error, const Map*>(Error::MoreTargetsThanBoxes, nullptr);

  StaticMap* newMap = new StaticMap(_width, _height);
  State* state = new State();

  for (Coordinate p : _blocks)
    newMap->set(p, StaticType::Block);

  for (Coordinate p : _targets) {
    if (newMap->get(p) != StaticType::Nothing)
      return std::pair<Error, const Map*>(Error::SpotTaken, nullptr);

    newMap->set(p, StaticType::Target);
  }

  std::unordered_map<Coordinate, BoxState>* boxMap = state->getBoxes();

  for (Coordinate p : _boxes) {
    if (newMap->get(p) == StaticType::Block)
      return std::pair<Error, const Map*>(Error::SpotTaken, nullptr);

    if (boxMap->count(p) > 0) {
      return std::pair<Error, const Map*>(Error::SpotTaken, nullptr);
    }

    boxMap->insert(std::pair<Coordinate, BoxState>(p, BoxState()));
  }

  state->setPlayerPosition(_player);

  return std::pair<Error, const Map*>(Error::Success,
      new Map(state, newMap, _width, _height));
}

}  // namespace Sokoban
