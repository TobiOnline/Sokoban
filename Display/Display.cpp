// Copyright Tobias Faller 2016

#include "Display.h"

namespace Sokoban {

Display::Display() : _valid(false) { }
Display::~Display() { }

bool Display::isValid() const {
  return _valid;
}

}  // namespace Sokoban
