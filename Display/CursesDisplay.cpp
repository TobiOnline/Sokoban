// Copyright Tobias Faller 2016

#include "CursesDisplay.h"

#include <curses.h>

#include <algorithm>

#include "../Map/StaticMap.h"
#include "../Map/State.h"

namespace Sokoban {

CursesDisplay::CursesDisplay(WINDOW* window)
    : _window(window), _map(nullptr), _staticMap(nullptr), _state(nullptr),
      _enabled(false), _rectangle(0, 0, 30, 20) {
  _valid = true;
}
CursesDisplay::~CursesDisplay() { }

void CursesDisplay::setEnabled(bool enabled) {
  _enabled = enabled;

  if (enabled)
    update();
}

bool CursesDisplay::isEnabled() {
  return _enabled;
}

void CursesDisplay::setPosition(const Coordinate& position) {
  _rectangle.setPosition(position);
}
Coordinate CursesDisplay::getPosition() const {
  return _rectangle.getPosition();
}
void CursesDisplay::setSize(const Size& size) {
  _rectangle.setSize(size);
}
Size CursesDisplay::getSize() const {
  return _rectangle.getSize();
}
void CursesDisplay::setRectangle(const Rectangle& rectangle) {
  _rectangle = rectangle;
}
Rectangle CursesDisplay::getRectangle() const {
  return _rectangle;
}

void CursesDisplay::setMap(const Map* map) {
  _map = map;

  if (map) {
    _staticMap = map->getMap();
    _state = map->getInitialState();
  } else {
    _staticMap = nullptr;
    _state = nullptr;
  }

  update();
}

void CursesDisplay::updateState(const State* state) {
  _state = state;

  update();
}

const Map* CursesDisplay::getMap() const {
  return _map;
}
const State* CursesDisplay::getState() const {
  return _state;
}

void CursesDisplay::update() {
  if (!_enabled || !_map || !_staticMap || !_state)
    return;

  uint32_t width = std::min(_map->getWidth(), _rectangle.width);
  uint32_t height = std::min(_map->getHeight(), _rectangle.height);

  for (uint32_t y = 0; y < height; y++) {
    bool moved = false;
    for (uint32_t x = 0; x < width; x++) {
      char c = getCharForState(_staticMap->get(x, y), _state,
          Coordinate(x, y));

      if (c != ' ' || moved) {
        if (!moved) {
          wmove(_window, _rectangle.y + y, _rectangle.x + x);
        }
        waddch(_window, c);
      }
    }
  }
}

char CursesDisplay::getCharForState(StaticType type, const State* state,
    const Coordinate& coordinate) {
  const std::unordered_map<Coordinate, BoxState>* boxMap = state->getBoxes();
  std::unordered_map<Coordinate, BoxState>::const_iterator boxEnd
    = boxMap->cend();

  if (type == StaticType::Block) {
    return '#';
  } else {
    if (state->getPlayerPosition() == coordinate) {
      return (type == StaticType::Nothing) ? '@' : '+';
    } else if (boxMap->find(coordinate) != boxEnd) {
      return (type == StaticType::Nothing) ? '$' : '*';
    } else if (type == StaticType::Target) {
      return '.';
    }
  }
  return ' ';
}

}  // namespace Sokoban
