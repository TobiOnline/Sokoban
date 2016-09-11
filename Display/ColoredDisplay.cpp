// Copyright Tobias Faller 2016

#include "ColoredDisplay.h"

#include <curses.h>

#include <algorithm>

#include "../Map/StaticMap.h"
#include "../Map/State.h"

namespace Sokoban {

ColoredDisplay::ColoredDisplay(WINDOW* window)
    : CursesDisplay(window), _scale(3, 2) {
  if (start_color() == ERR) {
    _valid = false;
    return;
  }

  init_pair(1, COLOR_WHITE, COLOR_BLACK);  // Nothing (' ')
  init_pair(2, COLOR_WHITE, COLOR_BLACK);  // Block
  init_pair(3, COLOR_GREEN, COLOR_BLACK);  // Player
  init_pair(4, COLOR_GREEN, COLOR_BLUE);  // Player on target
  init_pair(5, COLOR_YELLOW, COLOR_BLACK);  // Box
  init_pair(6, COLOR_YELLOW, COLOR_BLUE);  // Box on target
  init_pair(7, COLOR_BLACK, COLOR_BLUE);  // Target
  _valid = true;
}
ColoredDisplay::~ColoredDisplay() { }

void ColoredDisplay::update() {
  if (!_enabled || !_map || !_staticMap || !_state)
    return;

  uint32_t width = std::min(_map->getWidth(), _rectangle.width);
  uint32_t height = std::min(_map->getHeight(), _rectangle.height);

  for (uint32_t y = 0; y < height; y++) {
    for (uint32_t subY = 0; subY < _scale.height; subY++) {
      bool moved = false;

      for (uint32_t x = 0; x < width; x++) {
        char c = getCharForState(_staticMap->get(x, y), _state,
          Coordinate(x, y));

        wattron(_window, COLOR_PAIR(getColorForChar(c)));

        if (c != ' ' || moved) {
          if (!moved && (moved = true)) {
            wmove(_window, _rectangle.y + (y * _scale.height) + subY,
                _rectangle.x + (x * _scale.width));
          }

          c = modifyChar(c);
          for (uint32_t subX = 0; subX < _scale.width; subX++) {
            waddch(_window, c);
          }
        }
      }
    }
  }
}

Size ColoredDisplay::getScale() const {
  return _scale;
}

void ColoredDisplay::setScale(const Size& scale) {
  _scale = scale;
}

char ColoredDisplay::modifyChar(char c) {
  switch (c) {
    case '#':  // Block
      return '#';
    case '+':  // Player
      return '@';
    case '@':  // Player on target
      return '@';
    case '$':  // Box
      return 'O';
    case '*':  // Box on target
      return 'O';
    case '.':  // Target
      return ' ';
    default:  // Nothing (' ')
      return ' ';
    }
}

uint16_t ColoredDisplay::getColorForChar(char c) {
  switch (c) {
  case '#':  // Block
    return 2;
  case '@':  // Player
    return 3;
  case '+':  // Player on target
    return 4;
  case '$':  // Box
    return 5;
  case '*':  // Box on target
    return 6;
  case '.':  // Target
    return 7;
  default:  // Nothing (' ')
    return 1;
  }
}

}  // namespace Sokoban
